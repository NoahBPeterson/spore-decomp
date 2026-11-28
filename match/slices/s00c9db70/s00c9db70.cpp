// 0x00c9db70: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPTribeTool.cpp, match/slices/s00c9d230/s00c9d230.cpp.

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
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual int s10(int, int, int);
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
    virtual int s8();
};
struct il2c_vc5 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual int s6();
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
    virtual int s8();
};
struct il2c_vc7 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual int s6();
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
    virtual int s8();
};
struct il2c_vc9 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual int s6();
};

extern "C" unsigned char g_0157c5d0[];
struct C_00692f90 { int FUN_00692f90(unsigned int, unsigned int, unsigned int); };
struct C_00693e10 { int FUN_00693e10(unsigned int); };
extern "C" void __cdecl FUN_0093a780(...);
struct C_00b18600 { int FUN_00b18600(unsigned int); };
struct C_00bfc540 { int FUN_00bfc540(unsigned int); };
struct C_00c88b00 { int FUN_00c88b00(unsigned int); };

// @ 0x00c9db70
extern "C" bool __fastcall FUN_00c9db70(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1007;
    int t1008;
    int t1009;
    int t1013;
    int t1015;
    int t1018;
    int v_l2584;
    int t1022;
    int t1023;
    int t1026;
    int t1027;
    int t1030;
    int t1031;
    int t1034;
    int t1000;
    int t1042;
    int t1043;
    unsigned char t1046;
    int t1049;
    int t1050;
    int t1054;
    int t1056;
    int t1059;
    int t1065;
    int t1066;
    int t1070;
    int t1072;
    int t1075;
    int t1081;
    int t1082;
    int t1086;
    int t1088;
    int t1091;
    int t1095;
    int v_l2580[645];
    int t1096;
    int t1099;
    bool t1104;
    bool t1108;
    t1002 = (int)((int)(a4));
    t1007 = (int)((int)(self));
    t1008 = (int)(t1002);
    t1009 = (int)((il2c_vc0*)(t1008))->s8();
    t1013 = (int)(t1009);
    t1015 = (int)((il2c_vc1*)(t1013))->s6();
    t1018 = (int)((int)&v_l2584);
    FUN_0093a780((unsigned int)(t1015), (unsigned int)(t1018), (unsigned int)((int)1), (unsigned int)((int)0));
    t1022 = (int)(t1007);
    t1023 = (int)((C_00b18600*)(t1022))->FUN_00b18600((unsigned int)(t1002));
    if ((unsigned char)(t1023) != (unsigned char)0) {
        t1026 = (int)(t1007 + (int)52);
        t1027 = (int)((C_00c88b00*)(t1026))->FUN_00c88b00((unsigned int)(t1002));
        if ((unsigned char)(t1027) != (unsigned char)0) {
            t1030 = (int)(t1007 + (int)288);
            t1031 = (int)((C_00bfc540*)(t1030))->FUN_00bfc540((unsigned int)(t1002));
            if ((unsigned char)(t1031) != (unsigned char)0) {
                t1034 = (int)(*(int*)((char*)(t1007) + 504));
                t1000 = (int)(t1007 + (int)504);
                if (t1034 != (int)0) {
                    *(int*)((char*)(t1000)) = (int)((int)0);
                    ((il2c_vc2*)(t1034))->s1();
                }
                t1042 = (int)(t1002);
                t1043 = (int)((il2c_vc3*)(t1042))->s10((int)((int)1329162854), (int)(t1000), (int)((int)0));
                if ((unsigned char)(t1043) != (unsigned char)0) {
                    t1046 = (unsigned char)((int)1);
                    goto Lc9dc07;
                }
            }
        }
    }
    t1046 = (unsigned char)((int)0);
    Lc9dc07:;
    t1049 = (int)(t1002);
    t1050 = (int)((il2c_vc4*)(t1049))->s8();
    t1054 = (int)(t1050);
    t1056 = (int)((il2c_vc5*)(t1054))->s6();
    t1059 = (int)(t1007 + (int)204);
    FUN_0093a780((unsigned int)(t1056), (unsigned int)(t1059), (unsigned int)((int)1), (unsigned int)((int)0));
    t1065 = (int)(t1002);
    t1066 = (int)((il2c_vc6*)(t1065))->s8();
    t1070 = (int)(t1066);
    t1072 = (int)((il2c_vc7*)(t1070))->s6();
    t1075 = (int)(t1007 + (int)196);
    FUN_0093a780((unsigned int)(t1072), (unsigned int)(t1075), (unsigned int)((int)1), (unsigned int)((int)0));
    t1081 = (int)(t1002);
    t1082 = (int)((il2c_vc8*)(t1081))->s8();
    t1086 = (int)(t1082);
    t1088 = (int)((il2c_vc9*)(t1086))->s6();
    t1091 = (int)(t1007 + (int)200);
    FUN_0093a780((unsigned int)(t1088), (unsigned int)(t1091), (unsigned int)((int)1), (unsigned int)((int)0));
    t1095 = (int)((int)&v_l2580);
    t1096 = (int)((C_00692f90*)(t1095))->FUN_00692f90((unsigned int)(t1007), (unsigned int)((int)g_0157c5d0), (unsigned int)((int)27790630));
    if (t1046 != (unsigned char)0) {
        t1099 = (int)((int)&v_l2580);
        t1096 = (int)((C_00693e10*)(t1099))->FUN_00693e10((unsigned int)(t1002));
        if ((unsigned char)(t1096) != (unsigned char)0) {
            t1104 = true;
            return (bool)(t1104);
        }
    }
    t1108 = false;
    return (bool)(t1108);
}
