// 0x01133020: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/cmn/_at_01130000.cpp, match/slices/s01132ad0/s01132ad0.cpp.

extern "C" unsigned char g_015bfe38[];
extern "C" int __cdecl FUN_0113f1c0(...);

// @ 0x01133020
extern "C" int __cdecl FUN_01133020(int a4, int a8)
{
    int t1000;
    int t1001;
    int t1002;
    int t1;
    int t2;
    int t1004;
    int t3;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1011;
    t1000 = (int)((int)(a4));
    t1001 = (int)((int)(*(int*)g_015bfe38));
    t1002 = (int)((int)(a8));
    t1 = (int)(t1000 << (int)2);
    t2 = (int)(t1000 + t1);
    t1004 = (int)(t2 + (int)65);
    t3 = (int)(t1004 << (int)1);
    t1005 = (int)(t1001 + t3);
    t1006 = (int)(t1005 + t1005);
    t1007 = (int)(t1006 + t1006);
    t1008 = (int)FUN_0113f1c0((unsigned int)(t1002));
    t1011 = (int)(t1008 + t1007);
    return (int)(t1011);
}
