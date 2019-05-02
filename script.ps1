Clear-Content ./json/test.json
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
  $outstr = "`""
  $outstr += $instr
  $outstr += "`""
  $outstr = $outstr.replace("  ", "`t")
  $outstr = $outstr.replace("`t", "`\t")
  $outstr = $outstr.replace("`n", "`\n")
  if (($final -eq $false)) {$outstr += ","}
  ngtwrite $outstr $tabs
}
function parse {
  param (
    $inpath
  )
  ngtwrite "{"
  Get-ChildItem -Path ${inpath} | ForEach-Object{
    $snippet_name =  [System.IO.Path]::GetFileNameWithoutExtension($_.Name).replace("_", " ")
    ngtwrite "`"$snippet_name`": {" 1
    ngtwrite "`"prefix`": `"$snippet_name`"," 2
    ngtwrite "`"body`": [" 2
    $stream = New-Object System.IO.StreamReader($_.FullName)
    $flg = $false
    $line = ""
    while (($nxtline = $stream.ReadLine()) -ne $null) {
      if (($flg -eq $true)) {
        escape_and_quote $line 3 (($nxtline -eq "// end"))
      }
      if (($line -eq "// begin")) {$flg = $true}
      if (($nxtline -eq "// end")) {$flg = $false}
        $line = $nxtline
      }
      $stream.Close()
    ngtwrite "]," 2
    ngtwrite "`"description`": `"none`"" 2
    ngtwrite "}," 1
  }
  ngtwrite "`"none`": {" 1
  ngtwrite "}" 1
  ngtwrite "}" 0
}
parse "library/*.cpp" | Set-Content ./json/test.json