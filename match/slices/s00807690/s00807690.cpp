// 0x00807690: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/Spui/SPUIHelpers.cpp, match/slices/s008068d0/s008068d0.cpp.

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
    virtual int s45(int);
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual int s3(int);
};
struct il2c_vc2 {
    virtual void s0();
};
struct il2c_vc3 {
    virtual void s0();
    virtual int s1();
};

struct C_0082a500 { void FUN_0082a500(unsigned int); };

// @ 0x00807690
extern "C" bool __cdecl FUN_00807690(int a4, int a8)
{
    int t1000;
    int t1006;
    int t1008;
    int t1012;
    int t1015;
    int t1019;
    int t1020;
    int t1026;
    bool t1030;
    bool t1032;
    t1000 = (int)((int)(a4));
    t1006 = (int)((il2c_vc0*)(t1000))->s45((int)((int)77994737));
    if (t1006 != (int)0) {
        t1008 = (int)(t1006);
        t1006 = (int)((il2c_vc1*)(t1008))->s3((int)((int)77994738));
        t1012 = (int)(t1006);
        if (t1012 != (int)0) {
            t1015 = (int)(t1012);
            ((il2c_vc2*)(t1015))->s0();
            t1019 = (int)((int)(a8));
            t1020 = (int)(t1012);
            ((C_0082a500*)(t1020))->FUN_0082a500((unsigned int)(t1019));
            t1026 = (int)(t1012);
            ((il2c_vc3*)(t1026))->s1();
            t1030 = true;
            return (bool)(t1030);
        }
    }
    t1032 = false;
    return (bool)(t1032);
}
