// 0x01131540: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s01130c50/s01130c50.cpp.

#include "sse_helpers.h"  // MATCH_SSE_HELPERS_H

extern "C" unsigned char g_0140d204[];
extern "C" void __cdecl FUN_0113ff00(...);

// @ 0x01131540
// @ 0x01131540
extern "C" int __cdecl FUN_01131540(int a4, int a8)
{
    int t1000;
    float t1001;
    float t1002;
    int t1003;
    int t1004;
    int t1005;
    int t1009;
    t1000 = (int)((int)(a4));
    t1001 = (float)(*(float*)((char*)(t1000)));
    t1002 = (float)(t1001 * (float)(*(float*)g_0140d204));
    *(float*)&(a4) = (float)(t1002);
    t1003 = (int)SseRoundToInt((float)((*(float*)&a4)));
    t1004 = (int)((int)(a8));
    t1005 = (int)(*(int*)((char*)(t1004) + 180));
    FUN_0113ff00((unsigned int)(t1005), (unsigned int)(t1003));
    t1009 = (int)((int)0);
    return (int)(t1009);
}
