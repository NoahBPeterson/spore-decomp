// 0x011302a0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0112fc10/s0112fc10.cpp.

#include "sse_helpers.h"  // MATCH_SSE_HELPERS_H

extern "C" unsigned char g_01451600[];
extern "C" void __cdecl FUN_0113fba0(...);

// @ 0x011302a0
// @ 0x011302a0
extern "C" int __cdecl FUN_011302a0(int a4, int a8)
{
    int t1000;
    float t1001;
    float t1002;
    int t1004;
    int t1005;
    int t1006;
    int t1010;
    t1000 = (int)((int)(a4));
    t1001 = (float)(*(float*)((char*)(t1000) + 4));
    t1002 = (float)(t1001 * (float)(*(float*)g_01451600));
    *(float*)&(a4) = (float)(t1002);
    t1004 = (int)SseRoundToInt((float)((*(float*)&a4)));
    t1005 = (int)((int)(a8));
    t1006 = (int)(*(int*)((char*)(t1005) + 168));
    FUN_0113fba0((unsigned int)(t1006), (unsigned int)(t1004));
    *(int*)((char*)(t1005) + 12) = (int)((int)0);
    t1010 = (int)((int)0);
    return (int)(t1010);
}
