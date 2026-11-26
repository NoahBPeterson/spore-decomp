// 0x01372bb0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" unsigned char g_013c79b0[];
extern "C" unsigned char g_01481da0[];
extern "C" unsigned char g_014820c8[];
extern "C" unsigned char g_015a59f4[];
extern "C" unsigned char g_016acd64[];
extern "C" unsigned char g_016acd68[];
extern "C" unsigned char g_016acd6c[];
extern "C" unsigned char g_016acd70[];
extern "C" int __cdecl FUN_00932e80(...);
extern "C" int __cdecl FUN_011e07ef(...);

// @ 0x01372bb0
extern "C" void __cdecl FUN_01372bb0(void)
{
    int t1003;
    int t1004;
    t1003 = (int)FUN_00932e80((unsigned int)((int)g_014820c8), (unsigned int)((int)(-2128831035)), (unsigned int)((int)1));
    *(int*)g_016acd68 = (int)(t1003);
    t1004 = (int)((int)(*(int*)g_015a59f4));
    *(int*)g_016acd6c = (int)(t1004);
    *(int*)g_015a59f4 = (int)((int)g_016acd64);
    *(int*)g_016acd64 = (int)((int)g_01481da0);
    *(int*)g_016acd70 = (int)((int)4000);
    FUN_011e07ef((unsigned int)((int)g_013c79b0));
    return;
}
