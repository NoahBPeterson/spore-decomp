// 0x00f9b2b0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPTerrain/SPTerrainSphere.cpp, match/slices/s00f9a610/s00f9a610.cpp.

struct C_0041cb40 { void FUN_0041cb40(unsigned int); };
extern "C" int __cdecl FUN_00f96390(...);
extern "C" void __cdecl FUN_011e073e(...);

// @ 0x00f9b2b0
extern "C" int __fastcall FUN_00f9b2b0(char* self, int edx_unused, int a4, int a8, int a12)
{
    int t1002;
    int t1004;
    unsigned short t1006;
    unsigned short t1007;
    int t1008;
    int t1009;
    int t1013;
    int t1014;
    int t1015;
    int t1016;
    int t1017;
    int t1020;
    int t1021;
    int t1024;
    int t1029;
    t1002 = (int)((int)(self));
    t1004 = (int)((int)(a8));
    t1006 = (unsigned short)(*(unsigned short*)((char*)(t1004)));
    *(unsigned short*)((char*)(t1002)) = (unsigned short)(t1006);
    t1007 = (unsigned short)(*(unsigned short*)((char*)(t1004) + 2));
    *(unsigned short*)((char*)(t1002) + 2) = (unsigned short)(t1007);
    *(float*)((char*)(t1002) + 4) = (float)(*(float*)((char*)(t1004) + 4));
    t1008 = (int)(t1004 + (int)20);
    *(float*)((char*)(t1002) + 8) = (float)(*(float*)((char*)(t1004) + 8));
    t1009 = (int)(t1002 + (int)20);
    *(float*)((char*)(t1002) + 12) = (float)(*(float*)((char*)(t1004) + 12));
    *(float*)((char*)(t1002) + 16) = (float)(*(float*)((char*)(t1004) + 16));
    ((C_0041cb40*)(t1009))->FUN_0041cb40((unsigned int)(t1008));
    t1013 = (int)((int)(a4));
    t1014 = (int)(*(int*)((char*)(t1013)));
    *(int*)((char*)(t1002) + 152) = (int)(t1014);
    t1015 = (int)(*(int*)((char*)(t1013) + 4));
    *(int*)((char*)(t1002) + 156) = (int)(t1015);
    t1016 = (int)((unsigned char)(a12));
    t1017 = (int)(*(int*)((char*)(t1013) + 8));
    t1020 = (int)(((int)(t1016) != (int)((int)0)) ? (int)((int)67108864) : (int)((int)0));
    *(int*)((char*)(t1002) + 160) = (int)(t1017);
    *(int*)((char*)(t1002) + 164) = (int)(t1020);
    t1021 = (int)FUN_00f96390((unsigned int)(t1004), (unsigned int)(t1013));
    *(int*)((char*)(t1002) + 168) = (int)(t1021);
    t1024 = (int)(t1002 + (int)56);
    FUN_011e073e((unsigned int)(t1024), (unsigned int)((int)0), (unsigned int)((int)96));
    t1029 = (int)(t1002);
    return (int)(t1029);
}
