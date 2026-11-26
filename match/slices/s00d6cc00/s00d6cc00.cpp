// 0x00d6cc00: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

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
    virtual void s33(int, int, int);
};

struct C_00c17350 { int FUN_00c17350(unsigned int, unsigned int); };

// @ 0x00d6cc00
extern "C" void __cdecl FUN_00d6cc00(int a4)
{
    int t1001;
    int t1004;
    int t1008;
    t1001 = (int)((int)(a4));
    t1004 = (int)(t1001);
    ((il2c_vc0*)(t1004))->s33((int)((int)0), (int)((int)0), (int)((int)0));
    t1008 = (int)(t1001);
    ((C_00c17350*)(t1008))->FUN_00c17350((unsigned int)((int)(-1878663151)), (unsigned int)((int)0));
    return;
}
