// 0x00f16330: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/_at_00f10000.cpp, match/slices/s00f15890/s00f15890.cpp.

struct il2c_vc0 {
    virtual void s0(int);
};

extern "C" int __cdecl FUN_00f14900(...);

// @ 0x00f16330
extern "C" int __fastcall FUN_00f16330(char* self, int edx_unused, int a4, int a8)
{
    int t1002;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1012;
    int t1013;
    int t1016;
    int t1020;
    int t1021;
    int t1029;
    int t1030;
    int t1034;
    t1002 = (int)((int)(a8));
    t1006 = (int)((int)(self));
    t1007 = (int)((int)(a4));
    t1008 = (int)(*(int*)((char*)(t1006) + 4));
    t1009 = (int)FUN_00f14900((unsigned int)(t1002), (unsigned int)(t1008), (unsigned int)(t1007));
    t1012 = (int)(*(int*)((char*)(t1006) + 4));
    t1013 = (int)(t1009);
    if ((unsigned int)(t1009) < (unsigned int)(t1012)) {
        do {
            t1016 = (int)(t1013);
            ((il2c_vc0*)(t1016))->s0((int)((int)0));
            t1013 = (int)(t1013 + (int)112);
        } while ((unsigned int)(t1013) < (unsigned int)(t1012));
    }
    t1020 = (int)((int)(a4));
    t1021 = (int)(t1002 - t1020);
    t1029 = (int)(t1021 / (int)(-112));
    t1030 = (int)(t1029 * (int)112);
    *(int*)((char*)(t1006) + 4) += t1030;
    t1034 = (int)(t1020);
    return (int)(t1034);
}
