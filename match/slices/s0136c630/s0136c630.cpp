// 0x0136c630: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" unsigned char g_013c6140[];
extern "C" unsigned char g_014194ac[];
extern "C" unsigned char g_0147d7f8[];
extern "C" unsigned char g_015a2ff8[];
extern "C" unsigned char g_016a0f0c[];
extern "C" unsigned char g_016a0f10[];
extern "C" unsigned char g_016a0f14[];
extern "C" unsigned char g_016a0f18[];
extern "C" int __cdecl FUN_00932e80(...);
extern "C" int __cdecl FUN_011e07ef(...);

// @ 0x0136c630
extern "C" void __cdecl FUN_0136c630(void)
{
    int t1003;
    int t1004;
    t1003 = (int)FUN_00932e80((unsigned int)((int)g_0147d7f8), (unsigned int)((int)(-2128831035)), (unsigned int)((int)1));
    *(int*)g_016a0f10 = (int)(t1003);
    t1004 = (int)((int)(*(int*)g_015a2ff8));
    *(int*)g_016a0f14 = (int)(t1004);
    *(int*)g_015a2ff8 = (int)((int)g_016a0f0c);
    *(int*)g_016a0f0c = (int)((int)g_014194ac);
    *(int*)g_016a0f18 = (int)((int)15);
    FUN_011e07ef((unsigned int)((int)g_013c6140));
    return;
}
