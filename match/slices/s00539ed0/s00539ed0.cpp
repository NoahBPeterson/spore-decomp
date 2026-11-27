// 0x00539ed0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00539d70/s00539d70.cpp, src/game/SPBake/SPSkinPaintParticleDescription.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5(int, int);
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual int s6(int, int);
};

extern "C" unsigned char g_013f1ffc[];
extern "C" unsigned char g_013f2ec8[];
extern "C" unsigned char g_013f332c[];
extern "C" unsigned char g_013f3344[];
extern "C" unsigned char g_013f3368[];
struct C_00539f90 { int FUN_00539f90(); };
struct C_0083c800 { void FUN_0083c800(); };
extern "C" int __cdecl FUN_00f473a0(...);
#pragma pack(push, 1)
struct Fr0_00539ed0 {
    int v_l36;
    int v_l32;
    int dead0[4];
    int v_l12;
    int v_l8;
};
#pragma pack(pop)

// @ 0x00539ed0
extern "C" void __cdecl FUN_00539ed0(int a4, int a8)
{
    Fr0_00539ed0 fb;
    fb.v_l8 = (int)(int)FUN_00f473a0((unsigned int)84, (unsigned int)(int)g_013f3368, (unsigned int)0, (unsigned int)0, (unsigned int)0, (unsigned int)0);
    if (fb.v_l8 != 0) {
        fb.v_l32 = ((C_00539f90*)fb.v_l8)->FUN_00539f90();
    } else {
        fb.v_l32 = 0;
    }
    ((il2c_vc0*)a8)->s5(*(int*)g_013f2ec8, fb.v_l32);
    fb.v_l12 = (int)(int)FUN_00f473a0((unsigned int)16, (unsigned int)(int)g_013f3344, (unsigned int)0, (unsigned int)0, (unsigned int)0, (unsigned int)0);
    if (fb.v_l12 != 0) {
        ((C_0083c800*)fb.v_l12)->FUN_0083c800();
        *(int*)(char*)fb.v_l12 = (int)g_013f1ffc;
        *(int*)(char*)fb.v_l12 = (int)g_013f1ffc;
        *(int*)(char*)fb.v_l12 = (int)g_013f332c;
        fb.v_l36 = fb.v_l12;
    } else {
        fb.v_l36 = 0;
    }
    ((il2c_vc1*)a4)->s6(*(int*)g_013f2ec8, fb.v_l36);
    return;
}
