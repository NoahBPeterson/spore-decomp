// 0x00e81ba0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00e819b0/s00e819b0.cpp.

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
    virtual void s12(int, int, int);
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
    virtual void s12(int, int, int);
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
};
struct il2c_vc3 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc4 {
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
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20(int);
};
struct il2c_vc5 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc6 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6(int);
};
struct il2c_vc7 {
    virtual void s0();
    virtual void s1();
};

extern "C" unsigned char g_00e7f960[];
extern "C" unsigned char g_00e809a0[];
extern "C" unsigned char g_01010050[];
extern "C" unsigned char g_01010051[];
extern "C" unsigned char g_016b3c04[];
extern "C" unsigned char g_016b3c08[];
extern "C" int __cdecl FUN_0067dcc0(...);
extern "C" int __cdecl FUN_0067dd80(...);
extern "C" int __cdecl FUN_0067ddd0(...);
extern "C" int __cdecl FUN_00e4ce20(...);
extern "C" void __cdecl FUN_00e548d0(...);
struct C_00e661c0 { void FUN_00e661c0(); };
extern "C" void __cdecl FUN_00e66980(...);
extern "C" void __cdecl FUN_00e7f9b0(...);

// @ 0x00e81ba0
extern "C" void __cdecl FUN_00e81ba0(void)
{
    int t1004;
    int t1006;
    int t1013;
    int t1015;
    int t1029;
    int t1033;
    int t1034;
    int t1040;
    int t1041;
    int t1042;
    int t1050;
    int t1052;
    int t1057;
    int t1058;
    int t1066;
    int t1068;
    int t1073;
    int t1074;
    int t1083;
    t1004 = (int)FUN_0067dcc0();
    t1006 = (int)(t1004);
    ((il2c_vc0*)(t1006))->s12((int)((int)g_00e7f960), (int)((int)71694121), (int)((int)(-9999)));
    t1013 = (int)FUN_0067dcc0();
    t1015 = (int)(t1013);
    ((il2c_vc1*)(t1015))->s12((int)((int)g_00e809a0), (int)((int)51122631), (int)((int)(-9999)));
    FUN_00e7f9b0();
    FUN_00e548d0();
    FUN_00e66980();
    t1029 = (int)((int)(*(int*)g_016b3c08));
    ((C_00e661c0*)(t1029))->FUN_00e661c0();
    t1033 = (int)((int)(*(int*)g_016b3c08));
    t1034 = (int)(*(int*)((char*)(t1033) + 88));
    ((il2c_vc2*)(t1034))->s8();
    t1040 = (int)((int)(*(int*)g_016b3c08));
    t1041 = (int)(*(int*)((char*)(t1040) + 88));
    t1042 = (int)((int)0);
    if (t1041 != t1042) {
        *(int*)((char*)(t1040) + 88) = (int)(t1042);
        ((il2c_vc3*)(t1041))->s1();
    }
    t1050 = (int)FUN_0067ddd0();
    t1052 = (int)(t1050);
    ((il2c_vc4*)(t1052))->s20((int)((int)g_01010051));
    t1057 = (int)((int)(*(int*)g_016b3c08));
    t1058 = (int)(*(int*)((char*)(t1057) + 80));
    if (t1058 != t1042) {
        *(int*)((char*)(t1057) + 80) = (int)(t1042);
        ((il2c_vc5*)(t1058))->s1();
    }
    t1066 = (int)FUN_0067dd80();
    t1068 = (int)(t1066);
    ((il2c_vc6*)(t1068))->s6((int)((int)g_01010050));
    t1073 = (int)((int)(*(int*)g_016b3c08));
    t1074 = (int)(*(int*)((char*)(t1073) + 84));
    if (t1074 != t1042) {
        *(int*)((char*)(t1073) + 84) = (int)(t1042);
        ((il2c_vc7*)(t1074))->s1();
    }
    FUN_00e4ce20();
    t1083 = (int)((int)(*(int*)g_016b3c04));
    *(unsigned char*)((char*)(t1083) + 16673) = (unsigned char)((unsigned char)(t1042));
    return;
}
