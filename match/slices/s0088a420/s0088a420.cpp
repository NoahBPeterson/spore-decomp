// 0x0088a420: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s008894a0/s008894a0.cpp.

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
    virtual void s18(int, int, int, int, int, int, int, int, int, int);
};
struct il2c_gm1 { int m(unsigned int); };
typedef int (il2c_gm1::*il2c_gp1)(unsigned int);

extern "C" unsigned char g_013cc2d8[];
extern "C" unsigned char g_013cc2dc[];

// @ 0x0088a420
extern "C" bool __fastcall FUN_0088a420(char* self, int edx_unused, int a4, int a8, int a12, int a16, int a20, int a24, int a28, int a32)
{
    int t1003;
    int t1004;
    int t1008;
    int t1009;
    int t1011;
    int t1012;
    int t1014;
    int t1016;
    int t1017;
    int t1018;
    int t1019;
    int t1020;
    int t1021;
    int t1022;
    bool t1031;
    bool t1037;
    t1003 = (int)((int)(self));
    t1004 = (int)(t1003 + (int)360);
    ((void (__stdcall*)(unsigned int))(*(int*)g_013cc2d8))((unsigned int)(t1004));
    t1008 = (int)((int)(a4));
    t1009 = (int)(*(int*)((char*)(t1008) + 56));
    if (t1009 != (int)0) {
        t1011 = (int)((int)(a32));
        t1012 = (int)((int)(a28));
        t1014 = (int)((int)(a24));
        t1016 = (int)((int)(a20));
        t1017 = (int)((int)(a16));
        t1018 = (int)(*(int*)((char*)(t1008) + 68));
        t1019 = (int)(*(int*)((char*)(t1008) + 60));
        t1020 = (int)((int)(a12));
        t1021 = (int)((int)(a8));
        t1022 = (int)(t1003);
        ((il2c_vc0*)(t1022))->s18((int)(t1009), (int)(t1021), (int)(t1020), (int)(t1019), (int)(t1018), (int)(t1017), (int)(t1016), (int)(t1014), (int)(t1012), (int)(t1011));
        ((int (__stdcall*)(unsigned int))(*(int*)g_013cc2dc))((unsigned int)(t1004));
        t1031 = true;
        return (bool)(t1031);
    }
    (((il2c_gm1*)(t1009))->*(*(il2c_gp1*)g_013cc2dc))((unsigned int)(t1004));
    t1037 = false;
    return (bool)(t1037);
}
