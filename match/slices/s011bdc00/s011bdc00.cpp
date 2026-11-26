// 0x011bdc00: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" int __cdecl FUN_011d21d0(...);

// @ 0x011bdc00
extern "C" void __cdecl FUN_011bdc00(int a4, int a8)
{
    int t1000;
    int t1001;
    int t1002;
    t1000 = (int)((int)(a4));
    t1001 = (int)(*(int*)((char*)(t1000) + 12));
    t1002 = (int)((int)(a8));
    FUN_011d21d0((unsigned int)(t1002), (unsigned int)(t1001));
    return;
}
