// 0x00ef0cd0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEditors/_at_00ef0000.cpp, match/slices/s00ef07d0/s00ef07d0.cpp.

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
    virtual int s20();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual int s7();
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
    virtual int s20();
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
    virtual int s14();
};
struct il2c_vc4 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual int s3(int);
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
    virtual int s8(int, int);
};

extern "C" unsigned char g_013f6b68[];
extern "C" unsigned char g_014007f4[];
extern "C" int __cdecl FUN_0067dd10(...);
extern "C" void __cdecl FUN_0069b600(...);
struct C_007c3d30 { void FUN_007c3d30(unsigned int, unsigned int, unsigned int, unsigned int); };
extern "C" int __stdcall FUN_00b3d230(unsigned int);
struct C_00b5cde0 { void FUN_00b5cde0(); };
struct C_00d20910 { void FUN_00d20910(float); };
struct C_00d25ca0 { void FUN_00d25ca0(float); };
struct C_00d26ed0 { void FUN_00d26ed0(unsigned int, unsigned int, float, float, float); };

// @ 0x00ef0cd0
extern "C" void __cdecl FUN_00ef0cd0(void)
{
    int t1005;
    int t1007;
    int t1011;
    int t1013;
    int t1017;
    int t1018;
    int v_l52[3];
    int t1019;
    int t1020;
    int v_l40[3];
    int t1021;
    int v_l28[3];
    int t1022;
    int t1026;
    int t1027;
    int t1028;
    int v_l16[4];
    int t1034;
    int t1035;
    int t1041;
    int t1043;
    int t1047;
    int t1049;
    int t1053;
    int t1055;
    int t1059;
    int t1060;
    int t1061;
    int t1062;
    int t1066;
    int t1070;
    int t1076;
    t1005 = (int)FUN_0067dd10();
    t1007 = (int)(t1005);
    t1011 = (int)((il2c_vc0*)(t1007))->s20();
    t1013 = (int)(t1011);
    t1017 = (int)((il2c_vc1*)(t1013))->s7();
    t1018 = (int)((int)&v_l52);
    t1019 = (int)(t1017);
    t1020 = (int)((int)&v_l40);
    t1021 = (int)((int)&v_l28);
    t1022 = (int)(t1019);
    ((C_007c3d30*)(t1022))->FUN_007c3d30((unsigned int)(t1021), (unsigned int)(t1020), (unsigned int)(t1018), (unsigned int)((int)0));
    t1026 = (int)((int)&v_l52);
    t1027 = (int)((int)&v_l40);
    t1028 = (int)((int)&v_l16);
    FUN_0069b600((unsigned int)(t1028), (unsigned int)(t1027), (unsigned int)(t1026));
    t1034 = (int)FUN_00b3d230((unsigned int)((int)(-1338312295)));
    t1035 = (int)(t1034);
    ((C_00b5cde0*)(t1035))->FUN_00b5cde0();
    t1041 = (int)FUN_0067dd10();
    t1043 = (int)(t1041);
    t1047 = (int)((il2c_vc2*)(t1043))->s20();
    t1049 = (int)(t1047);
    t1053 = (int)((il2c_vc3*)(t1049))->s14();
    if (t1053 != (int)0) {
        t1055 = (int)(t1053);
        t1053 = (int)((il2c_vc4*)(t1055))->s3((int)((int)44559570));
        t1059 = (int)(t1053);
    } else {
        t1059 = (int)((int)0);
    }
    if (t1019 != (int)0) {
        if (t1059 != (int)0) {
            t1060 = (int)((int)&v_l16);
            t1061 = (int)((int)&v_l28);
            t1062 = (int)(t1059);
            ((C_00d26ed0*)(t1062))->FUN_00d26ed0((unsigned int)(t1061), (unsigned int)(t1060), (float)((float)0), (float)((float)0), (float)((float)0));
            t1066 = (int)(t1059);
            ((C_00d25ca0*)(t1066))->FUN_00d25ca0((float)((float)(*(float*)g_013f6b68)));
            t1070 = (int)(t1059);
            ((C_00d20910*)(t1070))->FUN_00d20910((float)((float)(*(float*)g_014007f4)));
            t1076 = (int)(t1059);
            t1053 = (int)((il2c_vc5*)(t1076))->s8((int)((int)0), (int)(t1019));
        }
    }
    return;
}
