// 0x00b73a30: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00b72b60/s00b72b60.cpp, src/game/SPGonzago/_at_00b70000.cpp.

// lifted by il2c_lift + l2c_search (bind@t1002); CI scorer MATCH; corpus status nonmatching/residual
extern "C" unsigned char g_01465024[];
extern "C" unsigned char g_01465038[];
extern "C" unsigned char g_01485720[];
extern "C" unsigned char g_01687ad4[];
extern "C" unsigned char g_01687ad8[];
extern "C" unsigned char g_01687adc[];
extern "C" unsigned char g_01687af0[];
extern "C" unsigned char g_01687af4[];
extern "C" unsigned char g_01687af8[];
struct C_00b18660 { void FUN_00b18660(); };

template<class HsT> __forceinline HsT& hs_bind(HsT& x) { HsT& r = x; return r; }
// @ 0x00b73a30
extern "C" int __fastcall FUN_00b73a30(char* self, int edx_unused)
{
    int t1002;
    int t1006;
    float t1007;
    float t1008;
    float t1009;
    float t1010;
    float t1011;
    int t1003;
    int t1012;
    int t1013;
    int t1014;
    int t1015;
    int t1016;
    t1002 = (int)((int)(self));
    ((C_00b18660*)((int)(self)))->FUN_00b18660();
    *(int*)((char*)(hs_bind(t1002))) = (int)((int)g_01465038);
    *(int*)((char*)(t1002) + 4) = (int)((int)g_01465024);
    t1006 = (int)((int)0);
    *(int*)((char*)(t1002) + 52) = (int)(t1006);
    t1007 = (float)((float)(*(float*)g_01687ad4));
    *(float*)((char*)(t1002) + 56) = (float)(t1007);
    t1008 = (float)((float)(*(float*)g_01687ad8));
    *(float*)((char*)(t1002) + 60) = (float)(t1008);
    t1009 = (float)((float)(*(float*)g_01687adc));
    *(float*)((char*)(t1002) + 64) = (float)(t1009);
    t1010 = (float)((float)0);
    *(float*)((char*)(t1002) + 68) = (float)(t1010);
    *(float*)((char*)(t1002) + 72) = (float)(t1010);
    *(float*)((char*)(t1002) + 76) = (float)(t1010);
    t1011 = (float)((float)(*(float*)g_01485720));
    t1012 = (int)(t1003 | (int)(-1));
    *(int*)((char*)(t1002) + 80) = (int)(t1012);
    *(int*)((char*)(t1002) + 84) = (int)(t1006);
    *(int*)((char*)(t1002) + 88) = (int)(t1006);
    *(int*)((char*)(t1002) + 96) = (int)(t1006);
    *(int*)((char*)(t1002) + 108) = (int)(t1006);
    *(int*)((char*)(t1002) + 92) = (int)(t1012);
    *(int*)((char*)(t1002) + 100) = (int)(t1012);
    *(float*)((char*)(t1002) + 104) = (float)(t1011);
    *(int*)((char*)(t1002) + 112) = (int)(t1006);
    *(int*)((char*)(t1002) + 116) = (int)(t1006);
    *(int*)((char*)(t1002) + 120) = (int)(t1006);
    t1013 = (int)((int)(*(int*)g_01687af0));
    *(int*)((char*)(t1002) + 124) = (int)(t1013);
    t1014 = (int)((int)(*(int*)g_01687af4));
    *(int*)((char*)(t1002) + 128) = (int)(t1014);
    t1015 = (int)((int)(*(int*)g_01687af8));
    *(int*)((char*)(t1002) + 136) = (int)(t1006);
    *(int*)((char*)(t1002) + 132) = (int)(t1015);
    t1016 = (int)(t1002);
    return (int)(t1016);
}
