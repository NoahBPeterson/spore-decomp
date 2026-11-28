// 0x00a05830: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00a04d20/s00a04d20.cpp, src/game/SPCreatureAnim/SPCreatureAnimManager.cpp.

extern "C" unsigned char g_013ebb38[];
extern "C" unsigned char g_013f2150[];
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x00a05830
extern "C" int __fastcall FUN_00a05830(char* self, int edx_unused, int a4, int a8)
{
    int t1001;
    int t1004;
    int t2;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t9;
    int t1012;
    int t1013;
    int t10;
    int t1014;
    int t1015;
    t1001 = (int)((int)(a4));
    t1004 = (int)((int)(self));
    if (t1001 != (int)0) {
        t2 = (int)(t1001 << (int)3);
        t1005 = (int)(t2);
        t1006 = (int)(t1005 - t1001);
        t1007 = (int)(t1006 + t1006);
        t1008 = (int)(t1007 + t1007);
        t1009 = (int)FUN_00f473a0((unsigned int)(t1008), (unsigned int)((int)g_013f2150), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)g_013ebb38), (unsigned int)((int)209));
    } else {
        t1009 = (int)((int)0);
    }
    t9 = (int)(t1001 << (int)3);
    t1012 = (int)(t9);
    t1013 = (int)(t1012 - t1001);
    t10 = (int)(t1013 << (int)2);
    t1014 = (int)(t1009 + t10);
    *(int*)((char*)(t1004)) = (int)(t1009);
    *(int*)((char*)(t1004) + 4) = (int)(t1009);
    *(int*)((char*)(t1004) + 8) = (int)(t1014);
    t1015 = (int)(t1004);
    return (int)(t1015);
}
