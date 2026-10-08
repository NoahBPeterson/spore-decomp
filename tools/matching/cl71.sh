#!/bin/sh
# Run the Visual C++ Toolkit 2003 compiler (cl 13.10.3052) under wine, for code built with
# VC .NET 2003 (Havok: the dev PDB's S_COMPILE records say 13.10.3077).
# Toolchain: work/toolchain/vc71tk (bin/include/lib from VCToolkitSetup.exe's MSI, extracted
# without running the installer). Shares the VS2008 wine prefix; see cl.sh for the keep-alive.
root=$(cd "$(dirname "$0")/../.." && pwd)
tc="$root/work/toolchain/vc71tk"
winpath() { printf 'Z:%s' "$1" | tr '/' '\\'; }
export WINEPREFIX="${CL_WINEPREFIX:-$root/work/toolchain/wineprefix}" WINEDEBUG=-all
export INCLUDE="$(winpath "$root/match/include/vc71");$(winpath "$tc/include");$(winpath "$root/work/toolchain/vc9sp1/WinSDK/Include")"
export LIB="$(winpath "$tc/lib")"
export WINEPATH="$(winpath "$tc/bin")"
tmp=$(mktemp "${TMPDIR:-/tmp}/cl71.XXXXXX")
wine "$tc/bin/cl.exe" "$@" </dev/null >"$tmp" 2>&1
rc=$?
cat "$tmp"; rm -f "$tmp"
exit $rc
