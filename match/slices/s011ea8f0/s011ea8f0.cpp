// 0x011ea8f0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" int __cdecl FUN_011ed2a0(...);

// @ 0x011ea8f0
extern "C" void __cdecl FUN_011ea8f0(int a4, int a8)
{
    int t1000;
    int t1001;
    t1000 = (int)((int)(a8));
    t1001 = (int)((int)(a4));
    FUN_011ed2a0((unsigned int)(t1001), (unsigned int)((int)0), (unsigned int)(t1000));
    return;
}
