// 0x00e53580: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00e52d80/s00e52d80.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual int s3(int);
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
    virtual void s10(int, int);
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
    virtual void s2();
    virtual void s3(int);
};
struct il2c_vc4 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3(int);
};
struct il2c_vc5 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5(int, int, int);
};
struct il2c_vc6 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual int s5(int, int, int);
};

extern "C" unsigned char g_016b3c04[];
extern "C" unsigned char g_016b3c08[];
extern "C" unsigned char g_016b3c0c[];
struct C_008105b0 { int FUN_008105b0(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00883860(...);

// @ 0x00e53580
extern "C" int __cdecl FUN_00e53580(void)
{
    int t1000;
    int t1001;
    int t1002;
    int t1006;
    int t1008;
    int t1013;
    int t1018;
    int t1019;
    int t1025;
    int t1026;
    int t1032;
    int t1033;
    int t1039;
    int t1042;
    int t1043;
    unsigned char t16;
    int t1046;
    unsigned char t22;
    int t1052;
    int t1053;
    int t1056;
    t1000 = (int)((int)(*(int*)g_016b3c0c));
    t1001 = (int)(*(int*)((char*)(t1000) + 144));
    t1002 = (int)((C_008105b0*)(t1001))->FUN_008105b0((unsigned int)((int)(-754595196)), (unsigned int)((int)1));
    if (t1002 != (int)0) {
        t1006 = (int)(t1002);
        t1008 = (int)((il2c_vc0*)(t1006))->s3((int)((int)(-1898807686)));
    } else {
        t1008 = (int)((int)0);
    }
    t1013 = (int)(t1008);
    ((il2c_vc1*)(t1013))->s10((int)((int)4), (int)((int)0));
    t1018 = (int)((int)(*(int*)g_016b3c08));
    t1019 = (int)(*(int*)((char*)(t1018) + 90556));
    ((il2c_vc2*)(t1019))->s3((int)((int)0));
    t1025 = (int)((int)(*(int*)g_016b3c08));
    t1026 = (int)(*(int*)((char*)(t1025) + 90548));
    ((il2c_vc3*)(t1026))->s3((int)((int)0));
    t1032 = (int)((int)(*(int*)g_016b3c08));
    t1033 = (int)(*(int*)((char*)(t1032) + 90568));
    ((il2c_vc4*)(t1033))->s3((int)((int)0));
    t1039 = (int)FUN_00883860();
    t1042 = (int)(t1039);
    t1043 = (int)((int)(*(int*)g_016b3c04));
    t16 = (unsigned char)((unsigned char)*(unsigned char*)((char*)(t1043) + 20828) & (unsigned char)2);
    if (t16 != (unsigned char)0) {
        t1046 = (int)(t1042);
        ((il2c_vc5*)(t1046))->s5((int)((int)59142804), (int)((int)0), (int)((int)0));
        t1043 = (int)((int)(*(int*)g_016b3c04));
    }
    t22 = (unsigned char)((unsigned char)*(unsigned char*)((char*)(t1043) + 20828) & (unsigned char)1);
    if (t22 != (unsigned char)0) {
        t1052 = (int)(t1042);
        t1053 = (int)((il2c_vc6*)(t1052))->s5((int)((int)88521656), (int)((int)0), (int)((int)0));
        t1056 = (int)((int)(*(int*)g_016b3c04));
        *(int*)((char*)(t1056) + 20828) = (int)((int)0);
        return (int)(t1053);
    }
    *(int*)((char*)(t1043) + 20828) = (int)((int)0);
    return (int)(t1043);
}
