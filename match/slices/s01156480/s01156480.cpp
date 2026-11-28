// 0x01156480: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s011559a0/s011559a0.cpp.

extern "C" unsigned char g_015c3828[];
extern "C" unsigned char g_015c382c[];
extern "C" unsigned char g_015c3830[];
extern "C" unsigned char g_015c3834[];
extern "C" unsigned char g_015c3838[];
extern "C" unsigned char g_015c383c[];
extern "C" unsigned char g_016f16d4[];
extern "C" unsigned char g_016f16d8[];
extern "C" unsigned char g_016f16dc[];
extern "C" unsigned char g_016f16e0[];
extern "C" unsigned char g_016f16e4[];
extern "C" unsigned char g_016f16e8[];

// @ 0x01156480
extern "C" int __cdecl FUN_01156480(int a4)
{
    int t1000;
    int t1001;
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
    int t1012;
    t1000 = (int)((int)(a4));
    t1001 = (int)((int)(*(int*)g_015c3828));
    t1002 = (int)((int)(*(int*)g_015c382c));
    t1003 = (int)(t1001 + t1000);
    t1004 = (int)(t1002 + t1000);
    *(int*)g_016f16d4 = (int)(t1003);
    t1005 = (int)((int)(*(int*)g_015c3830));
    *(int*)g_016f16d8 = (int)(t1004);
    t1006 = (int)((int)(*(int*)g_015c3834));
    t1007 = (int)(t1005 + t1000);
    t1008 = (int)(t1006 + t1000);
    *(int*)g_016f16dc = (int)(t1007);
    t1009 = (int)((int)(*(int*)g_015c3838));
    *(int*)g_016f16e0 = (int)(t1008);
    t1010 = (int)((int)(*(int*)g_015c383c));
    t1011 = (int)(t1009 + t1000);
    t1012 = (int)(t1010 + t1000);
    *(int*)g_016f16e4 = (int)(t1011);
    *(int*)g_016f16e8 = (int)(t1012);
    return (int)(t1000);
}
