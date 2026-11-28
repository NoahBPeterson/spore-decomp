// 0x0112f080: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0112ebf0/s0112ebf0.cpp.

#include "sse_helpers.h"  // MATCH_SSE_HELPERS_H

extern "C" unsigned char g_0140d204[];
extern "C" void __cdecl FUN_0113fdd0(...);

// @ 0x0112f080
extern "C" int __cdecl FUN_0112f080(int a4, int a8, int a12)
{
    int t1000;
    int t1001;
    int t1002;
    float t1003;
    float t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1011;
    t1000 = (int)((int)(a4));
    t1001 = (int)(*(int*)((char*)(t1000) + 12));
    t1002 = (int)((int)(a8));
    t1003 = (float)(*(float*)((char*)(t1001) + (t1002)*4));
    t1004 = (float)(t1003 * (float)(*(float*)g_0140d204));
    *(float*)&(a4) = (float)(t1004);
    t1005 = (int)SseRoundToInt((float)((*(float*)&a4)));
    t1006 = (int)((int)(a12));
    t1007 = (int)(*(int*)((char*)(t1006) + 164));
    FUN_0113fdd0((unsigned int)(t1007), (unsigned int)(t1002), (unsigned int)(t1005));
    t1011 = (int)((int)0);
    return (int)(t1011);
}
