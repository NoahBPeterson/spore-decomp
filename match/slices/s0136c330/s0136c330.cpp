// 0x0136c330: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" unsigned char g_013c60b0[];
extern "C" unsigned char g_014194ac[];
extern "C" unsigned char g_0147d6e0[];
extern "C" unsigned char g_015a2ff8[];
extern "C" unsigned char g_016a0e7c[];
extern "C" unsigned char g_016a0e80[];
extern "C" unsigned char g_016a0e84[];
extern "C" unsigned char g_016a0e88[];
extern "C" int __cdecl FUN_00932e80(...);
extern "C" int __cdecl FUN_011e07ef(...);

// @ 0x0136c330
extern "C" void __cdecl FUN_0136c330(void)
{
    int t1003;
    int t1004;
    t1003 = (int)FUN_00932e80((unsigned int)((int)g_0147d6e0), (unsigned int)((int)(-2128831035)), (unsigned int)((int)1));
    *(int*)g_016a0e80 = (int)(t1003);
    t1004 = (int)((int)(*(int*)g_015a2ff8));
    *(int*)g_016a0e84 = (int)(t1004);
    *(int*)g_015a2ff8 = (int)((int)g_016a0e7c);
    *(int*)g_016a0e7c = (int)((int)g_014194ac);
    *(int*)g_016a0e88 = (int)((int)0);
    FUN_011e07ef((unsigned int)((int)g_013c60b0));
    return;
}
