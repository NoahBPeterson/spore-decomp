// 0x00bcaa00: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/_at_00bc0000.cpp, match/slices/s00bca040/s00bca040.cpp.

// lifted by il2c_lift + l2c_search (bind@t1008); CI scorer MATCH; corpus status nonmatching/residual
struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
};

extern "C" unsigned char g_013ec458[];
extern "C" unsigned char g_01466998[];

template<class HsT> __forceinline HsT& hs_bind(HsT& x) { HsT& r = x; return r; }
// @ 0x00bcaa00
extern "C" void __fastcall FUN_00bcaa00(char* self, int edx_unused)
{
    int t1002;
    int t1004;
    int t1008;
    int t1009;
    int t1015;
    t1002 = (int)((int)(self));
    t1004 = (int)(*(int*)((char*)(t1002)));
    if (t1004 != t1002) {
        goto Lbcaa10;
        Lbcaa10:;
        t1008 = (int)(t1004);
        t1004 = (int)(*(int*)((char*)(t1004)));
        *(int*)((char*)(hs_bind(t1008)) + 8) = (int)((int)g_01466998);
        t1009 = (int)(*(int*)((char*)(t1008) + 424));
        if (t1009 != (int)0) {
            ((il2c_vc0*)(t1009))->s1();
        }
        *(int*)((char*)(t1008) + 8) = (int)((int)g_013ec458);
        t1015 = (int)(*(int*)((char*)(t1002) + 24));
        *(int*)((char*)(t1008)) = (int)(t1015);
        *(int*)((char*)(t1002) + 24) = (int)(t1008);
        if (t1004 != t1002) goto Lbcaa10;
    }
    return;
}
