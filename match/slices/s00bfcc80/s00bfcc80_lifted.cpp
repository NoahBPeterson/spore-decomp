// 0x00bfcc80: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPCombatant.cpp, match/slices/s00bfcc80/s00bfcc80.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual int s4();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
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
    virtual int s11(int, int, int);
};

extern "C" int __cdecl FUN_0067ddd0(...);

// @ 0x00bfcc80
extern "C" int __fastcall FUN_00bfcc80(char* self, int edx_unused, int a4)
{
    int t1003;
    int t1005;
    int t1006;
    int t1008;
    int t1013;
    int t1016;
    int t1020;
    int t1021;
    int t6;
    int t7;
    int t1022;
    int t1023;
    int t1029;
    int t1032;
    int t1035;
    int t1036;
    t1003 = (int)((int)(self));
    t1005 = (int)((int)0);
    t1006 = (int)(t1003 + (int)188);
    do {
        t1008 = (int)(*(int*)((char*)(t1006)));
        if (t1008 == (int)0) goto Lbfccb2;
        t1013 = (int)((il2c_vc0*)(t1008))->s4();
        if ((unsigned char)(t1013) == (unsigned char)0) goto Lbfccb2;
        t1005 = (int)(t1005 + (int)1);
        t1006 = (int)(t1006 + (int)4);
    } while ((unsigned int)(t1005) < (unsigned int)3);
    Lbfccaa:;
    t1016 = (int)((int)0);
    return (int)(t1016);
    Lbfccb2:;
    if ((unsigned int)(t1005) >= (unsigned int)3) goto Lbfccaa;
    t1020 = (int)FUN_0067ddd0();
    t1021 = (int)(*(int*)((char*)(t1003) + (t1005)*4 + 188));
    t6 = (int)(t1005 << (int)2);
    t7 = (int)(t1003 + t6);
    t1022 = (int)(t7 + (int)188);
    t1023 = (int)(t1020);
    if (t1021 != (int)0) {
        *(int*)((char*)(t1022)) = (int)((int)0);
        ((il2c_vc1*)(t1021))->s1();
    }
    t1029 = (int)((int)(a4));
    t1032 = (int)(t1023);
    t1035 = (int)((il2c_vc2*)(t1032))->s11((int)(t1029), (int)((int)0), (int)(t1022));
    if ((unsigned char)(t1035) == (unsigned char)0) goto Lbfccaa;
    t1036 = (int)(*(int*)((char*)(t1022)));
    return (int)(t1036);
}
