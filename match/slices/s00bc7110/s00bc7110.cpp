// 0x00bc7110: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/_at_00bc0000.cpp, match/slices/s00bc6360/s00bc6360.cpp.

struct C_00bc4730 { void FUN_00bc4730(); };
extern "C" int __cdecl FUN_00bc6570(...);

// @ 0x00bc7110
extern "C" int __fastcall FUN_00bc7110(char* self, int edx_unused, int a4, int a8)
{
    int t1002;
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
    int t1027;
    int t1031;
    t1002 = (int)((int)(a8));
    t1005 = (int)((int)(self));
    t1006 = (int)((int)(a4));
    t1007 = (int)(*(int*)((char*)(t1005) + 4));
    t1009 = (int)FUN_00bc6570((unsigned int)(t1002), (unsigned int)(t1007), (unsigned int)(t1006));
    t1012 = (int)(*(int*)((char*)(t1005) + 4));
    t1013 = (int)(t1009);
    if ((unsigned int)(t1009) < (unsigned int)(t1012)) {
        do {
            t1014 = (int)(t1013);
            ((C_00bc4730*)(t1014))->FUN_00bc4730();
            t1013 = (int)(t1013 + (int)1972);
        } while ((unsigned int)(t1013) < (unsigned int)(t1012));
    }
    t1018 = (int)((int)(a4));
    t1019 = (int)(t1002 - t1018);
    t1026 = (int)(t1019 / (int)(-1972));
    t1027 = (int)(t1026 * (int)1972);
    *(int*)((char*)(t1005) + 4) += t1027;
    t1031 = (int)(t1018);
    return (int)(t1031);
}
