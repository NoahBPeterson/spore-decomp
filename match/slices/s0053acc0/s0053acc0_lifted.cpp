// 0x0053acc0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0053acc0/s0053acc0.cpp, src/game/SPBake/SPSkinPaintParticleDescription.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12(int, int);
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12(int, int);
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12(int, int);
};
struct il2c_vc3 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12(int, int);
};

extern "C" void __cdecl FUN_0053a6d0(...);
extern "C" void __cdecl FUN_0053bc90(...);
extern "C" int __cdecl FUN_0093a6c0(...);
extern "C" void __cdecl FUN_0093a780(...);
#pragma pack(push, 1)
struct Fr0_0053acc0 {
    int dead0[3];
};
#pragma pack(pop)

// @ 0x0053acc0
extern "C" void __cdecl FUN_0053acc0(int a4, int a8, int a12)
{
    Fr0_0053acc0 fb;
    FUN_0053bc90((unsigned int)a4, (unsigned int)(a12 + 12));
    FUN_0093a780((unsigned int)a4, (unsigned int)(a12 + 32), (unsigned int)1, (unsigned int)0);
    FUN_0093a780((unsigned int)a4, (unsigned int)(a12 + 36), (unsigned int)1, (unsigned int)0);
    ((il2c_vc0*)a4)->s12(a12 + 40, 12);
    FUN_0093a6c0((unsigned int)a4, (unsigned int)(a12 + 52), (unsigned int)1);
    FUN_0093a6c0((unsigned int)a4, (unsigned int)(a12 + 53), (unsigned int)1);
    FUN_0093a6c0((unsigned int)a4, (unsigned int)(a12 + 54), (unsigned int)1);
    FUN_0093a6c0((unsigned int)a4, (unsigned int)(a12 + 55), (unsigned int)1);
    ((il2c_vc1*)a4)->s12(a12 + 56, 12);
    ((il2c_vc2*)a4)->s12(a12 + 68, 12);
    ((il2c_vc3*)a4)->s12(a12 + 80, 12);
    FUN_0093a780((unsigned int)a4, (unsigned int)(a12 + 92), (unsigned int)1, (unsigned int)0);
    FUN_0093a780((unsigned int)a4, (unsigned int)(a12 + 96), (unsigned int)1, (unsigned int)0);
    FUN_0093a780((unsigned int)a4, (unsigned int)(a12 + 100), (unsigned int)1, (unsigned int)0);
    FUN_0093a780((unsigned int)a4, (unsigned int)(a12 + 104), (unsigned int)1, (unsigned int)0);
    FUN_0093a780((unsigned int)a4, (unsigned int)(a12 + 108), (unsigned int)1, (unsigned int)0);
    FUN_0093a780((unsigned int)a4, (unsigned int)(a12 + 112), (unsigned int)1, (unsigned int)0);
    FUN_0053a6d0((unsigned int)a4, (unsigned int)(a12 + 116));
    FUN_0093a6c0((unsigned int)a4, (unsigned int)(a12 + 176), (unsigned int)1);
    FUN_0093a6c0((unsigned int)a4, (unsigned int)(a12 + 177), (unsigned int)1);
    FUN_0093a6c0((unsigned int)a4, (unsigned int)(a12 + 178), (unsigned int)1);
    return;
}
