// 0x0080ead0: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/Spui/SPUILayers.cpp, match/slices/s0080e6b0/s0080e6b0.cpp.

// lifted by il2c_lift + l2c_search (ref@t1004); CI scorer MATCH; corpus status nonmatching/residual
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
    virtual void s32();
    virtual void s33();
    virtual void s34();
    virtual void s35();
    virtual void s36();
    virtual void s37();
    virtual void s38();
    virtual void s39();
    virtual void s40();
    virtual void s41();
    virtual void s42();
    virtual void s43();
    virtual void s44();
    virtual void s45();
    virtual void s46();
    virtual void s47();
    virtual void s48();
    virtual void s49();
    virtual void s50();
    virtual void s51();
    virtual void s52();
    virtual void s53();
    virtual void s54();
    virtual void s55();
    virtual void s56();
    virtual void s57();
    virtual void s58();
    virtual void s59();
    virtual void s60();
    virtual void s61();
    virtual void s62();
    virtual void s63();
    virtual void s64();
    virtual void s65();
    virtual void s66(int);
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc3 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc4 {
    virtual void s0();
    virtual int s1();
};
struct il2c_vc5 {
    virtual void s0();
    virtual int s1();
};

extern "C" unsigned char g_013ec458[];
extern "C" unsigned char g_01417dc4[];
struct C_005f3680 { int FUN_005f3680(unsigned int, unsigned int); };
struct C_007c3ba0 { void FUN_007c3ba0(); };
struct C_007c4000 { void FUN_007c4000(); };
struct C_0080e980 { void FUN_0080e980(unsigned int); };
extern "C" int __cdecl FUN_00f47380(...);

// @ 0x0080ead0
extern "C" void __fastcall FUN_0080ead0(char* self, int edx_unused)
{
    int t1002;
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1012;
    int t1013;
    int t1019;
    int t1020;
    int t1021;
    int t1028;
    int t1030;
    int t1035;
    int t1041;
    int t1047;
    int t1053;
    int t1054;
    int t1055;
    int t1059;
    int t1062;
    int t1067;
    t1002 = (int)((int)(self));
    t1004 = (int)(t1002 + (int)20);
    int& t1004_r = t1004;
    *(int*)((char*)(t1002)) = (int)((int)g_01417dc4);
    t1005 = (int)(*(int*)((char*)(t1004_r)));
    if (t1005 != (int)*(int*)((char*)(t1004_r) + 4)) {
        do {
            t1006 = (int)(*(int*)((char*)(t1004_r)));
            t1007 = (int)(*(int*)((char*)(t1006)));
            t1008 = (int)(t1002);
            ((C_0080e980*)(t1008))->FUN_0080e980((unsigned int)(t1007));
            t1012 = (int)(*(int*)((char*)(t1004_r)));
        } while (t1012 != (int)*(int*)((char*)(t1004_r) + 4));
    }
    t1013 = (int)(*(int*)((char*)(t1002) + 8));
    ((C_007c3ba0*)(t1013))->FUN_007c3ba0();
    t1019 = (int)(*(int*)((char*)(t1002) + 8));
    t1020 = (int)((int)0);
    if (t1019 != t1020) {
        t1021 = (int)(t1019);
        ((C_007c4000*)(t1021))->FUN_007c4000();
        FUN_00f47380((unsigned int)(t1019));
    }
    t1028 = (int)(*(int*)((char*)(t1002) + 12));
    *(int*)((char*)(t1002) + 8) = (int)(t1020);
    if (t1028 != t1020) {
        if ((unsigned char)*(unsigned char*)((char*)(t1002) + 116) != (unsigned char)(t1020)) {
            t1030 = (int)(*(int*)((char*)(t1002) + 16));
            ((il2c_vc0*)(t1028))->s66((int)(t1030));
        }
        t1035 = (int)(*(int*)((char*)(t1002) + 12));
        if (t1035 != t1020) {
            *(int*)((char*)(t1002) + 12) = (int)(t1020);
            ((il2c_vc1*)(t1035))->s1();
        }
        *(unsigned char*)((char*)(t1002) + 116) = (unsigned char)((unsigned char)(t1020));
    }
    t1041 = (int)(*(int*)((char*)(t1002) + 16));
    if (t1041 != t1020) {
        *(int*)((char*)(t1002) + 16) = (int)(t1020);
        ((il2c_vc2*)(t1041))->s1();
    }
    t1047 = (int)(*(int*)((char*)(t1002) + 40));
    if (t1047 != t1020) {
        ((il2c_vc3*)(t1047))->s1();
    }
    t1053 = (int)(*(int*)((char*)(t1004_r) + 4));
    t1054 = (int)(*(int*)((char*)(t1004_r)));
    t1055 = (int)(t1004_r);
    ((C_005f3680*)(t1055))->FUN_005f3680((unsigned int)(t1054), (unsigned int)(t1053));
    t1059 = (int)(*(int*)((char*)(t1004_r)));
    if (t1059 != t1020) {
        if ((int)*(int*)((char*)(t1059) - 4) != t1020) {
            FUN_00f47380((unsigned int)(t1059));
        }
    }
    t1062 = (int)(*(int*)((char*)(t1002) + 16));
    if (t1062 != t1020) {
        ((il2c_vc4*)(t1062))->s1();
    }
    t1067 = (int)(*(int*)((char*)(t1002) + 12));
    if (t1067 != t1020) {
        ((il2c_vc5*)(t1067))->s1();
    }
    *(int*)((char*)(t1002)) = (int)((int)g_013ec458);
    return;
}
