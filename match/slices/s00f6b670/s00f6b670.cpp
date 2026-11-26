// 0x00f6b670: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPTerrain/SPTerrainEditor.cpp, match/slices/s00f6a960/s00f6a960.cpp.

#include <string.h>
extern "C" unsigned char g_004098a0[];
struct C_00406540 { void FUN_00406540(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int); };
struct C_00f6b000 { void FUN_00f6b000(unsigned int); };
struct C_00f6b4b0 { void FUN_00f6b4b0(unsigned int); };

// @ 0x00f6b670
extern "C" int __fastcall FUN_00f6b670(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1004;
    int t1008;
    int t1009;
    int t1013;
    int t1014;
    int t1015;
    int t1019;
    int t1020;
    int t1021;
    int t1022;
    int t1026;
    int t1027;
    int t1028;
    int t1035;
    t1002 = (int)((int)(a4));
    t1004 = (int)((int)(self));
    t1008 = (int)(t1002);
    t1009 = (int)(t1004);
    memcpy((void*)(t1009), (const void*)(t1008), (unsigned int)((int)124));
    t1013 = (int)(*(int*)((char*)(t1002) + 124));
    t1014 = (int)(t1002 + (int)128);
    t1015 = (int)(t1004 + (int)128);
    *(int*)((char*)(t1004) + 124) = (int)(t1013);
    ((C_00f6b000*)(t1015))->FUN_00f6b000((unsigned int)(t1014));
    t1019 = (int)(*(int*)((char*)(t1002) + 248));
    *(int*)((char*)(t1004) + 248) = (int)(t1019);
    *(float*)((char*)(t1004) + 252) = (float)(*(float*)((char*)(t1002) + 252));
    *(float*)((char*)(t1004) + 256) = (float)(*(float*)((char*)(t1002) + 256));
    t1020 = (int)(t1002 + (int)272);
    *(float*)((char*)(t1004) + 260) = (float)(*(float*)((char*)(t1002) + 260));
    t1021 = (int)(t1004 + (int)272);
    *(float*)((char*)(t1004) + 264) = (float)(*(float*)((char*)(t1002) + 264));
    t1022 = (int)(*(int*)((char*)(t1002) + 268));
    *(int*)((char*)(t1004) + 268) = (int)(t1022);
    ((C_00406540*)(t1020))->FUN_00406540((unsigned int)(t1021), (unsigned int)(t1020), (unsigned int)((int)12), (unsigned int)((int)16), (unsigned int)((int)g_004098a0));
    t1026 = (int)(*(int*)((char*)(t1002) + 464));
    t1027 = (int)(t1002 + (int)468);
    t1028 = (int)(t1004 + (int)468);
    *(int*)((char*)(t1004) + 464) = (int)(t1026);
    ((C_00f6b4b0*)(t1028))->FUN_00f6b4b0((unsigned int)(t1027));
    t1035 = (int)(t1004);
    return (int)(t1035);
}
