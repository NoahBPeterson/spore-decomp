// 0x00782800: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEngine/_at_00780000.cpp, match/slices/s007819d0/s007819d0.cpp.

struct C_00781b10 { void FUN_00781b10(); };
extern "C" int __cdecl FUN_00782420(...);

// @ 0x00782800
extern "C" int __fastcall FUN_00782800(char* self, int edx_unused, int a4, int a8)
{
    int t1001;
    int t1005;
    int t1006;
    int t1007;
    int t1009;
    int t1012;
    int t1013;
    int t1014;
    int t1018;
    int t1019;
    int t1026;
    int t7;
    int t1027;
    int t1028;
    int t1030;
    int t1033;
    t1001 = (int)((int)(a8));
    t1005 = (int)((int)(self));
    t1006 = (int)((int)(a4));
    t1007 = (int)(*(int*)((char*)(t1005) + 4));
    t1009 = (int)FUN_00782420((unsigned int)(t1001), (unsigned int)(t1007), (unsigned int)(t1006));
    t1012 = (int)(*(int*)((char*)(t1005) + 4));
    t1013 = (int)(t1009);
    if ((unsigned int)(t1009) < (unsigned int)(t1012)) {
        do {
            t1014 = (int)(t1013 + (int)4);
            ((C_00781b10*)(t1014))->FUN_00781b10();
            t1013 = (int)(t1013 + (int)36);
        } while ((unsigned int)(t1013) < (unsigned int)(t1012));
    }
    t1018 = (int)((int)(a4));
    t1019 = (int)(t1001 - t1018);
    t1026 = (int)(t1019 / (int)(-36));
    t7 = (int)(t1026 << (int)3);
    t1027 = (int)(t1026 + t7);
    t1028 = (int)(t1027 + t1027);
    t1030 = (int)(t1028 + t1028);
    *(int*)((char*)(t1005) + 4) += t1030;
    t1033 = (int)(t1018);
    return (int)(t1033);
}
