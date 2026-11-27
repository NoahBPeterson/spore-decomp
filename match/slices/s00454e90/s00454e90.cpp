// 0x00454e90: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00454330/s00454330.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
};

extern "C" void __cdecl FUN_00f47380(...);
__forceinline void il2c_d_FUN_00f47380(int p, int fl) { if (fl & 1) FUN_00f47380((unsigned int)(p)); }


struct D_00454e90 { void FUN_00454e90(int a4, int a8); };
// @ 0x00454e90
void D_00454e90::FUN_00454e90(int a4, int a8)
{
    for (; (unsigned int)a4 < (unsigned int)a8; *(int*)&a4 = a4 + 4) {
        if ((int)*(int*)(char*)a4 != 0) {
            ((il2c_vc0*)(int)(int)*(int*)(char*)a4)->s2();
        }
        il2c_d_FUN_00f47380(a4, 0);
    }
    return;
}
