// 0x00edd6b0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00edcfc0/s00edcfc0.cpp.

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
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc3 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc4 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc5 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
};
struct il2c_vc6 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
};
struct il2c_vc7 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
};
struct il2c_vc8 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc9 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc10 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc11 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc12 {
    virtual void s0();
    virtual void s1();
    virtual int s2();
};

extern "C" unsigned char g_013eb394[];
extern "C" unsigned char g_013eb938[];
extern "C" unsigned char g_013ec458[];
extern "C" unsigned char g_0148a7d8[];
extern "C" unsigned char g_0148a7dc[];
extern "C" unsigned char g_0148a7e4[];
extern "C" unsigned char g_0148a7f0[];
extern "C" unsigned char g_0148a80c[];
extern "C" void __cdecl FUN_00571db0(...);
struct C_0067dcc0 { int FUN_0067dcc0(); };
extern "C" int __cdecl FUN_0067dcc0(...);
struct C_00e0a400 { void FUN_00e0a400(); };

// @ 0x00edd6b0
extern "C" int __fastcall FUN_00edd6b0(char* self, int edx_unused)
{
    int t1002;
    int t1004;
    int t1007;
    int t1010;
    int t1012;
    int t1017;
    int t1018;
    int t1019;
    int t1020;
    int t1021;
    int t1025;
    int t1031;
    int t1037;
    int t1043;
    int t1049;
    int t1053;
    int t1059;
    int t1065;
    int t1071;
    int t1077;
    int t1083;
    int t1089;
    int t1095;
    int t1096;
    t1002 = (int)((int)(self));
    t1004 = (int)(t1002 + (int)16);
    *(int*)((char*)(t1002)) = (int)((int)g_0148a80c);
    *(int*)((char*)(t1002) + 8) = (int)((int)g_0148a7f0);
    *(int*)((char*)(t1002) + 12) = (int)((int)g_0148a7e4);
    *(int*)((char*)(t1004)) = (int)((int)g_0148a7dc);
    *(int*)((char*)(t1002) + 20) = (int)((int)g_0148a7d8);
    t1007 = (int)((C_0067dcc0*)((int)(self)))->FUN_0067dcc0();
    if (t1007 != (int)0) {
        t1010 = (int)FUN_0067dcc0();
        t1012 = (int)(t1010);
        ((il2c_vc0*)(t1012))->s11((int)(t1004), (int)((int)106952010), (int)((int)(-9999)));
    }
    t1017 = (int)(*(int*)((char*)(t1002) + 240));
    if (t1017 != (int)0) {
        t1018 = (int)(*(int*)((char*)(t1002) + 256));
        t1019 = (int)(*(int*)((char*)(t1002) + 252));
        t1020 = (int)(*(int*)((char*)(t1002) + 248));
        t1021 = (int)(*(int*)((char*)(t1002) + 244));
        *(int*)((char*)(t1002) + 240) = (int)((int)0);
        FUN_00571db0((unsigned int)(t1017), (unsigned int)(t1021), (unsigned int)(t1020), (unsigned int)(t1019), (unsigned int)(t1018));
    }
    t1025 = (int)(*(int*)((char*)(t1002) + 216));
    if (t1025 != (int)0) {
        ((il2c_vc1*)(t1025))->s1();
    }
    t1031 = (int)(*(int*)((char*)(t1002) + 212));
    if (t1031 != (int)0) {
        ((il2c_vc2*)(t1031))->s1();
    }
    t1037 = (int)(*(int*)((char*)(t1002) + 192));
    if (t1037 != (int)0) {
        ((il2c_vc3*)(t1037))->s1();
    }
    t1043 = (int)(*(int*)((char*)(t1002) + 188));
    if (t1043 != (int)0) {
        ((il2c_vc4*)(t1043))->s1();
    }
    t1049 = (int)(t1002 + (int)76);
    ((C_00e0a400*)(t1049))->FUN_00e0a400();
    t1053 = (int)(*(int*)((char*)(t1002) + 72));
    if (t1053 != (int)0) {
        ((il2c_vc5*)(t1053))->s2();
    }
    t1059 = (int)(*(int*)((char*)(t1002) + 68));
    if (t1059 != (int)0) {
        ((il2c_vc6*)(t1059))->s2();
    }
    t1065 = (int)(*(int*)((char*)(t1002) + 64));
    if (t1065 != (int)0) {
        ((il2c_vc7*)(t1065))->s2();
    }
    t1071 = (int)(*(int*)((char*)(t1002) + 40));
    if (t1071 != (int)0) {
        ((il2c_vc8*)(t1071))->s1();
    }
    t1077 = (int)(*(int*)((char*)(t1002) + 36));
    if (t1077 != (int)0) {
        ((il2c_vc9*)(t1077))->s1();
    }
    t1083 = (int)(*(int*)((char*)(t1002) + 32));
    if (t1083 != (int)0) {
        ((il2c_vc10*)(t1083))->s1();
    }
    t1089 = (int)(*(int*)((char*)(t1002) + 28));
    if (t1089 != (int)0) {
        ((il2c_vc11*)(t1089))->s1();
    }
    t1095 = (int)(*(int*)((char*)(t1002) + 24));
    if (t1095 != (int)0) {
        t1096 = (int)(t1095 + (int)4);
        t1095 = (int)((il2c_vc12*)(t1096))->s2();
    }
    *(int*)((char*)(t1004)) = (int)((int)g_013eb394);
    *(int*)((char*)(t1002) + 8) = (int)((int)g_013eb938);
    *(int*)((char*)(t1002)) = (int)((int)g_013ec458);
    return (int)(t1095);
}
