// 0x00a8d020: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00a8c850/s00a8c850.cpp.

struct il2c_vc0 {
    virtual void s0();
};

extern "C" int __cdecl FUN_00a8c070(...);

// @ 0x00a8d020
extern "C" int __fastcall FUN_00a8d020(char* self, int edx_unused, int a4, int a8)
{
    int t1001;
    int t1005;
    int t1006;
    int t1007;
    int t1009;
    int t1012;
    int t1013;
    int t1014;
    int t1020;
    int t1021;
    int t1028;
    int t8;
    int t1029;
    int t1030;
    int t1031;
    int t1033;
    int t1036;
    t1001 = (int)((int)(a8));
    t1005 = (int)((int)(self));
    t1006 = (int)((int)(a4));
    t1007 = (int)(*(int*)((char*)(t1005) + 4));
    t1009 = (int)FUN_00a8c070((unsigned int)(t1001), (unsigned int)(t1007), (unsigned int)(t1006));
    t1012 = (int)(*(int*)((char*)(t1005) + 4));
    t1013 = (int)(t1009);
    if ((unsigned int)(t1009) < (unsigned int)(t1012)) {
        do {
            t1014 = (int)(*(int*)((char*)(t1013)));
            if (t1014 != (int)0) {
                ((il2c_vc0*)(t1014))->s0();
            }
            t1013 = (int)(t1013 + (int)24);
        } while ((unsigned int)(t1013) < (unsigned int)(t1012));
    }
    t1020 = (int)((int)(a4));
    t1021 = (int)(t1001 - t1020);
    t1028 = (int)(t1021 / (int)(-24));
    t8 = (int)(t1028 << (int)1);
    t1029 = (int)(t1028 + t8);
    t1030 = (int)(t1029 + t1029);
    t1031 = (int)(t1030 + t1030);
    t1033 = (int)(t1031 + t1031);
    *(int*)((char*)(t1005) + 4) += t1033;
    t1036 = (int)(t1020);
    return (int)(t1036);
}
