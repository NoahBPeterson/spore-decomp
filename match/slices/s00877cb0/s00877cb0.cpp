// 0x00877cb0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" void __cdecl FUN_0086aa50(...);
extern "C" int __cdecl FUN_00877330(...);

// @ 0x00877cb0
extern "C" void __cdecl FUN_00877cb0(int a4, int a8, int a12)
{
    int t1001;
    int t1003;
    int t1005;
    t1001 = (int)((int)(a4));
    if (t1001 != (int)0) {
        t1003 = (int)((int)(a8));
        if (t1003 != (int)0) {
            t1005 = (int)((int)(a12));
            if ((unsigned int)(t1005) > (unsigned int)0) {
                FUN_0086aa50((unsigned int)(t1001), (unsigned int)(t1003), (unsigned int)(t1005));
                FUN_00877330((unsigned int)(t1001), (unsigned int)(t1003), (unsigned int)(t1005));
            }
        }
    }
    return;
}
