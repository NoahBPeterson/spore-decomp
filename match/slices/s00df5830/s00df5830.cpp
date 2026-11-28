// 0x00df5830: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPGalaxyGameEntry.cpp, match/slices/s00df5670/s00df5670.cpp.

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
    virtual void s65(int);
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
    virtual int s32(int);
};

struct C_008105b0 { int FUN_008105b0(unsigned int, unsigned int); };
struct C_00811ad0 { int FUN_00811ad0(unsigned int); };
struct C_008120d0 { int FUN_008120d0(unsigned int, unsigned int, unsigned int); };

// @ 0x00df5830
extern "C" bool __fastcall FUN_00df5830(char* self, int edx_unused, int a4)
{
    int t1004;
    int t1005;
    int v_l12[3];
    int t1006;
    int t1007;
    int t1008;
    int t1011;
    int t1012;
    int t1015;
    int t1019;
    int t1023;
    int t1026;
    int t1032;
    int t1036;
    int t1037;
    int t1040;
    int t1041;
    int t1044;
    bool t1051;
    int t1053;
    bool t1058;
    t1004 = (int)((int)(self));
    t1005 = (int)((int)&v_l12);
    t1006 = (int)(t1004 + (int)12);
    t1007 = (int)(t1006);
    (*(int*)&v_l12[0]) = (int)((int)(-150461887));
    (*(int*)&v_l12[1]) = (int)((int)84978011);
    (*(int*)&v_l12[2]) = (int)((int)1078345984);
    t1008 = (int)((C_008120d0*)(t1007))->FUN_008120d0((unsigned int)(t1005), (unsigned int)((int)1), (unsigned int)((int)95787258));
    if ((unsigned char)(t1008) != (unsigned char)0) {
        t1011 = (int)(t1006);
        t1012 = (int)((C_008105b0*)(t1011))->FUN_008105b0((unsigned int)((int)104347024), (unsigned int)((int)1));
        t1015 = (int)(t1012);
        if (t1015 != (int)0) {
            t1019 = (int)(t1015);
            ((il2c_vc0*)(t1019))->s65((int)(t1004));
            t1023 = (int)(*(int*)((char*)(t1004) + 36));
            if (t1015 != t1023) {
                t1026 = (int)(t1015);
                ((il2c_vc1*)(t1026))->s0();
                *(int*)((char*)(t1004) + 36) = (int)(t1015);
                if (t1023 != (int)0) {
                    t1032 = (int)(t1023);
                    ((il2c_vc2*)(t1032))->s1();
                }
            }
            t1036 = (int)(t1006);
            t1037 = (int)((C_008105b0*)(t1036))->FUN_008105b0((unsigned int)((int)104414744), (unsigned int)((int)1));
            t1040 = (int)((int)(a4));
            t1041 = (int)(*(int*)((char*)(t1040)));
            t1044 = (int)(t1037);
            ((il2c_vc3*)(t1044))->s32((int)(t1041));
            t1051 = true;
            return (bool)(t1051);
        }
        t1053 = (int)(t1006);
        t1008 = (int)((C_00811ad0*)(t1053))->FUN_00811ad0((unsigned int)((int)1));
    }
    t1058 = false;
    return (bool)(t1058);
}
