// 0x00f2f4f0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00f2e7d0/s00f2e7d0.cpp.

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
    virtual int s7();
};

extern "C" unsigned char g_015af358[];
struct C_00692f90 { void FUN_00692f90(unsigned int, unsigned int, unsigned int); };
struct C_00693e10 { void FUN_00693e10(unsigned int); };
extern "C" void __cdecl FUN_0093a780(...);
struct C_00dfce40 { void FUN_00dfce40(); };
struct C_00dff130 { void FUN_00dff130(unsigned int); };
struct C_00f2d330 { void FUN_00f2d330(); };
struct C_00f2ef10 { void FUN_00f2ef10(unsigned int); };
struct C_00f2efe0 { void FUN_00f2efe0(unsigned int, unsigned int); };
struct C_00f2f050 { void FUN_00f2f050(unsigned int, unsigned int); };

// @ 0x00f2f4f0
extern "C" void __cdecl FUN_00f2f4f0(int a4, int a8)
{
    int t1002;
    int t1003;
    int t1004;
    int t1006;
    int t1010;
    int t1013;
    int v_l3916;
    int t1014;
    int t1018;
    int t1020;
    int t1023;
    int t1027;
    int t1028;
    int t1032;
    int t1033;
    int v_l3912[333];
    int t1037;
    int t1038;
    int v_l2580[645];
    int t1042;
    int t1046;
    int t1047;
    int t1048;
    int t1052;
    int t1053;
    int t1057;
    int t1063;
    t1002 = (int)((int)(a8));
    t1003 = (int)(*(int*)((char*)(t1002) + 4));
    t1004 = (int)(*(int*)((char*)(t1002)));
    t1006 = (int)(t1002);
    ((C_00f2efe0*)(t1006))->FUN_00f2efe0((unsigned int)(t1004), (unsigned int)(t1003));
    t1010 = (int)((int)(a4));
    t1013 = (int)(t1010);
    v_l3916 = (int)((int)0);
    t1014 = (int)((il2c_vc0*)(t1013))->s8();
    t1018 = (int)(t1014);
    t1020 = (int)((il2c_vc1*)(t1018))->s6();
    t1023 = (int)((int)&v_l3916);
    FUN_0093a780((unsigned int)(t1020), (unsigned int)(t1023), (unsigned int)((int)1), (unsigned int)((int)0));
    t1027 = (int)(v_l3916);
    t1028 = (int)(t1002);
    ((C_00f2ef10*)(t1028))->FUN_00f2ef10((unsigned int)(t1027));
    t1032 = (int)((int)0);
    if ((unsigned int)(v_l3916) > (unsigned int)(t1032)) {
        do {
            t1033 = (int)((int)&v_l3912);
            ((C_00f2d330*)(t1033))->FUN_00f2d330();
            t1037 = (int)((int)&v_l3912);
            t1038 = (int)((int)&v_l2580);
            ((C_00692f90*)(t1038))->FUN_00692f90((unsigned int)(t1037), (unsigned int)((int)g_015af358), (unsigned int)((int)27790630));
            t1042 = (int)((int)&v_l2580);
            ((C_00693e10*)(t1042))->FUN_00693e10((unsigned int)(t1010));
            t1046 = (int)(*(int*)((char*)(t1002) + 4));
            if ((unsigned int)(t1046) < (unsigned int)*(int*)((char*)(t1002) + 8)) {
                t1047 = (int)(t1046 + (int)1332);
                *(int*)((char*)(t1002) + 4) = (int)(t1047);
                if (t1046 == (int)0) goto Lf2f5b4;
                t1048 = (int)((int)&v_l3912);
                ((C_00dff130*)(t1046))->FUN_00dff130((unsigned int)(t1048));
                goto Lf2f5b4;
            }
            t1052 = (int)((int)&v_l3912);
            t1053 = (int)(t1002);
            ((C_00f2f050*)(t1053))->FUN_00f2f050((unsigned int)(t1046), (unsigned int)(t1052));
            Lf2f5b4:;
            t1057 = (int)((int)&v_l3912);
            ((C_00dfce40*)(t1057))->FUN_00dfce40();
            t1032 = (int)(t1032 + (int)1);
        } while ((unsigned int)(t1032) < (unsigned int)(v_l3916));
    }
    t1063 = (int)(t1010);
    ((il2c_vc2*)(t1063))->s7();
    return;
}
