// 0x008668d0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" int __cdecl FUN_011e0744(...);

// @ 0x008668d0
extern "C" void __cdecl FUN_008668d0(int a4, int a8, int a12)
{
    int t1000;
    int t1001;
    int t1002;
    int t1003;
    t1000 = (int)((int)(a12));
    t1001 = (int)((int)(a4));
    t1002 = (int)((int)(a8));
    t1003 = (int)(t1000 << (int)7);
    FUN_011e0744((unsigned int)(t1002), (unsigned int)(t1001), (unsigned int)(t1003));
    return;
}
