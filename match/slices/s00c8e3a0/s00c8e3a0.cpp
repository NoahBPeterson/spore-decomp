// 0x00c8e3a0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPTribe.cpp, match/slices/s00c8db30/s00c8db30.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual int s8();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual int s6();
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
    virtual int s8();
};
struct il2c_vc3 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual int s6();
};
struct il2c_vc4 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual int s8();
};
struct il2c_vc5 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual int s6();
};

extern "C" void __cdecl FUN_0093a780(...);

// @ 0x00c8e3a0
extern "C" int __cdecl FUN_00c8e3a0(int a4, int a8)
{
    int t1001;
    int t1005;
    int t1008;
    int t1010;
    int t1014;
    int t1015;
    int t1021;
    int t1024;
    int t1026;
    int t1030;
    int t1031;
    int t1037;
    int t1040;
    int t1042;
    int t1046;
    int t1047;
    int t1052;
    t1001 = (int)((int)(a4));
    t1005 = (int)(t1001);
    t1008 = (int)((il2c_vc0*)(t1005))->s8();
    t1010 = (int)(t1008);
    t1014 = (int)((il2c_vc1*)(t1010))->s6();
    t1015 = (int)((int)(a8));
    FUN_0093a780((unsigned int)(t1014), (unsigned int)(t1015), (unsigned int)((int)1), (unsigned int)((int)0));
    t1021 = (int)(t1001);
    t1024 = (int)((il2c_vc2*)(t1021))->s8();
    t1026 = (int)(t1024);
    t1030 = (int)((il2c_vc3*)(t1026))->s6();
    t1031 = (int)(t1015 + (int)4);
    FUN_0093a780((unsigned int)(t1030), (unsigned int)(t1031), (unsigned int)((int)1), (unsigned int)((int)0));
    t1037 = (int)(t1001);
    t1040 = (int)((il2c_vc4*)(t1037))->s8();
    t1042 = (int)(t1040);
    t1046 = (int)((il2c_vc5*)(t1042))->s6();
    t1047 = (int)(t1015 + (int)8);
    FUN_0093a780((unsigned int)(t1046), (unsigned int)(t1047), (unsigned int)((int)1), (unsigned int)((int)0));
    t1052 = (int)(t1001);
    return (int)(t1052);
}
