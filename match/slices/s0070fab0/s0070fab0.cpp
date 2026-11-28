// 0x0070fab0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0070efa0/s0070efa0.cpp, src/game/SPEngine/SPGraphicsMaterialManager.cpp.

struct C_006fd300 { void FUN_006fd300(); };
extern "C" int __cdecl FUN_0070e390(...);

// @ 0x0070fab0
extern "C" int __fastcall FUN_0070fab0(char* self, int edx_unused, int a4, int a8)
{
    int t1001;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1012;
    int t1013;
    int t1014;
    int t1018;
    int t1019;
    int t1020;
    int t1021;
    int t1022;
    int t1023;
    t1001 = (int)((int)(a8));
    t1006 = (int)((int)(self));
    t1007 = (int)((int)(a4));
    t1008 = (int)(*(int*)((char*)(t1006) + 4));
    t1009 = (int)FUN_0070e390((unsigned int)(t1001), (unsigned int)(t1008), (unsigned int)(t1007));
    t1012 = (int)(*(int*)((char*)(t1006) + 4));
    t1013 = (int)(t1009);
    if ((unsigned int)(t1009) < (unsigned int)(t1012)) {
        do {
            t1014 = (int)(*(int*)((char*)(t1013)));
            if (t1014 != (int)0) {
                ((C_006fd300*)(t1014))->FUN_006fd300();
            }
            t1013 = (int)(t1013 + (int)4);
        } while ((unsigned int)(t1013) < (unsigned int)(t1012));
    }
    t1018 = (int)((int)(a4));
    t1019 = (int)(t1001 - t1018);
    t1020 = (int)(t1019 >> (int)2);
    t1021 = (int)(-t1020);
    t1022 = (int)(t1021 + t1021);
    t1023 = (int)(t1022 + t1022);
    *(int*)((char*)(t1006) + 4) += t1023;
    return (int)(t1018);
}
