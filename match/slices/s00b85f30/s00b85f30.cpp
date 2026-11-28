// 0x00b85f30: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00b85380/s00b85380.cpp, src/game/SPGonzago/SPPlanetModel.cpp.

extern "C" void __cdecl FUN_00720250(...);
struct C_00b84e90 { int FUN_00b84e90(unsigned int, unsigned int, unsigned int); };

// @ 0x00b85f30
extern "C" int __fastcall FUN_00b85f30(char* self, int edx_unused, int a4)
{
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1016;
    int t1012;
    int t1017;
    int v_l24[6];
    int t1018;
    int t1019;
    int t1020;
    int t6;
    int t1026;
    int t7;
    int t1027;
    int t1031;
    int t1038;
    int t11;
    int t1039;
    int t1040;
    int t1041;
    int t1042;
    t1004 = (int)((int)(self));
    t1005 = (int)(*(int*)((char*)(t1004) + 4));
    t1006 = (int)(*(int*)((char*)(t1004)));
    t1007 = (int)(t1005);
    t1008 = (int)(t1007 - t1006);
    t1016 = (int)(t1008 / (int)24);
    t1012 = (int)((int)(a4));
    if ((unsigned int)(t1012) > (unsigned int)(t1016)) {
        t1017 = (int)((int)&v_l24);
        t1018 = (int)(t1012 - t1016);
        t1019 = (int)(t1004);
        t1020 = (int)((C_00b84e90*)(t1019))->FUN_00b84e90((unsigned int)(t1005), (unsigned int)(t1018), (unsigned int)(t1017));
        return (int)(t1020);
    }
    t6 = (int)(t1012 << (int)1);
    t1026 = (int)(t1012 + t6);
    t7 = (int)(t1026 << (int)3);
    t1027 = (int)(t1006 + t7);
    FUN_00720250((unsigned int)(t1005), (unsigned int)(t1005), (unsigned int)(t1027));
    t1031 = (int)(t1005 - t1027);
    t1038 = (int)(t1031 / (int)(-24));
    t11 = (int)(t1038 << (int)1);
    t1039 = (int)(t1038 + t11);
    t1040 = (int)(t1039 + t1039);
    t1041 = (int)(t1040 + t1040);
    t1042 = (int)(t1041 + t1041);
    *(int*)((char*)(t1004) + 4) += t1042;
    return (int)(t1038);
}
