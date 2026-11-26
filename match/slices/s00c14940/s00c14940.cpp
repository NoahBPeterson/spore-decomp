// 0x00c14940: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPCreatureBase.cpp, match/slices/s00c14350/s00c14350.cpp.

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
    virtual int s46(int);
};

extern "C" void __cdecl FUN_00c0b510(...);
struct C_00c12190 { int FUN_00c12190(unsigned int, unsigned int, unsigned int); };

// @ 0x00c14940
extern "C" int __fastcall FUN_00c14940(char* self, int edx_unused, int a4, int a8, int a12, int a16)
{
    int t1000;
    int t1004;
    int t1005;
    int t1006;
    int t1009;
    int t1010;
    int t1011;
    int t1016;
    int t1017;
    t1000 = (int)((int)(a16));
    t1004 = (int)((int)(self));
    t1005 = (int)((int)(a4));
    t1006 = (int)(t1004);
    t1009 = (int)((C_00c12190*)(t1006))->FUN_00c12190((unsigned int)(t1005), (unsigned int)((int)1), (unsigned int)(t1000));
    t1010 = (int)((int)(a8));
    t1011 = (int)(t1009);
    if (t1010 != (int)0) {
        t1016 = (int)((il2c_vc0*)(t1010))->s46((int)((int)(-297840274)));
        if (t1016 != (int)0) {
            t1017 = (int)((int)(a12));
            FUN_00c0b510((unsigned int)(t1004), (unsigned int)(t1011), (unsigned int)(t1016), (unsigned int)(t1017));
        }
        t1009 = (int)(t1011);
    }
    return (int)(t1009);
}
