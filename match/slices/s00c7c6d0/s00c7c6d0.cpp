// 0x00c7c6d0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPPlayer.cpp, match/slices/s00c7c0c0/s00c7c0c0.cpp.

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
    virtual void s10();
    virtual int s11(int, int, int);
};

extern "C" unsigned char g_01472dac[];
extern "C" unsigned char g_0150d6dc[];
struct C_00597e00 { int FUN_00597e00(); };
struct C_00599440 { void FUN_00599440(unsigned int, unsigned int, unsigned int); };
extern "C" int __cdecl FUN_0067de30(...);
extern "C" void __cdecl FUN_0091ff50(...);
struct C_00b18550 { void FUN_00b18550(unsigned int); };
struct C_00c751e0 { void FUN_00c751e0(); };
struct C_00c7c4a0 { void FUN_00c7c4a0(unsigned int); };
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x00c7c6d0
extern "C" void __fastcall FUN_00c7c6d0(char* self, int edx_unused, int a4)
{
    int t1000;
    int t1004;
    int t1008;
    int t1012;
    int t1018;
    int t1019;
    int t1022;
    int t1023;
    int t1025;
    int t1028;
    int t1034;
    int t1038;
    int t1039;
    int t1043;
    int t1049;
    int t1050;
    int t1051;
    int t1052;
    int t1061;
    t1000 = (int)((int)(a4));
    t1004 = (int)((int)(self));
    ((C_00b18550*)((int)(self)))->FUN_00b18550((unsigned int)(t1000));
    t1008 = (int)(t1004 + (int)4344);
    FUN_0091ff50((unsigned int)(t1008));
    t1012 = (int)(t1004 + (int)4412);
    ((C_00c7c4a0*)(t1012))->FUN_00c7c4a0((unsigned int)((int)10));
    t1018 = (int)FUN_00f473a0((unsigned int)((int)28076), (unsigned int)((int)g_01472dac), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
    if (t1018 != (int)0) {
        t1019 = (int)(t1018);
        t1022 = (int)((C_00597e00*)(t1019))->FUN_00597e00();
        t1023 = (int)(t1022);
    } else {
        t1023 = (int)((int)0);
    }
    t1025 = (int)(*(int*)((char*)(t1004) + 4328));
    if (t1023 != t1025) {
        if (t1023 != (int)0) {
            t1028 = (int)(t1023);
            ((il2c_vc0*)(t1028))->s0();
        }
        *(int*)((char*)(t1004) + 4328) = (int)(t1023);
        if (t1025 != (int)0) {
            t1034 = (int)(t1025);
            ((il2c_vc1*)(t1034))->s1();
        }
    }
    t1038 = (int)((int)(*(int*)g_0150d6dc));
    t1039 = (int)(*(int*)((char*)(t1004) + 4328));
    ((C_00599440*)(t1039))->FUN_00599440((unsigned int)((int)(-1386870772)), (unsigned int)((int)1247560851), (unsigned int)(t1038));
    t1043 = (int)(t1004);
    *(int*)((char*)(t1004) + 4332) = (int)((int)0);
    ((C_00c751e0*)(t1043))->FUN_00c751e0();
    t1049 = (int)FUN_0067de30();
    t1050 = (int)(*(int*)((char*)(t1004) + 4596));
    t1051 = (int)(t1004 + (int)4596);
    t1052 = (int)(t1049);
    if (t1050 != (int)0) {
        *(int*)((char*)(t1051)) = (int)((int)0);
        ((il2c_vc2*)(t1050))->s1();
    }
    t1061 = (int)(t1052);
    ((il2c_vc3*)(t1061))->s11((int)((int)46802305), (int)((int)44960894), (int)(t1051));
    return;
}
