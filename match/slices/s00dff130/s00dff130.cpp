// 0x00dff130: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPGalaxyGameEntry.cpp, match/slices/s00dfe460/s00dfe460.cpp.

struct C_00dfb280 { void FUN_00dfb280(unsigned int); };
struct C_00dfeb00 { void FUN_00dfeb00(unsigned int); };

// @ 0x00dff130
extern "C" int __fastcall FUN_00dff130(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1004;
    int t1008;
    int t1009;
    int t1013;
    unsigned char t1014;
    int t1015;
    int t1016;
    int t1017;
    int t1018;
    int t1019;
    int t1024;
    t1002 = (int)((int)(a4));
    t1004 = (int)((int)(self));
    ((C_00dfb280*)((int)(self)))->FUN_00dfb280((unsigned int)(t1002));
    t1008 = (int)(t1002 + (int)60);
    t1009 = (int)(t1004 + (int)60);
    ((C_00dfb280*)(t1009))->FUN_00dfb280((unsigned int)(t1008));
    t1013 = (int)(*(int*)((char*)(t1002) + 120));
    *(int*)((char*)(t1004) + 120) = (int)(t1013);
    t1014 = (unsigned char)(*(unsigned char*)((char*)(t1002) + 124));
    *(unsigned char*)((char*)(t1004) + 124) = (unsigned char)(t1014);
    t1015 = (int)(*(int*)((char*)(t1002) + 128));
    *(int*)((char*)(t1004) + 128) = (int)(t1015);
    t1016 = (int)(t1004 + (int)132);
    t1017 = (int)(t1016 + (int)24);
    *(int*)((char*)(t1016)) = (int)(t1017);
    *(int*)((char*)(t1016) + 4) = (int)(t1017);
    t1018 = (int)(t1017 + (int)1176);
    t1019 = (int)(t1002 + (int)132);
    *(int*)((char*)(t1016) + 20) = (int)((int)0);
    *(int*)((char*)(t1016) + 8) = (int)(t1018);
    ((C_00dfeb00*)(t1016))->FUN_00dfeb00((unsigned int)(t1019));
    t1024 = (int)(t1004);
    return (int)(t1024);
}
