// 0x01159760: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s01159630/s01159630.cpp.

extern "C" void __cdecl FUN_0116b6c0(...);
extern "C" void __cdecl FUN_0116b7c0(...);
extern "C" void __cdecl FUN_0116b920(...);
extern "C" unsigned char g_016e80a0[];
extern "C" unsigned char g_016e80a4[];
extern "C" unsigned char g_016e80a8[];
extern "C" unsigned char g_016e80ac[];
extern "C" unsigned char g_016e80b0[];
extern "C" unsigned char g_016e80b4[];
extern "C" unsigned char g_016e80e8[];
extern "C" unsigned char g_016e80ec[];
extern "C" unsigned char g_016e80f0[];
extern "C" unsigned char g_016e80f4[];
extern "C" unsigned char g_016e80f8[];
extern "C" unsigned char g_016e80fc[];

// @ 0x01159760
extern "C" int __cdecl FUN_01159760(void)
{
    int t1000;
    int t1001;
    int t1002;
    t1000 = (int)((int)60);
    t1001 = (int)((int)&FUN_0116b920);
    t1002 = (int)((int)48);
    *(int*)g_016e80a0 = (int)((int)&FUN_0116b7c0);
    *(int*)g_016e80e8 = (int)((int)44);
    *(int*)g_016e80a8 = (int)((int)&FUN_0116b6c0);
    *(int*)g_016e80f0 = (int)(t1000);
    *(int*)g_016e80a4 = (int)(t1001);
    *(int*)g_016e80ec = (int)(t1002);
    *(int*)g_016e80ac = (int)((int)&FUN_0116b7c0);
    *(int*)g_016e80f4 = (int)((int)44);
    *(int*)g_016e80b4 = (int)((int)&FUN_0116b6c0);
    *(int*)g_016e80fc = (int)(t1000);
    *(int*)g_016e80b0 = (int)(t1001);
    *(int*)g_016e80f8 = (int)(t1002);
    return (int)(t1002);
}
