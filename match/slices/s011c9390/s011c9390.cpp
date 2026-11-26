// 0x011c9390: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" unsigned char g_014f23a4[];
extern "C" void __cdecl FUN_011815d0(...);

// @ 0x011c9390
extern "C" int __cdecl FUN_011c9390(int a4)
{
    int t1001;
    int t1002;
    int t1007;
    t1001 = (int)((int)(a4));
    t1002 = (int)(t1001 + (int)24);
    FUN_011815d0((unsigned int)(t1002), (unsigned int)((int)1), (unsigned int)((int)36), (unsigned int)((int)g_014f23a4), (unsigned int)((int)127));
    t1007 = (int)(t1001);
    return (int)(t1007);
}
