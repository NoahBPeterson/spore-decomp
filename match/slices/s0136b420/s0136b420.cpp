// 0x0136b420: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" unsigned char g_013c5ce0[];
extern "C" unsigned char g_014194ac[];
extern "C" unsigned char g_0147d0bc[];
extern "C" unsigned char g_015a2ca8[];
extern "C" unsigned char g_016a0a60[];
extern "C" unsigned char g_016a0a64[];
extern "C" unsigned char g_016a0a68[];
extern "C" unsigned char g_016a0a6c[];
extern "C" int __cdecl FUN_00932e80(...);
extern "C" int __cdecl FUN_011e07ef(...);

// @ 0x0136b420
extern "C" void __cdecl FUN_0136b420(void)
{
    int t1003;
    int t1004;
    t1003 = (int)FUN_00932e80((unsigned int)((int)g_0147d0bc), (unsigned int)((int)(-2128831035)), (unsigned int)((int)1));
    *(int*)g_016a0a64 = (int)(t1003);
    t1004 = (int)((int)(*(int*)g_015a2ca8));
    *(int*)g_016a0a68 = (int)(t1004);
    *(int*)g_015a2ca8 = (int)((int)g_016a0a60);
    *(int*)g_016a0a60 = (int)((int)g_014194ac);
    *(int*)g_016a0a6c = (int)((int)32);
    FUN_011e07ef((unsigned int)((int)g_013c5ce0));
    return;
}
