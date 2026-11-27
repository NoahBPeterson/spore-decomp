// 0x005300d0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/SPSkinPaintDistributeDescription.cpp.

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

extern "C" void __cdecl FUN_005302b0(...);
struct C_00530b70 { void FUN_00530b70(unsigned int); };
struct C_00530c80 { int FUN_00530c80(unsigned int, unsigned int); };
extern "C" void __cdecl FUN_0093a780(...);
extern "C" int __cdecl FUN_0093ac80(...);
#pragma pack(push, 1)
struct Fr0_005300d0 {
    int v_l76;
    int v_l72;
    int dead0[8];
    int v_l36;
    int dead1[5];
    int v_l12;
    int v_l8;
};
#pragma pack(pop)

// @ 0x005300d0
extern "C" void __cdecl FUN_005300d0(int a4, int a8, int a12)
{
    Fr0_005300d0 fb;
    FUN_005302b0((unsigned int)a4, (unsigned int)(a12 + 8));
    FUN_0093a780((unsigned int)a4, (unsigned int)(a12 + 24), (unsigned int)1, (unsigned int)0);
    FUN_0093a780((unsigned int)a4, (unsigned int)(a12 + 28), (unsigned int)1, (unsigned int)0);
    FUN_0093a780((unsigned int)a4, (unsigned int)(a12 + 32), (unsigned int)1, (unsigned int)0);
    FUN_0093a780((unsigned int)a4, (unsigned int)(a12 + 36), (unsigned int)1, (unsigned int)0);
    FUN_0093a780((unsigned int)a4, (unsigned int)(a12 + 40), (unsigned int)1, (unsigned int)0);
    FUN_0093a780((unsigned int)a4, (unsigned int)(a12 + 44), (unsigned int)1, (unsigned int)0);
    ((il2c_vc0*)a4)->s12(a12 + 48, 8);
    FUN_0093ac80((unsigned int)a4, (unsigned int)(a12 + 56));
    FUN_0093ac80((unsigned int)a4, (unsigned int)(a12 + 57));
    FUN_0093ac80((unsigned int)a4, (unsigned int)(a12 + 58));
    FUN_0093ac80((unsigned int)a4, (unsigned int)(a12 + 59));
    if (a8 < 2) {
        fb.v_l36 = a12 + 60;
        ((C_00530c80*)fb.v_l36)->FUN_00530c80((unsigned int)(int)*(int*)(char*)fb.v_l36, (unsigned int)(int)*(int*)((char*)fb.v_l36 + 4));
        *(unsigned char*)((char*)a12 + 80) = (unsigned char)0;
    } else {
        FUN_0093a780((unsigned int)a4, (unsigned int)(int)&fb.v_l8, (unsigned int)1, (unsigned int)0);
        ((C_00530b70*)(a12 + 60))->FUN_00530b70((unsigned int)fb.v_l8);
        fb.v_l12 = 0;
        for (; fb.v_l12 < fb.v_l8; fb.v_l12 = fb.v_l12 + 1) {
            fb.v_l72 = (int)(int)((int)*(int*)((char*)a12 + 60) + (fb.v_l12 << 3));
            FUN_0093a780((unsigned int)a4, (unsigned int)fb.v_l72, (unsigned int)1, (unsigned int)0);
            fb.v_l76 = (int)(int)((int)((int)*(int*)((char*)a12 + 60) + (fb.v_l12 << 3)) + 4);
            FUN_0093a780((unsigned int)a4, (unsigned int)fb.v_l76, (unsigned int)1, (unsigned int)0);
        }
        FUN_0093ac80((unsigned int)a4, (unsigned int)(a12 + 80));
    }
    return;
}
