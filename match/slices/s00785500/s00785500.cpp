// Slice s00785500: one 4022-byte function, the explicit template instance
// SP::RotateZHToSHAdd<rw::math::vpu::Vector4, rw::math::vpu::Vector4> (0x785500).
// /O2 /MD /Gy /EHsc /TP module.
//
// PARTIAL: the 4022-byte body is a fully unrolled ZonalHarmonic-to-SH rotation
// accumulation; only the signature is reproduced here.  Listed in partial.txt.
#include "types.h"

// @ 0x00785500
void SP_RotateZHToSHAdd(float* param_1, int param_2, float* param_3, float* param_4)
{
    // omitted: the full unrolled ZH->SH accumulation
    (void)param_1;
    (void)param_2;
    (void)param_3;
    (void)param_4;
}
