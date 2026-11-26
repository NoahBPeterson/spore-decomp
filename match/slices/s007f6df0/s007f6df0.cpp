// 0x007f6df0: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/Spui/SPUIAnimation.cpp, match/slices/s007f64d0/s007f64d0.cpp.

// lifted by il2c_lift + l2c_search (bind@t1002); CI scorer MATCH; corpus status nonmatching/residual
#include <string.h>
struct il2c_vc0 {
    virtual void s0();
};
struct il2c_vc1 {
    virtual void s0();
};

extern "C" unsigned char g_013f63fc[];
extern "C" unsigned char g_013f6400[];
extern "C" unsigned char g_014153bc[];

template<class HsT> __forceinline HsT& hs_bind(HsT& x) { HsT& r = x; return r; }
// @ 0x007f6df0
extern "C" int __fastcall FUN_007f6df0(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1004;
    int t1005;
    int t1006;
    int t1014;
    int t1015;
    int t1020;
    int t1028;
    int t1030;
    t1002 = (int)((int)(self));
    *(int*)((char*)(hs_bind(t1002))) = (int)((int)g_014153bc);
    *(int*)((char*)(t1002) + 4) = (int)((int)g_013f6400);
    t1004 = (int)((int)(a4));
    t1005 = (int)(*(int*)((char*)(t1004) + 8));
    *(int*)((char*)(t1002) + 8) = (int)(t1005);
    *(int*)((char*)(t1002) + 12) = (int)((int)g_013f63fc);
    t1006 = (int)(*(int*)((char*)(t1004) + 16));
    *(int*)((char*)(t1002) + 16) = (int)(t1006);
    if (t1006 != (int)0) {
        ((il2c_vc0*)(t1006))->s0();
    }
    t1014 = (int)(t1004 + (int)20);
    t1015 = (int)(t1002 + (int)20);
    memcpy((void*)(t1015), (const void*)(t1014), (unsigned int)((int)112));
    t1020 = (int)(*(int*)((char*)(t1004) + 132));
    *(int*)((char*)(t1002) + 132) = (int)(t1020);
    if (t1020 != (int)0) {
        ((il2c_vc1*)(t1020))->s0();
    }
    t1028 = (int)(*(int*)((char*)(t1004) + 136));
    *(int*)((char*)(t1002) + 136) = (int)(t1028);
    t1030 = (int)(t1002);
    return (int)(t1030);
}
