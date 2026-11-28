// 0x0093cf60: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0093c950/s0093c950.cpp, src/game/UTFSpore_Win32/EATextEncoding.cpp.

#include <string.h>
extern "C" void __cdecl FUN_0093c950(...);

// @ 0x0093cf60
extern "C" int __cdecl FUN_0093cf60(int a4, int a8, int a12, int a16)
{
    int t1000;
    int t1001;
    int t1004;
    int t1005;
    int t1008;
    int t1009;
    int t1013;
    int t1014;
    t1000 = (int)((int)(a16));
    t1001 = (int)((int)(a12));
    t1004 = (int)((int)(a8));
    if (t1000 == (int)(-1)) {
        t1005 = (int)(t1001);
        t1000 = (int)strlen((const char*)(t1005));
    }
    t1008 = (int)((int)(a4));
    t1009 = (int)((int)&a8);
    FUN_0093c950((unsigned int)(t1001), (unsigned int)(t1000), (unsigned int)((int)8), (unsigned int)(t1008), (unsigned int)(t1009), (unsigned int)((int)16));
    t1013 = (int)((int)(a8));
    if ((unsigned int)(t1004) > (unsigned int)(t1013)) {
        t1014 = (int)((int)0);
        *(unsigned short*)((char*)(t1008) + (t1013)*2) = (unsigned short)((unsigned short)(t1014));
        t1013 = (int)((int)(a8));
    }
    return (int)(t1013);
}
