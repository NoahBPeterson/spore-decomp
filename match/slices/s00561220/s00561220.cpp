// 0x00561220: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s005609a0/s005609a0.cpp, src/game/SPEditors/SPObjectTemplateDB.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5(int, int, int);
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5(int, int, int);
};

struct C_004e19a0 { void FUN_004e19a0(unsigned int); };
struct C_005156b0 { int FUN_005156b0(); };
struct C_00558bc0 { int FUN_00558bc0(unsigned int, unsigned int); };
struct C_0055d230 { void FUN_0055d230(unsigned int, unsigned int); };
struct C_0055d790 { void FUN_0055d790(unsigned int, unsigned int); };
extern "C" void __cdecl FUN_00560f20(...);
struct C_005631e0 { int FUN_005631e0(unsigned int); };
extern "C" int __cdecl FUN_0067dcc0(...);
#pragma pack(push, 1)
struct Fr0_00561220 {
    int dead0[3];
    int v_l56;
    int dead1[2];
    int v_l44[4];
    int v_l28;
    int v_l24;
    int v_l20;
    int dead2[2];
    int v_l8;
};
#pragma pack(pop)


struct D_00561220 { void FUN_00561220(int a4); };
// @ 0x00561220
void D_00561220::FUN_00561220(int a4)
{
    Fr0_00561220 fb;
    fb.v_l8 = (int)((C_005631e0*)(int)this)->FUN_005631e0((unsigned int)(a4 + 8));
    if (fb.v_l8 != -1) {
        fb.v_l28 = 0;
        fb.v_l24 = 0;
        fb.v_l20 = 0;
        ((C_004e19a0*)(int)&fb.v_l28)->FUN_004e19a0((unsigned int)((C_00558bc0*)(int)&fb.v_l44)->FUN_00558bc0((unsigned int)63736241, (unsigned int)(int)*(int*)(char*)a4));
        if ((int)*(int*)((char*)a4 + 4) > 0) {
            ((C_0055d230*)(int)this)->FUN_0055d230((unsigned int)fb.v_l8, (unsigned int)(int)&fb.v_l28);
            FUN_00560f20((unsigned int)(a4 + 8), (unsigned int)(int)&fb.v_l28, (unsigned int)1);
            ((il2c_vc0*)(int)FUN_0067dcc0())->s5(105798618, a4, 0);
        } else {
            ((C_0055d790*)(int)this)->FUN_0055d790((unsigned int)fb.v_l8, (unsigned int)(int)&fb.v_l28);
            FUN_00560f20((unsigned int)(a4 + 8), (unsigned int)(int)&fb.v_l28, (unsigned int)0);
            ((il2c_vc1*)(int)FUN_0067dcc0())->s5(105798618, a4, 0);
        }
        fb.v_l56 = fb.v_l28;
        for (; (unsigned int)fb.v_l56 < (unsigned int)fb.v_l24; fb.v_l56 = fb.v_l56 + 12) {
        }
        ((C_005156b0*)(int)&fb.v_l28)->FUN_005156b0();
    }
    return;
}
