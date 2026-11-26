// 0x0086d780: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" int __cdecl FUN_011e073e(...);

// @ 0x0086d780
extern "C" void __cdecl FUN_0086d780(int a4, int a8, int a12, int a16)
{
    int t1000;
    int t1001;
    int t1002;
    t1000 = (int)((int)(a16));
    t1001 = (int)((int)(a12));
    t1002 = (int)((int)(a8));
    FUN_011e073e((unsigned int)(t1002), (unsigned int)(t1001), (unsigned int)(t1000));
    return;
}
