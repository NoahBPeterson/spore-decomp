// 0x00b01d30: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00b01690/s00b01690.cpp, src/game/SPGonzago/SPPlanet.cpp.

// lifted by il2c_lift + l2c_search (bind@t1004); CI scorer MATCH; corpus status nonmatching/residual
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
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
};


template<class HsT> __forceinline HsT& hs_bind(HsT& x) { HsT& r = x; return r; }
// @ 0x00b01d30
extern "C" int __fastcall FUN_00b01d30(char* self, int edx_unused, int a4)
{
    int t1004;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1010;
    int t1011;
    int t1014;
    int t1020;
    int t1024;
    int t1025;
    int t1028;
    int t1034;
    int t1038;
    int t1040;
    t1004 = (int)((int)(self));
    t1006 = (int)((int)(a4));
    t1007 = (int)(*(int*)((char*)(t1006)));
    *(int*)((char*)(hs_bind(t1004))) = (int)(t1007);
    t1008 = (int)(*(int*)((char*)(t1006) + 8));
    *(int*)((char*)(t1004) + 8) = (int)(t1008);
    t1009 = (int)(*(int*)((char*)(t1006) + 12));
    *(int*)((char*)(t1004) + 12) = (int)(t1009);
    t1010 = (int)(*(int*)((char*)(t1006) + 16));
    t1011 = (int)(*(int*)((char*)(t1004) + 16));
    if (t1010 != t1011) {
        if (t1010 != (int)0) {
            t1014 = (int)(t1010);
            ((il2c_vc0*)(t1014))->s0();
        }
        *(int*)((char*)(t1004) + 16) = (int)(t1010);
        if (t1011 != (int)0) {
            t1020 = (int)(t1011);
            ((il2c_vc1*)(t1020))->s1();
        }
    }
    t1024 = (int)(*(int*)((char*)(t1006) + 20));
    t1025 = (int)(*(int*)((char*)(t1004) + 20));
    if (t1024 != t1025) {
        if (t1024 != (int)0) {
            t1028 = (int)(t1024);
            ((il2c_vc2*)(t1028))->s13();
        }
        *(int*)((char*)(t1004) + 20) = (int)(t1024);
        if (t1025 != (int)0) {
            t1034 = (int)(t1025);
            ((il2c_vc3*)(t1034))->s14();
        }
    }
    t1038 = (int)(*(int*)((char*)(t1006) + 24));
    *(int*)((char*)(t1004) + 24) = (int)(t1038);
    t1040 = (int)(t1004);
    return (int)(t1040);
}
