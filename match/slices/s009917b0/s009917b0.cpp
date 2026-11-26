// 0x009917b0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s009913d0/s009913d0.cpp, src/game/UTFSpore_Win32/TreeView.cpp.

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
    virtual int s31(int, int);
};

struct C_009609b0 { void FUN_009609b0(); };
struct C_0098fbe0 { void FUN_0098fbe0(); };
struct C_00990ff0 { void FUN_00990ff0(unsigned int); };

// @ 0x009917b0
extern "C" void __fastcall FUN_009917b0(char* self, int edx_unused)
{
    int t1003;
    int t1007;
    int t1008;
    int t1012;
    int t1016;
    int t1022;
    t1003 = (int)((int)(self));
    ((C_009609b0*)((int)(self)))->FUN_009609b0();
    t1007 = (int)(t1003 + (int)(-4));
    t1008 = (int)(t1007);
    ((C_00990ff0*)(t1008))->FUN_00990ff0((unsigned int)((int)1));
    t1012 = (int)(t1007);
    ((C_00990ff0*)(t1012))->FUN_00990ff0((unsigned int)((int)0));
    t1016 = (int)(t1007);
    ((C_0098fbe0*)(t1016))->FUN_0098fbe0();
    t1022 = (int)(t1003);
    ((il2c_vc0*)(t1022))->s31((int)((int)8), (int)((int)1));
    return;
}
