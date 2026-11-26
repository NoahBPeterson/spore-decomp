// 0x00ca03a0: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPVehicle.cpp, match/slices/s00c9ffd0/s00c9ffd0.cpp.

// lifted by il2c_lift + l2c_search (swap@25); CI scorer MATCH; corpus status nonmatching/residual
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
    virtual int s16(int);
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual int s2(int, int);
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3(int, int);
};
struct il2c_vc3 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6(int);
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
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16(int, int);
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
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15(int, int);
};

struct C_0067cb20 { int FUN_0067cb20(); };

// @ 0x00ca03a0
extern "C" int __fastcall FUN_00ca03a0(char* self, int edx_unused, int a4)
{
    int t1004;
    int t1005;
    int t1007;
    int t1010;
    int t1011;
    int t1014;
    int t1019;
    int t1023;
    int t1025;
    int t1031;
    int t1037;
    int t1043;
    int t1049;
    t1004 = (int)((int)(self));
    t1005 = (int)((int)0);
    if ((int)*(int*)((char*)(t1004) + 3328) != t1005) {
        t1007 = (int)((C_0067cb20*)((int)(self)))->FUN_0067cb20();
        t1010 = (int)((int)(a4));
        t1011 = (int)(t1007);
        t1014 = (int)((il2c_vc0*)(t1011))->s16((int)(t1010));
        if (t1014 == (int)0) {
            return 0;
        }
        t1019 = (int)(*(int*)((char*)(t1004) + 3328));
        t1023 = (int)((il2c_vc1*)(t1019))->s2((int)(t1010), (int)((int)0));
        t1005 = (int)(t1023);
        t1025 = (int)(*(int*)((char*)(t1004) + 3328));
        ((il2c_vc2*)(t1025))->s3((int)(t1005), (int)((int)1));
        t1031 = (int)(*(int*)((char*)(t1004) + 3328));
        ((il2c_vc3*)(t1031))->s6((int)(t1005));
        t1037 = (int)(*(int*)((char*)(t1004) + 3328));
        ((il2c_vc4*)(t1037))->s16((int)(t1005), (int)(t1010));
        t1043 = (int)(*(int*)((char*)(t1004) + 3328));
        ((il2c_vc5*)(t1043))->s15((int)(t1005), (int)((int)0));
    }
    t1049 = (int)(t1005);
    return (int)(t1049);
}
