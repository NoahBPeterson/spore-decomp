// 0x004a9610: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/SPEditorManipulationUtilities.cpp, match/slices/s004a89e0/s004a89e0.cpp.

#include <string.h>
struct C_0041cb40 { int FUN_0041cb40(unsigned int); };
extern "C" int __cdecl FUN_004a9b40(...);
struct S9 { int m0; int m1; int m2; int m3; int m4; int m5; int m6; int m7; int m8; };
template<class T> __forceinline T il2c_k(T v) { return v; }

// @ 0x004a9610
extern "C" void __cdecl FUN_004a9610(int a4, int a8)
{
    float v_l16_i;
    float v_l12_40;
    float v_l8;
    float v_l64_z;
    float v_l60_f;
    int v_l56_a[9];
    float v_l20;
    int v_l108_63[9];
    float v_l72_a;
    float v_l68;
    int dead_0[11];
    int v_l156;
    v_l60_f = *(float*)((char*)a4 + (il2c_k(3) << 2));
    v_l72_a = *(float*)((char*)a4 + (il2c_k(0) << 2));
    v_l68 = *(float*)((char*)a4 + (il2c_k(1) << 2));
    v_l64_z = *(float*)((char*)a4 + (il2c_k(2) << 2));
    v_l20 = (float)v_l72_a;
    v_l16_i = (float)v_l68;
    v_l12_40 = (float)v_l64_z;
    v_l8 = (float)v_l60_f;
    v_l156 = (int)(int)FUN_004a9b40((unsigned int)(int)&v_l108_63, (unsigned int)(int)(int)&v_l20);
    ((C_0041cb40*)(int)&v_l56_a)->FUN_0041cb40((unsigned int)v_l156);
    *(S9*)a8 = *(S9*)(int)&v_l56_a;
    return;
}
