// 0x00af9cf0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/_at_00af0000.cpp, match/slices/s00af9aa0/s00af9aa0.cpp.

extern "C" unsigned char g_0156737c[];
extern "C" unsigned char g_01567380[];
extern "C" unsigned char g_01567384[];
extern "C" unsigned char g_01567388[];

// @ 0x00af9cf0
extern "C" int __fastcall FUN_00af9cf0(char* self, int edx_unused, int a4, float a8, int a12, float a16)
{
    float t1000;
    int t1002;
    int t1003;
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1010;
    int t1011;
    float t1012;
    int t1013;
    int t1014;
    t1000 = (float)((float)(a8));
    *(unsigned char*)((char*)((int)(self)) + 40) = (unsigned char)((int)0);
    t1002 = (int)((int)(*(int*)g_0156737c));
    *(int*)((char*)((int)(self)) + 44) = (int)(t1002);
    t1003 = (int)((int)(*(int*)g_01567380));
    *(int*)((char*)((int)(self)) + 48) = (int)(t1003);
    t1004 = (int)((int)(*(int*)g_01567384));
    *(int*)((char*)((int)(self)) + 52) = (int)(t1004);
    t1005 = (int)((int)(*(int*)g_01567388));
    t1006 = (int)((int)(a4));
    *(int*)((char*)((int)(self)) + 56) = (int)(t1005);
    t1007 = (int)(*(int*)((char*)(t1006)));
    *(int*)((char*)((int)(self)) + 20) = (int)(t1007);
    t1008 = (int)(*(int*)((char*)(t1006) + 4));
    *(int*)((char*)((int)(self)) + 24) = (int)(t1008);
    t1009 = (int)(*(int*)((char*)(t1006) + 8));
    *(int*)((char*)((int)(self)) + 28) = (int)(t1009);
    t1010 = (int)((int)(a12));
    *(float*)((char*)((int)(self)) + 12) = (float)(t1000);
    t1011 = (int)(*(int*)((char*)(t1010)));
    t1012 = (float)((float)(a16));
    *(int*)((char*)((int)(self))) = (int)(t1011);
    t1013 = (int)(*(int*)((char*)(t1010) + 4));
    *(int*)((char*)((int)(self)) + 4) = (int)(t1013);
    t1014 = (int)(*(int*)((char*)(t1010) + 8));
    *(int*)((char*)((int)(self)) + 8) = (int)(t1014);
    *(float*)((char*)((int)(self)) + 32) = (float)(t1012);
    return (int)(t1014);
}
