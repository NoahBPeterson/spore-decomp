// 0x006f9cf0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEngine/SPGraphicsFilterChain.cpp, match/slices/s006f9250/s006f9250.cpp.

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
    virtual void s11(int, int, int);
};

struct C_0067dcc0 { int FUN_0067dcc0(); };
struct C_006f51b0 { void FUN_006f51b0(); };
struct C_006f8190 { void FUN_006f8190(); };
struct C_006f9a50 { int FUN_006f9a50(unsigned int, unsigned int); };
struct C_007c3ba0 { int FUN_007c3ba0(); };
struct C_007c4000 { void FUN_007c4000(); };
extern "C" int __cdecl FUN_00f47380(...);

// @ 0x006f9cf0
extern "C" bool __fastcall FUN_006f9cf0(char* self, int edx_unused)
{
    int t1002;
    int t1005;
    int t1006;
    int t1009;
    int t1014;
    int t1018;
    int t1019;
    int t1023;
    int t1024;
    int t1025;
    int t1032;
    int t1033;
    int t1034;
    int t1038;
    int t1042;
    int t1043;
    int t1049;
    int t1052;
    int t1053;
    int t1059;
    int t1062;
    int t1063;
    int t1069;
    int t1073;
    int t1074;
    bool t1080;
    t1002 = (int)((int)(self));
    t1005 = (int)((C_0067dcc0*)((int)(self)))->FUN_0067dcc0();
    if (t1002 != (int)0) {
        t1006 = (int)(t1002 + (int)4);
    } else {
        t1006 = (int)((int)0);
    }
    t1009 = (int)(t1005);
    ((il2c_vc0*)(t1009))->s11((int)(t1006), (int)((int)72277404), (int)((int)(-9999)));
    t1014 = (int)((int)0);
    goto L6f9d20;
    L6f9d20:;
    t1018 = (int)(*(int*)((char*)(t1002) + 312));
    t1019 = (int)(*(int*)((char*)(t1014) + t1018));
    ((C_006f8190*)(t1019))->FUN_006f8190();
    t1023 = (int)(*(int*)((char*)(t1002) + 312));
    t1024 = (int)(*(int*)((char*)(t1014) + t1023));
    if (t1024 != (int)0) {
        t1025 = (int)(t1024);
        ((C_006f51b0*)(t1025))->FUN_006f51b0();
        FUN_00f47380((unsigned int)(t1024));
    }
    t1014 = (int)(t1014 + (int)4);
    if ((unsigned int)(t1014) < (unsigned int)8) goto L6f9d20;
    t1032 = (int)(*(int*)((char*)(t1002) + 292));
    t1033 = (int)(*(int*)((char*)(t1002) + 288));
    t1034 = (int)(t1002 + (int)288);
    ((C_006f9a50*)(t1034))->FUN_006f9a50((unsigned int)(t1033), (unsigned int)(t1032));
    t1038 = (int)(*(int*)((char*)(t1002) + 372));
    if (t1038 != (int)0) {
        ((C_007c3ba0*)(t1038))->FUN_007c3ba0();
        t1042 = (int)(*(int*)((char*)(t1002) + 372));
        if (t1042 != (int)0) {
            t1043 = (int)(t1042);
            ((C_007c4000*)(t1043))->FUN_007c4000();
            FUN_00f47380((unsigned int)(t1042));
        }
    }
    t1049 = (int)(*(int*)((char*)(t1002) + 376));
    if (t1049 != (int)0) {
        ((C_007c3ba0*)(t1049))->FUN_007c3ba0();
        t1052 = (int)(*(int*)((char*)(t1002) + 376));
        if (t1052 != (int)0) {
            t1053 = (int)(t1052);
            ((C_007c4000*)(t1053))->FUN_007c4000();
            FUN_00f47380((unsigned int)(t1052));
        }
    }
    t1059 = (int)(*(int*)((char*)(t1002) + 380));
    if (t1059 != (int)0) {
        ((C_007c3ba0*)(t1059))->FUN_007c3ba0();
        t1062 = (int)(*(int*)((char*)(t1002) + 380));
        if (t1062 != (int)0) {
            t1063 = (int)(t1062);
            ((C_007c4000*)(t1063))->FUN_007c4000();
            FUN_00f47380((unsigned int)(t1062));
        }
    }
    t1069 = (int)(*(int*)((char*)(t1002) + 384));
    if (t1069 != (int)0) {
        ((C_007c3ba0*)(t1069))->FUN_007c3ba0();
        t1073 = (int)(*(int*)((char*)(t1002) + 384));
        if (t1073 != (int)0) {
            t1074 = (int)(t1073);
            ((C_007c4000*)(t1074))->FUN_007c4000();
            FUN_00f47380((unsigned int)(t1073));
        }
    }
    t1080 = true;
    return (bool)(t1080);
}
