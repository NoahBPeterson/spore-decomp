// 0x00bbc460: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPUISpace.cpp, match/slices/s00bbb9d0/s00bbb9d0.cpp.

extern "C" unsigned char g_0168a488[];
extern "C" unsigned char g_0168a48c[];
extern "C" unsigned char g_0168a490[];

// @ 0x00bbc460
extern "C" int __fastcall FUN_00bbc460(char* self, int edx_unused, int a4, int a8, int a12)
{
    int t1000;
    int t1002;
    int t1003;
    int t1004;
    int t1005;
    int t1006;
    t1000 = (int)((int)(*(int*)g_0168a488));
    *(int*)((char*)((int)(self)) + 124) = (int)(t1000);
    t1002 = (int)((int)(*(int*)g_0168a48c));
    *(int*)((char*)((int)(self)) + 128) = (int)(t1002);
    t1003 = (int)((int)(*(int*)g_0168a490));
    t1004 = (int)((int)(a4));
    *(int*)((char*)((int)(self)) + 136) = (int)(t1004);
    t1005 = (int)((int)(a12));
    *(int*)((char*)((int)(self)) + 132) = (int)(t1003);
    t1006 = (int)((int)(a8));
    *(int*)((char*)((int)(self)) + 140) = (int)(t1006);
    *(int*)((char*)((int)(self)) + 144) = (int)(t1005);
    return (int)(t1006);
}
