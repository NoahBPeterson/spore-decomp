// 0x01300760: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s01300280/s01300280.cpp.

extern "C" void __cdecl FUN_013c1150(...);
extern "C" unsigned char g_01470f1c[];
extern "C" unsigned char g_01485720[];
extern "C" unsigned char g_0154df28[];
extern "C" unsigned char g_0166b194[];
extern "C" unsigned char g_0166b198[];
extern "C" unsigned char g_0166b19c[];
extern "C" unsigned char g_0166b1a0[];
extern "C" unsigned char g_0166b1a4[];
extern "C" unsigned char g_0166b1a8[];
extern "C" unsigned char g_0166b1ac[];
extern "C" unsigned char g_0166b1b0[];
extern "C" int __cdecl FUN_00925cb0(...);
extern "C" int __cdecl FUN_011e07ef(...);

// @ 0x01300760
extern "C" void __cdecl FUN_01300760(void)
{
    int t1001;
    float t1004;
    int t1005;
    float t1006;
    t1001 = (int)FUN_00925cb0();
    t1004 = (float)((float)(*(float*)g_01485720));
    *(int*)g_0166b1ac = (int)(t1001);
    t1005 = (int)((int)0);
    *(float*)g_0166b1a0 = (float)(t1004);
    t1006 = (float)((float)(*(float*)g_01470f1c));
    *(float*)g_0166b1a4 = (float)(t1006);
    *(int*)g_0166b1b0 = (int)(t1005);
    *(int*)g_0166b198 = (int)((int)1);
    *(int*)g_0166b194 = (int)((int)g_0154df28);
    *(int*)g_0166b19c = (int)(t1005);
    *(int*)g_0166b1a8 = (int)(t1005);
    FUN_011e07ef((unsigned int)((int)&FUN_013c1150));
    return;
}
