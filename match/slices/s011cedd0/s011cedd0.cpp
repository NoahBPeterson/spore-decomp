// 0x011cedd0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" void __cdecl FUN_011cfda0(...);

// @ 0x011cedd0
extern "C" int __cdecl FUN_011cedd0(int a4)
{
    int t1000;
    int t1005;
    t1000 = (int)((int)(a4));
    if (t1000 == (int)0) {
        return (int)(t1000);
    }
    FUN_011cfda0((unsigned int)(t1000));
    t1005 = (int)((int)1);
    return (int)(t1005);
}
