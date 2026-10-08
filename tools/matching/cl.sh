#!/bin/sh
# Run the VS2008 SP1 x86 compiler (cl 15.00.30729.01) under wine.
# Toolchain: work/toolchain/vc9sp1 (from Microsoft's VCForPython27.msi, SHA-1 7800d037...befe).
root=$(cd "$(dirname "$0")/../.." && pwd)

# Pseudo-flag /vc71: compile with VC .NET 2003 instead (cl71.sh), for code EA linked from libraries
# built with it (Havok). It lives in the flag list so manifests, chk.py and difftest select it per line.
for a in "$@"; do
  if [ "$a" = "/vc71" ]; then
    for b in "$@"; do shift; [ "$b" = "/vc71" ] || set -- "$@" "$b"; done
    exec "$root/tools/matching/cl71.sh" "$@"
  fi
done

tc="$root/work/toolchain/vc9sp1"
winpath() { printf 'Z:%s' "$1" | tr '/' '\\'; }
export WINEPREFIX="${CL_WINEPREFIX:-$root/work/toolchain/wineprefix}" WINEDEBUG=-all
export INCLUDE="$(winpath "$tc/VC/include");$(winpath "$tc/WinSDK/Include")"
export LIB="$(winpath "$tc/VC/lib");$(winpath "$tc/WinSDK/Lib")"
export WINEPATH="$(winpath "$tc/VC/bin")"

# Keep-alive. Wine starts its Windows services (services.exe, plugplay, svchost, winedevice) with
# the first program and stops them ~3 s after the last one exits, so a compile after an idle gap
# paid ~1.3 s to restart them (2.3 s vs 1.0 s). An idle `ping`, started detached, holds the session
# for 30 minutes; the first compile after it exits starts another. It is only started when this
# prefix has no running wineserver (no socket), so it never prolongs a session another process started.
keep="$WINEPREFIX/.keepalive.pid"
sock="/tmp/.wine-$(id -u)/server-$(stat -f '%d-%i' "$WINEPREFIX" 2>/dev/null | awk -F- '{printf "%x-%x", $1, $2}')/socket"
if ! { [ -f "$keep" ] && kill -0 "$(cat "$keep" 2>/dev/null)" 2>/dev/null; } && [ ! -S "$sock" ]; then
  find "$WINEPREFIX/.keepalive.lock" -maxdepth 0 -mmin +1 -exec rmdir {} \; 2>/dev/null  # stale lock
  if mkdir "$WINEPREFIX/.keepalive.lock" 2>/dev/null; then
    nohup wine ping -n 1800 127.0.0.1 </dev/null >/dev/null 2>&1 &
    echo $! > "$keep"
    rmdir "$WINEPREFIX/.keepalive.lock"
  fi
fi

# Output goes through a temp file, never our caller's pipes: the services wine starts with the
# session inherit cl's stdio, and holding a caller's pipe open made `subprocess.run(capture_output)`
# wait until the whole session ended (+3.3 s on a cold start; indefinitely while other agents compile).
tmp=$(mktemp "${TMPDIR:-/tmp}/clsh.XXXXXX")
wine "$tc/VC/bin/cl.exe" "$@" </dev/null >"$tmp" 2>&1
rc=$?
cat "$tmp"; rm -f "$tmp"
exit $rc
