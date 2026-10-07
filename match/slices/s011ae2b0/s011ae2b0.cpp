// Slice s011ae2b0: the single function in this slice is
//   0x011AE2B0  lib_cblock::FUN_011ae2b0   (7017 bytes, __cdecl, 3 args
//               (uint* pOut, const uint16_t* a, const uint16_t* b), ret)
//
// This lives in the C-library block region (lib_cblock, symbols/lib_names.txt).
// It reads two 16-bit packed vectors and a third pointer, computes a fairly large
// signed arithmetic combination of their 16-bit lanes (add/mul/compare/select),
// stored through the first argument, with nested loops and scattered branches.
// The entry does `sub esp,8` then pulls arg3 into EAX and arg2 into ECX, both used
// as uint16_t* arrays, so it is a plain __cdecl three-argument routine.
//
// 7017 bytes is beyond the slice budget for a full reconstruction; this file
// keeps the exact signature and a compiling skeleton, recorded as incomplete in
// partial.txt.
#include "types.h"

// @ 0x011AE2B0
void FUN_011ae2b0(uint32_t* pOut, const uint16_t* a, const uint16_t* b)
{
    (void)pOut;
    (void)a;
    (void)b;
    // 7017-byte packed-arithmetic body not reconstructed (see partial.txt)
}
