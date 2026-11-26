// 0x007f7b30: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
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
// @ 0x007f7b30
extern "C" int __cdecl FUN_007f7b30(int a4, int a8, int a12)
{
    int t1000;
    int t1001;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1012;
    int t1016;
    int t1019;
    int t1023;
    int t1024;
    int t1025;
    int t1026;
    int t1029;
    int t1034;
    int t1037;
    int t1038;
    int t1039;
    int t1040;
    int t1041;
    int t1042;
    t1000 = (int)((int)(a4));
    t1001 = (int)((int)(a12));
    if (t1000 != (int)(a8)) {
        t1006 = (int)(t1000 + (int)20);
        t1007 = (int)(t1001 + (int)20);
        do {
            t1008 = (int)(*(int*)((char*)(t1000)));
            t1009 = (int)(*(int*)((char*)(t1001)));
            if (t1008 != t1009) {
                if (t1008 != (int)0) {
                    t1012 = (int)(t1008);
                    ((il2c_vc0*)(t1012))->s0();
                }
                t1016 = (int)((int)(a12));
                *(int*)((char*)(t1016)) = (int)(t1008);
                if (t1009 != (int)0) {
                    t1019 = (int)(t1009);
                    ((il2c_vc1*)(t1019))->s1();
                }
            }
            t1023 = (int)(*(int*)((char*)(t1006) - 16));
            *(int*)((char*)(hs_bind(t1007)) - 16) = (int)(t1023);
            t1024 = (int)(*(int*)((char*)(t1006) - 8));
            *(int*)((char*)(t1007) - 8) = (int)(t1024);
            t1025 = (int)(*(int*)((char*)(t1006)));
            t1026 = (int)(*(int*)((char*)(t1007)));
            if (t1025 != t1026) {
                if (t1025 != (int)0) {
                    t1029 = (int)(t1025);
                    ((il2c_vc2*)(t1029))->s0();
                }
                *(int*)((char*)(t1007)) = (int)(t1025);
                if (t1026 != (int)0) {
                    t1034 = (int)(t1026);
                    ((il2c_vc3*)(t1034))->s1();
                }
            }
            t1037 = (int)(t1006);
            t1038 = (int)(t1007 + (int)4);
            t1039 = (int)(t1037 - t1007);
            t1040 = (int)((int)112);
            do {
                *(unsigned char*)&(t1024) = (unsigned char)(*(unsigned char*)((char*)(t1039) + t1038));
                *(unsigned char*)((char*)(t1038)) = (unsigned char)((unsigned char)(t1024));
                t1038 = (int)(t1038 + (int)1);
                t1040 = (int)(t1040 - (int)1);
            } while (t1040 != (int)0);
            t1041 = (int)((int)(a4));
            t1042 = (int)((int)(a12));
            t1000 = (int)(t1041 + (int)136);
            t1001 = (int)(t1042 + (int)136);
            t1007 = (int)(t1007 + (int)136);
            t1006 = (int)(t1006 + (int)136);
            *(int*)&(a12) = (int)(t1001);
            *(int*)&(a4) = (int)(t1000);
        } while (t1000 != (int)(a8));
    }
    return (int)(t1001);
}
