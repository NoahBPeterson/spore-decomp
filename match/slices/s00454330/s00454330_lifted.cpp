// 0x00454330: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00454330/s00454330.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
};

extern "C" void __cdecl FUN_004571d0(...);
extern "C" void __cdecl FUN_00f47380(...);
#pragma pack(push, 1)
struct Fr0_00454330 {
    int v_l24;
    int v_l20;
    int dead0[2];
    char dead1;
    unsigned char v_l7;
    unsigned char v_l6;
    unsigned char v_l5;
};
#pragma pack(pop)
__forceinline void il2c_d_FUN_00f47380(int p, int fl) { if (fl & 1) FUN_00f47380((unsigned int)(p)); }


struct D_00454330 { int FUN_00454330(int a4); };
// @ 0x00454330
int D_00454330::FUN_00454330(int a4)
{
    Fr0_00454330 fb;
    if ((unsigned int)(a4 + 4) < (unsigned int)*(int*)((char*)(int)this + 4)) {
        fb.v_l20 = (int)(int)*(int*)((char*)(int)this + 4);
        fb.v_l6 = (unsigned char)0;
        fb.v_l5 = (unsigned char)0;
        fb.v_l7 = (unsigned char)0;
        FUN_004571d0((unsigned int)(a4 + 4), (unsigned int)fb.v_l20, (unsigned int)a4);
    }
    *(int*)((char*)(int)this + 4) = (int)(int)((int)*(int*)((char*)(int)this + 4) - 4);
    fb.v_l24 = (int)(int)*(int*)((char*)(int)this + 4);
    if ((int)*(int*)(char*)fb.v_l24 != 0) {
        ((il2c_vc0*)(int)*(int*)(char*)fb.v_l24)->s2();
    }
    il2c_d_FUN_00f47380(fb.v_l24, 0);
    return a4;
}
