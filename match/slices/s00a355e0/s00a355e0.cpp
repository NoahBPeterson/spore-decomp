// 0x00a355e0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPAudio/SPAudioAmbienceLayer.cpp, match/slices/s00a34e80/s00a34e80.cpp.

#include <string.h>
struct C_00454cb0 { int FUN_00454cb0(unsigned int, unsigned int); };

// @ 0x00a355e0
extern "C" void __fastcall FUN_00a355e0(char* self, int edx_unused, int a4)
{
    int t1001;
    int t1002;
    int t1008;
    int t1009;
    int t1010;
    t1001 = (int)((int)(a4));
    t1002 = (int)(t1001);
    goto La355f0;
    La355f0:;
    t1008 = (int)strlen((const char*)(t1002));
    t1009 = (int)(t1008 + t1001);
    t1010 = (int)((int)(self) + (int)16);
    ((C_00454cb0*)(t1010))->FUN_00454cb0((unsigned int)(t1001), (unsigned int)(t1009));
    return;
}
