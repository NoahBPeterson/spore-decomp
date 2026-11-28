// 0x00e188b0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/_at_00e10000.cpp, match/slices/s00e17c10/s00e17c10.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
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
    virtual int s65(int);
};
struct il2c_vc3 {
    virtual void s0();
    virtual void s1();
    virtual int s2();
};

extern "C" unsigned char g_013f6b3c[];
struct C_00810000 { int FUN_00810000(); };
struct C_00810590 { void FUN_00810590(unsigned int); };
struct C_008105b0 { int FUN_008105b0(unsigned int, unsigned int); };
struct C_008120d0 { int FUN_008120d0(unsigned int, unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x00e188b0
extern "C" void __fastcall FUN_00e188b0(char* self, int edx_unused, int a4)
{
    int t1003;
    int t1004;
    int t1007;
    int t1008;
    int t1011;
    int t1013;
    int t1016;
    int t1022;
    int t1026;
    int t1027;
    int t1028;
    int v_l12[3];
    int t1029;
    int t1032;
    int t1037;
    int t1038;
    int t1042;
    t1003 = (int)((int)(self));
    t1004 = (int)FUN_00f473a0((unsigned int)((int)24), (unsigned int)((int)g_013f6b3c), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
    if (t1004 != (int)0) {
        t1007 = (int)(t1004);
        t1008 = (int)((C_00810000*)(t1007))->FUN_00810000();
        t1011 = (int)(t1008);
    } else {
        t1011 = (int)((int)0);
    }
    t1013 = (int)(*(int*)((char*)(t1003) + 48));
    if (t1011 != t1013) {
        if (t1011 != (int)0) {
            t1016 = (int)(t1011);
            ((il2c_vc0*)(t1016))->s1();
        }
        *(int*)((char*)(t1003) + 48) = (int)(t1011);
        if (t1013 != (int)0) {
            t1022 = (int)(t1013);
            ((il2c_vc1*)(t1022))->s2();
        }
    }
    t1026 = (int)((int)(a4));
    t1027 = (int)(*(int*)((char*)(t1003) + 48));
    t1028 = (int)((int)&v_l12);
    (*(int*)&v_l12[0]) = (int)(t1026);
    (*(int*)&v_l12[1]) = (int)((int)84978011);
    (*(int*)&v_l12[2]) = (int)((int)1078345984);
    t1029 = (int)((C_008120d0*)(t1027))->FUN_008120d0((unsigned int)(t1028), (unsigned int)((int)1), (unsigned int)((int)(-1953040299)));
    t1032 = (int)(*(int*)((char*)(t1003) + 48));
    if ((unsigned char)(t1029) != (unsigned char)0) {
        ((C_00810590*)(t1032))->FUN_00810590((unsigned int)((int)0));
        t1037 = (int)(*(int*)((char*)(t1003) + 48));
        t1038 = (int)((C_008105b0*)(t1037))->FUN_008105b0((unsigned int)((int)(-1)), (unsigned int)((int)1));
        t1042 = (int)(t1038);
        ((il2c_vc2*)(t1042))->s65((int)(t1003));
        return;
    }
    if (t1032 != (int)0) {
        *(int*)((char*)(t1003) + 48) = (int)((int)0);
        t1029 = (int)((il2c_vc3*)(t1032))->s2();
    }
    return;
}
