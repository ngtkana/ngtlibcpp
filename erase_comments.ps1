function trans {
  param (
    $infile
  )
  $stream = New-Object System.IO.StreamReader($infile)
  $flg = $false
  while ($null -ne ($line = $stream.ReadLine())) {
    if ($line -eq "// end") {$flg = $false}
    if ($flg -eq $true) {echo $line}
    if ($line -eq "// begin") {$flg = $true}
  }
  $stream.Close()
}

Get-ChildItem -Path src/*.cpp -Recurse | ForEach-Object {
  $path = $_
  $relative_path = Resolve-Path -Relative $path
  $relative_path = $relative_path.Remove(0, 6)
  $relative_path = "src_/$relative_path"
  "$_ to $relative_path"
  New-Item $relative_path -f
  Clear-Content $relative_path
  trans $_ | Add-Content -Encoding UTF8 $relative_path
}
