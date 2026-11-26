// 0x013728e0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" unsigned char g_013c7920[];
extern "C" unsigned char g_01481da0[];
extern "C" unsigned char g_01481fe8[];
extern "C" unsigned char g_015a59f4[];
extern "C" unsigned char g_016accd4[];
extern "C" unsigned char g_016accd8[];
extern "C" unsigned char g_016accdc[];
extern "C" unsigned char g_016acce0[];
extern "C" int __cdecl FUN_00932e80(...);
extern "C" int __cdecl FUN_011e07ef(...);

// @ 0x013728e0
extern "C" void __cdecl FUN_013728e0(void)
{
    int t1003;
    int t1004;
    t1003 = (int)FUN_00932e80((unsigned int)((int)g_01481fe8), (unsigned int)((int)(-2128831035)), (unsigned int)((int)1));
    *(int*)g_016accd8 = (int)(t1003);
    t1004 = (int)((int)(*(int*)g_015a59f4));
    *(int*)g_016accdc = (int)(t1004);
    *(int*)g_015a59f4 = (int)((int)g_016accd4);
    *(int*)g_016accd4 = (int)((int)g_01481da0);
    *(int*)g_016acce0 = (int)((int)250);
    FUN_011e07ef((unsigned int)((int)g_013c7920));
    return;
}
