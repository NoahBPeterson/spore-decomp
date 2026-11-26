// 0x00bcaab0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/_at_00bc0000.cpp, match/slices/s00bca040/s00bca040.cpp.

extern "C" unsigned char g_01466998[];
struct C_00926650 { int FUN_00926650(unsigned int, unsigned int); };

// @ 0x00bcaab0
extern "C" int __fastcall FUN_00bcaab0(char* self, int edx_unused)
{
    int t1003;
    int t1004;
    int t1005;
    int t1008;
    int t1009;
    int t1010;
    int t1013;
    t1003 = (int)((int)(self) + (int)8);
    t1004 = (int)((int)0);
    do {
        if ((int)*(int*)((char*)(t1003) + 16) != t1004) goto Lbcaaf3;
        t1005 = (int)(t1003);
        t1008 = (int)((C_00926650*)(t1005))->FUN_00926650((unsigned int)(t1004), (unsigned int)(t1004));
    } while ((unsigned char)(t1008) != (unsigned char)0);
    t1009 = (int)((int)0);
    Lbcaacb:;
    t1010 = (int)(t1009 + (int)8);
    if (t1010 != t1004) {
        *(int*)((char*)(t1010) + 4) = (int)(t1004);
        *(int*)((char*)(t1010)) = (int)((int)g_01466998);
        *(unsigned char*)((char*)(t1010) + 28) = (unsigned char)((unsigned char)(t1004));
        *(int*)((char*)(t1010) + 416) = (int)(t1004);
        *(int*)((char*)(t1010) + 548) = (int)(t1004);
        *(int*)((char*)(t1010) + 552) = (int)(t1004);
    }
    return (int)(t1009);
    Lbcaaf3:;
    t1009 = (int)(*(int*)((char*)(t1003) + 16));
    t1013 = (int)(*(int*)((char*)(t1009)));
    *(int*)((char*)(t1003) + 16) = (int)(t1013);
    goto Lbcaacb;
}
