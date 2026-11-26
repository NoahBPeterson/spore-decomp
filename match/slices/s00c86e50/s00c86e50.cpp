// 0x00c86e50: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00c86aa0/s00c86aa0.cpp, src/game/SPGonzago/SPSolarSystem.cpp.

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
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
};

struct C_005f3680 { int FUN_005f3680(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_005f4e10(...);
struct C_00b48e40 { void FUN_00b48e40(unsigned int, unsigned int); };
struct C_00c86c70 { void FUN_00c86c70(unsigned int); };
struct C_00e25bd0 { void FUN_00e25bd0(unsigned int, unsigned int); };

// @ 0x00c86e50
extern "C" void __fastcall FUN_00c86e50(char* self, int edx_unused)
{
    int t1004;
    int t1008;
    int t1009;
    int t1010;
    int t1016;
    int t1017;
    int t1018;
    int t1022;
    int t1023;
    int t1024;
    int t1028;
    int t1034;
    int t1040;
    int t1041;
    int t1042;
    int t1044;
    int t1046;
    int t1047;
    int t1051;
    int t1052;
    int t1053;
    int t1054;
    int t1055;
    t1004 = (int)((int)(self));
    int& t1004_r = t1004;
    ((C_00c86c70*)((int)(self)))->FUN_00c86c70((unsigned int)((int)0));
    t1008 = (int)(*(int*)((char*)(t1004_r) + 36));
    t1009 = (int)(t1004_r + (int)36);
    if (t1008 != (int)*(int*)((char*)(t1004_r) + 40)) {
        do {
            t1010 = (int)(*(int*)((char*)(t1008)));
            ((il2c_vc0*)(t1010))->s17();
            t1008 = (int)(t1008 + (int)4);
        } while (t1008 != (int)*(int*)((char*)(t1004_r) + 40));
    }
    t1016 = (int)(*(int*)((char*)(t1009) + 4));
    t1017 = (int)(*(int*)((char*)(t1009)));
    t1018 = (int)(t1009);
    ((C_00e25bd0*)(t1018))->FUN_00e25bd0((unsigned int)(t1017), (unsigned int)(t1016));
    t1022 = (int)(*(int*)((char*)(t1004_r) + 20));
    t1023 = (int)(*(int*)((char*)(t1004_r) + 16));
    t1024 = (int)(t1004_r + (int)16);
    ((C_00b48e40*)(t1024))->FUN_00b48e40((unsigned int)(t1023), (unsigned int)(t1022));
    *(int*)((char*)(t1004_r) + 12) = (int)((int)0);
    t1028 = (int)(*(int*)((char*)(t1004_r) + 56));
    if (t1028 != (int)0) {
        *(int*)((char*)(t1004_r) + 56) = (int)((int)0);
        ((il2c_vc1*)(t1028))->s1();
    }
    t1034 = (int)(*(int*)((char*)(t1004_r) + 60));
    if (t1034 != (int)0) {
        *(int*)((char*)(t1004_r) + 60) = (int)((int)0);
        ((il2c_vc2*)(t1034))->s1();
    }
    t1040 = (int)(*(int*)((char*)(t1004_r) + 64));
    t1041 = (int)(t1004_r + (int)64);
    t1042 = (int)(*(int*)((char*)(t1041) + 4));
    t1044 = (int)FUN_005f4e10((unsigned int)(t1042), (unsigned int)(t1042), (unsigned int)(t1040));
    t1046 = (int)(*(int*)((char*)(t1041) + 4));
    t1047 = (int)(t1041);
    ((C_005f3680*)(t1047))->FUN_005f3680((unsigned int)(t1044), (unsigned int)(t1046));
    t1051 = (int)(t1042 - t1040);
    t1052 = (int)(t1051 >> (int)2);
    t1053 = (int)(-t1052);
    t1054 = (int)(t1053 + t1053);
    t1055 = (int)(t1054 + t1054);
    *(int*)((char*)(t1041) + 4) += t1055;
    return;
}
