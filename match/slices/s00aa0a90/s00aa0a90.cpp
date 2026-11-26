// 0x00aa0a90: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/Swarm/_at_00aa0000.cpp, match/slices/s00aa0030/s00aa0030.cpp.

// lifted by il2c_lift + l2c_search (bind@t1006); CI scorer MATCH; corpus status nonmatching/residual
struct C_00aa06b0 { void FUN_00aa06b0(unsigned int); };

template<class HsT> __forceinline HsT& hs_bind(HsT& x) { HsT& r = x; return r; }
// @ 0x00aa0a90
extern "C" int __fastcall FUN_00aa0a90(char* self, int edx_unused)
{
    int t1003;
    int t1004;
    int t1006;
    int t1008;
    int t1009;
    int t1010;
    int t1011;
    int t1016;
    int t1019;
    t1003 = (int)((int)(self));
    t1004 = (int)(t1003 + (int)36);
    t1006 = (int)(*(int*)((char*)(t1004)));
    if (t1006 != t1004) {
        do {
            t1008 = (int)(*(int*)((char*)(hs_bind(t1006)) + 4));
            t1009 = (int)(*(int*)((char*)(t1006)));
            *(int*)((char*)(t1008)) = (int)(t1009);
            t1010 = (int)(t1006);
            *(int*)((char*)(t1009) + 4) = (int)(t1008);
            *(int*)((char*)(t1006)) = (int)((int)0);
            *(int*)((char*)(t1006) + 4) = (int)((int)0);
            t1011 = (int)(t1003);
            t1006 = (int)(t1009);
            ((C_00aa06b0*)(t1011))->FUN_00aa06b0((unsigned int)(t1010));
            *(int*)((char*)(t1003) + 44) -= (int)1;
        } while (t1009 != t1004);
    }
    t1016 = (int)(*(int*)((char*)(t1004)));
    if (t1016 != t1004) {
        goto Laa0ae0;
        goto Laa0ae0;
        Laa0ae0:;
        t1019 = (int)(*(int*)((char*)(t1016)));
        *(int*)((char*)(t1016) + 4) = (int)((int)0);
        *(int*)((char*)(t1016)) = (int)((int)0);
        t1016 = (int)(t1019);
        if (t1019 != t1004) goto Laa0ae0;
    }
    *(int*)((char*)(t1004)) = (int)(t1004);
    *(int*)((char*)(t1004) + 4) = (int)(t1004);
    return (int)(t1016);
}
