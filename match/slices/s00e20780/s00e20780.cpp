// 0x00e20780: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00e1fb20/s00e1fb20.cpp, src/game/SPGonzago/_at_00e20000.cpp.

extern "C" unsigned char g_013ec468[];
extern "C" unsigned char g_01480498[];
struct C_00579a90 { int FUN_00579a90(unsigned int); };

// @ 0x00e20780
extern "C" int __fastcall FUN_00e20780(char* self, int edx_unused)
{
    int t1002;
    int t1004;
    int t1005;
    int t1009;
    int t1013;
    int t1015;
    t1002 = (int)((int)(self));
    t1004 = (int)((int)0);
    t1005 = (int)(t1002 + (int)68);
    *(int*)((char*)(t1002) + 4) = (int)(t1004);
    *(int*)((char*)(t1002)) = (int)((int)g_01480498);
    *(int*)((char*)(t1005)) = (int)(t1004);
    *(int*)((char*)(t1005) + 4) = (int)(t1004);
    *(int*)((char*)(t1005) + 8) = (int)(t1004);
    ((C_00579a90*)(t1005))->FUN_00579a90((unsigned int)((int)g_013ec468));
    t1009 = (int)(t1002 + (int)8296);
    *(int*)((char*)(t1009)) = (int)(t1004);
    *(int*)((char*)(t1009) + 4) = (int)(t1004);
    *(int*)((char*)(t1009) + 8) = (int)(t1004);
    ((C_00579a90*)(t1009))->FUN_00579a90((unsigned int)((int)g_013ec468));
    t1013 = (int)((int)(-1));
    *(int*)((char*)(t1002) + 8) = (int)(t1004);
    *(int*)((char*)(t1002) + 12) = (int)(t1004);
    *(int*)((char*)(t1002) + 56) = (int)(t1004);
    *(int*)((char*)(t1002) + 16) = (int)(t1004);
    *(int*)((char*)(t1002) + 20) = (int)(t1004);
    *(int*)((char*)(t1002) + 24) = (int)(t1004);
    *(int*)((char*)(t1002) + 28) = (int)(t1004);
    *(int*)((char*)(t1002) + 36) = (int)(t1004);
    *(int*)((char*)(t1002) + 32) = (int)(t1004);
    *(int*)((char*)(t1002) + 48) = (int)(t1004);
    *(int*)((char*)(t1002) + 40) = (int)(t1004);
    *(int*)((char*)(t1002) + 52) = (int)(t1004);
    *(int*)((char*)(t1002) + 84) = (int)(t1004);
    *(int*)((char*)(t1002) + 88) = (int)(t1004);
    *(int*)((char*)(t1002) + 60) = (int)(t1004);
    *(int*)((char*)(t1002) + 92) = (int)(t1013);
    *(int*)((char*)(t1002) + 96) = (int)(t1013);
    t1015 = (int)(t1002);
    return (int)(t1015);
}
