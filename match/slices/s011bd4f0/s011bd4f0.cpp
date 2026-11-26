// 0x011bd4f0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" int __cdecl FUN_011bd440(...);

// @ 0x011bd4f0
extern "C" void __cdecl FUN_011bd4f0(int a4, int a8, int a12, int a16, int a20, int a24)
{
    int t1000;
    int t1001;
    int t1002;
    int t1003;
    int t1004;
    int t1005;
    t1000 = (int)((int)(a24));
    t1001 = (int)((int)(a20));
    t1002 = (int)((int)(a16));
    t1003 = (int)((int)(a12));
    t1004 = (int)((int)(a8));
    t1005 = (int)((int)(a4));
    FUN_011bd440((unsigned int)(t1005), (unsigned int)(t1004), (unsigned int)(t1003), (unsigned int)(t1002), (unsigned int)(t1001), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)(t1000));
    return;
}
