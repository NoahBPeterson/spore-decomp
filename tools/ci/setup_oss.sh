#!/bin/sh
# Download, verify and unpack the open-source library sources some manifest rows compile (THIRD_PARTY.md), then
# recreate the configured trees and include directories those rows name.  Linux (CI) or macOS; needs curl, tar,
# unzip, patch, perl, make, python3, sha256sum/shasum.  Nothing here is game code; no third-party source is committed.
#   work/third_party/src/{jpeg-6a,libpng-1.2.25,zlib-1.2.3,openssl-0.9.8g}   pristine upstream releases
#   work/third_party/build/jpeg-6a-inc/jconfig.h                              third_party/jpeg-6a/jconfig.h (ours)
#   work/third_party/build/openssl-0.9.8g-d2110920                            perl Configure VC-WIN32 + make links, as
#                                                                             tools/third_party/build_faithful.py does
#   work/ext/EAWebKitSupportPackages                                          from EA's EAWebKit 1.21.00 GPL release,
#                                                                             plus tools/ci/oss/EATextOpenType.patch
#   work/match/scratch_*_inc                                                  include dirs manifest rows name with
#                                                                             /Iscratch_*_inc (run_all.py resolve_flags)
# Downloads are cached in $OSS_CACHE (default work/toolchain/downloads/oss).  Steps whose output exists are skipped.
set -eu
root=$(cd "$(dirname "$0")/../.." && pwd)
dl="${OSS_CACHE:-$root/work/toolchain/downloads/oss}"
tp="$root/work/third_party"
oss="$root/tools/ci/oss"
mkdir -p "$dl" "$tp/src" "$tp/build" "$root/work/ext" "$root/work/match"

sha256() { if command -v sha256sum >/dev/null; then sha256sum "$1"; else shasum -a 256 "$1"; fi | cut -d' ' -f1; }
fetch() {   # url sha256 file
  if [ ! -f "$3" ] || [ "$(sha256 "$3")" != "$2" ]; then
    curl -fsSL --retry 5 --retry-delay 10 -A "spore-decomp-ci" -o "$3.part" "$1"
    mv "$3.part" "$3"
  fi
  got=$(sha256 "$3")
  [ "$got" = "$2" ] || { echo "$3: SHA-256 $got, expected $2" >&2; exit 1; }
}
untar() {   # url sha256 tarball extract_dir
  fetch "$1" "$2" "$dl/$3"
  if [ ! -d "$tp/src/$4" ]; then
    x=$(mktemp -d)
    tar xzf "$dl/$3" -C "$x"
    mv "$x/$4" "$tp/src/$4"
    rm -rf "$x"
  fi
}

untar https://www.ijg.org/files/jpegsrc.v6a.tar.gz \
  0e963fdd29d5049f61f3dc137bdc9437473a0ad505dbcfc8925f0fcad46c5929 jpegsrc.v6a.tar.gz jpeg-6a
untar https://www.openssl.org/source/old/0.9.x/openssl-0.9.8g.tar.gz \
  0e26886845de95716c9f1b9b75c0e06e9d4075d2bdc9e11504eaa5f7ee901cf0 openssl-0.9.8g.tar.gz openssl-0.9.8g
untar https://zlib.net/fossils/zlib-1.2.3.tar.gz \
  1795c7d067a43174113fdf03447532f373e1c6c57c08d61d9e4e9be5e244b05e zlib-1.2.3.tar.gz zlib-1.2.3
untar https://downloads.sourceforge.net/project/libpng/libpng12/older-releases/1.2.25/libpng-1.2.25.tar.gz \
  295ba7b7744efe93fb4c34d4973cc1099055d9c379a1e9397209857e80611e18 libpng-1.2.25.tar.gz libpng-1.2.25

# libjpeg 6a ships no jconfig.h: ours is jconfig.vc (third_party/jpeg-6a/jconfig.h)
mkdir -p "$tp/build/jpeg-6a-inc"
cp "$root/third_party/jpeg-6a/jconfig.h" "$tp/build/jpeg-6a-inc/jconfig.h"

# OpenSSL configured for VC-WIN32 with the options in third_party/manifest.json (directory suffix = their hash)
ossl=$(cd "$root" && python3 -c 'import sys; sys.path.insert(0, "tools/third_party"); import build_faithful as b
lib = b.load_manifest()["libraries"]["openssl"]
print(b.prepare_openssl(lib, "work/third_party/src/openssl-0.9.8g"))')
[ -f "$ossl/include/openssl/ssl.h" ] || { echo "OpenSSL configure failed: $ossl" >&2; exit 1; }

# EAWebKit 1.21.00 support packages (EABase, EASTL, EAText, EAIO, ...), from EA's GPL page for Darkspore
if [ ! -d "$root/work/ext/EAWebKitSupportPackages" ]; then
  fetch https://gpl.ea.com/EAWebKit-1.21.00.darkspore.zip \
    a2f8ac0b7d2938d386389aec0a7b12d0c6eaffc2778ad90c88b87d04a60d1c77 "$dl/EAWebKit-1.21.00.darkspore.zip"
  x=$(mktemp -d)
  unzip -q "$dl/EAWebKit-1.21.00.darkspore.zip" 'EAWebKitSupportPackages/*' -d "$x"
  f="$x/EAWebKitSupportPackages/EATextEAWebKit/local/source/internal/EATextOpenType.cpp"
  tr -d '\r' < "$f" > "$f.lf" && mv "$f.lf" "$f"
  patch -s -p1 -d "$x" < "$oss/EATextOpenType.patch"
  mv "$x/EAWebKitSupportPackages" "$root/work/ext/EAWebKitSupportPackages"
  rm -rf "$x"
fi

# include dirs named by manifest rows (/Iscratch_*_inc, resolved against work/match)
sh "$root/tools/third_party/eawebkit_include_links.sh" >/dev/null
d="$root/work/match/scratch_s00894440_inc/eathread"     # our minimal EAThread headers for EAText's StyleManager
mkdir -p "$d" && cp "$oss/eathread/eathread_atomic.h" "$oss/eathread/eathread_futex.h" "$d/"
# OpenSSL: cryptlib.h, e_os.h and include/openssl as files; some slices undefine OPENSSL_EXPORT_VAR_AS_FUNCTION
# (retail pushes &X509_it as data rather than calling X509_it); a few also take a private header from the tree
osslinc() {   # dir variant [extra header path in the configured tree ...]
  dir="$root/work/match/$1"; variant=$2; shift 2
  [ -f "$dir/openssl/ssl.h" ] && return 0
  rm -rf "$dir.part"; mkdir -p "$dir.part"
  cp "$ossl/e_os.h" "$ossl/crypto/cryptlib.h" "$dir.part/"
  cp -RL "$ossl/include/openssl" "$dir.part/openssl"
  conf="$dir.part/openssl/opensslconf.h"
  case $variant in
    define) ;;
    undef) sed 's/^#define OPENSSL_EXPORT_VAR_AS_FUNCTION$/#undef OPENSSL_EXPORT_VAR_AS_FUNCTION/' "$conf" > "$conf.x" ;;
    comment) awk '$0 == "#define OPENSSL_EXPORT_VAR_AS_FUNCTION" {
        print "/* Spore build uses ASN1 item pointers as data, not as functions (retail bytes"
        print "   show `push &X509_it`, not `call X509_it`): keep the macro undefined. */"; next } { print }' "$conf" > "$conf.x" ;;
  esac
  [ -f "$conf.x" ] && mv "$conf.x" "$conf"
  for h in "$@"; do cp "$ossl/$h" "$dir.part/"; done
  rm -rf "$dir"; mv "$dir.part" "$dir"
}
for s in 0119f820 011a09c0 011a2780 011a4600 011a5310 011a81e0 011aae40 011b8e10 011bb2b0 011bc410 011bdbf0 \
         011c9630 011cae60 01192400; do
  osslinc scratch_s${s}_inc define
done
osslinc scratch_s01189d60_inc define crypto/md32_common.h
osslinc scratch_s011b34f0_inc define crypto/opensslconf.h
osslinc scratch_s011b7070_inc define crypto/engine/eng_int.h
osslinc scratch_s011c8c30_inc define crypto/ui/ui_locl.h
for s in 0117e620 01198850 0119a2e0 011a61c0 011cf390 011d7de0; do
  osslinc scratch_s${s}_inc undef
done
osslinc scratch_s011b4660_inc comment
echo "open-source sources OK: jpeg-6a, libpng-1.2.25, zlib-1.2.3, openssl-0.9.8g ($(basename "$ossl")), EAWebKit 1.21.00"
