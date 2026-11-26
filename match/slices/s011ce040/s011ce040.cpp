// 0x011ce040: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" unsigned char g_0117cfb0[];
extern "C" unsigned char g_014e4f1c[];
extern "C" int __cdecl FUN_01190020(...);

// @ 0x011ce040
extern "C" void __cdecl FUN_011ce040(int a4, int a8, int a12, int a16)
{
    int t1000;
    int t1001;
    int t1002;
    int t1003;
    t1000 = (int)((int)(a16));
    t1001 = (int)((int)(a12));
    t1002 = (int)((int)(a8));
    t1003 = (int)((int)(a4));
    FUN_01190020((unsigned int)((int)g_0117cfb0), (unsigned int)((int)g_014e4f1c), (unsigned int)(t1003), (unsigned int)(t1002), (unsigned int)(t1001), (unsigned int)(t1000));
    return;
}
