// 0x0053aea0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
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
    virtual void s12();
    virtual void s13();
    virtual int s14(int, int);
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
    virtual void s12();
    virtual void s13();
    virtual void s14(int, int);
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
    virtual void s12();
    virtual void s13();
    virtual void s14(int, int);
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
    virtual void s12();
    virtual void s13();
    virtual void s14(int, int);
};

extern "C" int __cdecl FUN_0053a930(...);
extern "C" void __cdecl FUN_0053bd00(...);
extern "C" int __cdecl FUN_0093a9a0(...);
extern "C" void __cdecl FUN_0093aa70(...);
#pragma pack(push, 1)
struct Fr0_0053aea0 {
    unsigned char v_l100;
    unsigned char v_l99;
    unsigned char v_l98;
    unsigned char v_l97;
    int v_l96;
    int v_l92;
    float v_l88;
    float v_l84;
    float v_l80;
    float v_l76;
    float v_l72;
    float v_l68;
    float v_l64;
    float v_l60;
    float v_l56;
    float v_l52;
    unsigned char v_l48;
    unsigned char v_l47;
    unsigned char v_l46;
    unsigned char v_l45;
    unsigned char v_l44;
    unsigned char v_l43;
    unsigned char v_l42;
    unsigned char v_l41;
    int v_l40;
    int v_l36;
    int v_l32;
    int v_l28;
    int dead0[5];
};
struct Fr1_0053aea0 {
    char dead0;
    char dead1;
    unsigned char v_l102;
    unsigned char v_l101;
};
#pragma pack(pop)

// @ 0x0053aea0
extern "C" void __cdecl FUN_0053aea0(int a4, int a8)
{
    Fr0_0053aea0 fb;
    Fr1_0053aea0 fa;
    FUN_0053bd00((unsigned int)a4, (unsigned int)(a8 + 12));
    fb.v_l32 = (int)(int)*(int*)((char*)a8 + 32);
    fb.v_l28 = fb.v_l32;
    FUN_0093aa70((unsigned int)a4, (unsigned int)(int)&fb.v_l28, (unsigned int)1, (unsigned int)0);
    fb.v_l40 = (int)(int)*(int*)((char*)a8 + 36);
    fb.v_l36 = fb.v_l40;
    FUN_0093aa70((unsigned int)a4, (unsigned int)(int)&fb.v_l36, (unsigned int)1, (unsigned int)0);
    ((il2c_vc0*)a4)->s14(a8 + 40, 12);
    fb.v_l42 = (unsigned char)(unsigned char)*(unsigned char*)((char*)a8 + 52);
    fb.v_l41 = (unsigned char)(unsigned char)fb.v_l42;
    FUN_0093a9a0((unsigned int)a4, (unsigned int)(int)(int)&fb.v_l41, (unsigned int)1);
    fb.v_l44 = (unsigned char)(unsigned char)*(unsigned char*)((char*)a8 + 53);
    fb.v_l43 = (unsigned char)(unsigned char)fb.v_l44;
    FUN_0093a9a0((unsigned int)a4, (unsigned int)(int)(int)&fb.v_l43, (unsigned int)1);
    fb.v_l46 = (unsigned char)(unsigned char)*(unsigned char*)((char*)a8 + 54);
    fb.v_l45 = (unsigned char)(unsigned char)fb.v_l46;
    FUN_0093a9a0((unsigned int)a4, (unsigned int)(int)(int)&fb.v_l45, (unsigned int)1);
    fb.v_l48 = (unsigned char)(unsigned char)*(unsigned char*)((char*)a8 + 55);
    fb.v_l47 = (unsigned char)(unsigned char)fb.v_l48;
    FUN_0093a9a0((unsigned int)a4, (unsigned int)(int)(int)&fb.v_l47, (unsigned int)1);
    ((il2c_vc1*)a4)->s14(a8 + 56, 12);
    ((il2c_vc2*)a4)->s14(a8 + 68, 12);
    ((il2c_vc3*)a4)->s14(a8 + 80, 12);
    fb.v_l56 = *(float*)((char*)a8 + 92);
    fb.v_l52 = (float)fb.v_l56;
    FUN_0093aa70((unsigned int)a4, (unsigned int)(int)(int)&fb.v_l52, (unsigned int)1, (unsigned int)0);
    fb.v_l64 = *(float*)((char*)a8 + 96);
    fb.v_l60 = (float)fb.v_l64;
    FUN_0093aa70((unsigned int)a4, (unsigned int)(int)(int)&fb.v_l60, (unsigned int)1, (unsigned int)0);
    fb.v_l72 = *(float*)((char*)a8 + 100);
    fb.v_l68 = (float)fb.v_l72;
    FUN_0093aa70((unsigned int)a4, (unsigned int)(int)(int)&fb.v_l68, (unsigned int)1, (unsigned int)0);
    fb.v_l80 = *(float*)((char*)a8 + 104);
    fb.v_l76 = (float)fb.v_l80;
    FUN_0093aa70((unsigned int)a4, (unsigned int)(int)(int)&fb.v_l76, (unsigned int)1, (unsigned int)0);
    fb.v_l88 = *(float*)((char*)a8 + 108);
    fb.v_l84 = (float)fb.v_l88;
    FUN_0093aa70((unsigned int)a4, (unsigned int)(int)(int)&fb.v_l84, (unsigned int)1, (unsigned int)0);
    fb.v_l96 = (int)(int)*(int*)((char*)a8 + 112);
    fb.v_l92 = fb.v_l96;
    FUN_0093aa70((unsigned int)a4, (unsigned int)(int)&fb.v_l92, (unsigned int)1, (unsigned int)0);
    FUN_0053a930((unsigned int)a4, (unsigned int)(a8 + 116));
    fb.v_l98 = (unsigned char)(unsigned char)*(unsigned char*)((char*)a8 + 176);
    fb.v_l97 = (unsigned char)(unsigned char)fb.v_l98;
    FUN_0093a9a0((unsigned int)a4, (unsigned int)(int)(int)&fb.v_l97, (unsigned int)1);
    fb.v_l100 = (unsigned char)(unsigned char)*(unsigned char*)((char*)a8 + 177);
    fb.v_l99 = (unsigned char)(unsigned char)fb.v_l100;
    FUN_0093a9a0((unsigned int)a4, (unsigned int)(int)(int)&fb.v_l99, (unsigned int)1);
    fa.v_l102 = (unsigned char)(unsigned char)*(unsigned char*)((char*)a8 + 178);
    fa.v_l101 = (unsigned char)(unsigned char)fa.v_l102;
    FUN_0093a9a0((unsigned int)a4, (unsigned int)(int)(int)&fa.v_l101, (unsigned int)1);
    return;
}
