// 0x0086ae50: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" int __cdecl FUN_0086aaa0(...);
extern "C" int __cdecl FUN_0086d850(...);
extern "C" int __cdecl FUN_011e073e(...);

// @ 0x0086ae50
extern "C" void __cdecl FUN_0086ae50(int a4, int a8)
{
    int t1001;
    int t1003;
    int t1008;
    t1001 = (int)((int)(a4));
    t1003 = (int)((int)(a8));
    FUN_0086aaa0((unsigned int)(t1001), (unsigned int)(t1003), (unsigned int)((int)32767), (unsigned int)((int)(-1)));
    if ((int)*(int*)((char*)(t1001) + 544) != (int)0) {
        t1008 = (int)(*(int*)((char*)(t1001) + 548));
        FUN_0086d850((unsigned int)(t1001), (unsigned int)(t1008));
        *(int*)((char*)(t1001) + 548) = (int)((int)0);
        *(int*)((char*)(t1001) + 544) = (int)((int)0);
    }
    if (t1003 != (int)0) {
        FUN_011e073e((unsigned int)(t1003), (unsigned int)((int)0), (unsigned int)((int)288));
    }
    return;
}
