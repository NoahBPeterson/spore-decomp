// 0x011c84f0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" int __cdecl FUN_0117a8e0(...);
extern "C" int __cdecl FUN_0117ab40(...);
extern "C" void __cdecl FUN_0117ac20(...);

// @ 0x011c84f0
extern "C" int __cdecl FUN_011c84f0(int a4, int a8)
{
    int t1001;
    int t1003;
    int t1007;
    int t1010;
    int t1016;
    int t1018;
    t1001 = (int)((int)(a4));
    t1003 = (int)((int)(a8));
    t1007 = (int)FUN_0117ab40((unsigned int)(t1001), (unsigned int)(t1003));
    if (t1007 == (int)0) {
        return 0;
    }
    t1010 = (int)(t1001 + (int)20);
    FUN_0117ac20((unsigned int)(t1010), (unsigned int)((int)0));
    t1016 = (int)FUN_0117a8e0((unsigned int)(t1003));
    *(int*)((char*)(t1001) + 40) = (int)(t1016);
    *(int*)((char*)(t1001) + 44) = (int)((int)0);
    t1018 = (int)((int)1);
    return (int)(t1018);
}
