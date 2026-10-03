#!/bin/sh
# Run the VS2008 SP1 x86 compiler (cl 15.00.30729.01) under wine.
# Toolchain: work/toolchain/vc9sp1 (from Microsoft's VCForPython27.msi, SHA-1 7800d037...befe).
root=$(cd "$(dirname "$0")/../.." && pwd)
tc="$root/work/toolchain/vc9sp1"
winpath() { printf 'Z:%s' "$1" | tr '/' '\\'; }
export WINEPREFIX="$root/work/toolchain/wineprefix" WINEDEBUG=-all
export INCLUDE="$(winpath "$tc/VC/include");$(winpath "$tc/WinSDK/Include")"
export LIB="$(winpath "$tc/VC/lib");$(winpath "$tc/WinSDK/Lib")"
export WINEPATH="$(winpath "$tc/VC/bin")"
exec wine "$tc/VC/bin/cl.exe" "$@"
