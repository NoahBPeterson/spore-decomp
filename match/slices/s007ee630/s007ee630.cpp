// 0x007ee630: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEngine/SPAppVolumeDescription.cpp, match/slices/s007ee060/s007ee060.cpp.

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
    virtual void s12(int, int);
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
    virtual void s12(int, int);
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
    virtual void s12(int, int);
};

extern "C" unsigned char g_013f1fdc[];
struct C_007ee540 { int FUN_007ee540(); };
extern "C" void __cdecl FUN_0093a780(...);
extern "C" void __cdecl FUN_0093a800(...);
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x007ee630
extern "C" int __cdecl FUN_007ee630(int a4)
{
    int t1007;
    int t1008;
    int t1011;
    int t1012;
    int t1013;
    int t1016;
    int t1017;
    int t1021;
    int t1025;
    int t1029;
    int t1030;
    int t1033;
    int t1034;
    int t1040;
    int t1047;
    t1007 = (int)FUN_00f473a0((unsigned int)((int)240), (unsigned int)((int)g_013f1fdc), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
    if (t1007 != (int)0) {
        t1008 = (int)(t1007);
        t1011 = (int)((C_007ee540*)(t1008))->FUN_007ee540();
        t1012 = (int)(t1011);
    } else {
        t1012 = (int)((int)0);
    }
    t1013 = (int)((int)(a4));
    t1016 = (int)(t1012 + (int)8);
    t1017 = (int)(t1013);
    ((il2c_vc0*)(t1017))->s12((int)(t1016), (int)((int)12));
    t1021 = (int)(t1012 + (int)20);
    FUN_0093a780((unsigned int)(t1013), (unsigned int)(t1021), (unsigned int)((int)1), (unsigned int)((int)0));
    t1025 = (int)(t1012 + (int)40);
    FUN_0093a800((unsigned int)(t1013), (unsigned int)(t1025), (unsigned int)((int)1), (unsigned int)((int)0));
    t1029 = (int)(t1012 + (int)60);
    t1030 = (int)((int)8);
    do {
        t1033 = (int)(t1029 + (int)(-12));
        t1034 = (int)(t1013);
        ((il2c_vc1*)(t1034))->s12((int)(t1033), (int)((int)12));
        t1040 = (int)(t1013);
        ((il2c_vc2*)(t1040))->s12((int)(t1029), (int)((int)12));
        t1029 = (int)(t1029 + (int)24);
        t1030 = (int)(t1030 - (int)1);
    } while (t1030 != (int)0);
    t1047 = (int)(t1012);
    return (int)(t1047);
}
