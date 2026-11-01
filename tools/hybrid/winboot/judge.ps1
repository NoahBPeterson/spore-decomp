# judge.ps1 NAME: is the hybrid NAME.exe alive, crashed, or deadlocked in the texture-load stall?
param([string]$Name)
$p = Get-Process -Name $Name -ErrorAction SilentlyContinue
if (-not $p) {
  $e = Get-WinEvent -FilterHashtable @{LogName='Application'; StartTime=(Get-Date).AddMinutes(-5)} -ErrorAction SilentlyContinue |
       ? { $_.Message -like "*$Name.exe*" } | select -First 1
  if ($e) { "GONE " + (($e.Message -split "`n") | ? { $_ -match '0x' } | % { $_.Trim() }) -join ' | ' } else { "GONE (no event)" }
  exit
}
$out = & D:\spore\.venv\Scripts\python D:\spore_run\threads.py $p.Id 2
$stall = ($out | ? { $_ -match '007ab03d' }).Count
"ALIVE pid $($p.Id) cpu $([math]::Round($p.CPU,1)) threads $($p.Threads.Count) stall-frames $stall"
$out | select -First 1
