// 0x0088a330: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
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
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual int s22(int, int, int, int, int);
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
    virtual void s11();
    virtual int s12(int, int);
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
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual int s15(int, int, int, int);
};

extern "C" unsigned char g_013cc2d8[];
extern "C" unsigned char g_013cc2dc[];

// @ 0x0088a330
extern "C" int __fastcall FUN_0088a330(char* self, int edx_unused, int a4, int a8, int a12, int a16)
{
    int t1004;
    int t1005;
    int v_l4;
    int t1010;
    int t1011;
    int t1012;
    int t1013;
    int v_l8;
    int t1015;
    int t1016;
    int t1017;
    int t1018;
    int t1021;
    int t1022;
    int t1023;
    int t1026;
    int t1027;
    int t1028;
    int t1029;
    int t1032;
    int t1035;
    int t1036;
    int t1037;
    int t1040;
    int t1041;
    int t1042;
    int t1045;
    int t1046;
    int t1050;
    t1004 = (int)((int)(self));
    t1005 = (int)(t1004 + (int)360);
    v_l4 = (int)(t1005);
    ((void (__stdcall*)(unsigned int))(*(int*)g_013cc2d8))((unsigned int)(t1005));
    t1010 = (int)(*(int*)((char*)(t1004) + 52));
    t1011 = (int)(t1010 - (int)*(int*)((char*)(t1004) + 48));
    t1012 = (int)((int)0);
    t1013 = (int)(t1011 >> (int)2);
    v_l8 = (int)(t1012);
    if ((unsigned int)(t1013) > (unsigned int)(t1012)) {
        do {
            t1015 = (int)(*(int*)((char*)(t1004) + 48));
            t1016 = (int)(*(int*)((char*)(t1015) + (t1012)*4));
            if ((unsigned char)*(unsigned char*)((char*)(t1016) + 415) != (unsigned char)0) {
                t1017 = (int)((int)(a16));
                t1018 = (int)((int)(a12));
                t1021 = (int)((int)(a8));
                t1022 = (int)((int)(a4));
                t1023 = (int)(t1004);
                t1026 = (int)((il2c_vc0*)(t1023))->s22((int)(t1022), (int)(t1021), (int)(t1016), (int)(t1018), (int)(t1017));
                if ((unsigned char)(t1026) != (unsigned char)0) goto L88a40d;
            }
            t1012 = (int)(t1012 + (int)1);
        } while ((unsigned int)(t1012) < (unsigned int)(t1013));
    }
    if ((unsigned char)*(unsigned char*)((char*)(t1004) + 352) != (unsigned char)0) {
        t1027 = (int)(*(int*)((char*)(t1004) + 52));
        t1028 = (int)(t1027 - (int)*(int*)((char*)(t1004) + 48));
        t1029 = (int)(t1028 >> (int)2);
        if ((unsigned int)(t1029) < (unsigned int)*(int*)((char*)(t1004) + 80)) {
            if ((unsigned char)*(unsigned char*)((char*)(t1004) + 354) == (unsigned char)0) {
                t1032 = (int)(t1004);
                t1035 = (int)((il2c_vc1*)(t1032))->s12((int)((int)0), (int)((int)0));
                if (t1035 != (int)0) {
                    t1036 = (int)((int)(a16));
                    t1037 = (int)((int)(a12));
                    *(unsigned char*)((char*)(t1004) + 354) += (unsigned char)1;
                    t1040 = (int)((int)(a8));
                    t1041 = (int)((int)(a4));
                    t1042 = (int)(t1004);
                    t1045 = (int)((il2c_vc2*)(t1042))->s15((int)(t1041), (int)(t1040), (int)(t1037), (int)(t1036));
                    *(unsigned char*)((char*)(t1004) + 354) -= (unsigned char)1;
                    v_l8 = (int)(t1045);
                }
            }
        }
    }
    L88a3f4:;
    t1046 = (int)(v_l4);
    ((void (__stdcall*)(unsigned int))(*(int*)g_013cc2dc))((unsigned int)(t1046));
    t1050 = (int)(v_l8);
    return (int)(t1050);
    L88a40d:;
    v_l8 = (int)(t1016);
    goto L88a3f4;
}
