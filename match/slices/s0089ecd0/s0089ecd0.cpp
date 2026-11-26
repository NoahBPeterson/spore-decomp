// 0x0089ecd0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" int __cdecl FUN_0089e6d0(...);
extern "C" void __cdecl FUN_0089e740(...);
extern "C" void __cdecl FUN_0089e8e0(...);
extern "C" void __cdecl FUN_0089eb00(...);
extern "C" int __cdecl FUN_0089ec70(...);

// @ 0x0089ecd0
extern "C" void __cdecl FUN_0089ecd0(int a4, int a8, int a12, int a16)
{
    int t1000;
    int t1002;
    int t1004;
    int t1008;
    int t1010;
    t1000 = (int)((int)(a8));
    t1002 = (int)((int)(a16));
    t1004 = (int)((int)(a12));
    t1008 = (int)FUN_0089e6d0((unsigned int)(t1000), (unsigned int)(t1004), (unsigned int)(t1002));
    if ((unsigned char)(t1008) != (unsigned char)0) {
        t1010 = (int)((int)(a4));
        FUN_0089e740((unsigned int)(t1010), (unsigned int)(t1004), (unsigned int)(t1002), (unsigned int)((int)0), (unsigned int)((int)0));
        FUN_0089e8e0((unsigned int)(t1010), (unsigned int)(t1004), (unsigned int)(t1002));
        FUN_0089eb00((unsigned int)(t1010), (unsigned int)(t1004), (unsigned int)(t1002));
        t1008 = (int)FUN_0089ec70((unsigned int)(t1004), (unsigned int)(t1002));
    }
    return;
}
