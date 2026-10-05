// Slice s00794610: SP::MultiplyZH<float, rw::math::vpu::Vector4> (0x794610) and
// SP::AddColourSample (0x7948d0).  /O2 /MD /Gy /EHsc /TP module.
//
// PARTIAL: 00794610 is the ZonalHarmonic basis multiply (the ZH analogue of
// SP::MultiplySH with sqrt band-index decoding); 007948d0 is the colour-sample
// accumulation.  Both are large and only their signatures are reproduced here.
#include "types.h"

// @ 0x00794610
void SP_MultiplyZH(int param_1, int param_2, int param_3, void* param_4, char* param_5)
{
    // omitted: the ZH basis multiply
    (void)param_1;
    (void)param_2;
    (void)param_3;
    (void)param_4;
    (void)param_5;
}

// @ 0x007948d0
void SP_AddColourSample(float* param_1, int param_2, float* param_3, float* param_4)
{
    // omitted: the colour-sample accumulation
    (void)param_1;
    (void)param_2;
    (void)param_3;
    (void)param_4;
}
