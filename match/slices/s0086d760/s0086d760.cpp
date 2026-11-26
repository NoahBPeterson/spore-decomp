// 0x0086d760: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" int __cdecl FUN_011e0744(...);

// @ 0x0086d760
extern "C" void __cdecl FUN_0086d760(int a4, int a8, int a12, int a16)
{
    int t1000;
    int t1001;
    int t1002;
    t1000 = (int)((int)(a16));
    t1001 = (int)((int)(a12));
    t1002 = (int)((int)(a8));
    FUN_011e0744((unsigned int)(t1002), (unsigned int)(t1001), (unsigned int)(t1000));
    return;
}
