// 0x0053b930: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0053b930/s0053b930.cpp, src/game/SPBake/SPSkinPaintParticleDescription.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6(int, int);
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6(int, int);
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6(int, int);
};
struct il2c_vc3 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6(int, int);
};
struct il2c_vc4 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6(int, int);
};
struct il2c_vc5 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6(int, int);
};
struct il2c_vc6 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6(int, int);
};
struct il2c_vc7 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual int s6(int, int);
};

extern "C" unsigned char g_013f2424[];
extern "C" unsigned char g_013f2b7c[];
extern "C" unsigned char g_013f2ba4[];
extern "C" unsigned char g_013f2bcc[];
extern "C" unsigned char g_013f2be4[];
extern "C" unsigned char g_013f2bec[];
extern "C" unsigned char g_013f2bf4[];
extern "C" unsigned char g_013f2bfc[];
extern "C" unsigned char g_013f2c04[];
extern "C" unsigned char g_013f2c34[];
extern "C" unsigned char g_013f2c58[];
extern "C" unsigned char g_013f2c8c[];
extern "C" unsigned char g_013f2e78[];
extern "C" unsigned char g_013f33b8[];
extern "C" unsigned char g_013f33d0[];
extern "C" unsigned char g_013f33e8[];
extern "C" unsigned char g_013f340c[];
struct C_0053b1f0 { void FUN_0053b1f0(); };
struct C_0053cca0 { void FUN_0053cca0(); };
extern "C" int __cdecl FUN_00f473a0(...);
#pragma pack(push, 1)
struct Fr0_0053b930 {
    int v_l68;
    int v_l64;
    int v_l60;
    int v_l56;
    int v_l52;
    int v_l48;
    int v_l44;
    int v_l40;
    int v_l36;
    int v_l32;
    int v_l28;
    int v_l24;
    int v_l20;
    int v_l16;
    int v_l12;
    int v_l8;
};
struct Fr1_0053b930 {
    int v_l72;
};
#pragma pack(pop)

// @ 0x0053b930
extern "C" void __cdecl FUN_0053b930(int a4)
{
    Fr0_0053b930 fb;
    Fr1_0053b930 fa;
    fb.v_l8 = 0;
    for (; fb.v_l8 < 19; fb.v_l8 = fb.v_l8 + 1) {
        fb.v_l12 = (int)(int)FUN_00f473a0((unsigned int)20, (unsigned int)(int)g_013f2c8c, (unsigned int)0, (unsigned int)0, (unsigned int)0, (unsigned int)0);
        if (fb.v_l12 != 0) {
            ((C_0053b1f0*)fb.v_l12)->FUN_0053b1f0();
            *(int*)(char*)fb.v_l12 = (int)g_013f2424;
            *(int*)(char*)fb.v_l12 = (int)g_013f340c;
            *(int*)((char*)fb.v_l12 + 16) = fb.v_l8;
            fb.v_l44 = fb.v_l12;
        } else {
            fb.v_l44 = 0;
        }
        ((il2c_vc0*)a4)->s6((int)(int)*(int*)((char*)(fb.v_l8 * 4) + (int)g_013f2e78), fb.v_l44);
    }
    fb.v_l16 = (int)(int)FUN_00f473a0((unsigned int)52, (unsigned int)(int)g_013f2c58, (unsigned int)0, (unsigned int)0, (unsigned int)0, (unsigned int)0);
    if (fb.v_l16 != 0) {
        ((C_0053cca0*)fb.v_l16)->FUN_0053cca0();
        *(int*)(char*)fb.v_l16 = (int)g_013f2c34;
        *(int*)(char*)fb.v_l16 = (int)g_013f33e8;
        fb.v_l48 = fb.v_l16;
    } else {
        fb.v_l48 = 0;
    }
    ((il2c_vc1*)a4)->s6((int)g_013f2c04, fb.v_l48);
    fb.v_l20 = (int)(int)FUN_00f473a0((unsigned int)20, (unsigned int)(int)g_013f2c8c, (unsigned int)0, (unsigned int)0, (unsigned int)0, (unsigned int)0);
    if (fb.v_l20 != 0) {
        ((C_0053b1f0*)fb.v_l20)->FUN_0053b1f0();
        *(int*)(char*)fb.v_l20 = (int)g_013f2424;
        *(int*)(char*)fb.v_l20 = (int)g_013f340c;
        *(int*)((char*)fb.v_l20 + 16) = 2;
        fb.v_l52 = fb.v_l20;
    } else {
        fb.v_l52 = 0;
    }
    ((il2c_vc2*)a4)->s6((int)g_013f2bfc, fb.v_l52);
    fb.v_l24 = (int)(int)FUN_00f473a0((unsigned int)20, (unsigned int)(int)g_013f2c8c, (unsigned int)0, (unsigned int)0, (unsigned int)0, (unsigned int)0);
    if (fb.v_l24 != 0) {
        ((C_0053b1f0*)fb.v_l24)->FUN_0053b1f0();
        *(int*)(char*)fb.v_l24 = (int)g_013f2424;
        *(int*)(char*)fb.v_l24 = (int)g_013f340c;
        *(int*)((char*)fb.v_l24 + 16) = 7;
        fb.v_l56 = fb.v_l24;
    } else {
        fb.v_l56 = 0;
    }
    ((il2c_vc3*)a4)->s6((int)g_013f2bf4, fb.v_l56);
    fb.v_l28 = (int)(int)FUN_00f473a0((unsigned int)20, (unsigned int)(int)g_013f2c8c, (unsigned int)0, (unsigned int)0, (unsigned int)0, (unsigned int)0);
    if (fb.v_l28 != 0) {
        ((C_0053b1f0*)fb.v_l28)->FUN_0053b1f0();
        *(int*)(char*)fb.v_l28 = (int)g_013f2424;
        *(int*)(char*)fb.v_l28 = (int)g_013f340c;
        *(int*)((char*)fb.v_l28 + 16) = 8;
        fb.v_l60 = fb.v_l28;
    } else {
        fb.v_l60 = 0;
    }
    ((il2c_vc4*)a4)->s6((int)g_013f2bec, fb.v_l60);
    fb.v_l32 = (int)(int)FUN_00f473a0((unsigned int)20, (unsigned int)(int)g_013f2c8c, (unsigned int)0, (unsigned int)0, (unsigned int)0, (unsigned int)0);
    if (fb.v_l32 != 0) {
        ((C_0053b1f0*)fb.v_l32)->FUN_0053b1f0();
        *(int*)(char*)fb.v_l32 = (int)g_013f2424;
        *(int*)(char*)fb.v_l32 = (int)g_013f340c;
        *(int*)((char*)fb.v_l32 + 16) = 9;
        fb.v_l64 = fb.v_l32;
    } else {
        fb.v_l64 = 0;
    }
    ((il2c_vc5*)a4)->s6((int)g_013f2be4, fb.v_l64);
    fb.v_l36 = (int)(int)FUN_00f473a0((unsigned int)16, (unsigned int)(int)g_013f2bcc, (unsigned int)0, (unsigned int)0, (unsigned int)0, (unsigned int)0);
    if (fb.v_l36 != 0) {
        ((C_0053b1f0*)fb.v_l36)->FUN_0053b1f0();
        *(int*)(char*)fb.v_l36 = (int)g_013f2424;
        *(int*)(char*)fb.v_l36 = (int)g_013f33d0;
        fb.v_l68 = fb.v_l36;
    } else {
        fb.v_l68 = 0;
    }
    ((il2c_vc6*)a4)->s6((int)g_013f2ba4, fb.v_l68);
    fb.v_l40 = (int)(int)FUN_00f473a0((unsigned int)16, (unsigned int)(int)g_013f2bcc, (unsigned int)0, (unsigned int)0, (unsigned int)0, (unsigned int)0);
    if (fb.v_l40 != 0) {
        ((C_0053b1f0*)fb.v_l40)->FUN_0053b1f0();
        *(int*)(char*)fb.v_l40 = (int)g_013f2424;
        *(int*)(char*)fb.v_l40 = (int)g_013f33b8;
        fa.v_l72 = fb.v_l40;
    } else {
        fa.v_l72 = 0;
    }
    ((il2c_vc7*)a4)->s6((int)g_013f2b7c, fa.v_l72);
    return;
}
