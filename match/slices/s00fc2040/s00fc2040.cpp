// 0x00fc2040: C++ lifted from retail's machine code by vs2005-cpp lift2il, float helpers from sse_helpers.h; byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPTerrain/SPTerrainTerraform.cpp, match/slices/s00fc10d0/s00fc10d0.cpp.

#include <math.h>
#include "sse_helpers.h"  // MATCH_SSE_HELPERS_H

extern "C" unsigned char g_01471064[];
extern "C" unsigned char g_014913bc[];

// @ 0x00fc2040
extern "C" float __cdecl FUN_00fc2040(float a4, float a8)
{
    float t1;
    float t2;
    double t6;
    float v_l16;
    float t1002;
    t1 = (float)((float)(a4) - (float)(*(float*)g_01471064));
    t2 = (float)((float)(a8) - (float)(*(float*)g_01471064));
    t6 = (double)sqrt((double)(((t1 * t1) + (t2 * t2))));
    v_l16 = (float)(((double)1 - (t6 * (double)((float)(*(float*)g_014913bc)))));
    t1002 = (float)SseMaxZero((float)(v_l16));
    v_l16 = (float)(t1002);
    return (float)(v_l16);
}
