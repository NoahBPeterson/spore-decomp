#!/bin/zsh
# win.sh: drive hybrid boots on a Windows machine over OpenSSH (docs/hybrid.md, "Native Windows").
#   win.sh push FILE...           copy files to D:\spore_run (the remote helpers live there too: win.sh setup)
#   win.sh setup                  copy boot.bat, judge.ps1, threads.py, wgc.py to D:\spore_run
#   win.sh boot NAME [secs=50]    copy D:\spore_run\NAME.exe into SporeBin, start it on the console session, wait, judge
#   win.sh shot NAME TAG          capture NAME's SPORE(TM) window (Windows.Graphics.Capture) -> work/hybrid/win/TAG.png
#   win.sh bisect BASE CANDS PAT  which hook of CANDS (one VA per line) in work/hybrid/BASE.exe makes `boot` print PAT
# SPORE_WIN_HOST (default noah@100.84.111.92) and SPORE_WIN_PWFILE (the password, chmod 600; never in the repo).
# The machine needs Steam signed in, Spore installed, the game launched once through Steam (registry), windowed mode
# in %APPDATA%\SPORE\Preferences\Preferences.prop, and D:\spore\.venv with windows-capture (wgc.py).
ROOT=$(cd "$(dirname "$0")/../../.." && pwd)
H=${SPORE_WIN_HOST:-noah@100.84.111.92}
PWF=${SPORE_WIN_PWFILE:?set SPORE_WIN_PWFILE to a file holding the Windows password}
HERE=$(cd "$(dirname "$0")" && pwd)
B='C:\Program Files (x86)\Steam\steamapps\common\Spore\SporeBin'
# the host refuses some logins in quick succession: retry
w() { for i in 1 2 3 4 5; do out=$(sshpass -f $PWF ssh -o StrictHostKeyChecking=no $H "$1" 2>/dev/null) && { echo "$out" | LC_ALL=C tr -d '\r' | iconv -f cp850 -t utf-8 2>/dev/null; return 0; }; sleep 3; done; echo "ssh failed"; return 1; }
put() { for i in 1 2 3 4 5; do sshpass -f $PWF scp -q -o StrictHostKeyChecking=no "$@" "$H:D:/spore_run/" && return 0; sleep 3; done; return 1; }
get() { for i in 1 2 3 4 5; do sshpass -f $PWF scp -q -o StrictHostKeyChecking=no "$H:$1" "$2" 2>/dev/null && return 0; sleep 3; done; return 1; }
case $1 in
  push)  shift; put "$@" ;;
  setup) w "mkdir D:\\spore_run 2>nul & echo ok" >/dev/null; put $HERE/boot.bat $HERE/judge.ps1 $HERE/threads.py $HERE/wgc.py ;;
  boot)  N=$2; T=${3:-50}
         w "powershell -NoProfile -Command \"Get-Process | ? { \$_.Path -like '*SporeBin*' } | Stop-Process -Force\" & copy /y D:\\spore_run\\$N.exe \"$B\\$N.exe\" >nul & schtasks /create /f /tn sporeboot /sc once /st 00:00 /it /rl highest /tr \"D:\\spore_run\\boot.bat $N.exe\" >nul 2>&1 & schtasks /run /tn sporeboot >nul && echo started"
         sleep $T
         w "powershell -NoProfile -ExecutionPolicy Bypass -File D:\\spore_run\\judge.ps1 $N" ;;
  shot)  mkdir -p $ROOT/work/hybrid/win
         w "del D:\\spore_run\\$3.png 2>nul & schtasks /create /f /tn sporewshot /sc once /st 00:00 /it /tr \"cmd /c D:\\spore\\.venv\\Scripts\\python D:\\spore_run\\wgc.py D:\\spore_run\\$3.png > D:\\spore_run\\wshot.txt\" >nul 2>&1 & schtasks /run /tn sporewshot >nul & ping -n 12 127.0.0.1 >nul & type D:\\spore_run\\wshot.txt"
         get "D:/spore_run/$3.png" $ROOT/work/hybrid/win/$3.png && $ROOT/.venv/bin/python -W ignore -c "
from PIL import Image
im=Image.open('$ROOT/work/hybrid/win/$3.png').convert('L'); w,h=im.size
px=list(im.getdata()); left=[im.getpixel((x,y)) for x in range(0,w//8) for y in range(h//3,h,4)]
print('work/hybrid/win/$3.png %dx%d mean %.1f left-strip %.1f' % (w,h,sum(px)/len(px), sum(left)/len(left)))" ;;
  bisect) cd $ROOT; base=$2; cands=(${(f)"$(cat $3)"}); pat=$4; all=($cands); step=0
         while (( ${#cands} > 1 )); do
           half=(${cands[1,$(( ${#cands} / 2 ))]}); step=$((step+1))
           off=(${all:|half}); print -l $off > work/hybrid/win_off.txt
           .venv/bin/python $HERE/unhook.py work/hybrid/$base.exe work/hybrid/bis_$step.exe @work/hybrid/win_off.txt >/dev/null
           put work/hybrid/bis_$step.exe
           v=$($0 boot bis_$step 50 | tail -2 | tr '\n' ' ')
           if [[ $v == *${~pat}* ]]; then r=bad; cands=($half); else r=good; cands=(${cands:|half}); fi
           echo "step $step: ${#half} hooked (${half[1]}..${half[-1]}) -> $r  [${v[1,160]}]"
         done
         echo "CULPRIT ${cands[*]}" ;;
  *) sed -n 2,11p $0 ;;
esac
