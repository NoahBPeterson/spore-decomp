#!/bin/sh
# Build work/toolchain/{vc9sp1,vc71tk} and the wine prefix from Microsoft's public installers, then check every file
# against tools/ci/toolchain.sha256 (the toolchains the maintainers match with).  Linux (CI) or macOS; needs wine
# (32-bit), msiextract (msitools), curl, sha1sum/shasum, sha256sum/shasum.
#   VC9 SP1, cl 15.00.30729.01: VCForPython27.msi from Microsoft's original URL via the Wayback Machine, extracted
#     with msiextract (no installer runs)
#   VC 2003 Toolkit 1.01, cl 13.10.3077: VCToolkitSetup.exe from archive.org, silent install under wine
# Downloads are cached in $TOOLCHAIN_CACHE (default work/toolchain/downloads).
set -eu
root=$(cd "$(dirname "$0")/../.." && pwd)
tc="$root/work/toolchain"
dl="${TOOLCHAIN_CACHE:-$tc/downloads}"
mkdir -p "$tc" "$dl"

VC9_URL="https://web.archive.org/web/20210106040224id_/https://download.microsoft.com/download/7/9/6/796EF2E4-801B-4FC4-AB28-B59FBF6D907B/VCForPython27.msi"
VC9_SHA1=7800d037ba962f288f9b952001106d35ef57befe
VC71_URL="https://archive.org/download/20260623_202606/VCToolkitSetup.exe"
VC71_SHA1=50dc6cca1503f08a41d56816f3f1abcaf347b0bd

sha1() { if command -v sha1sum >/dev/null; then sha1sum "$1"; else shasum -a 1 "$1"; fi | cut -d' ' -f1; }
fetch() {   # url sha1 file
  if [ ! -f "$3" ] || [ "$(sha1 "$3")" != "$2" ]; then
    curl -fsSL --retry 5 --retry-delay 10 -o "$3.part" "$1"
    mv "$3.part" "$3"
  fi
  got=$(sha1 "$3")
  [ "$got" = "$2" ] || { echo "$3: SHA-1 $got, expected $2" >&2; exit 1; }
}

if [ ! -x "$tc/vc9sp1/VC/bin/cl.exe" ] && [ ! -f "$tc/vc9sp1/VC/bin/cl.exe" ]; then
  fetch "$VC9_URL" "$VC9_SHA1" "$dl/VCForPython27.msi"
  x=$(mktemp -d)
  msiextract -C "$x" "$dl/VCForPython27.msi" >/dev/null
  rm -rf "$tc/vc9sp1"
  mv "$x/Microsoft/Visual C++ for Python/9.0" "$tc/vc9sp1"
  rm -rf "$x"
fi

export WINEPREFIX="$tc/wineprefix" WINEDEBUG=-all
[ -d "$WINEPREFIX/drive_c" ] || wineboot -i >/dev/null 2>&1 || true
if [ ! -f "$tc/vc71tk/bin/cl.exe" ]; then
  fetch "$VC71_URL" "$VC71_SHA1" "$dl/VCToolkitSetup_1.01.exe"
  # InstallShield launcher: /s silent, /v passes the rest to msiexec.  It installs under Program Files whatever
  # TARGETDIR says, so take bin/include/lib from wherever cl.exe lands
  run=""; command -v xvfb-run >/dev/null && run="xvfb-run -a"
  $run wine "$dl/VCToolkitSetup_1.01.exe" /s /v"/qn TARGETDIR=C:\\vc71tk" </dev/null >/dev/null 2>&1 || true
  wineserver -w 2>/dev/null || true
  cl=$(find "$WINEPREFIX/drive_c" -ipath '*Visual C++ Toolkit 2003/bin/cl.exe' | head -1)
  [ -n "$cl" ] || { echo "VC 2003 Toolkit install produced no cl.exe" >&2; exit 1; }
  kit=$(dirname "$(dirname "$cl")")
  rm -rf "$tc/vc71tk"; mkdir -p "$tc/vc71tk"
  cp -R "$kit/bin" "$kit/include" "$kit/lib" "$tc/vc71tk/"
fi

cd "$tc"
if command -v sha256sum >/dev/null; then sha256sum --quiet -c "$root/tools/ci/toolchain.sha256"
else shasum -a 256 --quiet -c "$root/tools/ci/toolchain.sha256"; fi
echo "toolchains OK: $(wc -l < "$root/tools/ci/toolchain.sha256") files match tools/ci/toolchain.sha256"
