// 0x00805310: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/Spui/SPUIHelpers.cpp, match/slices/s00804920/s00804920.cpp.

struct il2c_vc0 {
    virtual void s0();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual int s4();
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
    virtual void s55(int);
};

struct C_00810000 { void FUN_00810000(); };
struct C_008105b0 { int FUN_008105b0(unsigned int, unsigned int); };
struct C_00811ad0 { void FUN_00811ad0(unsigned int); };
struct C_00811fe0 { int FUN_00811fe0(); };
struct C_008120d0 { int FUN_008120d0(unsigned int, unsigned int, unsigned int); };

// @ 0x00805310
// @ 0x00805310
extern "C" bool __cdecl FUN_00805310(int a4, int a8, int a12)
{
    int t1000;
    int v_l24[6];
    int t1005;
    int t1006;
    int t1009;
    bool t1013;
    int t1017;
    int t1018;
    int t1021;
    int t1023;
    int t1028;
    int t1031;
    int t1034;
    int t1037;
    bool t1041;
    int t1042;
    int t1046;
    bool t1051;
    t1000 = (int)((int)&v_l24);
    ((C_00810000*)(t1000))->FUN_00810000();
    t1005 = (int)((int)&v_l24);
    t1006 = (int)((C_008120d0*)(t1005))->FUN_008120d0((unsigned int)(a4), (unsigned int)((int)0), (unsigned int)((int)95787258));
    if ((unsigned char)(t1006) == (unsigned char)0) {
        t1009 = (int)((int)&v_l24);
        ((C_00811fe0*)(t1009))->FUN_00811fe0();
        t1013 = false;
        return (bool)(t1013);
    }
    t1017 = (int)((int)&v_l24);
    t1018 = (int)((C_008105b0*)(t1017))->FUN_008105b0((unsigned int)(a8), (unsigned int)((int)1));
    t1021 = (int)((int)(a12));
    *(int*)((char*)(t1021)) = (int)(t1018);
    if (t1018 != (int)0) {
        t1023 = (int)(t1018);
        ((il2c_vc0*)(t1023))->s0();
        t1028 = (int)(*(int*)((char*)(t1021)));
        t1031 = (int)((il2c_vc1*)(t1028))->s4();
        if (t1031 != (int)0) {
            t1034 = (int)(*(int*)((char*)(t1021)));
            t1037 = (int)(t1031);
            ((il2c_vc2*)(t1037))->s55((int)(t1034));
        }
        t1041 = true;
    } else {
        t1041 = false;
    }
    t1042 = (int)((int)&v_l24);
    ((C_00811ad0*)(t1042))->FUN_00811ad0((unsigned int)((int)1));
    t1046 = (int)((int)&v_l24);
    ((C_00811fe0*)(t1046))->FUN_00811fe0();
    t1051 = t1041;
    return t1051;
}
