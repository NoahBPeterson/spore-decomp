// 0x00803b70: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

// lifted by il2c_lift + l2c_search (bind@t1006); CI scorer MATCH; corpus status nonmatching/residual
struct il2c_vc0 {
    virtual int s0();
};
struct il2c_vc1 {
    virtual void s0();
    virtual int s1();
};


template<class HsT> __forceinline HsT& hs_bind(HsT& x) { HsT& r = x; return r; }
// @ 0x00803b70
extern "C" int __fastcall FUN_00803b70(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1003;
    int t1006;
    int t1007;
    int t1009;
    int t1012;
    int t1017;
    int t1020;
    int t1021;
    unsigned char t1022;
    unsigned char t1023;
    int t1025;
    t1002 = (int)((int)(a4));
    t1003 = (int)(*(int*)((char*)(t1002)));
    t1006 = (int)((int)(self));
    *(int*)((char*)(hs_bind(t1006))) = (int)(t1003);
    t1007 = (int)(*(int*)((char*)(t1006) + 4));
    t1009 = (int)(*(int*)((char*)(t1002) + 4));
    if (t1009 != t1007) {
        if (t1009 != (int)0) {
            t1012 = (int)(t1009);
            t1003 = (int)((il2c_vc0*)(t1012))->s0();
        }
        *(int*)((char*)(t1006) + 4) = (int)(t1009);
        if (t1007 != (int)0) {
            t1017 = (int)(t1007);
            t1003 = (int)((il2c_vc1*)(t1017))->s1();
        }
    }
    t1020 = (int)(*(int*)((char*)(t1002) + 8));
    *(int*)((char*)(t1006) + 8) = (int)(t1020);
    t1021 = (int)(*(int*)((char*)(t1002) + 12));
    *(int*)((char*)(t1006) + 12) = (int)(t1021);
    t1022 = (unsigned char)(*(unsigned char*)((char*)(t1002) + 16));
    *(unsigned char*)((char*)(t1006) + 16) = (unsigned char)(t1022);
    t1023 = (unsigned char)(*(unsigned char*)((char*)(t1002) + 17));
    *(unsigned char*)((char*)(t1006) + 17) = (unsigned char)(t1023);
    t1025 = (int)(t1006);
    return (int)(t1025);
}
