#!/bin/sh
# Boot a hybrid exe under CrossOver and report what happened.
# usage: boottest.sh <exe> [seconds=90] [tag=boot]
# Prints one of:
#   ALIVE at Ns (cpu P%)              still running, no exception in the trace; P is the game's CPU
#                                      share at the end (the menu renders continuously; ~0% means it
#                                      is stuck). Screenshot: work/hybrid/<tag>.png
#   ALIVE at Ns (closed by hand)      exited without exception or dialog after MIN_ALIVE seconds
#   INCONCLUSIVE at Ns (closed early) exited cleanly before MIN_ALIVE seconds; callers should redo it
#   DIALOG at Ns: <MessageBoxA text>  the game's own fatal error
#   CRASH at Ns: <exception>          an access violation in the trace; the process may still be
#                                      alive behind CrossOver's crash dialog (which this script kills)
#   GONE at Ns                        exited with no exception (should not happen; investigate)
# The game needs the Steam client running in the bottle. The exe is copied next to the Steam
# install's SporeBin as SporeApp_hybrid.exe.
exe=$1; secs=${2:-90}; tag=${3:-boot}
MIN_ALIVE=45
root=$(cd "$(dirname "$0")/../.." && pwd)
W=~/Applications/CrossOver.app/Contents/SharedSupport/CrossOver/bin/wine
S="$HOME/Library/Application Support/CrossOver/Bottles/Steam/drive_c/Program Files (x86)/Steam/steamapps/common/Spore"
EXE='C:\Program Files (x86)\Steam\steamapps\common\Spore\SporeBin\SporeApp_hybrid.exe'
L="$root/work/hybrid/$tag.log"
cp "$exe" "$S/SporeBin/SporeApp_hybrid.exe" || exit 2
[ -f "$S/SporeBin/steam_appid.txt" ] || printf 17390 > "$S/SporeBin/steam_appid.txt"
cleanup() { pkill -f "SporeApp_hybrid.exe" 2>/dev/null; pkill -f "winedbg --auto" 2>/dev/null; pkill -f "conhost.exe" 2>/dev/null; }
cleanup; sleep 1
"$W" --bottle Steam reg add 'HKCU\Software\Wine\Debug' /v RelayInclude /t REG_SZ /d 'user32.MessageBoxA' /f >/dev/null 2>&1
rm -f "$L"
( cd "$S/SporeBin" && CX_DEBUGMSG="-all,+relay,+seh" "$W" --bottle Steam --cx-app "$EXE" </dev/null >"$L" 2>&1; echo "exit=$?" >>"$L" ) &
first_av() { grep -o "dispatch_exception code=c0[0-9a-f]* ([A-Z_]*) flags=[0-9] addr=[0-9A-Fa-f]*" "$L" 2>/dev/null | grep -v 406d1388 | head -1; }
t=0; verdict=""
while [ $t -lt "$secs" ]; do
  sleep 5; t=$((t+5))
  if grep -q "Call user32.MessageBoxA" "$L" 2>/dev/null; then
    verdict="DIALOG at ${t}s: $(grep -o 'Call user32.MessageBoxA([^)]*' "$L" | head -1 | cut -c1-160)"; break; fi
  ex=$(first_av)
  if [ -n "$ex" ]; then sleep 2; verdict="CRASH at ${t}s: $(first_av)"; break; fi
  if ! pgrep -qf "SporeApp_hybrid.exe"; then
    sleep 2; ex=$(first_av)
    if [ -n "$ex" ]; then verdict="CRASH at ${t}s: $ex"
    elif [ $t -ge $MIN_ALIVE ]; then verdict="ALIVE at ${t}s (closed by hand)"
    else verdict="INCONCLUSIVE at ${t}s (closed early)"; fi
    break; fi
done
if [ -z "$verdict" ]; then
  # the game is the largest process matching the name (the wrapper and winewrapper also match)
  pid=$(ps -axo pid,rss,command | grep "SporeApp_hybrid.exe" | grep -v grep | sort -k2 -n | tail -1 | awk '{print $1}')
  cpu=$(ps -o %cpu= -p "$pid" 2>/dev/null | tr -d ' ')
  hint=""; [ -n "$cpu" ] && [ "${cpu%.*}" -lt 3 ] && hint=": hung?"
  # window content: the game renders a black window when a hooked function breaks rendering
  shot=$("$root/.venv/bin/python" "$root/tools/hybrid/winshot.py" "$root/work/hybrid/$tag.win.png" 2>/dev/null); rc=$?
  [ $rc -eq 2 ] && hint="$hint: black screen"
  verdict="ALIVE at ${t}s (cpu ${cpu:-?}%${hint}; window ${shot:-?})"
fi
screencapture -x "$root/work/hybrid/$tag.png" 2>/dev/null
"$W" --bottle Steam reg delete 'HKCU\Software\Wine\Debug' /v RelayInclude /f >/dev/null 2>&1
cleanup
echo "$verdict"
