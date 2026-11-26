// 0x011cf2a0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" void __cdecl FUN_011835c0(...);
extern "C" void __cdecl FUN_011cfda0(...);

// @ 0x011cf2a0
extern "C" int __cdecl FUN_011cf2a0(int a4)
{
    int t1001;
    int t1009;
    int t1011;
    t1001 = (int)((int)(a4));
    if (t1001 != (int)0) {
        FUN_011cfda0((unsigned int)(t1001));
        FUN_011835c0((unsigned int)(t1001));
        t1009 = (int)((int)1);
        return (int)(t1009);
    }
    t1011 = (int)((int)0);
    return (int)(t1011);
}
