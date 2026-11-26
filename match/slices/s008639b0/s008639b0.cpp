// 0x008639b0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" void __cdecl FUN_00862d60(...);
extern "C" void __cdecl FUN_008638c0(...);
extern "C" int __cdecl FUN_00c2e4e0(...);

// @ 0x008639b0
extern "C" void __cdecl FUN_008639b0(int a4)
{
    int t1002;
    int t1003;
    int t1010;
    t1002 = (int)((int)(a4));
    t1003 = (int)((int)1);
    goto L8639c0;
    L8639c0:;
    FUN_008638c0((unsigned int)(t1002), (unsigned int)(t1003));
    t1003 = (int)(t1003 - (int)1);
    if (t1003 >= (int)0) goto L8639c0;
    t1010 = (int)(*(int*)((char*)(t1002) + 4));
    FUN_00862d60((unsigned int)(t1002), (unsigned int)(t1010), (unsigned int)((int)80));
    *(int*)((char*)(t1002) + 4) = (int)((int)0);
    FUN_00c2e4e0((unsigned int)(t1002));
    return;
}
