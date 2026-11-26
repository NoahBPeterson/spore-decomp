// 0x00ea1a30: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00ea1900/s00ea1900.cpp, src/game/SPGonzago/SPAudioCityMusicLargeAssetView.cpp.

// lifted by il2c_lift + l2c_search (bind@t1002); CI scorer MATCH; corpus status nonmatching/residual
struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc2 {
    virtual void s0();
    virtual int s1();
};
struct il2c_vc3 {
    virtual void s0();
    virtual int s1();
};
struct il2c_vc4 {
    virtual void s0();
    virtual int s1();
};
struct il2c_vc5 {
    virtual void s0();
    virtual int s1();
};
struct il2c_vc6 {
    virtual void s0();
    virtual int s1();
};
struct il2c_vc7 {
    virtual void s0();
    virtual int s1();
};
struct il2c_vc8 {
    virtual void s0();
    virtual int s1();
};
struct il2c_vc9 {
    virtual void s0();
    virtual int s1();
};
struct il2c_vc10 {
    virtual void s0();
    virtual void s1();
    virtual int s2();
};

extern "C" unsigned char g_013eb938[];
extern "C" unsigned char g_013ec458[];
extern "C" unsigned char g_01487214[];
extern "C" unsigned char g_01487224[];
extern "C" unsigned char g_01487240[];

template<class HsT> __forceinline HsT& hs_bind(HsT& x) { HsT& r = x; return r; }
// @ 0x00ea1a30
extern "C" int __fastcall FUN_00ea1a30(char* self, int edx_unused)
{
    int t1002;
    int t1003;
    int t1004;
    int t1010;
    int t1016;
    int t1017;
    int t1022;
    int t1027;
    int t1032;
    int t1037;
    int t1042;
    int t1047;
    int t1052;
    int t1057;
    t1002 = (int)((int)(self));
    *(int*)((char*)(hs_bind(t1002))) = (int)((int)g_01487240);
    *(int*)((char*)(t1002) + 4) = (int)((int)g_01487224);
    *(int*)((char*)(t1002) + 8) = (int)((int)g_01487214);
    t1003 = (int)(*(int*)((char*)(t1002) + 60));
    if (t1003 != (int)0) {
        t1004 = (int)(t1003 + (int)4);
        ((il2c_vc0*)(t1004))->s2();
    }
    t1010 = (int)(*(int*)((char*)(t1002) + 56));
    if (t1010 != (int)0) {
        ((il2c_vc1*)(t1010))->s1();
    }
    t1016 = (int)(*(int*)((char*)(t1002) + 48));
    if (t1016 != (int)0) {
        t1017 = (int)(t1016 + (int)16);
        t1016 = (int)((il2c_vc2*)(t1017))->s1();
    }
    t1022 = (int)(*(int*)((char*)(t1002) + 44));
    if (t1022 != (int)0) {
        t1016 = (int)((il2c_vc3*)(t1022))->s1();
    }
    t1027 = (int)(*(int*)((char*)(t1002) + 40));
    if (t1027 != (int)0) {
        t1016 = (int)((il2c_vc4*)(t1027))->s1();
    }
    t1032 = (int)(*(int*)((char*)(t1002) + 36));
    if (t1032 != (int)0) {
        t1016 = (int)((il2c_vc5*)(t1032))->s1();
    }
    t1037 = (int)(*(int*)((char*)(t1002) + 32));
    if (t1037 != (int)0) {
        t1016 = (int)((il2c_vc6*)(t1037))->s1();
    }
    t1042 = (int)(*(int*)((char*)(t1002) + 28));
    if (t1042 != (int)0) {
        t1016 = (int)((il2c_vc7*)(t1042))->s1();
    }
    t1047 = (int)(*(int*)((char*)(t1002) + 24));
    if (t1047 != (int)0) {
        t1016 = (int)((il2c_vc8*)(t1047))->s1();
    }
    t1052 = (int)(*(int*)((char*)(t1002) + 20));
    if (t1052 != (int)0) {
        t1016 = (int)((il2c_vc9*)(t1052))->s1();
    }
    t1057 = (int)(*(int*)((char*)(t1002) + 16));
    if (t1057 != (int)0) {
        t1016 = (int)((il2c_vc10*)(t1057))->s2();
    }
    *(int*)((char*)(t1002) + 4) = (int)((int)g_013eb938);
    *(int*)((char*)(t1002) + 8) = (int)((int)g_013ec458);
    return (int)(t1016);
}
