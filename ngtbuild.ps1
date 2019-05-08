# ----------------------------------------------
# build .vocode/cpp.code-snippets
# ----------------------------------------------
$snippets = "build/snippets.json"
Clear-Content $snippets

function ngtwrite {
  param (
    $instr
  , $tabs
  )
  $outstr = ""
  for ($i = 0; $i -lt $tabs; $i++) {
    $outstr += "`t"
  }
  $outstr += $instr
  Write-Output -Encoding UTF8 $outstr
}
function escape_and_quote {
  param (
    $instr
    , $tabs
    , $final
  )
  $instr = $instr.replace("  ", "`t")
  $instr = $instr.replace("`t", "`\t")
  $instr = $instr.replace("`n", "`\n")
  $instr = $instr.replace("`"", "`\`"")
  $outstr = "`""
  $outstr += $instr
  $outstr += "`""
  if (($final -eq $false)) { $outstr += "," }
  ngtwrite $outstr $tabs
}
function parse {
  param (
    $infile
  )
  $snippet_name = [System.IO.Path]::GetFileNameWithoutExtension($infile.Name).replace("_", " ")
  ngtwrite "`"$snippet_name`": {" 1
  ngtwrite "`"prefix`": `"$snippet_name`"," 2
  ngtwrite "`"body`": [" 2
  $stream = New-Object System.IO.StreamReader($infile.FullName)
  $flg = $false
  $line = ""
  while ($null -ne ($nxtline = $stream.ReadLine())) {
    if (($flg -eq $true)) {
      escape_and_quote $line 3 (($nxtline -eq "// end"))
    }
    if (($line -eq "// begin")) { $flg = $true }
    if (($nxtline -eq "// end")) { $flg = $false }
    $line = $nxtline
  }
  $stream.Close()
  ngtwrite "]," 2
  ngtwrite "`"description`": `"none`"" 2
  ngtwrite "}," 1
}


# ----------------------------------------------
# build index.md
# ----------------------------------------------
$index = "docs/index.md"
Clear-Content $index

function write_markdown {
  param (
    $infile
  )
  "``````cpp"
  $stream = New-Object System.IO.StreamReader($infile, [System.Text.Encoding]::UTF8)
  $flg = $false
  $line = ""
  while ($null -ne ($nxtline = $stream.ReadLine())) {
    if (($flg -eq $true)) {
      $line
    }
    if (($line -eq "// begin")) { $flg = $true }
    if (($nxtline -eq "// end")) { $flg = $false }
    $line = $nxtline
  }
  "``````"
}

function make_link {
  param (
    $inpath
  )
  $outstr = "`| ["
  $outstr += [System.IO.Path]::GetFileNameWithoutExtension($inpath).replace("_", " ")
  $outstr += "]("
  $outstr += (Resolve-Path $inpath -Relative).remove(0, 7)
  $outstr += ") |"
  Write-Output $outstr 
}

function make_links_and_markdowns {
  param (
    $indir
  )
  "## " + $indir.name | Add-Content $index
  "" | Add-Content $index

  "|snippet name|" | Add-Content $index
  "---" | Add-Content $index
  $outdir = $indir.name
  Get-ChildItem $indir.fullname | ForEach-Object {
    $name_without_ext = [System.IO.Path]::GetFileNameWithoutExtension($_.Name)

    $outpath = $outdir + "/"
    $outpath += $name_without_ext
    $outpath += ".md"
    $docs_outpath = "docs/" + $outpath

    New-Item -Force $docs_outpath
    "# " + $name_without_ext | Add-Content -Encoding UTF8 $docs_outpath
    "[prev](..\index.md)" |  Add-Content -Encoding UTF8 $docs_outpath
    write_markdown $_.fullname | Add-Content -Encoding UTF8 $docs_outpath
    make_link $docs_outpath | Add-Content -Encoding UTF8 $index
  }
  "" | Add-Content $index
}


"# Library" | Add-Content $index
Get-ChildItem src | ForEach-Object {
  make_links_and_markdowns $_
}

ngtwrite "{" | Add-Content $snippets

Get-ChildItem -Recurse -Path src/*.cpp | ForEach-Object {
  parse $_ | Add-Content $snippets
}

Get-ChildItem -Path json/fragments.json | ForEach-Object {
  Get-Content -Encoding UTF8 $_.FullName | Add-Content -Encoding UTF8 $snippets
}

ngtwrite "}" 0 | Add-Content $snippets