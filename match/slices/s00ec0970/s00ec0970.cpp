// 0x00ec0970: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00ebfad0/s00ebfad0.cpp.

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
};

extern "C" unsigned char g_0145f924[];
extern "C" unsigned char g_0168d824[];
struct C_00c04590 { int FUN_00c04590(); };
struct C_00c047d0 { int FUN_00c047d0(); };
struct C_00d997e0 { void FUN_00d997e0(); };
struct C_00f30bc0 { int FUN_00f30bc0(); };
struct C_00f30cc0 { int FUN_00f30cc0(unsigned int, float, float); };
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x00ec0970
extern "C" float __cdecl FUN_00ec0970(int a4, int a8, int a12, int a16, int a20, int a24)
{
    int t1001;
    int t1002;
    int t1005;
    int t1010;
    int t1014;
    int t1015;
    int t1018;
    int t1019;
    int t1023;
    int t1026;
    int t1027;
    int t1028;
    int t1029;
    int t1033;
    int t1034;
    int t1037;
    int t1038;
    int t1039;
    int t1042;
    int t1043;
    int t1044;
    t1001 = (int)((int)(a4));
    t1002 = (int)(t1001);
    t1005 = (int)((C_00c047d0*)(t1002))->FUN_00c047d0();
    if (t1005 != (int)4) {
        return (float)((float)0);
    }
    t1010 = (int)(t1001);
    ((il2c_vc0*)(t1010))->s19();
    t1014 = (int)((int)(*(int*)g_0168d824));
    t1015 = (int)(t1001 + (int)1448);
    if (t1014 == (int)0) {
        t1018 = (int)FUN_00f473a0((unsigned int)((int)36), (unsigned int)((int)g_0145f924), (unsigned int)(t1014), (unsigned int)(t1014), (unsigned int)(t1014), (unsigned int)(t1014));
        if (t1018 != (int)0) {
            t1019 = (int)(t1018);
            t1014 = (int)((C_00f30bc0*)(t1019))->FUN_00f30bc0();
        } else {
            t1014 = (int)((int)0);
        }
        *(int*)g_0168d824 = (int)(t1014);
    }
    t1023 = (int)(t1014);
    t1026 = (int)((C_00f30cc0*)(t1023))->FUN_00f30cc0((unsigned int)(t1015), (float)((float)0), (float)((float)0));
    t1027 = (int)(t1026);
    if (t1027 != (int)0) {
        t1028 = (int)((int)(a20));
        if (t1028 != (int)0) {
            t1029 = (int)(t1028);
            ((C_00d997e0*)(t1029))->FUN_00d997e0();
        }
        t1033 = (int)((int)(a24));
        t1034 = (int)(t1001);
        *(unsigned char*)((char*)(t1033)) = (unsigned char)((int)1);
        t1037 = (int)((C_00c04590*)(t1034))->FUN_00c04590();
        t1038 = (int)(t1037 + (int)356);
        if (t1001 == (int)*(int*)((char*)(t1038))) {
            t1039 = (int)(t1001);
            t1042 = (int)((C_00c04590*)(t1039))->FUN_00c04590();
            t1043 = (int)(t1042 + (int)360);
            if ((int)*(int*)((char*)(t1043)) != t1043) {
                t1044 = (int)((int)1);
                goto Lec0a1f;
            }
        }
        t1044 = (int)((int)0);
        Lec0a1f:;
        *(int*)((char*)(t1028) + 4) = (int)(t1027);
        *(int*)((char*)(t1028) + 24) = (int)(t1044);
        *(int*)((char*)(t1028) + 8) = (int)((int)0);
        *(int*)((char*)(t1028)) = (int)((int)0);
        return (float)((float)1);
    }
    return (float)((float)0);
}
