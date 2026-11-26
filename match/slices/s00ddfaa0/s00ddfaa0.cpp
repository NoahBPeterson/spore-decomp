// 0x00ddfaa0: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/_at_00dd0000.cpp, match/slices/s00ddf990/s00ddf990.cpp.

// lifted by il2c_lift + l2c_search (bind@t1002); CI scorer MATCH; corpus status nonmatching/residual
struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
};

extern "C" unsigned char g_013eb394[];
extern "C" unsigned char g_013eb938[];
extern "C" unsigned char g_013ef094[];
extern "C" unsigned char g_0147dad4[];
extern "C" unsigned char g_0147dad8[];
extern "C" unsigned char g_0147dae8[];
extern "C" void __cdecl FUN_00f47380(...);

template<class HsT> __forceinline HsT& hs_bind(HsT& x) { HsT& r = x; return r; }
// @ 0x00ddfaa0
extern "C" int __fastcall FUN_00ddfaa0(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1003;
    unsigned char t3;
    int t1012;
    t1002 = (int)((int)(self));
    *(int*)((char*)(hs_bind(t1002))) = (int)((int)g_0147dae8);
    *(int*)((char*)(t1002) + 4) = (int)((int)g_0147dad8);
    *(int*)((char*)(t1002) + 8) = (int)((int)g_0147dad4);
    t1003 = (int)(*(int*)((char*)(t1002) + 16));
    if (t1003 != (int)0) {
        ((il2c_vc0*)(t1003))->s1();
    }
    t3 = (unsigned char)((unsigned char)(a4) & (unsigned char)1);
    *(int*)((char*)(t1002) + 8) = (int)((int)g_013ef094);
    *(int*)((char*)(t1002) + 4) = (int)((int)g_013eb394);
    *(int*)((char*)(t1002)) = (int)((int)g_013eb938);
    if (t3 != (unsigned char)0) {
        FUN_00f47380((unsigned int)(t1002));
    }
    t1012 = (int)(t1002);
    return (int)(t1012);
}
