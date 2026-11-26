// 0x00ef8600: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEditors/_at_00ef0000.cpp, match/slices/s00ef7d90/s00ef7d90.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual int s4();
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
    virtual void s31(int, int);
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
    virtual int s8();
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
    virtual void s14(int);
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
    virtual void s16(int, int);
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
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16(int, int);
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
};

extern "C" unsigned char g_015acef0[];
extern "C" unsigned char g_016c7b60[];
struct C_008105b0 { int FUN_008105b0(unsigned int, unsigned int); };
struct C_0093a480 { int FUN_0093a480(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00a206f0(...);
struct C_00ef7b40 { void FUN_00ef7b40(); };

// @ 0x00ef8600
extern "C" void __fastcall FUN_00ef8600(char* self, int edx_unused, int a4)
{
    int t1005;
    int t1009;
    int t1010;
    int t1011;
    int t1014;
    int t1016;
    int t1020;
    int t1022;
    int t1029;
    int t1031;
    int t1035;
    int t1036;
    int t1039;
    int t1040;
    int t1043;
    int t1049;
    int t1055;
    int t1061;
    int t1065;
    int t1069;
    t1005 = (int)((int)(self));
    ((C_00ef7b40*)((int)(self)))->FUN_00ef7b40();
    t1009 = (int)((int)(a4));
    t1010 = (int)(*(int*)((char*)(t1005) + 16));
    t1011 = (int)(t1009 + (int)1000);
    t1014 = (int)((C_008105b0*)(t1010))->FUN_008105b0((unsigned int)(t1011), (unsigned int)((int)1));
    t1016 = (int)(t1014);
    t1020 = (int)((il2c_vc0*)(t1016))->s4();
    t1022 = (int)(t1020);
    ((il2c_vc1*)(t1022))->s31((int)((int)2), (int)((int)1));
    t1029 = (int)FUN_00a206f0();
    if (t1029 != (int)0) {
        t1031 = (int)(t1029);
        t1035 = (int)((il2c_vc2*)(t1031))->s8();
        t1036 = (int)(t1035);
    } else {
        t1036 = (int)((int)0);
    }
    t1039 = (int)FUN_00a206f0();
    t1040 = (int)(t1039);
    if (t1040 != (int)0) {
        t1043 = (int)(t1040);
        ((il2c_vc3*)(t1043))->s14((int)((int)55006053));
        t1049 = (int)(t1040);
        ((il2c_vc4*)(t1049))->s16((int)((int)55006081), (int)((int)1938191575));
        t1055 = (int)(t1040);
        ((il2c_vc5*)(t1055))->s16((int)((int)55006085), (int)(t1036));
        t1061 = (int)(t1040);
        ((il2c_vc6*)(t1061))->s22();
    }
    t1065 = (int)((int)g_016c7b60);
    ((C_0093a480*)(t1065))->FUN_0093a480((unsigned int)((int)4), (unsigned int)((int)1));
    t1069 = (int)(*(int*)((char*)(t1005) + 40));
    *(int*)g_015acef0 = (int)(t1069);
    *(int*)((char*)(t1005) + 52) = (int)(t1009);
    return;
}
