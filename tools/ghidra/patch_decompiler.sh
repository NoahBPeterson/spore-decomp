#!/bin/sh
# Rebuild Ghidra's native decompiler with our patches and install it (original kept as decompile.orig).
# Patches: float-nonassociative.patch (keep float +,* grouping) and nan-exact.patch (exact NaN semantics of float
# compares, see docs/floating_point.md). float-nonassociative.patch:
# with the integer tokens marked associative, so `a + (b + c)` came out as `a + b + c` (= (a+b)+c),
# silently changing evaluation order of x87/SSE float sums. Re-run after every Ghidra upgrade.
set -e
here=$(cd "$(dirname "$0")/../.." && pwd)
G=$(ls -d /opt/homebrew/Cellar/ghidra/*/libexec | tail -1)/Ghidra/Features/Decompiler
B="$here/work/ghidra-build"
rm -rf "$B" && mkdir -p "$B" && cp -R "$G/src/decompile/cpp" "$B/cpp"
cd "$B/cpp"
for p in "$here"/tools/ghidra/patches/*.patch; do patch -p0 < "$p"; done
arch=$(uname -m); [ "$arch" = arm64 ] && A="-arch arm64" || A="-arch x86_64"
make -j8 ghidra_opt ARCH_TYPE="$A" > build.log 2>&1
OS=$(ls "$G/os")
[ -f "$G/os/$OS/decompile.orig" ] || cp "$G/os/$OS/decompile" "$G/os/$OS/decompile.orig"
cp ghidra_opt "$G/os/$OS/decompile"
echo "installed patched decompiler into $G/os/$OS (original: decompile.orig)"
