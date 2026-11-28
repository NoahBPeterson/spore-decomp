// 0x00957a60: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/UTFSpore_Win32/_at_00950000.cpp, match/slices/s009579f0/s009579f0.cpp.

extern "C" unsigned char g_0154edf0[];
extern "C" unsigned char g_0154edfc[];
extern "C" unsigned char g_0154ee00[];
extern "C" unsigned char g_0154ee04[];
extern "C" unsigned char g_0166b138[];

// @ 0x00957a60
extern "C" int __cdecl FUN_00957a60(int a4, int a8)
{
    int t1000;
    unsigned char t1;
    int t1001;
    int t1002;
    int t1003;
    t1000 = (int)((int)1);
    t1 = (unsigned char)((unsigned char)(*(unsigned char*)g_0166b138) & (unsigned char)(t1000));
    if (t1 == (unsigned char)0) {
        *(int*)g_0166b138 = (int)((int)(*(int*)g_0166b138) | t1000);
        t1001 = (int)((int)(a4));
        t1002 = (int)((int)(a8));
        *(int*)g_0154edfc = (int)(t1001);
        *(int*)g_0154ee00 = (int)(t1002);
        *(int*)g_0154ee04 = (int)((int)0);
    }
    t1003 = (int)((int)g_0154edf0);
    return (int)(t1003);
}
