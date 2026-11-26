// 0x0070ddd0: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0070ced0/s0070ced0.cpp, src/game/SPEngine/SPGraphicsLightingManager.cpp.

// lifted by il2c_lift + l2c_search (swap@34); CI scorer MATCH; corpus status nonmatching/residual
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

extern "C" unsigned char g_00f62def[];
struct C_0067dcc0 { int FUN_0067dcc0(); };
struct C_00707690 { void FUN_00707690(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00708ec0(...);
struct C_0070a3f0 { void FUN_0070a3f0(); };
extern "C" int __cdecl FUN_00921580(...);
struct C_00d0c930 { void FUN_00d0c930(unsigned int); };

// @ 0x0070ddd0
extern "C" bool __fastcall FUN_0070ddd0(char* self, int edx_unused)
{
    int t1004;
    int t1005;
    int t1008;
    int t1010;
    int t1015;
    int t1017;
    int t1018;
    int t1019;
    int t1022;
    int t1023;
    int t1027;
    int t1034;
    int t1035;
    int t1036;
    int t1037;
    int t1039;
    int t1043;
    int t1046;
    int t1047;
    int t1048;
    int t1052;
    int t1053;
    bool t1056;
    t1004 = (int)((int)(self));
    t1005 = (int)((C_0067dcc0*)((int)(self)))->FUN_0067dcc0();
    if (t1005 != (int)0) {
        if (t1004 != (int)0) {
            t1008 = (int)(t1004 + (int)4);
        } else {
            t1008 = (int)((int)0);
        }
        t1010 = (int)(t1005);
        ((il2c_vc0*)(t1010))->s11((int)(t1008), (int)((int)g_00f62def), (int)((int)(-9999)));
    }
    t1017 = (int)(*(int*)((char*)(t1004) + 24));
    t1015 = (int)(*(int*)((char*)(t1004) + 28));
    t1018 = (int)(t1004 + (int)24);
    t1019 = (int)FUN_00708ec0((unsigned int)(t1015), (unsigned int)(t1015), (unsigned int)(t1017));
    t1022 = (int)(*(int*)((char*)(t1018) + 4));
    t1023 = (int)(t1018);
    ((C_00707690*)(t1023))->FUN_00707690((unsigned int)(t1019), (unsigned int)(t1022));
    t1027 = (int)(t1015 - t1017);
    t1034 = (int)(t1027 / (int)(-324));
    t1035 = (int)(t1034 * (int)324);
    *(int*)((char*)(t1018) + 4) += t1035;
    t1036 = (int)(*(int*)((char*)(t1004) + 52));
    t1037 = (int)(t1004 + (int)48);
    if (t1036 != t1037) {
        do {
            t1039 = (int)(*(int*)((char*)(t1036) + 20));
            ((C_0070a3f0*)(t1039))->FUN_0070a3f0();
            t1043 = (int)FUN_00921580((unsigned int)(t1036));
            t1036 = (int)(t1043);
        } while (t1036 != t1037);
    }
    t1046 = (int)(*(int*)((char*)(t1004) + 56));
    t1047 = (int)(t1004 + (int)44);
    t1048 = (int)(t1047);
    ((C_00d0c930*)(t1048))->FUN_00d0c930((unsigned int)(t1046));
    t1052 = (int)(t1047 + (int)4);
    *(int*)((char*)(t1047) + 8) = (int)(t1052);
    *(int*)((char*)(t1052)) = (int)(t1052);
    t1053 = (int)((int)0);
    *(int*)((char*)(t1047) + 12) = (int)(t1053);
    *(unsigned char*)((char*)(t1047) + 16) = (unsigned char)((unsigned char)(t1053));
    *(int*)((char*)(t1047) + 20) = (int)(t1053);
    t1056 = true;
    return (bool)(t1056);
}
