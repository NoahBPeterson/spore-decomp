// 0x00e507d0: C++ lifted from retail's machine code by vs2005-cpp lift2il, float helpers from sse_helpers.h; byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00e4f860/s00e4f860.cpp.

#include "sse_helpers.h"  // MATCH_SSE_HELPERS_H

extern "C" unsigned char g_01470f1c[];

// @ 0x00e507d0
extern "C" bool __cdecl FUN_00e507d0(float a4, float a8)
{
    float t1000;
    float t1001;
    float t1002;
    float v_l16;
    float t1003;
    int t1008;
    unsigned char t1009;
    t1000 = (float)((float)(a4));
    t1001 = (float)(t1000 / (float)(a8));
    t1002 = (float)(t1001 * (float)(*(float*)g_01470f1c));
    v_l16 = (float)(t1002);
    t1003 = (float)(v_l16);
    t1008 = (int)SseFloorToInt((float)(t1003));
    t1009 = (unsigned char)((unsigned char)(t1008) & (unsigned char)1);
    return (bool)(t1009);
}
