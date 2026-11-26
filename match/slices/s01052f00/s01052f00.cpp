// 0x01052f00: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPToolStrategies.cpp, match/slices/s010527f0/s010527f0.cpp.

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
    virtual int s16(int, int, int);
};

struct C_00a1ad60 { int FUN_00a1ad60(); };
extern "C" int __cdecl FUN_00b3d240(...);
extern "C" int __cdecl FUN_00ffbe50(...);

// @ 0x01052f00
extern "C" int __stdcall FUN_01052f00(int a4)
{
    int t1004;
    int t1005;
    int t1008;
    int t1009;
    int t1012;
    int t1015;
    int v_l12[3];
    int t1016;
    int t1019;
    int t1020;
    int t1021;
    int t1022;
    int t1023;
    t1004 = (int)FUN_00ffbe50();
    t1005 = (int)(t1004);
    t1008 = (int)((C_00a1ad60*)(t1005))->FUN_00a1ad60();
    if (t1008 != (int)0) {
        t1009 = (int)(t1008 + (int)1288);
    } else {
        t1009 = (int)((int)0);
    }
    t1012 = (int)FUN_00b3d240();
    t1015 = (int)((int)&v_l12);
    t1016 = (int)(t1012);
    t1019 = (int)((il2c_vc0*)(t1016))->s16((int)(t1015), (int)((int)0), (int)(t1009));
    t1020 = (int)(*(int*)((char*)(t1019)));
    t1021 = (int)((int)(a4));
    *(int*)((char*)(t1021)) = (int)(t1020);
    t1022 = (int)(*(int*)((char*)(t1019) + 4));
    *(int*)((char*)(t1021) + 4) = (int)(t1022);
    t1023 = (int)(*(int*)((char*)(t1019) + 8));
    *(int*)((char*)(t1021) + 8) = (int)(t1023);
    return (int)(t1023);
}
