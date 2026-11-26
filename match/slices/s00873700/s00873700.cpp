// 0x00873700: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" unsigned char g_014227a4[];
extern "C" unsigned char g_014227c0[];
extern "C" void __cdecl FUN_0086b250(...);
extern "C" void __cdecl FUN_0086b300(...);
extern "C" int __cdecl FUN_008732d0(...);

// @ 0x00873700
extern "C" void __cdecl FUN_00873700(int a4, int a8, int a12)
{
    int t1001;
    int t1002;
    unsigned char t1;
    unsigned char t3;
    int t1008;
    t1001 = (int)((int)(a4));
    t1002 = (int)(*(int*)((char*)(t1001) + 104));
    t1 = (unsigned char)((unsigned char)(t1002) & (unsigned char)1);
    if (t1 != (unsigned char)0) {
        t3 = (unsigned char)((unsigned char)(t1002) & (unsigned char)4);
        if (t3 != (unsigned char)0) goto L87371f;
    }
    FUN_0086b250((unsigned int)(t1001), (unsigned int)((int)g_014227c0));
    L87371f:;
    t1008 = (int)((int)(a12));
    *(int*)((char*)(t1001) + 104) |= (int)24;
    if (t1008 != (int)0) {
        FUN_0086b300((unsigned int)(t1001), (unsigned int)((int)g_014227a4));
    }
    FUN_008732d0((unsigned int)(t1001), (unsigned int)(t1008));
    return;
}
