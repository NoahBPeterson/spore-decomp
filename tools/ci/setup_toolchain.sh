#!/bin/sh
# Build work/toolchain/{vc9sp1,vc71tk} and the wine prefix from Microsoft's public installers, then check every file
# against tools/ci/toolchain.sha256 (the toolchains the maintainers match with).  Linux (CI) or macOS; needs wine
# (32-bit), msiextract (msitools), curl, sha1sum/shasum, sha256sum/shasum.
#   VC9 SP1, cl 15.00.30729.01: VCForPython27.msi from Microsoft's original URL via the Wayback Machine, extracted
#     with msiextract (no installer runs)
#   VC 2003 Toolkit 1.01, cl 13.10.3077: VCToolkitSetup.exe from archive.org; its MSI unpacked by is_unpack.py, extracted
#     with msiextract (no installer runs)
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
# no wine-mono / wine-gecko: on first start wine offers to install them in a dialog, which waits forever on a headless
# runner (run 42656472534: wineboot timed out after 5 minutes); cl.exe needs neither
export WINEDLLOVERRIDES="mscoree,mshtml="
# every wine call gets a time limit (the first CI run hung 30 minutes, silently, in the installer under wine 9.0)
if [ ! -d "$WINEPREFIX/drive_c" ]; then
  timeout 300 wineboot -i </dev/null || { echo "wineboot failed or timed out" >&2; exit 1; }
  wineserver -w
fi
if [ ! -f "$tc/vc71tk/bin/cl.exe" ]; then
  fetch "$VC71_URL" "$VC71_SHA1" "$dl/VCToolkitSetup_1.01.exe"
  # the InstallShield 7 launcher would not run under the runner's wine (exit 109 before msiexec started, run
  # 42658111691): unpack its MSI without running it (tools/ci/is_unpack.py) and extract that, like VC9
  x=$(mktemp -d)
  python3 "$root/tools/ci/is_unpack.py" "$dl/VCToolkitSetup_1.01.exe" "$x/is" >/dev/null
  msiextract -C "$x/msi" "$x/is/Microsoft Visual C++ Toolkit 2003.msi" >/dev/null
  kit="$x/msi/Program Files/Microsoft Visual C++ Toolkit 2003"
  [ -f "$kit/bin/cl.exe" ] || { echo "VC 2003 Toolkit MSI held no bin/cl.exe" >&2; exit 1; }
  rm -rf "$tc/vc71tk"; mkdir -p "$tc/vc71tk"
  cp -R "$kit/bin" "$kit/include" "$kit/lib" "$tc/vc71tk/"
  rm -rf "$x"
fi

cd "$tc"
if command -v sha256sum >/dev/null; then sha256sum --quiet -c "$root/tools/ci/toolchain.sha256"
else shasum -a 256 --quiet -c "$root/tools/ci/toolchain.sha256"; fi
echo "toolchains OK: $(wc -l < "$root/tools/ci/toolchain.sha256") files match tools/ci/toolchain.sha256"
