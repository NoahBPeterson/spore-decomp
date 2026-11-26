// 0x011be2e0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" void __cdecl FUN_011d90c0(...);

// @ 0x011be2e0
extern "C" int __cdecl FUN_011be2e0(int a4, int a8, int a12, int a16)
{
    int t1000;
    int t1001;
    int t1002;
    int t1003;
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1011;
    t1000 = (int)((int)(a4));
    t1001 = (int)(*(int*)((char*)(t1000) + 8));
    t1002 = (int)(t1000 + (int)80);
    t1003 = (int)(*(int*)((char*)(t1000) + 96));
    t1004 = (int)(t1000 + (int)32);
    t1005 = (int)((int)(a16));
    t1006 = (int)((int)(a8));
    t1007 = (int)((int)(a12));
    FUN_011d90c0((unsigned int)(t1007), (unsigned int)(t1006), (unsigned int)(t1005), (unsigned int)(t1003), (unsigned int)(t1004), (unsigned int)(t1002), (unsigned int)(t1001));
    t1011 = (int)((int)1);
    return (int)(t1011);
}
