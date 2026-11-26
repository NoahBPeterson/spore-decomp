// 0x00d1bf20: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00d1afe0/s00d1afe0.cpp, src/game/SPGonzago/SPGameEditModeStrategy.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4(int, int, int);
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
    virtual void s14();
    virtual void s15(int);
};

extern "C" unsigned char g_00ebb801[];
extern "C" unsigned char g_01479e3c[];
extern "C" unsigned char g_01479e60[];
extern "C" unsigned char g_01479e78[];
extern "C" unsigned char g_01479e94[];
struct C_00b11870 { void FUN_00b11870(unsigned int); };
struct C_00b32220 { int FUN_00b32220(unsigned int); };
struct C_00b3d230 { int FUN_00b3d230(unsigned int); };
extern "C" int __cdecl FUN_00b3d250(...);
extern "C" int __cdecl FUN_00b3d280(...);
extern "C" int __cdecl FUN_00b3d380(...);
struct C_00b5cde0 { void FUN_00b5cde0(); };
struct C_00d15040 { int FUN_00d15040(); };
struct C_00d1bb60 { int FUN_00d1bb60(); };
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x00d1bf20
extern "C" bool __fastcall FUN_00d1bf20(char* self, int edx_unused)
{
    int t1003;
    int t1006;
    int t1007;
    int t1013;
    int t1014;
    int t1015;
    int t1021;
    int t1022;
    int t1025;
    int t1027;
    int t1032;
    int t1040;
    int t1042;
    int t1049;
    int t1051;
    int t1058;
    int t1059;
    int t1062;
    int t1065;
    int t1066;
    bool t1071;
    t1003 = (int)((int)(self));
    t1006 = (int)((C_00b3d230*)((int)(self)))->FUN_00b3d230((unsigned int)((int)g_00ebb801));
    t1007 = (int)(t1006);
    ((C_00b5cde0*)(t1007))->FUN_00b5cde0();
    t1013 = (int)FUN_00b3d280();
    t1014 = (int)(t1013);
    t1015 = (int)(t1014);
    ((C_00b11870*)(t1015))->FUN_00b11870((unsigned int)((int)1545364305));
    *(int*)((char*)(t1014) + 900) = (int)((int)1001);
    if ((int)*(int*)((char*)(t1003) + 36) == (int)0) {
        t1021 = (int)FUN_00f473a0((unsigned int)((int)280), (unsigned int)((int)g_01479e94), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
        if (t1021 != (int)0) {
            t1022 = (int)(t1021);
            t1025 = (int)((C_00d1bb60*)(t1022))->FUN_00d1bb60();
        } else {
            t1025 = (int)((int)0);
        }
        *(int*)((char*)(t1003) + 36) = (int)(t1025);
        t1027 = (int)(t1025);
        ((il2c_vc0*)(t1027))->s1();
    }
    t1032 = (int)(*(int*)((char*)(t1003) + 36));
    ((il2c_vc1*)(t1032))->s4();
    t1040 = (int)FUN_00b3d250();
    t1042 = (int)(t1040);
    ((il2c_vc2*)(t1042))->s4((int)((int)g_01479e78), (int)((int)0), (int)((int)1));
    t1049 = (int)FUN_00b3d250();
    t1051 = (int)(t1049);
    ((il2c_vc3*)(t1051))->s15((int)((int)g_01479e60));
    if ((int)*(int*)((char*)(t1003) + 40) == (int)0) {
        t1058 = (int)FUN_00f473a0((unsigned int)((int)56), (unsigned int)((int)g_01479e3c), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
        if (t1058 != (int)0) {
            t1059 = (int)(t1058);
            t1062 = (int)((C_00d15040*)(t1059))->FUN_00d15040();
        } else {
            t1062 = (int)((int)0);
        }
        *(int*)((char*)(t1003) + 40) = (int)(t1062);
    }
    t1065 = (int)FUN_00b3d380();
    t1066 = (int)(t1065);
    ((C_00b32220*)(t1066))->FUN_00b32220((unsigned int)((int)79640743));
    t1071 = true;
    return (bool)(t1071);
}
