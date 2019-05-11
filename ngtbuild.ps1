$log = "log.txt"
$snippets = "build/snippets.json"
$index = "docs/index.md"

# ----------------------------------------------
# build .vocode/cpp.code-snippets
# ----------------------------------------------

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
  Write-Output $outstr
}
function escape_and_quote {
  param (
    $instr
    , $tabs
    , $final
  )
  $instr = $instr.replace("  ", "`t")
  $instr = $instr.replace("\", "\\")
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
  while ($null -ne ($line = $stream.ReadLine())) {
    escape_and_quote $line 3 (($stream.Peek() -eq -1))
  }
  $stream.Close()
  ngtwrite "]," 2
  ngtwrite "`"description`": `"none`"" 2
  ngtwrite "}," 1
}


# ----------------------------------------------
# build index.md
# ----------------------------------------------

function write_markdown {
  param (
    $infile
  )
  $inflie | Add-Content $log
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
  # $outstr = "`| ["
  $outstr = "`- ["
  $outstr += [System.IO.Path]::GetFileNameWithoutExtension($inpath).replace("_", " ")
  $outstr += "]("
  $outstr += (Resolve-Path $inpath -Relative).remove(0, 7)
  $outstr += ")"
  # $outstr += ") |"
  Write-Output $outstr 
}

function make_links_and_markdowns {
  param (
    $indir
  )
  "## " + $indir.name | Add-Content $index
  "" | Add-Content $index

  $outdir = $indir.name
  Get-ChildItem $indir.fullname | ForEach-Object {
    $name_without_ext = [System.IO.Path]::GetFileNameWithoutExtension($_.Name)

    $outpath = "${outdir}/${name_without_ext}.md"
    $docs_outpath = "docs/" + $outpath

    New-Item -Force $docs_outpath
    "# ${name_without_ext}\n[prev](..\index.md)" | Add-Content -Encoding UTF8 $docs_outpath
    "foo" | Add-Content $log
    "docs/${out_path}" | Add-Content $log
    
    # write_markdown $_.fullname | Add-Content -Encoding UTF8 "docs/${out_path}"
    make_link $docs_outpath | Add-Content -Encoding UTF8 $index
  }
  "" | Add-Content $index
}


# ----------------------------------------------
# main
# ----------------------------------------------
Clear-Content $log
Clear-Content $snippets
Clear-Content $index

# "# Library" | Add-Content $index
# Get-ChildItem src | ForEach-Object {
#   if ($_.Name -ne "debug") {
#     make_links_and_markdowns $_
#   }
# }

ngtwrite "{" | Add-Content -Encoding UTF8 $snippets

Get-ChildItem -Recurse -Path src/*.cpp | ForEach-Object {
  parse $_ | Add-Content -Encoding UTF8 $snippets
}

ngtwrite "`"this_is_to_be_deleted`": `"foo`"" 1 | Add-Content $snippets
ngtwrite "}" 0 | Add-Content $snippets