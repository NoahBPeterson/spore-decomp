// 0x00fdc980: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00fdbd60/s00fdbd60.cpp, src/game/SPGonzago/SPAppModeSpace.cpp.

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
    virtual void s20();
    virtual int s21(int);
};
struct il2c_vc1 {
    virtual void s0();
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3(int);
};
struct il2c_vc3 {
    virtual void s0();
    virtual void s1();
};

extern "C" unsigned char g_00eb9968[];
extern "C" int __cdecl FUN_0067ddd0(...);
extern "C" int __cdecl FUN_00b3d350(...);
struct C_00b8c0f0 { void FUN_00b8c0f0(); };
struct C_00fda9f0 { void FUN_00fda9f0(); };
struct C_00fdc150 { void FUN_00fdc150(); };

// @ 0x00fdc980
extern "C" void __fastcall FUN_00fdc980(char* self, int edx_unused)
{
    int t1002;
    int t1008;
    int t1009;
    int t1013;
    int t1019;
    int t1021;
    int t1025;
    int t1026;
    int t1029;
    int t1035;
    int t1041;
    t1002 = (int)((int)(self));
    if ((int)*(int*)((char*)(t1002) + 348) != (int)0) {
        ((C_00fda9f0*)((int)(self)))->FUN_00fda9f0();
        t1008 = (int)FUN_00b3d350();
        t1009 = (int)(t1008);
        ((C_00b8c0f0*)(t1009))->FUN_00b8c0f0();
        t1013 = (int)(t1002);
        ((C_00fdc150*)(t1013))->FUN_00fdc150();
    }
    t1019 = (int)FUN_0067ddd0();
    t1021 = (int)(t1019);
    t1025 = (int)((il2c_vc0*)(t1021))->s21((int)((int)g_00eb9968));
    t1026 = (int)(t1025);
    if (t1026 != (int)0) {
        t1029 = (int)(t1026);
        ((il2c_vc1*)(t1029))->s0();
        t1035 = (int)(t1026);
        ((il2c_vc2*)(t1035))->s3((int)((int)5));
        t1041 = (int)(t1026);
        ((il2c_vc3*)(t1041))->s1();
        return;
    }
    return;
}
