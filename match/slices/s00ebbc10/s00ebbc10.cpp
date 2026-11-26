// 0x00ebbc10: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00ebb4c0/s00ebb4c0.cpp.

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
};
struct il2c_vc3 {
    virtual void s0();
    virtual void s1();
};


template<class HsT> __forceinline HsT& hs_bind(HsT& x) { HsT& r = x; return r; }
// @ 0x00ebbc10
extern "C" int __fastcall FUN_00ebbc10(char* self, int edx_unused, int a4)
{
    int t1004;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1010;
    int t1011;
    int t1012;
    int t1013;
    int t1014;
    int t1015;
    int t1016;
    int t1017;
    int t1018;
    unsigned char t1019;
    int t1020;
    int t1021;
    int t1022;
    int t1025;
    int t1031;
    int t1035;
    int t1036;
    int t1039;
    int t1045;
    int t1050;
    t1004 = (int)((int)(self));
    t1006 = (int)((int)(a4));
    t1007 = (int)(*(int*)((char*)(t1006)));
    *(int*)((char*)(hs_bind(t1004))) = (int)(t1007);
    t1008 = (int)(*(int*)((char*)(t1006) + 4));
    *(int*)((char*)(t1004) + 4) = (int)(t1008);
    *(float*)((char*)(t1004) + 8) = (float)(*(float*)((char*)(t1006) + 8));
    t1009 = (int)(*(int*)((char*)(t1006) + 12));
    *(int*)((char*)(t1004) + 12) = (int)(t1009);
    t1010 = (int)(*(int*)((char*)(t1006) + 16));
    *(int*)((char*)(t1004) + 16) = (int)(t1010);
    t1011 = (int)(*(int*)((char*)(t1006) + 20));
    *(int*)((char*)(t1004) + 20) = (int)(t1011);
    t1012 = (int)(*(int*)((char*)(t1006) + 24));
    *(int*)((char*)(t1004) + 24) = (int)(t1012);
    t1013 = (int)(*(int*)((char*)(t1006) + 28));
    *(int*)((char*)(t1004) + 28) = (int)(t1013);
    t1014 = (int)(*(int*)((char*)(t1006) + 32));
    *(int*)((char*)(t1004) + 32) = (int)(t1014);
    t1015 = (int)(*(int*)((char*)(t1006) + 48));
    *(int*)((char*)(t1004) + 48) = (int)(t1015);
    t1016 = (int)(*(int*)((char*)(t1006) + 52));
    *(int*)((char*)(t1004) + 52) = (int)(t1016);
    t1017 = (int)(*(int*)((char*)(t1006) + 56));
    *(int*)((char*)(t1004) + 56) = (int)(t1017);
    t1018 = (int)(*(int*)((char*)(t1006) + 60));
    *(int*)((char*)(t1004) + 60) = (int)(t1018);
    t1019 = (unsigned char)(*(unsigned char*)((char*)(t1006) + 64));
    *(unsigned char*)((char*)(t1004) + 64) = (unsigned char)(t1019);
    t1020 = (int)(*(int*)((char*)(t1006) + 68));
    *(int*)((char*)(t1004) + 68) = (int)(t1020);
    t1021 = (int)(*(int*)((char*)(t1006) + 72));
    t1022 = (int)(*(int*)((char*)(t1004) + 72));
    if (t1021 != t1022) {
        if (t1021 != (int)0) {
            t1025 = (int)(t1021);
            ((il2c_vc0*)(t1025))->s0();
        }
        *(int*)((char*)(t1004) + 72) = (int)(t1021);
        if (t1022 != (int)0) {
            t1031 = (int)(t1022);
            ((il2c_vc1*)(t1031))->s1();
        }
    }
    t1035 = (int)(*(int*)((char*)(t1006) + 76));
    t1036 = (int)(*(int*)((char*)(t1004) + 76));
    if (t1035 != t1036) {
        if (t1035 != (int)0) {
            t1039 = (int)(t1035);
            ((il2c_vc2*)(t1039))->s0();
        }
        *(int*)((char*)(t1004) + 76) = (int)(t1035);
        if (t1036 != (int)0) {
            t1045 = (int)(t1036);
            ((il2c_vc3*)(t1045))->s1();
        }
    }
    t1050 = (int)(t1004);
    return (int)(t1050);
}
