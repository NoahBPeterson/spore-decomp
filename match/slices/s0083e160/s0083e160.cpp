// 0x0083e160: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0083d3d0/s0083d3d0.cpp, src/game/UTFSpore_Win32/Expression.cpp.

#include <math.h>
extern "C" void __cdecl FUN_0083ce90(...);
struct C_0083dd70 { double FUN_0083dd70(unsigned int); };
struct C_0083e160 { double FUN_0083e160(unsigned int); };

// @ 0x0083e160
// @ 0x0083e160
extern "C" float __fastcall FUN_0083e160(char* self, int edx_unused, float a4)
{
    int t1001;
    int t1004;
    double t3;
    int t1011;
    int t1012;
    double v_l8;
    int t1013;
    double t8;
    double t9;
    t1001 = (int)((int)(*(int*)&a4));
    t1004 = (int)((int)(self));
    t3 = (double)((C_0083dd70*)((int)(self)))->FUN_0083dd70((unsigned int)(t1001));
    *(float*)&(a4) = (float)(t3);
    FUN_0083ce90((unsigned int)(t1001));
    t1011 = (int)(*(int*)((char*)(t1001)));
    if ((unsigned char)*(unsigned char*)((char*)(t1011)) == (unsigned char)94) {
        t1012 = (int)(t1011 + (int)1);
        v_l8 = (double)((float)(a4));
        t1013 = (int)(t1004);
        *(int*)((char*)(t1001)) = (int)(t1012);
        t8 = (double)((C_0083e160*)(t1013))->FUN_0083e160((unsigned int)(t1001));
        t9 = (double)pow((double)(v_l8), (double)(t8));
        return (float)(t9);
    }
    return (float)((float)(a4));
}
