// 0x007e6470: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEngine/SPAppSystem.cpp, match/slices/s007e6210/s007e6210.cpp.

extern "C" void __cdecl FUN_00f62add(...);
struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc3 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7(int);
};
struct il2c_vc4 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7(int);
};
struct il2c_vc5 {
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
struct il2c_vc6 {
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
struct il2c_vc7 {
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
struct il2c_vc8 {
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
    virtual int s11(int, int, int);
};
struct il2c_vc9 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
};
struct il2c_vc10 {
    virtual void s0();
    virtual int s1();
};
struct il2c_vc11 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
};
struct il2c_vc12 {
    virtual void s0();
    virtual int s1();
};
struct il2c_vc13 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual int s4();
};

extern "C" unsigned char g_0153f85c[];
extern "C" unsigned char g_0153f860[];
extern "C" int __cdecl FUN_0067de20(...);
extern "C" int __cdecl FUN_0067df00(...);
extern "C" int __cdecl FUN_0067df30(...);
extern "C" void __cdecl FUN_0067e090(...);
struct C_0068c460 { void FUN_0068c460(); };
struct C_006ae940 { void FUN_006ae940(); };
extern "C" void __cdecl FUN_00762f00(...);
extern "C" void __cdecl FUN_007c79e0(...);
extern "C" void __cdecl FUN_008d5d10(...);
extern "C" void __cdecl FUN_00c2e4e0(...);

// @ 0x007e6470
extern "C" bool __fastcall FUN_007e6470(char* self, int edx_unused)
{
    int t1003;
    int t1004;
    int t1010;
    int t1011;
    int t1023;
    int t1027;
    int t1036;
    int t1041;
    int t1044;
    int t1047;
    int t1051;
    int t1054;
    int t1057;
    int t1067;
    int t1070;
    int t1074;
    int t1080;
    int t1086;
    int t1092;
    int t1101;
    int t1106;
    int t1114;
    int t1119;
    bool t1126;
    t1003 = (int)((int)(self));
    t1004 = (int)(*(int*)((char*)(t1003) + 200));
    ((il2c_vc0*)(t1004))->s7();
    t1010 = (int)(*(int*)((char*)(t1003) + 64));
    t1011 = (int)((int)0);
    if (t1010 != t1011) {
        ((il2c_vc1*)(t1010))->s2();
        *(int*)((char*)(t1003) + 68) = (int)(t1011);
    }
    if ((int)*(int*)((char*)(t1003) + 32) != t1011) {
        FUN_008d5d10((unsigned int)(t1011));
        FUN_0067e090((unsigned int)(t1011));
        t1023 = (int)(*(int*)((char*)(t1003) + 32));
        ((C_006ae940*)(t1023))->FUN_006ae940();
        t1027 = (int)(*(int*)((char*)(t1003) + 32));
        ((il2c_vc2*)(t1027))->s1();
        *(int*)((char*)(t1003) + 32) = (int)(t1011);
    }
    if ((int)*(int*)((char*)(t1003) + 80) != t1011) {
        FUN_00762f00((unsigned int)(t1011));
        t1036 = (int)(*(int*)((char*)(t1003) + 80));
        ((C_0068c460*)(t1036))->FUN_0068c460();
    }
    t1041 = (int)FUN_0067de20();
    t1044 = (int)((int)(*(int*)g_0153f85c));
    t1047 = (int)(t1041);
    ((il2c_vc3*)(t1047))->s7((int)(t1044));
    t1051 = (int)FUN_0067de20();
    t1054 = (int)((int)(*(int*)g_0153f860));
    t1057 = (int)(t1051);
    ((il2c_vc4*)(t1057))->s7((int)(t1054));
    FUN_007c79e0();
    FUN_00c2e4e0();
    t1067 = (int)(*(int*)((char*)(t1003) + 20));
    t1070 = (int)(t1003 + (int)4);
    ((il2c_vc5*)(t1067))->s11((int)(t1070), (int)((int)&FUN_00f62add), (int)((int)(-9999)));
    t1074 = (int)(*(int*)((char*)(t1003) + 20));
    ((il2c_vc6*)(t1074))->s11((int)(t1070), (int)((int)(-1373831565)), (int)((int)(-9999)));
    t1080 = (int)(*(int*)((char*)(t1003) + 20));
    ((il2c_vc7*)(t1080))->s11((int)(t1070), (int)((int)39169013), (int)((int)(-9999)));
    t1086 = (int)(*(int*)((char*)(t1003) + 20));
    ((il2c_vc8*)(t1086))->s11((int)(t1070), (int)((int)34788327), (int)((int)(-9999)));
    t1092 = (int)(*(int*)((char*)(t1003) + 200));
    if (t1092 != t1011) {
        ((il2c_vc9*)(t1092))->s4();
        FUN_0067df00((unsigned int)(t1011));
        t1101 = (int)(*(int*)((char*)(t1003) + 200));
        if (t1101 != t1011) {
            *(int*)((char*)(t1003) + 200) = (int)(t1011);
            ((il2c_vc10*)(t1101))->s1();
        }
    }
    t1106 = (int)(*(int*)((char*)(t1003) + 52));
    if (t1106 != t1011) {
        ((il2c_vc11*)(t1106))->s5();
        FUN_0067df30((unsigned int)(t1011));
        t1114 = (int)(*(int*)((char*)(t1003) + 52));
        if (t1114 != t1011) {
            *(int*)((char*)(t1003) + 52) = (int)(t1011);
            ((il2c_vc12*)(t1114))->s1();
        }
    }
    t1119 = (int)(*(int*)((char*)(t1003) + 92));
    if (t1119 != t1011) {
        ((il2c_vc13*)(t1119))->s4();
    }
    t1126 = true;
    return (bool)(t1126);
}
