// 0x00dc5bc0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
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
    virtual int s48();
};


// @ 0x00dc5bc0
extern "C" bool __cdecl FUN_00dc5bc0(int a4)
{
    int t1000;
    int t1001;
    bool t1006;
    t1000 = (int)((int)(a4));
    t1001 = (int)(*(int*)((char*)(t1000) + 2940));
    if (t1001 != (int)0) {
        *(int*)((char*)(t1000) + 2940) = (int)((int)0);
        t1000 = (int)((il2c_vc0*)(t1001))->s48();
    }
    t1006 = true;
    return (bool)(t1006);
}
