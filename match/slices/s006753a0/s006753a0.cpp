// 0x006753a0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00674640/s00674640.cpp.

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
    virtual void s11(int, int, int);
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
    virtual void s11(int, int, int);
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
    virtual void s11(int, int, int);
};
struct il2c_vc3 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual int s7(int);
};
struct il2c_vc4 {
    virtual void s0();
    virtual int s1();
};
struct il2c_vc5 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
};

extern "C" unsigned char g_0152906c[];
struct C_005fe1d0 { int FUN_005fe1d0(); };
extern "C" void __cdecl FUN_0067cbe0(...);
extern "C" int __cdecl FUN_0067de20(...);
struct C_00883860 { int FUN_00883860(); };

// @ 0x006753a0
extern "C" void __fastcall FUN_006753a0(char* self, int edx_unused)
{
    int t1003;
    int t1006;
    int t1007;
    int t1010;
    int t1016;
    int t1022;
    int t1028;
    int t1029;
    int t1032;
    int t1036;
    int t1037;
    int t1045;
    int t1048;
    t1003 = (int)((int)(self));
    t1006 = (int)((C_00883860*)((int)(self)))->FUN_00883860();
    t1007 = (int)(t1006);
    t1010 = (int)(t1007);
    ((il2c_vc0*)(t1010))->s11((int)(t1003), (int)((int)34788327), (int)((int)(-9999)));
    t1016 = (int)(t1007);
    ((il2c_vc1*)(t1016))->s11((int)(t1003), (int)((int)37281436), (int)((int)(-9999)));
    t1022 = (int)(t1007);
    ((il2c_vc2*)(t1022))->s11((int)(t1003), (int)((int)79622627), (int)((int)(-9999)));
    t1028 = (int)FUN_0067de20();
    t1029 = (int)((int)(*(int*)g_0152906c));
    t1032 = (int)(t1028);
    ((il2c_vc3*)(t1032))->s7((int)(t1029));
    t1036 = (int)(*(int*)((char*)(t1003) + 8));
    t1037 = (int)((int)0);
    if (t1036 != t1037) {
        *(int*)((char*)(t1003) + 8) = (int)(t1037);
        ((il2c_vc4*)(t1036))->s1();
    }
    if ((int)*(int*)((char*)(t1003) + 4) != t1037) {
        FUN_0067cbe0((unsigned int)(t1037));
        t1045 = (int)(*(int*)((char*)(t1003) + 4));
        ((C_005fe1d0*)(t1045))->FUN_005fe1d0();
        t1048 = (int)(*(int*)((char*)(t1003) + 4));
        if (t1048 != t1037) {
            *(int*)((char*)(t1003) + 4) = (int)(t1037);
            ((il2c_vc5*)(t1048))->s2();
            return;
        }
    }
    return;
}
