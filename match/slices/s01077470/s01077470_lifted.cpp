// 0x01077470: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPUISpaceTrading.cpp, match/slices/s01077470/s01077470.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc1 {
    virtual void s0();
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
    virtual int s4();
};
struct il2c_vc4 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual int s4();
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
    virtual void s55(int);
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
    virtual void s54(int);
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
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual int s14();
};
struct il2c_gm8 { void m(unsigned int); };
typedef void (il2c_gm8::*il2c_gp8)(unsigned int);
struct il2c_vc9 {
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
    virtual void s25(float, float);
};

extern "C" unsigned char g_013fa3b4[];
extern "C" int __cdecl FUN_00807600(...);
extern "C" int __cdecl FUN_00807690(...);
struct C_01076a00 { void FUN_01076a00(); };

// @ 0x01077470
// @ 0x01077470
extern "C" void __fastcall FUN_01077470(char* self, int edx_unused)
{
    int t1003;
    int t1004;
    int t1006;
    int t1012;
    int t1015;
    int t1016;
    int t1019;
    int t1025;
    int t1029;
    int t1032;
    int t1035;
    int t1038;
    int t1041;
    int t1044;
    int t1048;
    int t1050;
    int t1055;
    int t1056;
    int t1058;
    int t1060;
    int t1061;
    int t1065;
    int t1069;
    int t1075;
    int t1079;
    t1003 = (int)((int)(self));
    t1004 = (int)(*(int*)((char*)(t1003) + 24));
    t1006 = (int)(t1003 + (int)24);
    if (t1004 != (int)0) {
        *(int*)((char*)(t1006)) = (int)((int)0);
        ((il2c_vc0*)(t1004))->s1();
    }
    t1012 = (int)FUN_00807600((unsigned int)((int)g_013fa3b4), (unsigned int)(t1006), (unsigned int)((int)1));
    t1015 = (int)(*(int*)((char*)(t1003) + 20));
    t1016 = (int)(t1012);
    if (t1016 != t1015) {
        if (t1016 != (int)0) {
            t1019 = (int)(t1016);
            ((il2c_vc1*)(t1019))->s0();
        }
        *(int*)((char*)(t1003) + 20) = (int)(t1016);
        if (t1015 != (int)0) {
            t1025 = (int)(t1015);
            ((il2c_vc2*)(t1025))->s1();
        }
    }
    t1029 = (int)(*(int*)((char*)(t1003) + 20));
    t1032 = (int)((il2c_vc3*)(t1029))->s4();
    if (t1032 != (int)0) {
        t1035 = (int)(*(int*)((char*)(t1003) + 20));
        t1038 = (int)((il2c_vc4*)(t1035))->s4();
        t1041 = (int)(*(int*)((char*)(t1003) + 20));
        t1044 = (int)(t1038);
        ((il2c_vc5*)(t1044))->s55((int)(t1041));
    }
    t1048 = (int)(*(int*)((char*)(t1003) + 16));
    t1050 = (int)(*(int*)((char*)(t1003) + 20));
    ((il2c_vc6*)(t1048))->s54((int)(t1050));
    t1055 = (int)(*(int*)((char*)(t1003) + 16));
    t1056 = (int)(*(int*)((char*)(t1003) + 20));
    t1058 = (int)(*(int*)((char*)(t1056)));
    t1060 = (int)(t1058 + (int)96);
    t1061 = (int)((il2c_vc7*)(t1055))->s14();
    t1065 = (int)(t1056);
    (((il2c_gm8*)(t1065))->*(*(il2c_gp8*)&(*(int*)((char*)(t1060)))))((unsigned int)(t1061));
    t1069 = (int)(*(int*)((char*)(t1003) + 20));
    ((il2c_vc9*)(t1069))->s25((float)((float)0), (float)((float)0));
    t1075 = (int)(t1003);
    ((C_01076a00*)(t1075))->FUN_01076a00();
    t1079 = (int)(*(int*)((char*)(t1003) + 20));
    FUN_00807690((unsigned int)(t1079), (unsigned int)((int)0));
    return;
}
