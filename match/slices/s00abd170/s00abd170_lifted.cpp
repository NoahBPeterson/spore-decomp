// 0x00abd170: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00abd170/s00abd170.cpp.

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

extern "C" void __cdecl FUN_0093a780(...);
struct C_00abd0f0 { void FUN_00abd0f0(unsigned int); };

// @ 0x00abd170
// @ 0x00abd170
extern "C" int __cdecl FUN_00abd170(int a4, int a8)
{
    int t1002;
    int t1003;
    int t1008;
    int t1009;
    int t1013;
    int t1016;
    int t1017;
    int t1018;
    int t1021;
    int t1022;
    int t1026;
    int t1032;
    t1002 = (int)((int)(a4));
    t1003 = (int)((int)&a4);
    FUN_0093a780((unsigned int)(t1002), (unsigned int)(t1003), (unsigned int)((int)1), (unsigned int)((int)0));
    t1008 = (int)((int)(a4));
    t1009 = (int)((int)(a8));
    ((C_00abd0f0*)(t1009))->FUN_00abd0f0((unsigned int)(t1008));
    t1013 = (int)((int)0);
    if ((unsigned int)((int)(a4)) > (unsigned int)(t1013)) {
        t1016 = (int)((int)0);
        do {
            t1017 = (int)((int)(a8));
            t1018 = (int)(*(int*)((char*)(t1017)));
            t1021 = (int)(t1018 + t1016);
            t1022 = (int)(t1002);
            ((il2c_vc0*)(t1022))->s12((int)(t1021), (int)((int)8));
            t1026 = (int)(t1021 + (int)8);
            FUN_0093a780((unsigned int)(t1002), (unsigned int)(t1026), (unsigned int)((int)1), (unsigned int)((int)0));
            t1013 = (int)(t1013 + (int)1);
            t1016 = (int)(t1016 + (int)12);
        } while ((unsigned int)(t1013) < (unsigned int)((int)(a4)));
    }
    t1032 = (int)(t1002);
    return (int)(t1032);
}
