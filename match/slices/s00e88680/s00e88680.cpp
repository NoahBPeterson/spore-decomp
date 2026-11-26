// 0x00e88680: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00e87cf0/s00e87cf0.cpp, src/game/SPGonzago/SPCityViews.cpp.

// lifted by il2c_lift + l2c_search (bind@t1002); CI scorer MATCH; corpus status nonmatching/residual
extern "C" unsigned char g_01486290[];
struct C_00e92af0 { void FUN_00e92af0(); };

template<class HsT> __forceinline HsT& hs_bind(HsT& x) { HsT& r = x; return r; }
// @ 0x00e88680
extern "C" int __fastcall FUN_00e88680(char* self, int edx_unused)
{
    int t1002;
    int t1006;
    int t1007;
    t1002 = (int)((int)(self));
    ((C_00e92af0*)((int)(self)))->FUN_00e92af0();
    t1006 = (int)((int)0);
    *(int*)((char*)(hs_bind(t1002))) = (int)((int)g_01486290);
    *(int*)((char*)(t1002) + 52) = (int)(t1006);
    *(unsigned char*)((char*)(t1002) + 56) = (unsigned char)((unsigned char)(t1006));
    *(unsigned char*)((char*)(t1002) + 57) = (unsigned char)((unsigned char)(t1006));
    *(unsigned char*)((char*)(t1002) + 58) = (unsigned char)((unsigned char)(t1006));
    t1007 = (int)(t1002);
    return (int)(t1007);
}
