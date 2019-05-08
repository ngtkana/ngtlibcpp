# $OutputEncoding = "utf-8"

$infile = "src\code_fragments\sort_reverse.cpp"
$stream = New-Object System.IO.StreamReader($infile, [System.Text.Encoding]::UTF8)
while ($null -ne ($line = $stream.ReadLine())) {
  $line
}