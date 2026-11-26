// 0x0138e480: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" unsigned char g_013c9830[];
extern "C" unsigned char g_01481da0[];
extern "C" unsigned char g_0148d534[];
extern "C" unsigned char g_015b0534[];
extern "C" unsigned char g_016c8958[];
extern "C" unsigned char g_016c895c[];
extern "C" unsigned char g_016c8960[];
extern "C" unsigned char g_016c8964[];
extern "C" int __cdecl FUN_00932e80(...);
extern "C" int __cdecl FUN_011e07ef(...);

// @ 0x0138e480
extern "C" void __cdecl FUN_0138e480(void)
{
    int t1003;
    int t1004;
    t1003 = (int)FUN_00932e80((unsigned int)((int)g_0148d534), (unsigned int)((int)(-2128831035)), (unsigned int)((int)1));
    *(int*)g_016c895c = (int)(t1003);
    t1004 = (int)((int)(*(int*)g_015b0534));
    *(int*)g_016c8960 = (int)(t1004);
    *(int*)g_015b0534 = (int)((int)g_016c8958);
    *(int*)g_016c8958 = (int)((int)g_01481da0);
    *(int*)g_016c8964 = (int)((int)3);
    FUN_011e07ef((unsigned int)((int)g_013c9830));
    return;
}
