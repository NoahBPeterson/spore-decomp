// @ 0x01112950  FUN_01112950   (no PDB name; /O2 /MD /TP)
//
// PARTIAL.  The retail function (5426 B) is a large scene/terrain query helper.
// It mixes SSE math with thread-local scratch storage (TlsGetValue/TlsSetValue)
// and an rdtsc-based timing block, and calls FUN_0110e510 / FUN_010810f0 /
// FUN_01081360 / FUN_010814a0 / FUN_0110cd00 / FUN_0110d1d0 / FUN_011120a0 /
// FUN_01112600 and FUN_01209f50 (4x).
//
// Only the signature and the callee set are reproduced here; the scalar
// scheduling and TLS bookkeeping are not transcribed.

#include "types.h"

extern "C" {
    void* __stdcall TlsGetValue(unsigned);
    int   __stdcall TlsSetValue(unsigned, void*);
    float FUN_01209f50(...);
    float FUN_0110e510(...);
    float FUN_010810f0(...);
    float FUN_01081360(...);
    float FUN_010814a0(...);
    float FUN_0110cd00(...);
    float FUN_0110d1d0(...);
    float FUN_011120a0(...);
    float FUN_01112600(...);
}

void __cdecl FUN_01112950(int* param_1, float param_2, float param_3, float param_4,
                          int param_5, float* param_6, int param_7)
{
    // The retail body performs, roughly:
    //   1. fetch a thread-local scratch block with TlsGetValue, lazily allocating
    //      and storing it with TlsSetValue;
    //   2. rdtsc timing probes around the query;
    //   3. several FUN_01209f50 / FUN_0110e510 / FUN_010810f0 / FUN_01081360 /
    //      FUN_010814a0 / FUN_0110cd00 / FUN_0110d1d0 / FUN_011120a0 /
    //      FUN_01112600 calls on the position/direction parameters.
    (void)param_1; (void)param_2; (void)param_3; (void)param_4;
    (void)param_5; (void)param_6; (void)param_7;
    (void)TlsGetValue; (void)TlsSetValue; (void)FUN_01209f50; (void)FUN_0110e510;
    (void)FUN_010810f0; (void)FUN_01081360; (void)FUN_010814a0; (void)FUN_0110cd00;
    (void)FUN_0110d1d0; (void)FUN_011120a0; (void)FUN_01112600;
}
