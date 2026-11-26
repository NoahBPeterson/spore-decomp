// 0x00bd7b90: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00bd70b0/s00bd70b0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual int s8();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual int s6();
};

extern "C" unsigned char g_0156e2a0[];
struct C_00692f90 { void FUN_00692f90(unsigned int, unsigned int, unsigned int); };
struct C_00693e10 { int FUN_00693e10(unsigned int); };
extern "C" void __cdecl FUN_0093a780(...);
struct C_00b18600 { int FUN_00b18600(unsigned int); };
struct C_00bfc540 { int FUN_00bfc540(unsigned int); };
struct C_00c88b00 { int FUN_00c88b00(unsigned int); };

// @ 0x00bd7b90
extern "C" bool __fastcall FUN_00bd7b90(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1007;
    int t1008;
    int t1011;
    int t1013;
    int t1017;
    int t1018;
    int v_l2584;
    int t1022;
    unsigned char t1023;
    int t1026;
    unsigned char t1027;
    int t1028;
    int t1031;
    unsigned char t1032;
    int t1033;
    int t1036;
    unsigned char t1037;
    int t1038;
    int v_l2580[645];
    int t1042;
    int t1045;
    bool t1048;
    bool t1052;
    t1002 = (int)((int)(a4));
    t1007 = (int)((int)(self));
    t1008 = (int)(t1002);
    t1011 = (int)((il2c_vc0*)(t1008))->s8();
    t1013 = (int)(t1011);
    t1017 = (int)((il2c_vc1*)(t1013))->s6();
    t1018 = (int)((int)&v_l2584);
    FUN_0093a780((unsigned int)(t1017), (unsigned int)(t1018), (unsigned int)((int)1), (unsigned int)((int)0));
    t1022 = (int)(t1007);
    t1023 = (unsigned char)((int)(v_l2584) == (int)((int)64341111));
    t1026 = (int)((C_00b18600*)(t1022))->FUN_00b18600((unsigned int)(t1002));
    if ((unsigned char)(t1026) != (unsigned char)0) {
        if (t1023 != (unsigned char)0) {
            t1027 = (unsigned char)((int)1);
            goto Lbd7be7;
        }
    }
    t1027 = (unsigned char)((int)0);
    Lbd7be7:;
    t1028 = (int)(t1007 + (int)56);
    t1031 = (int)((C_00bfc540*)(t1028))->FUN_00bfc540((unsigned int)(t1002));
    if ((unsigned char)(t1031) != (unsigned char)0) {
        if (t1027 != (unsigned char)0) {
            t1032 = (unsigned char)((int)1);
            goto Lbd7bfe;
        }
    }
    t1032 = (unsigned char)((int)0);
    Lbd7bfe:;
    t1033 = (int)(t1007 + (int)256);
    t1036 = (int)((C_00c88b00*)(t1033))->FUN_00c88b00((unsigned int)(t1002));
    if ((unsigned char)(t1036) != (unsigned char)0) {
        if (t1032 != (unsigned char)0) {
            t1037 = (unsigned char)((int)1);
            goto Lbd7c18;
        }
    }
    t1037 = (unsigned char)((int)0);
    Lbd7c18:;
    t1038 = (int)((int)&v_l2580);
    ((C_00692f90*)(t1038))->FUN_00692f90((unsigned int)(t1007), (unsigned int)((int)g_0156e2a0), (unsigned int)((int)27790630));
    t1042 = (int)((int)&v_l2580);
    t1045 = (int)((C_00693e10*)(t1042))->FUN_00693e10((unsigned int)(t1002));
    if ((unsigned char)(t1045) != (unsigned char)0) {
        if (t1037 != (unsigned char)0) {
            t1048 = true;
            return (bool)(t1048);
        }
    }
    t1052 = false;
    return (bool)(t1052);
}
