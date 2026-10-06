#!/bin/sh
# Recreate the local EAWebKit include links that some slices compile against
# (manifest flags /Iscratch_s00880170_inc, /Iscratch_s0088b250_inc; resolved against work/match by
# run_all.py/chk.py). They point into the EAWebKit 1.21 support packages unpacked under
# work/ext/EAWebKitSupportPackages (git-ignored; see THIRD_PARTY.md). No EA source is committed.
set -e
root=$(cd "$(dirname "$0")/../.." && pwd)
pk="$root/work/ext/EAWebKitSupportPackages"
[ -d "$pk" ] || { echo "missing $pk: unpack the EAWebKit 1.21 support packages there first (THIRD_PARTY.md)"; exit 1; }
for d in scratch_s00880170_inc scratch_s0088b250_inc; do
  dir="$root/work/match/$d"
  mkdir -p "$dir"
  ln -sfn "$pk/coreallocatorEAWebKit/local/include/coreallocator" "$dir/coreallocator"
  ln -sfn "$pk/EAAssertEAWebKit/local/include/EAAssert" "$dir/EAAssert"
  ln -sfn "$pk/EABaseEAWebKit/local/include/Common/EABase" "$dir/EABase"
  ln -sfn "$pk/EAIOEAWebKit/local/include/EAIO" "$dir/EAIO"
  ln -sfn "$pk/EASTLEAWebKit/local/include/EASTL" "$dir/EASTL"
  ln -sfn "$pk/EATextEAWebKit/local/include/EAText" "$dir/EAText"
  ln -sfn "$pk/FreeTypeEAWebKit/local/freetype-2.3.9/include/freetype" "$dir/freetype"
  ln -sfn "$pk/FreeTypeEAWebKit/local/freetype-2.3.9/include/ft2build.h" "$dir/ft2build.h"
  ln -sfn "$pk/EATextEAWebKit/local/source/internal" "$dir/internal"
  ln -sfn "$pk/PPMallocEAWebKit/local/include/PPMalloc" "$dir/PPMalloc"
done
echo "EAWebKit include links ready under work/match/scratch_*_inc"
