// 0x010030c0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPSimulatorSpaceGame.cpp, match/slices/s010021a0/s010021a0.cpp.

struct il2c_vc0 {
    virtual void s0();
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
    virtual void s10(int);
};
struct il2c_vc3 {
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
};

extern "C" unsigned char g_013f09b4[];
extern "C" int __cdecl FUN_0067ddc0(...);
extern "C" int __cdecl FUN_00f473a0(...);
struct C_00ff9390 { void FUN_00ff9390(); };
extern "C" int __cdecl FUN_01021080(...);
struct C_01070ba0 { int FUN_01070ba0(); };
struct C_01073700 { void FUN_01073700(); };

// @ 0x010030c0
extern "C" void __fastcall FUN_010030c0(char* self, int edx_unused)
{
    int t1003;
    int t1006;
    int t1007;
    int t1010;
    int t1011;
    int t1013;
    int t1016;
    int t1022;
    int t1026;
    int t1030;
    int t1037;
    int t1038;
    int t1043;
    int t1050;
    t1003 = (int)((int)(self));
    if ((int)*(int*)((char*)(t1003) + 20) == (int)0) {
        t1006 = (int)FUN_00f473a0((unsigned int)((int)1708), (unsigned int)((int)g_013f09b4), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
        if (t1006 != (int)0) {
            t1007 = (int)(t1006);
            t1010 = (int)((C_01070ba0*)(t1007))->FUN_01070ba0();
            t1011 = (int)(t1010);
        } else {
            t1011 = (int)((int)0);
        }
        t1013 = (int)(*(int*)((char*)(t1003) + 20));
        if (t1011 != t1013) {
            if (t1011 != (int)0) {
                t1016 = (int)(t1011);
                ((il2c_vc0*)(t1016))->s0();
            }
            *(int*)((char*)(t1003) + 20) = (int)(t1011);
            if (t1013 != (int)0) {
                t1022 = (int)(t1013);
                ((il2c_vc1*)(t1022))->s1();
            }
        }
        t1026 = (int)(*(int*)((char*)(t1003) + 20));
        ((C_01073700*)(t1026))->FUN_01073700();
        t1030 = (int)(*(int*)((char*)(t1003) + 84));
        if (t1030 != (int)0) {
            ((C_00ff9390*)(t1030))->FUN_00ff9390();
        }
    }
    t1037 = (int)FUN_0067ddc0();
    t1038 = (int)(t1037);
    if (t1038 != (int)0) {
        t1037 = (int)FUN_01021080();
        if (t1037 == (int)0) {
            t1043 = (int)(t1038);
            ((il2c_vc2*)(t1043))->s10((int)((int)1));
            t1050 = (int)(t1038);
            ((il2c_vc3*)(t1050))->s9();
            return;
        }
    }
    return;
}
