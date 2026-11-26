// 0x0136bf10: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" unsigned char g_013c5fe0[];
extern "C" unsigned char g_014194ac[];
extern "C" unsigned char g_0147d5a0[];
extern "C" unsigned char g_015a2ff8[];
extern "C" unsigned char g_016a0da4[];
extern "C" unsigned char g_016a0da8[];
extern "C" unsigned char g_016a0dac[];
extern "C" unsigned char g_016a0db0[];
extern "C" int __cdecl FUN_00932e80(...);
extern "C" int __cdecl FUN_011e07ef(...);

// @ 0x0136bf10
extern "C" void __cdecl FUN_0136bf10(void)
{
    int t1003;
    int t1004;
    t1003 = (int)FUN_00932e80((unsigned int)((int)g_0147d5a0), (unsigned int)((int)(-2128831035)), (unsigned int)((int)1));
    *(int*)g_016a0da8 = (int)(t1003);
    t1004 = (int)((int)(*(int*)g_015a2ff8));
    *(int*)g_016a0dac = (int)(t1004);
    *(int*)g_015a2ff8 = (int)((int)g_016a0da4);
    *(int*)g_016a0da4 = (int)((int)g_014194ac);
    *(int*)g_016a0db0 = (int)((int)1);
    FUN_011e07ef((unsigned int)((int)g_013c5fe0));
    return;
}
