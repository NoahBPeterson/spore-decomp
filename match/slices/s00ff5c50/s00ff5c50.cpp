// 0x00ff5c50: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00ff4d50/s00ff4d50.cpp, src/game/SPGonzago/SPSimulatorPlanet.cpp.

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
    virtual int s1();
};
struct il2c_vc3 {
    virtual void s0();
    virtual void s1();
    virtual int s2();
};

extern "C" unsigned char g_013f09b4[];
extern "C" unsigned char g_015b6160[];
struct C_00692f90 { void FUN_00692f90(unsigned int, unsigned int, unsigned int); };
struct C_00693e10 { int FUN_00693e10(unsigned int); };
extern "C" void __cdecl FUN_0093a780(...);
struct C_00b5b650 { int FUN_00b5b650(unsigned int); };
extern "C" int __cdecl FUN_00f473a0(...);
struct C_00ff54e0 { int FUN_00ff54e0(); };

// @ 0x00ff5c50
extern "C" bool __fastcall FUN_00ff5c50(char* self, int edx_unused, int a4)
{
    int t1003;
    int t1008;
    int t1009;
    int t1010;
    int t1014;
    int t1016;
    int t1019;
    int v_l2584;
    int t1023;
    int t1024;
    int t1027;
    int t1028;
    int v_l2580[645];
    unsigned char t1029;
    int t1033;
    int t1034;
    bool t1037;
    int t1038;
    int t1041;
    int t1044;
    int t1045;
    int t1048;
    int t1053;
    bool t1059;
    t1003 = (int)((int)(a4));
    t1008 = (int)((int)(self));
    t1009 = (int)(t1003);
    t1010 = (int)((il2c_vc0*)(t1009))->s8();
    t1014 = (int)(t1010);
    t1016 = (int)((il2c_vc1*)(t1014))->s6();
    t1019 = (int)((int)&v_l2584);
    FUN_0093a780((unsigned int)(t1016), (unsigned int)(t1019), (unsigned int)((int)1), (unsigned int)((int)0));
    t1023 = (int)(t1008);
    t1024 = (int)((C_00b5b650*)(t1023))->FUN_00b5b650((unsigned int)(t1003));
    t1027 = (int)(t1008 + (int)(-8));
    t1028 = (int)((int)&v_l2580);
    t1029 = (unsigned char)((unsigned char)(t1024));
    ((C_00692f90*)(t1028))->FUN_00692f90((unsigned int)(t1027), (unsigned int)((int)g_015b6160), (unsigned int)((int)27790630));
    if (t1029 != (unsigned char)0) {
        t1033 = (int)((int)&v_l2580);
        t1034 = (int)((C_00693e10*)(t1033))->FUN_00693e10((unsigned int)(t1003));
        if ((unsigned char)(t1034) != (unsigned char)0) {
            t1037 = true;
            goto Lff5cc0;
        }
    }
    t1037 = false;
    Lff5cc0:;
    t1038 = (int)FUN_00f473a0((unsigned int)((int)40), (unsigned int)((int)g_013f09b4), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
    if (t1038 != (int)0) {
        t1041 = (int)(t1038);
        t1038 = (int)((C_00ff54e0*)(t1041))->FUN_00ff54e0();
        t1044 = (int)(t1038);
    } else {
        t1044 = (int)((int)0);
    }
    t1045 = (int)(*(int*)((char*)(t1008) + 32));
    if (t1044 != t1045) {
        if (t1044 != (int)0) {
            t1048 = (int)(t1044);
            t1038 = (int)((il2c_vc2*)(t1048))->s1();
        }
        *(int*)((char*)(t1008) + 32) = (int)(t1044);
        if (t1045 != (int)0) {
            t1053 = (int)(t1045);
            t1038 = (int)((il2c_vc3*)(t1053))->s2();
        }
    }
    t1059 = t1037;
    return t1059;
}
