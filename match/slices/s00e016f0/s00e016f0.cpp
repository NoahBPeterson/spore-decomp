// 0x00e016f0: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00e00760/s00e00760.cpp, src/game/SPGonzago/SPUIGlobalUI.cpp.

// lifted by il2c_lift + l2c_search (bind@t1002); CI scorer MATCH; corpus status nonmatching/residual
struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
};

extern "C" unsigned char g_013eb394[];
extern "C" unsigned char g_013eb938[];
extern "C" unsigned char g_013ec458[];
extern "C" unsigned char g_0147f0bc[];
extern "C" unsigned char g_0147f0cc[];
extern "C" unsigned char g_0147f0dc[];
extern "C" void __cdecl FUN_00f47380(...);

template<class HsT> __forceinline HsT& hs_bind(HsT& x) { HsT& r = x; return r; }
// @ 0x00e016f0
extern "C" int __fastcall FUN_00e016f0(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1003;
    int t1009;
    unsigned char t5;
    int t1018;
    t1002 = (int)((int)(self));
    *(int*)((char*)(hs_bind(t1002))) = (int)((int)g_0147f0dc);
    *(int*)((char*)(t1002) + 4) = (int)((int)g_0147f0cc);
    *(int*)((char*)(t1002) + 12) = (int)((int)g_0147f0bc);
    t1003 = (int)(*(int*)((char*)(t1002) + 48));
    if (t1003 != (int)0) {
        ((il2c_vc0*)(t1003))->s1();
    }
    t1009 = (int)(*(int*)((char*)(t1002) + 44));
    if (t1009 != (int)0) {
        ((il2c_vc1*)(t1009))->s1();
    }
    t5 = (unsigned char)((unsigned char)(a4) & (unsigned char)1);
    *(int*)((char*)(t1002) + 12) = (int)((int)g_013eb394);
    *(int*)((char*)(t1002) + 4) = (int)((int)g_013ec458);
    *(int*)((char*)(t1002)) = (int)((int)g_013eb938);
    if (t5 != (unsigned char)0) {
        FUN_00f47380((unsigned int)(t1002));
    }
    t1018 = (int)(t1002);
    return (int)(t1018);
}
