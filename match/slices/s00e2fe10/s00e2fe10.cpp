// 0x00e2fe10: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/_at_00e20000.cpp, match/slices/s00e2f6e0/s00e2f6e0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8(int, int);
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
    virtual void s8(int, int);
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
    virtual void s8(int, int);
};

extern "C" unsigned char g_00f62def[];
extern "C" unsigned char g_014818a4[];
struct C_0067dcc0 { int FUN_0067dcc0(); };
extern "C" int __cdecl FUN_0067dcc0(...);
struct C_007f83e0 { int FUN_007f83e0(); };
struct C_00e2f980 { int FUN_00e2f980(); };
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x00e2fe10
// @ 0x00e2fe10
extern "C" int __fastcall FUN_00e2fe10(char* self, int edx_unused)
{
    int t1002;
    int t1004;
    int t1005;
    int t1009;
    int t1014;
    int t1015;
    int t1019;
    int t1024;
    int t1025;
    int t1029;
    int t1034;
    int t1035;
    int t1038;
    int t1041;
    int t1042;
    t1002 = (int)((int)(self));
    if (t1002 != (int)0) {
        t1004 = (int)(t1002 + (int)28);
    } else {
        t1004 = (int)((int)0);
    }
    t1005 = (int)((C_0067dcc0*)((int)(self)))->FUN_0067dcc0();
    t1009 = (int)(t1005);
    ((il2c_vc0*)(t1009))->s8((int)(t1004), (int)((int)g_00f62def));
    if (t1002 != (int)0) {
        t1014 = (int)(t1002 + (int)28);
    } else {
        t1014 = (int)((int)0);
    }
    t1015 = (int)FUN_0067dcc0();
    t1019 = (int)(t1015);
    ((il2c_vc1*)(t1019))->s8((int)(t1014), (int)((int)(-751080798)));
    if (t1002 != (int)0) {
        t1024 = (int)(t1002 + (int)28);
    } else {
        t1024 = (int)((int)0);
    }
    t1025 = (int)FUN_0067dcc0();
    t1029 = (int)(t1025);
    ((il2c_vc2*)(t1029))->s8((int)(t1024), (int)((int)1396402852));
    t1034 = (int)(t1002);
    t1035 = (int)((C_00e2f980*)(t1034))->FUN_00e2f980();
    if ((int)*(int*)((char*)(t1002) + 92) == (int)0) {
        t1038 = (int)FUN_00f473a0((unsigned int)((int)32), (unsigned int)((int)g_014818a4), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
        if (t1038 != (int)0) {
            t1041 = (int)(t1038);
            t1042 = (int)((C_007f83e0*)(t1041))->FUN_007f83e0();
            *(int*)((char*)(t1002) + 92) = (int)(t1042);
            return (int)(t1042);
        }
        t1035 = (int)((int)0);
        *(int*)((char*)(t1002) + 92) = (int)(t1035);
    }
    return (int)(t1035);
}
