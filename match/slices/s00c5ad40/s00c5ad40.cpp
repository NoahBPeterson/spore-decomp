// 0x00c5ad40: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/_at_00c50000.cpp, match/slices/s00c5a580/s00c5a580.cpp.

// lifted by il2c_lift + l2c_search (bind@t1005); CI scorer MATCH; corpus status nonmatching/residual
extern "C" unsigned char g_0146f3e0[];
extern "C" unsigned char g_0146f3f0[];
extern "C" unsigned char g_0146f400[];
extern "C" unsigned char g_01691f94[];
extern "C" unsigned char g_01691f98[];
extern "C" unsigned char g_01691f9c[];
struct C_004548d0 { void FUN_004548d0(unsigned int); };
struct C_004cd3c0 { void FUN_004cd3c0(unsigned int); };
struct C_00c48e90 { void FUN_00c48e90(); };

template<class HsT> __forceinline HsT& hs_bind(HsT& x) { HsT& r = x; return r; }
// @ 0x00c5ad40
extern "C" int __fastcall FUN_00c5ad40(char* self, int edx_unused)
{
    int t1005;
    int t1009;
    int t1010;
    int t1011;
    int t1012;
    int t1016;
    int t1017;
    int t1018;
    int t1022;
    int t1023;
    int t1024;
    int t1025;
    int t1026;
    int t1027;
    int t1028;
    int t1029;
    int t1031;
    int t1032;
    t1005 = (int)((int)(self));
    ((C_00c48e90*)((int)(self)))->FUN_00c48e90();
    *(int*)((char*)(hs_bind(t1005))) = (int)((int)g_0146f400);
    *(int*)((char*)(t1005) + 4) = (int)((int)g_0146f3f0);
    *(int*)((char*)(t1005) + 52) = (int)((int)g_0146f3e0);
    t1009 = (int)((int)0);
    *(int*)((char*)(t1005) + 496) = (int)(t1009);
    *(int*)((char*)(t1005) + 500) = (int)(t1009);
    *(int*)((char*)(t1005) + 504) = (int)(t1009);
    *(int*)((char*)(t1005) + 516) = (int)((int)(-1));
    t1010 = (int)(t1005 + (int)520);
    *(int*)((char*)(t1010)) = (int)(t1009);
    *(int*)((char*)(t1010) + 4) = (int)(t1009);
    *(int*)((char*)(t1010) + 8) = (int)(t1009);
    t1011 = (int)(t1005 + (int)540);
    t1012 = (int)(t1010);
    *(int*)((char*)(t1011)) = (int)(t1009);
    *(int*)((char*)(t1011) + 4) = (int)(t1009);
    *(int*)((char*)(t1011) + 8) = (int)(t1009);
    ((C_004cd3c0*)(t1012))->FUN_004cd3c0((unsigned int)((int)2));
    t1016 = (int)(*(int*)((char*)(t1010)));
    *(int*)((char*)(t1016)) = (int)(t1009);
    t1017 = (int)(*(int*)((char*)(t1010)));
    *(int*)((char*)(t1017) + 4) = (int)(t1009);
    t1018 = (int)(t1011);
    ((C_004548d0*)(t1018))->FUN_004548d0((unsigned int)((int)2));
    t1022 = (int)(*(int*)((char*)(t1011)));
    t1023 = (int)((int)(*(int*)g_01691f94));
    *(int*)((char*)(t1022)) = (int)(t1023);
    t1024 = (int)((int)(*(int*)g_01691f98));
    *(int*)((char*)(t1022) + 4) = (int)(t1024);
    t1025 = (int)((int)(*(int*)g_01691f9c));
    *(int*)((char*)(t1022) + 8) = (int)(t1025);
    t1026 = (int)(*(int*)((char*)(t1011)));
    t1027 = (int)((int)(*(int*)g_01691f94));
    t1028 = (int)(t1026 + (int)12);
    *(int*)((char*)(t1028)) = (int)(t1027);
    t1029 = (int)((int)(*(int*)g_01691f98));
    *(int*)((char*)(t1028) + 4) = (int)(t1029);
    t1031 = (int)((int)(*(int*)g_01691f9c));
    t1032 = (int)(t1005);
    *(int*)((char*)(t1028) + 8) = (int)(t1031);
    return (int)(t1032);
}
