// 0x010dc150: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" int __cdecl FUN_010dbd30(...);

// @ 0x010dc150
extern "C" void __stdcall FUN_010dc150(int a4, int a8, int a12, int a16, int a20)
{
    int t1000;
    int t1001;
    int t1002;
    int t1003;
    int t1004;
    t1000 = (int)((int)(a20));
    t1001 = (int)((int)(a16));
    t1002 = (int)((int)(a12));
    t1003 = (int)((int)(a8));
    t1004 = (int)((int)(a4));
    FUN_010dbd30((unsigned int)(t1004), (unsigned int)(t1003), (unsigned int)(t1002), (unsigned int)(t1001), (unsigned int)(t1000));
    return;
}
