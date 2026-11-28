// 0x00802890: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/Spui/_at_00800000.cpp, match/slices/s008019f0/s008019f0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual int s7();
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
    virtual int s60(int, int);
};

extern "C" unsigned char g_014a4606[];
struct C_008105b0 { int FUN_008105b0(unsigned int, unsigned int); };

// @ 0x00802890
extern "C" int __fastcall FUN_00802890(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1003;
    int t1006;
    int t1009;
    int t1010;
    int t1013;
    int t1014;
    int t1018;
    int t1019;
    int t1023;
    t1002 = (int)((int)(self) + (int)16);
    t1003 = (int)((C_008105b0*)(t1002))->FUN_008105b0((unsigned int)((int)g_014a4606), (unsigned int)((int)1));
    t1006 = (int)(t1003);
    if (t1006 != (int)0) {
        t1009 = (int)(t1006);
        t1010 = (int)((il2c_vc0*)(t1009))->s7();
        t1013 = (int)((int)(a4));
        if (t1010 == t1013) {
            t1014 = (int)(t1006);
            return (int)(t1014);
        }
        t1018 = (int)(t1006);
        t1019 = (int)((il2c_vc1*)(t1018))->s60((int)(t1013), (int)((int)1));
        return (int)(t1019);
    }
    t1023 = (int)((int)0);
    return (int)(t1023);
}
