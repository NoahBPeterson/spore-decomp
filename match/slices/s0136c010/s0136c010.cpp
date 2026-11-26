// 0x0136c010: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" unsigned char g_013c6010[];
extern "C" unsigned char g_014194ac[];
extern "C" unsigned char g_0147d5d0[];
extern "C" unsigned char g_015a2ff8[];
extern "C" unsigned char g_016a0ddc[];
extern "C" unsigned char g_016a0de0[];
extern "C" unsigned char g_016a0de4[];
extern "C" unsigned char g_016a0de8[];
extern "C" int __cdecl FUN_00932e80(...);
extern "C" int __cdecl FUN_011e07ef(...);

// @ 0x0136c010
extern "C" void __cdecl FUN_0136c010(void)
{
    int t1003;
    int t1004;
    t1003 = (int)FUN_00932e80((unsigned int)((int)g_0147d5d0), (unsigned int)((int)(-2128831035)), (unsigned int)((int)1));
    *(int*)g_016a0de0 = (int)(t1003);
    t1004 = (int)((int)(*(int*)g_015a2ff8));
    *(int*)g_016a0de4 = (int)(t1004);
    *(int*)g_015a2ff8 = (int)((int)g_016a0ddc);
    *(int*)g_016a0ddc = (int)((int)g_014194ac);
    *(int*)g_016a0de8 = (int)((int)32);
    FUN_011e07ef((unsigned int)((int)g_013c6010));
    return;
}
