// 0x011c8bc0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

// @ 0x011c8bc0
extern "C" int __cdecl FUN_011c8bc0(int a4)
{
    int t1000;
    int t1001;
    t1000 = (int)((int)(a4));
    if (t1000 == (int)0) {
        return (int)(t1000);
    }
    t1001 = (int)(*(int*)((char*)(t1000) + 8));
    return (int)(t1001);
}
