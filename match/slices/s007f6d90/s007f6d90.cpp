// 0x007f6d90: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/Spui/SPUIAnimation.cpp, match/slices/s007f64d0/s007f64d0.cpp.

#include <string.h>
struct il2c_vc0 {
    virtual void s0();
};
struct il2c_vc1 {
    virtual void s0();
};

extern "C" unsigned char g_013f63fc[];
extern "C" unsigned char g_013f6400[];

// @ 0x007f6d90
extern "C" int __fastcall FUN_007f6d90(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1004;
    int t1005;
    int t1012;
    int t1013;
    int t1014;
    int t1020;
    int t1021;
    int t1028;
    t1002 = (int)((int)(a4));
    t1004 = (int)((int)(self));
    t1005 = (int)(*(int*)((char*)(t1002)));
    *(int*)((char*)(t1004)) = (int)(t1005);
    if (t1005 != (int)0) {
        ((il2c_vc0*)(t1005))->s0();
    }
    t1012 = (int)(*(int*)((char*)(t1002) + 4));
    *(int*)((char*)(t1004) + 4) = (int)(t1012);
    *(int*)((char*)(t1004) + 8) = (int)((int)g_013f6400);
    t1013 = (int)(*(int*)((char*)(t1002) + 12));
    *(int*)((char*)(t1004) + 12) = (int)(t1013);
    *(int*)((char*)(t1004) + 16) = (int)((int)g_013f63fc);
    t1014 = (int)(*(int*)((char*)(t1002) + 20));
    *(int*)((char*)(t1004) + 20) = (int)(t1014);
    if (t1014 != (int)0) {
        ((il2c_vc1*)(t1014))->s0();
    }
    t1020 = (int)(t1002 + (int)24);
    t1021 = (int)(t1004 + (int)24);
    memcpy((void*)(t1021), (const void*)(t1020), (unsigned int)((int)112));
    t1028 = (int)(t1004);
    return (int)(t1028);
}
