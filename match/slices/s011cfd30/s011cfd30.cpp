// 0x011cfd30: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" int __cdecl FUN_011941f0(...);

// @ 0x011cfd30
extern "C" int __cdecl FUN_011cfd30(int a4, int a8)
{
    int t1000;
    int t1001;
    t1000 = (int)((int)(a4));
    if ((int)*(int*)((char*)(t1000) + 4) != (int)0) {
        t1001 = (int)((int)(a8));
        t1000 = (int)FUN_011941f0((unsigned int)(t1001), (unsigned int)(t1000));
    }
    return (int)(t1000);
}
