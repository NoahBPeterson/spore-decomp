// 0x007e07f0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s007e06b0/s007e06b0.cpp, src/game/SPEngine/SPAppSplitModelDescription.cpp.

#include <string.h>
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
    virtual int s35(int);
};

struct C_00454cb0 { void FUN_00454cb0(unsigned int, unsigned int); };
struct C_00838020 { int FUN_00838020(unsigned int, unsigned int, unsigned int); };
struct C_00a6f090 { void FUN_00a6f090(unsigned int, unsigned int, unsigned int); };

// @ 0x007e07f0
extern "C" void __fastcall FUN_007e07f0(char* self, int edx_unused, int a4)
{
    int t1003;
    int t1005;
    int t1006;
    int t1009;
    int t1010;
    int t1011;
    int t1012;
    int t1014;
    int t1015;
    int t1016;
    int t1020;
    int t1021;
    int t1025;
    t1003 = (int)((int)&a4);
    t1005 = (int)((int)(self));
    t1006 = (int)((int)(a4));
    t1009 = (int)((C_00838020*)(t1006))->FUN_00838020((unsigned int)(t1003), (unsigned int)((int)1), (unsigned int)((int)3));
    t1010 = (int)(t1009);
    t1011 = (int)(*(int*)((char*)(t1010)));
    t1012 = (int)(t1011);
    t1014 = (int)strlen((const char*)(t1012));
    t1015 = (int)(t1014 + t1011);
    t1016 = (int)(t1005 + (int)64);
    ((C_00454cb0*)(t1016))->FUN_00454cb0((unsigned int)(t1011), (unsigned int)(t1015));
    t1020 = (int)((int)(a4));
    if (t1020 > (int)1) {
        t1021 = (int)(*(int*)((char*)(t1005) + 48));
        ((C_00a6f090*)(t1021))->FUN_00a6f090((unsigned int)(t1010), (unsigned int)(t1020), (unsigned int)((int)41));
    }
    t1025 = (int)(*(int*)((char*)(t1005) + 4));
    ((il2c_vc0*)(t1025))->s35((int)(t1005));
    return;
}
