// 0x009338e0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00933320/s00933320.cpp, src/game/UTFSpore_Win32/EAInifile.cpp.

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
    virtual int s9(int, int, int);
};

extern "C" unsigned char g_01667bac[];
extern "C" unsigned char g_01667bae[];
extern "C" int __cdecl FUN_00939d30(...);
extern "C" void __cdecl FUN_00f47380(...);

// @ 0x009338e0
// @ 0x009338e0
extern "C" int __cdecl FUN_009338e0(int a4, int a8, int a12, int a16, int a20)
{
    int t1000;
    int t1002;
    int v_l16[4];
    int t1004;
    int t1008;
    int t1009;
    int t1012;
    int t1013;
    int t1014;
    int t1015;
    int t1018;
    int t1019;
    int t1020;
    int t1021;
    int t1025;
    t1000 = (int)((int)(a4));
    t1002 = (int)((int)&v_l16);
    t1004 = (int)((int)g_01667bac);
    (*(int*)&v_l16[0]) = (int)(t1004);
    (*(int*)&v_l16[1]) = (int)(t1004);
    t1008 = (int)((int)0);
    (*(int*)&v_l16[2]) = (int)((int)g_01667bae);
    t1009 = (int)((il2c_vc0*)(t1000))->s9((int)(a8), (int)(a12), (int)(t1002));
    if (t1009 != (int)0) {
        t1012 = (int)((int)(a16));
        t1013 = (int)((*(int*)&v_l16[0]));
        t1014 = (int)((int)&a20);
        t1015 = (int)FUN_00939d30((unsigned int)(t1013), (unsigned int)(t1012), (unsigned int)(t1014));
        t1008 = (int)(t1015);
    }
    t1018 = (int)((*(int*)&v_l16[2]));
    t1019 = (int)((*(int*)&v_l16[0]));
    t1020 = (int)(t1018 - t1019);
    t1021 = (int)(t1020 & (int)(-2));
    if (t1021 > (int)2) {
        if (t1019 != (int)0) {
            FUN_00f47380((unsigned int)(t1019));
        }
    }
    t1025 = (int)(t1008);
    return (int)(t1025);
}
