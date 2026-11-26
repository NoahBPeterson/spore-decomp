// 0x010a4850: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/Havok/_at_010a0000.cpp, match/slices/s010a3ed0/s010a3ed0.cpp.

extern "C" unsigned char g_016e5090[];
extern "C" unsigned char g_016e5094[];
extern "C" unsigned char g_016e5098[];
extern "C" unsigned char g_016e509c[];
extern "C" unsigned char g_016e50a0[];
extern "C" unsigned char g_016e50a4[];
extern "C" unsigned char g_016e50a8[];
extern "C" unsigned char g_016e50ac[];
extern "C" unsigned char g_016e50b0[];
extern "C" unsigned char g_016e50b4[];
extern "C" unsigned char g_016e50b8[];
extern "C" unsigned char g_016e50bc[];
extern "C" unsigned char g_016e50c0[];
extern "C" unsigned char g_016e50c4[];
extern "C" unsigned char g_016e50c8[];
extern "C" unsigned char g_016e50cc[];
extern "C" unsigned char g_016e50d0[];

// @ 0x010a4850
extern "C" int __stdcall FUN_010a4850(int a4, int a8, int a12, int a16, int a20)
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
    int t1013;
    int t1014;
    int t1015;
    int t1016;
    int t1017;
    t1000 = (int)((int)(a12));
    *(unsigned char*)g_016e50d0 = (unsigned char)((int)1);
    t1001 = (int)(*(int*)((char*)(t1000)));
    *(int*)g_016e5090 = (int)(t1001);
    t1002 = (int)(*(int*)((char*)(t1000) + 4));
    *(int*)g_016e5094 = (int)(t1002);
    t1003 = (int)(*(int*)((char*)(t1000) + 8));
    *(int*)g_016e5098 = (int)(t1003);
    t1004 = (int)(*(int*)((char*)(t1000) + 12));
    *(int*)g_016e509c = (int)(t1004);
    t1005 = (int)(*(int*)((char*)(t1000) + 16));
    *(int*)g_016e50a0 = (int)(t1005);
    t1006 = (int)(*(int*)((char*)(t1000) + 20));
    *(int*)g_016e50a4 = (int)(t1006);
    t1007 = (int)(*(int*)((char*)(t1000) + 24));
    *(int*)g_016e50a8 = (int)(t1007);
    t1008 = (int)(*(int*)((char*)(t1000) + 28));
    t1009 = (int)((int)(a20));
    *(int*)g_016e50ac = (int)(t1008);
    t1010 = (int)(*(int*)((char*)(t1009)));
    *(int*)g_016e50b0 = (int)(t1010);
    t1011 = (int)(*(int*)((char*)(t1009) + 4));
    *(int*)g_016e50b4 = (int)(t1011);
    t1012 = (int)(*(int*)((char*)(t1009) + 8));
    *(int*)g_016e50b8 = (int)(t1012);
    t1013 = (int)(*(int*)((char*)(t1009) + 12));
    *(int*)g_016e50bc = (int)(t1013);
    t1014 = (int)(*(int*)((char*)(t1009) + 16));
    *(int*)g_016e50c0 = (int)(t1014);
    t1015 = (int)(*(int*)((char*)(t1009) + 20));
    *(int*)g_016e50c4 = (int)(t1015);
    t1016 = (int)(*(int*)((char*)(t1009) + 24));
    *(int*)g_016e50c8 = (int)(t1016);
    t1017 = (int)(*(int*)((char*)(t1009) + 28));
    *(int*)g_016e50cc = (int)(t1017);
    return (int)(t1009);
}
