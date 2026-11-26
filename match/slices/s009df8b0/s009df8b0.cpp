// 0x009df8b0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPCreatureAnim/gait_record.cpp, match/slices/s009de8b0/s009de8b0.cpp.

extern "C" unsigned char g_013ebb38[];
extern "C" unsigned char g_014479f4[];
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x009df8b0
extern "C" int __fastcall FUN_009df8b0(char* self, int edx_unused, int a4, int a8, int a12)
{
    int t1001;
    int t1004;
    int t2;
    int t1005;
    int t1006;
    int t1007;
    int t1010;
    int t9;
    int t1011;
    int t1012;
    int t1013;
    int t1014;
    int t1015;
    int t1016;
    int t1018;
    int t1019;
    int t1020;
    int t1022;
    int t1023;
    int t1024;
    t1001 = (int)((int)(a4));
    t1004 = (int)((int)(self));
    if (t1001 != (int)0) {
        t2 = (int)(t1001 << (int)1);
        t1005 = (int)(t1001 + t2);
        t1006 = (int)(t1005 + t1005);
        t1007 = (int)(t1006 + t1006);
        t1010 = (int)FUN_00f473a0((unsigned int)(t1007), (unsigned int)((int)g_014479f4), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)g_013ebb38), (unsigned int)((int)209));
    } else {
        t1010 = (int)((int)0);
    }
    t9 = (int)(t1001 << (int)1);
    t1011 = (int)(t1001 + t9);
    t1012 = (int)(t1011 + t1011);
    t1013 = (int)(t1012 + t1012);
    t1014 = (int)(t1013 + t1010);
    *(int*)((char*)(t1004) + 8) = (int)(t1014);
    *(int*)((char*)(t1004)) = (int)(t1010);
    *(int*)((char*)(t1004) + 4) = (int)(t1010);
    t1015 = (int)(t1001);
    if ((unsigned int)(t1001) > (unsigned int)0) {
        t1016 = (int)((int)(a8));
        do {
            if (t1010 != (int)0) {
                t1018 = (int)(*(int*)((char*)(t1016)));
                *(int*)((char*)(t1010)) = (int)(t1018);
                t1019 = (int)(*(int*)((char*)(t1016) + 4));
                *(int*)((char*)(t1010) + 4) = (int)(t1019);
                t1020 = (int)(*(int*)((char*)(t1016) + 8));
                *(int*)((char*)(t1010) + 8) = (int)(t1020);
            }
            t1015 = (int)(t1015 - (int)1);
            t1010 = (int)(t1010 + (int)12);
        } while ((unsigned int)(t1015) > (unsigned int)0);
    }
    t1022 = (int)(*(int*)((char*)(t1004)));
    t1023 = (int)(t1022 + t1013);
    *(int*)((char*)(t1004) + 4) = (int)(t1023);
    t1024 = (int)(t1004);
    return (int)(t1024);
}
