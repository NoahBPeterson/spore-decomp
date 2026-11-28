// 0x00c798a0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPPlayer.cpp, match/slices/s00c793e0/s00c793e0.cpp.

struct C_00b638b0 { void FUN_00b638b0(); };
extern "C" int __cdecl FUN_00c771e0(...);

// @ 0x00c798a0
extern "C" int __fastcall FUN_00c798a0(char* self, int edx_unused, int a4, int a8)
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
    int t1029;
    int t1031;
    int t1034;
    t1001 = (int)((int)(a8));
    t1005 = (int)((int)(self));
    t1006 = (int)((int)(a4));
    t1007 = (int)(*(int*)((char*)(t1005) + 4));
    t1009 = (int)FUN_00c771e0((unsigned int)(t1001), (unsigned int)(t1007), (unsigned int)(t1006));
    t1012 = (int)(*(int*)((char*)(t1005) + 4));
    t1013 = (int)(t1009);
    if ((unsigned int)(t1009) < (unsigned int)(t1012)) {
        do {
            t1014 = (int)(t1013 + (int)8);
            ((C_00b638b0*)(t1014))->FUN_00b638b0();
            t1013 = (int)(t1013 + (int)40);
        } while ((unsigned int)(t1013) < (unsigned int)(t1012));
    }
    t1018 = (int)((int)(a4));
    t1019 = (int)(t1001 - t1018);
    t1026 = (int)(t1019 / (int)(-40));
    t7 = (int)(t1026 << (int)2);
    t1027 = (int)(t1026 + t7);
    t1028 = (int)(t1027 + t1027);
    t1029 = (int)(t1028 + t1028);
    t1031 = (int)(t1029 + t1029);
    *(int*)((char*)(t1005) + 4) += t1031;
    t1034 = (int)(t1018);
    return (int)(t1034);
}
