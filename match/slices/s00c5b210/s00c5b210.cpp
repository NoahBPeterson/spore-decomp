// 0x00c5b210: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPMissionRaid.cpp, match/slices/s00c5a580/s00c5a580.cpp.

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
    virtual int s15();
};

extern "C" unsigned char g_01576bc8[];
struct C_00692f90 { void FUN_00692f90(unsigned int, unsigned int, unsigned int); };
struct C_00693e10 { int FUN_00693e10(unsigned int); };
struct C_00c44ad0 { int FUN_00c44ad0(unsigned int); };

// @ 0x00c5b210
// @ 0x00c5b210
extern "C" bool __fastcall FUN_00c5b210(char* self, int edx_unused, int a4)
{
    int t1003;
    int t1005;
    int t1006;
    int t1009;
    int v_l2580[645];
    unsigned char t1010;
    int t1014;
    int t1015;
    bool t1018;
    int t1021;
    int t1022;
    bool t1027;
    t1003 = (int)((int)(a4));
    t1005 = (int)((int)(self));
    t1006 = (int)((C_00c44ad0*)((int)(self)))->FUN_00c44ad0((unsigned int)(t1003));
    t1009 = (int)((int)&v_l2580);
    t1010 = (unsigned char)((unsigned char)(t1006));
    ((C_00692f90*)(t1009))->FUN_00692f90((unsigned int)(t1005), (unsigned int)((int)g_01576bc8), (unsigned int)((int)27790630));
    t1014 = (int)((int)&v_l2580);
    t1015 = (int)((C_00693e10*)(t1014))->FUN_00693e10((unsigned int)(t1003));
    if ((unsigned char)(t1015) != (unsigned char)0) {
        if (t1010 != (unsigned char)0) {
            t1018 = true;
            goto Lc5b256;
        }
    }
    t1018 = false;
    Lc5b256:;
    t1021 = (int)(t1003);
    t1022 = (int)((il2c_vc0*)(t1021))->s15();
    if ((unsigned int)(t1022) < (unsigned int)2162708) {
        t1022 = (int)(*(int*)((char*)(t1005) + 140));
        *(int*)((char*)(t1005) + 560) = (int)(t1022);
    }
    t1027 = t1018;
    return t1027;
}
