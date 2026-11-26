// 0x01372930: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" unsigned char g_013c7930[];
extern "C" unsigned char g_01481da0[];
extern "C" unsigned char g_01482000[];
extern "C" unsigned char g_015a59f4[];
extern "C" unsigned char g_016acce4[];
extern "C" unsigned char g_016acce8[];
extern "C" unsigned char g_016accec[];
extern "C" unsigned char g_016accf0[];
extern "C" int __cdecl FUN_00932e80(...);
extern "C" int __cdecl FUN_011e07ef(...);

// @ 0x01372930
extern "C" void __cdecl FUN_01372930(void)
{
    int t1003;
    int t1004;
    t1003 = (int)FUN_00932e80((unsigned int)((int)g_01482000), (unsigned int)((int)(-2128831035)), (unsigned int)((int)1));
    *(int*)g_016acce8 = (int)(t1003);
    t1004 = (int)((int)(*(int*)g_015a59f4));
    *(int*)g_016accec = (int)(t1004);
    *(int*)g_015a59f4 = (int)((int)g_016acce4);
    *(int*)g_016acce4 = (int)((int)g_01481da0);
    *(int*)g_016accf0 = (int)((int)10000);
    FUN_011e07ef((unsigned int)((int)g_013c7930));
    return;
}
