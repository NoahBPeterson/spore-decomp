// 0x011cf210: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" unsigned char g_014f2878[];
extern "C" unsigned char g_014f2880[];
extern "C" int __cdecl FUN_0118a460(...);

// @ 0x011cf210
extern "C" void __cdecl FUN_011cf210(int a4, int a8)
{
    int t1000;
    int t1001;
    int t1002;
    int t1003;
    int t1004;
    int t1008;
    int t1009;
    t1000 = (int)((int)(a4));
    t1001 = (int)(*(int*)((char*)(t1000) + 4));
    if (t1001 != (int)0) {
        t1002 = (int)(*(int*)((char*)(t1000) + 8));
        t1003 = (int)(*(int*)((char*)(t1000)));
        t1004 = (int)((int)(a8));
        FUN_0118a460((unsigned int)(t1004), (unsigned int)((int)g_014f2880), (unsigned int)(t1003), (unsigned int)(t1001), (unsigned int)(t1002));
        return;
    }
    t1008 = (int)(*(int*)((char*)(t1000)));
    t1009 = (int)((int)(a8));
    FUN_0118a460((unsigned int)(t1009), (unsigned int)((int)g_014f2878), (unsigned int)(t1008));
    return;
}
