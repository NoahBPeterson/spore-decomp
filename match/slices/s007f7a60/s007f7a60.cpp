// 0x007f7a60: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/Spui/SPUIAnimation.cpp, match/slices/s007f7530/s007f7530.cpp.

// lifted by il2c_lift + l2c_search (bind@t1007); CI scorer MATCH; corpus status nonmatching/residual
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
// @ 0x007f7a60
extern "C" int __cdecl FUN_007f7a60(int a4, int a8, int a12)
{
    int t1001;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1010;
    int t1013;
    int t1019;
    int t1022;
    int t1023;
    int t1024;
    int t1025;
    unsigned char v_aedx;
    int t1026;
    int t1027;
    int t1030;
    int t1035;
    int t1038;
    int t1039;
    int t1040;
    int t1044;
    t1001 = (int)((int)(a4));
    if (t1001 != (int)(a8)) {
        t1005 = (int)((int)(a12));
        t1006 = (int)(t1001 + (int)16);
        t1007 = (int)(t1005 + (int)16);
        do {
            t1008 = (int)(*(int*)((char*)(t1006) - 8));
            *(int*)((char*)(hs_bind(t1007)) - 8) = (int)(t1008);
            t1009 = (int)(*(int*)((char*)(t1006)));
            t1010 = (int)(*(int*)((char*)(t1007)));
            if (t1009 != t1010) {
                if (t1009 != (int)0) {
                    t1013 = (int)(t1009);
                    ((il2c_vc0*)(t1013))->s0();
                }
                *(int*)((char*)(t1007)) = (int)(t1009);
                if (t1010 != (int)0) {
                    t1019 = (int)(t1010);
                    ((il2c_vc1*)(t1019))->s1();
                }
            }
            t1022 = (int)(t1006);
            t1023 = (int)(t1007 + (int)4);
            t1024 = (int)(t1022 - t1007);
            t1025 = (int)((int)112);
            do {
                v_aedx = (unsigned char)(*(unsigned char*)((char*)(t1024) + t1023));
                *(unsigned char*)((char*)(t1023)) = (unsigned char)(v_aedx);
                t1023 = (int)(t1023 + (int)1);
                t1025 = (int)(t1025 - (int)1);
            } while (t1025 != (int)0);
            t1026 = (int)(*(int*)((char*)(t1006) + 116));
            t1027 = (int)(*(int*)((char*)(t1007) + 116));
            if (t1026 != t1027) {
                if (t1026 != (int)0) {
                    t1030 = (int)(t1026);
                    ((il2c_vc2*)(t1030))->s0();
                }
                *(int*)((char*)(t1007) + 116) = (int)(t1026);
                if (t1027 != (int)0) {
                    t1035 = (int)(t1027);
                    ((il2c_vc3*)(t1035))->s1();
                }
            }
            t1038 = (int)(*(int*)((char*)(t1006) + 120));
            *(int*)&(a12) = (int)((int)(a12) + (int)140);
            *(int*)((char*)(t1007) + 120) = (int)(t1038);
            t1039 = (int)((int)(a4));
            t1040 = (int)(t1039 + (int)140);
            t1007 = (int)(t1007 + (int)140);
            t1006 = (int)(t1006 + (int)140);
            *(int*)&(a4) = (int)(t1040);
        } while (t1040 != (int)(a8));
    }
    t1044 = (int)((int)(a12));
    return (int)(t1044);
}
