// 0x00d5edc0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPCityVisualizer.cpp, match/slices/s00d5e730/s00d5e730.cpp.

struct C_00afbad0 { void FUN_00afbad0(); };
extern "C" int __cdecl FUN_00d5d530(...);

// @ 0x00d5edc0
extern "C" int __fastcall FUN_00d5edc0(char* self, int edx_unused, int a4, int a8)
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
    t1009 = (int)FUN_00d5d530((unsigned int)(t1002), (unsigned int)(t1007), (unsigned int)(t1006));
    t1012 = (int)(*(int*)((char*)(t1005) + 4));
    t1013 = (int)(t1009);
    if ((unsigned int)(t1009) < (unsigned int)(t1012)) {
        do {
            t1014 = (int)(t1013);
            ((C_00afbad0*)(t1014))->FUN_00afbad0();
            t1013 = (int)(t1013 + (int)100);
        } while ((unsigned int)(t1013) < (unsigned int)(t1012));
    }
    t1018 = (int)((int)(a4));
    t1019 = (int)(t1002 - t1018);
    t1026 = (int)(t1019 / (int)(-100));
    t1027 = (int)(t1026 * (int)100);
    *(int*)((char*)(t1005) + 4) += t1027;
    t1031 = (int)(t1018);
    return (int)(t1031);
}
