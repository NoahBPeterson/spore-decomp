// 0x011900b0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" int __cdecl FUN_0117df20(...);

// @ 0x011900b0
extern "C" int __cdecl FUN_011900b0(int a4, int a8)
{
    int t1000;
    int t1002;
    int t1006;
    int t1008;
    t1000 = (int)((int)(a8));
    t1002 = (int)(*(int*)((char*)(t1000)));
    if ((int)(a4) == (int)1) {
        t1006 = (int)FUN_0117df20();
        *(int*)((char*)(t1002) + 24) = (int)(t1006);
        if (t1006 == (int)0) {
            return 0;
        }
    }
    t1008 = (int)((int)1);
    return (int)(t1008);
}
