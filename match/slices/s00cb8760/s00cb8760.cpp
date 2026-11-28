// 0x00cb8760: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPWeapons.cpp, match/slices/s00cb7e50/s00cb7e50.cpp.

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
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
    virtual int s2();
};
struct il2c_vc3 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual int s3(int);
};
struct il2c_vc4 {
    virtual void s0();
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
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual double s13();
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
    virtual int s11(float);
};

extern "C" unsigned char g_0147515c[];
extern "C" unsigned char g_01475964[];
extern "C" unsigned char g_0157d350[];
extern "C" unsigned char g_0169a410[];
struct C_00b20c60 { int FUN_00b20c60(unsigned int); };
extern "C" int __cdecl FUN_00b3d300(...);
struct C_00bc3130 { void FUN_00bc3130(); };
struct C_00c3f160 { void FUN_00c3f160(unsigned int); };
struct C_00c3f1b0 { void FUN_00c3f1b0(float, float); };
struct C_00c3f2d0 { int FUN_00c3f2d0(unsigned int); };
struct C_00c41d40 { double FUN_00c41d40(unsigned int); };
struct C_00c421b0 { void FUN_00c421b0(unsigned int); };
struct C_00cb54a0 { int FUN_00cb54a0(float); };
extern "C" int __cdecl FUN_00f473a0(...);
extern "C" int __cdecl FUN_01021080(...);
struct C_0104be50 { double FUN_0104be50(float); };

// @ 0x00cb8760
extern "C" void __fastcall FUN_00cb8760(char* self, int edx_unused, int a4, int a8)
{
    int t1004;
    int t1005;
    int t1007;
    int t1010;
    int t1016;
    int t1020;
    int t1023;
    int t1026;
    int t1027;
    int t1028;
    int t1031;
    double t16;
    int t1035;
    double t20;
    int t1039;
    int t1040;
    int t1043;
    int t1044;
    int t1048;
    int t1049;
    int t1050;
    int t1051;
    int t1052;
    int t1056;
    int t1059;
    int t1062;
    int t1063;
    int t1067;
    int t1069;
    int t1072;
    int t1073;
    int t1076;
    int t1082;
    int t1088;
    int t1089;
    double t39;
    int t1095;
    int t1096;
    int t1099;
    int t1103;
    int t1107;
    t1004 = (int)((int)(self));
    t1005 = (int)(*(int*)((char*)(t1004) + 1508));
    t1007 = (int)((int)(a8));
    if (t1007 != t1005) {
        if (t1007 != (int)0) {
            t1010 = (int)(t1007);
            ((il2c_vc0*)(t1010))->s24();
        }
        *(int*)((char*)(t1004) + 1508) = (int)(t1007);
        if (t1005 != (int)0) {
            t1016 = (int)(t1005);
            ((il2c_vc1*)(t1016))->s25();
        }
    }
    *(int*)((char*)(t1004) + 548) = (int)((int)4);
    t1020 = (int)FUN_00f473a0((unsigned int)((int)72), (unsigned int)((int)g_01475964), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
    t1023 = (int)(t1020);
    if (t1023 != (int)0) {
        t1026 = (int)(*(int*)((char*)(t1004) + 1504));
        t1027 = (int)(t1007);
        t1028 = (int)((il2c_vc2*)(t1027))->s2();
        t1031 = (int)(t1026);
        t16 = (double)((C_00c41d40*)(t1031))->FUN_00c41d40((unsigned int)(t1028));
        t1035 = (int)(t1026);
        t20 = (double)((C_0104be50*)(t1035))->FUN_0104be50((float)((t16)));
        t1039 = (int)(t1023);
        t1040 = (int)((C_00cb54a0*)(t1039))->FUN_00cb54a0((float)((t20)));
    } else {
        t1040 = (int)((int)0);
    }
    t1043 = (int)(t1004 + (int)52);
    t1044 = (int)(t1043);
    ((C_00c421b0*)(t1044))->FUN_00c421b0((unsigned int)(t1040));
    t1048 = (int)((int)(a4));
    t1049 = (int)(*(int*)((char*)(t1048)));
    *(int*)((char*)(t1004) + 508) = (int)(t1049);
    t1050 = (int)(*(int*)((char*)(t1048) + 4));
    *(int*)((char*)(t1004) + 512) = (int)(t1050);
    t1051 = (int)(*(int*)((char*)(t1048) + 8));
    t1052 = (int)(t1004 + (int)1512);
    *(int*)((char*)(t1004) + 516) = (int)(t1051);
    ((C_00bc3130*)(t1052))->FUN_00bc3130();
    t1056 = (int)FUN_01021080();
    if (t1056 == (int)0) {
        t1059 = (int)FUN_00b3d300();
        t1062 = (int)(t1059);
        t1063 = (int)((C_00b20c60*)(t1062))->FUN_00b20c60((unsigned int)((int)48704686));
        if (t1063 != (int)0) {
            t1067 = (int)(t1063);
            t1069 = (int)((il2c_vc3*)(t1067))->s3((int)((int)48699994));
            t1072 = (int)(t1069);
        } else {
            t1072 = (int)((int)0);
        }
        t1073 = (int)(*(int*)((char*)(t1004) + 1544));
        if (t1072 != t1073) {
            if (t1072 != (int)0) {
                t1076 = (int)(t1072);
                ((il2c_vc4*)(t1076))->s0();
            }
            *(int*)((char*)(t1004) + 1544) = (int)(t1072);
            if (t1073 != (int)0) {
                t1082 = (int)(t1073);
                ((il2c_vc5*)(t1082))->s1();
            }
        }
        t1088 = (int)(*(int*)((char*)(t1004) + 1544));
        t1089 = (int)(t1043);
        t39 = (double)((il2c_vc6*)(t1089))->s13();
        t1095 = (int)(t1043);
        t1096 = (int)((il2c_vc7*)(t1095))->s11((float)(((t39 * (double)((float)(*(float*)g_0157d350))))));
        t1099 = (int)(t1088);
        ((C_00c3f160*)(t1099))->FUN_00c3f160((unsigned int)(t1096));
        t1103 = (int)(*(int*)((char*)(t1004) + 1544));
        ((C_00c3f1b0*)(t1103))->FUN_00c3f1b0((float)((float)(*(float*)g_0169a410)), (float)((float)(*(float*)g_0147515c)));
        t1107 = (int)(*(int*)((char*)(t1004) + 1544));
        t1056 = (int)((C_00c3f2d0*)(t1107))->FUN_00c3f2d0((unsigned int)(t1004));
    }
    return;
}
