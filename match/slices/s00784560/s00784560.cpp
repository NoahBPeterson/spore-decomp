// Slice s00784560: one 3987-byte function (0x784560) in the SH/ground-bounce
// subsystem.  /O2 /MD /Gy /EHsc /TP module.
//
// PARTIAL: the 3987-byte body is a heavily unrolled/vectorised spherical-harmonic
// accumulation routine; only the signature and the top-level argument handling
// are reproduced here.  Listed in partial.txt, not nonmatching.txt.
#include "types.h"

// @ 0x00784560
void FUN_00784560(float* param_1, int param_2, void* param_3, void* param_4)
{
    // omitted: the full unrolled SH accumulation
    (void)param_1;
    (void)param_2;
    (void)param_3;
    (void)param_4;
}
