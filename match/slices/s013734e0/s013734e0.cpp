// 0x013734e0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" unsigned char g_013c7b30[];
extern "C" unsigned char g_01481da0[];
extern "C" unsigned char g_0148231c[];
extern "C" unsigned char g_015a59f4[];
extern "C" unsigned char g_016acf20[];
extern "C" unsigned char g_016acf24[];
extern "C" unsigned char g_016acf28[];
extern "C" unsigned char g_016acf2c[];
extern "C" int __cdecl FUN_00932e80(...);
extern "C" int __cdecl FUN_011e07ef(...);

// @ 0x013734e0
extern "C" void __cdecl FUN_013734e0(void)
{
    int t1003;
    int t1004;
    t1003 = (int)FUN_00932e80((unsigned int)((int)g_0148231c), (unsigned int)((int)(-2128831035)), (unsigned int)((int)1));
    *(int*)g_016acf24 = (int)(t1003);
    t1004 = (int)((int)(*(int*)g_015a59f4));
    *(int*)g_016acf28 = (int)(t1004);
    *(int*)g_015a59f4 = (int)((int)g_016acf20);
    *(int*)g_016acf20 = (int)((int)g_01481da0);
    *(int*)g_016acf2c = (int)((int)1000);
    FUN_011e07ef((unsigned int)((int)g_013c7b30));
    return;
}
