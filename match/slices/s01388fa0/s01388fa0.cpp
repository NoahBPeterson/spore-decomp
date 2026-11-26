// 0x01388fa0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" unsigned char g_013c8ca0[];
extern "C" unsigned char g_01481da0[];
extern "C" unsigned char g_0148af2c[];
extern "C" unsigned char g_015aca38[];
extern "C" unsigned char g_016c7a2c[];
extern "C" unsigned char g_016c7a30[];
extern "C" unsigned char g_016c7a34[];
extern "C" unsigned char g_016c7a38[];
extern "C" int __cdecl FUN_00932e80(...);
extern "C" int __cdecl FUN_011e07ef(...);

// @ 0x01388fa0
extern "C" void __cdecl FUN_01388fa0(void)
{
    int t1003;
    int t1004;
    t1003 = (int)FUN_00932e80((unsigned int)((int)g_0148af2c), (unsigned int)((int)(-2128831035)), (unsigned int)((int)1));
    *(int*)g_016c7a30 = (int)(t1003);
    t1004 = (int)((int)(*(int*)g_015aca38));
    *(int*)g_016c7a34 = (int)(t1004);
    *(int*)g_015aca38 = (int)((int)g_016c7a2c);
    *(int*)g_016c7a2c = (int)((int)g_01481da0);
    *(int*)g_016c7a38 = (int)((int)0);
    FUN_011e07ef((unsigned int)((int)g_013c8ca0));
    return;
}
