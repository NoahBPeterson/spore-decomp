// 0x00efcae0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEditors/_at_00ef0000.cpp, match/slices/s00efc270/s00efc270.cpp.

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
    virtual int s20();
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
    virtual int s14();
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual int s3(int);
};

extern "C" int __cdecl FUN_0067dd10(...);
struct C_00b0f950 { void FUN_00b0f950(unsigned int); };
struct C_00b10c40 { int FUN_00b10c40(unsigned int); };
extern "C" int __cdecl FUN_00b3d280(...);
struct C_00d20430 { int FUN_00d20430(unsigned int); };

// @ 0x00efcae0
extern "C" void __cdecl FUN_00efcae0(void)
{
    int t1003;
    int t1005;
    int t1009;
    int t1011;
    int t1015;
    int t1017;
    int t1021;
    int t1022;
    int t1029;
    int t1030;
    int t1031;
    int t1035;
    t1003 = (int)FUN_0067dd10();
    t1005 = (int)(t1003);
    t1009 = (int)((il2c_vc0*)(t1005))->s20();
    t1011 = (int)(t1009);
    t1015 = (int)((il2c_vc1*)(t1011))->s14();
    if (t1015 != (int)0) {
        t1017 = (int)(t1015);
        t1021 = (int)((il2c_vc2*)(t1017))->s3((int)((int)44559570));
        if (t1021 != (int)0) {
            t1022 = (int)(t1021);
            *(unsigned char*)((char*)(t1021) + 789) = (unsigned char)((int)0);
            ((C_00d20430*)(t1022))->FUN_00d20430((unsigned int)((int)0));
            return;
        }
    }
    t1029 = (int)FUN_00b3d280();
    t1030 = (int)(t1029);
    if (t1030 != (int)0) {
        t1031 = (int)(t1030);
        ((C_00b0f950*)(t1031))->FUN_00b0f950((unsigned int)((int)0));
        t1035 = (int)(t1030);
        t1029 = (int)((C_00b10c40*)(t1035))->FUN_00b10c40((unsigned int)((int)0));
    }
    return;
}
