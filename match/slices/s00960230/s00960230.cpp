// 0x00960230: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0095ff20/s0095ff20.cpp, src/game/UTFSpore_Win32/Window.cpp.

struct il2c_vc0 {
    virtual void s0();
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
    virtual void s55(int);
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
};
struct il2c_vc3 {
    virtual void s0();
    virtual int s1();
};


// @ 0x00960230
extern "C" void __fastcall FUN_00960230(char* self, int edx_unused, int a4)
{
    int t1000;
    int t1004;
    int t1005;
    int t1008;
    int t1012;
    int t1015;
    int t1021;
    int t1027;
    t1000 = (int)((int)(a4));
    t1004 = (int)((int)(self));
    if (t1000 != (int)0) {
        t1005 = (int)(t1000 + (int)(-4));
        if (t1005 == (int)0) goto L960252;
        t1008 = (int)(t1005);
        ((il2c_vc0*)(t1008))->s0();
        t1012 = (int)(t1005 + (int)4);
        goto L960254;
    }
    t1005 = (int)((int)0);
    L960252:;
    t1012 = (int)((int)0);
    L960254:;
    t1015 = (int)(t1004);
    ((il2c_vc1*)(t1015))->s55((int)(t1012));
    t1021 = (int)(t1005);
    ((il2c_vc2*)(t1021))->s7();
    t1027 = (int)(t1005);
    ((il2c_vc3*)(t1027))->s1();
    return;
}
