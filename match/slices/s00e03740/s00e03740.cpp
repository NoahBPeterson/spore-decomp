// 0x00e03740: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00e033d0/s00e033d0.cpp, src/game/SPGonzago/SPUIGlobalUI.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
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
    virtual int s8();
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
    virtual void s8(int);
};
struct il2c_vc4 {
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
struct il2c_vc5 {
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
struct il2c_vc6 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual int s8(int);
};

extern "C" unsigned char g_0169e3e8[];
extern "C" void __cdecl FUN_00571db0(...);
struct C_0067ca40 { void FUN_0067ca40(); };
extern "C" int __cdecl FUN_0067cac0(...);
extern "C" int __cdecl FUN_0067de40(...);
struct C_00811ad0 { void FUN_00811ad0(unsigned int); };
extern "C" void __cdecl FUN_00dd14b0(...);
struct C_00e02e10 { void FUN_00e02e10(); };
extern "C" void __cdecl FUN_00e097c0(...);

// @ 0x00e03740
extern "C" bool __fastcall FUN_00e03740(char* self, int edx_unused)
{
    int t1002;
    int t1003;
    int t1005;
    int t1009;
    int t1015;
    int t1019;
    int t1031;
    int t1032;
    int t1033;
    int t1034;
    int t1035;
    int t1041;
    int t1042;
    int t1048;
    int t1050;
    int t1054;
    int t1055;
    int t1058;
    int t1062;
    int t1065;
    int t1068;
    int t1070;
    int t1074;
    int t1077;
    int t1079;
    int t1083;
    int t1085;
    bool t1090;
    t1002 = (int)((int)(self));
    t1003 = (int)(*(int*)((char*)(t1002) + 8));
    t1005 = (int)((int)0);
    if (t1003 != t1005) {
        ((C_00811ad0*)(t1003))->FUN_00811ad0((unsigned int)((int)1));
        t1009 = (int)(*(int*)((char*)(t1002) + 8));
        if (t1009 != t1005) {
            *(int*)((char*)(t1002) + 8) = (int)(t1005);
            ((il2c_vc0*)(t1009))->s2();
        }
    }
    t1015 = (int)(*(int*)((char*)(t1002) + 4));
    if (t1015 != t1005) {
        ((C_00e02e10*)(t1015))->FUN_00e02e10();
        t1019 = (int)(*(int*)((char*)(t1002) + 4));
        if (t1019 != t1005) {
            *(int*)((char*)(t1002) + 4) = (int)(t1005);
            ((il2c_vc1*)(t1019))->s1();
        }
    }
    FUN_00dd14b0();
    FUN_00e097c0();
    t1031 = (int)(*(int*)((char*)(t1002) + 84));
    if (t1031 != t1005) {
        t1032 = (int)(*(int*)((char*)(t1002) + 100));
        t1033 = (int)(*(int*)((char*)(t1002) + 96));
        t1034 = (int)(*(int*)((char*)(t1002) + 92));
        t1035 = (int)(*(int*)((char*)(t1002) + 88));
        *(int*)((char*)(t1002) + 84) = (int)(t1005);
        FUN_00571db0((unsigned int)(t1031), (unsigned int)(t1035), (unsigned int)(t1034), (unsigned int)(t1033), (unsigned int)(t1032));
    }
    t1041 = (int)FUN_0067cac0();
    t1042 = (int)(t1041);
    ((C_0067ca40*)(t1042))->FUN_0067ca40();
    t1048 = (int)FUN_0067de40();
    t1050 = (int)(t1048);
    t1054 = (int)((il2c_vc2*)(t1050))->s8();
    t1055 = (int)((int)(*(int*)g_0169e3e8));
    t1058 = (int)(t1054);
    ((il2c_vc3*)(t1058))->s8((int)(t1055));
    *(int*)g_0169e3e8 = (int)(t1005);
    t1062 = (int)(t1002 + (int)12);
    t1065 = (int)FUN_0067de40();
    if (t1065 != (int)0) {
        t1068 = (int)FUN_0067de40();
        t1070 = (int)(t1068);
        t1065 = (int)((il2c_vc4*)(t1070))->s8();
        if (t1065 != (int)0) {
            if (t1062 != t1005) {
                t1074 = (int)(t1062 + (int)4);
            } else {
                t1074 = (int)((int)0);
            }
            t1077 = (int)FUN_0067de40();
            t1079 = (int)(t1077);
            t1083 = (int)((il2c_vc5*)(t1079))->s8();
            t1085 = (int)(t1083);
            t1065 = (int)((il2c_vc6*)(t1085))->s8((int)(t1074));
        }
    }
    t1090 = true;
    return (bool)(t1090);
}
