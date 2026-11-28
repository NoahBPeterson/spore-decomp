// 0x00d07770: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/_at_00d00000.cpp, match/slices/s00d07770/s00d07770.cpp.

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
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual void s29();
    virtual void s30();
    virtual void s31();
    virtual void s32(int);
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
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual void s29();
    virtual void s30();
    virtual void s31();
    virtual void s32(int);
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
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual void s29();
    virtual void s30();
    virtual void s31();
    virtual int s32(int);
};

extern "C" unsigned char g_013f01bc[];
struct C_008105b0 { int FUN_008105b0(unsigned int, unsigned int); };
extern "C" void __cdecl FUN_009399c0(...);
struct C_00b25f40 { int FUN_00b25f40(); };
struct C_00b3d300 { int FUN_00b3d300(unsigned int); };
struct C_00bf0c60 { int FUN_00bf0c60(unsigned int, unsigned int, unsigned int, unsigned int); };

// @ 0x00d07770
extern "C" void __fastcall FUN_00d07770(char* self, int edx_unused)
{
    int t1003;
    int t1004;
    int t1005;
    int t1006;
    int t1009;
    int t1010;
    int t1013;
    int t1016;
    int t1017;
    int t1020;
    int t1021;
    int t1022;
    int t1025;
    int t1026;
    int t1027;
    int t1030;
    int v_l68;
    int t1031;
    int t1034;
    int t1035;
    int v_l64[16];
    int t1041;
    int t1042;
    int t1046;
    int t1047;
    int t1050;
    int t1051;
    int t1057;
    int t1058;
    int t1062;
    int t1063;
    int t1066;
    int t1069;
    int t1070;
    int t1076;
    int t1077;
    t1003 = (int)((int)(self));
    t1004 = (int)(*(int*)((char*)(t1003) + 8));
    t1005 = (int)(*(int*)((char*)(t1004) + 132));
    t1006 = (int)((C_00b3d300*)((int)(self)))->FUN_00b3d300((unsigned int)(t1005));
    t1009 = (int)(t1006);
    t1010 = (int)((C_00b25f40*)(t1009))->FUN_00b25f40();
    t1013 = (int)(t1010);
    if (t1013 != (int)0) {
        t1016 = (int)(t1013);
        t1017 = (int)((C_00bf0c60*)(t1016))->FUN_00bf0c60((unsigned int)((int)2), (unsigned int)((int)(-1)), (unsigned int)((int)0), (unsigned int)((int)0));
        t1020 = (int)(t1013);
        t1021 = (int)(t1017);
        t1022 = (int)((C_00bf0c60*)(t1020))->FUN_00bf0c60((unsigned int)((int)2), (unsigned int)((int)(-1)), (unsigned int)((int)1), (unsigned int)((int)0));
        t1025 = (int)(t1013);
        t1026 = (int)(t1022);
        t1027 = (int)((C_00bf0c60*)(t1025))->FUN_00bf0c60((unsigned int)((int)2), (unsigned int)((int)(-1)), (unsigned int)((int)2), (unsigned int)((int)0));
        t1030 = (int)(*(int*)((char*)(t1003) + 4));
        v_l68 = (int)(t1027);
        t1031 = (int)((C_008105b0*)(t1030))->FUN_008105b0((unsigned int)((int)103248109), (unsigned int)((int)1));
        t1034 = (int)(t1031);
        if (t1034 != (int)0) {
            t1035 = (int)((int)&v_l64);
            FUN_009399c0((unsigned int)(t1035), (unsigned int)((int)g_013f01bc), (unsigned int)(t1021));
            t1041 = (int)((int)&v_l64);
            t1042 = (int)(t1034);
            ((il2c_vc0*)(t1042))->s32((int)(t1041));
        }
        t1046 = (int)(*(int*)((char*)(t1003) + 4));
        t1047 = (int)((C_008105b0*)(t1046))->FUN_008105b0((unsigned int)((int)103248110), (unsigned int)((int)1));
        t1050 = (int)(t1047);
        if (t1050 != (int)0) {
            t1051 = (int)((int)&v_l64);
            FUN_009399c0((unsigned int)(t1051), (unsigned int)((int)g_013f01bc), (unsigned int)(t1026));
            t1057 = (int)((int)&v_l64);
            t1058 = (int)(t1050);
            ((il2c_vc1*)(t1058))->s32((int)(t1057));
        }
        t1062 = (int)(*(int*)((char*)(t1003) + 4));
        t1063 = (int)(t1062);
        t1010 = (int)((C_008105b0*)(t1063))->FUN_008105b0((unsigned int)((int)103248111), (unsigned int)((int)1));
        t1066 = (int)(t1010);
        if (t1066 != (int)0) {
            t1069 = (int)(v_l68);
            t1070 = (int)((int)&v_l64);
            FUN_009399c0((unsigned int)(t1070), (unsigned int)((int)g_013f01bc), (unsigned int)(t1069));
            t1076 = (int)((int)&v_l64);
            t1077 = (int)(t1066);
            t1010 = (int)((il2c_vc2*)(t1077))->s32((int)(t1076));
        }
    }
    return;
}
