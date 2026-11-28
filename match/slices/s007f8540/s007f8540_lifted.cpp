// 0x007f8540: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s007f8540/s007f8540.cpp.

struct il2c_vc0 {
    virtual void s0(int);
};

extern "C" int __cdecl FUN_007f7a60(...);

// @ 0x007f8540
extern "C" int __fastcall FUN_007f8540(char* self, int edx_unused, int a4, int a8)
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
    t1009 = (int)FUN_007f7a60((unsigned int)(t1002), (unsigned int)(t1008), (unsigned int)(t1007));
    t1012 = (int)(*(int*)((char*)(t1006) + 4));
    t1013 = (int)(t1009);
    if ((unsigned int)(t1009) < (unsigned int)(t1012)) {
        do {
            t1016 = (int)(t1013);
            ((il2c_vc0*)(t1016))->s0((int)((int)0));
            t1013 = (int)(t1013 + (int)140);
        } while ((unsigned int)(t1013) < (unsigned int)(t1012));
    }
    t1020 = (int)((int)(a4));
    t1021 = (int)(t1002 - t1020);
    t1029 = (int)(t1021 / (int)(-140));
    t1030 = (int)(t1029 * (int)140);
    *(int*)((char*)(t1006) + 4) += t1030;
    t1034 = (int)(t1020);
    return (int)(t1034);
}
