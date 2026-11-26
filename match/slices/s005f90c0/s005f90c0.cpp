// 0x005f90c0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s005f8fe0/s005f8fe0.cpp.

struct C_005f8700 { void FUN_005f8700(unsigned int, unsigned int); };
extern "C" void __cdecl FUN_00f47380(...);

// @ 0x005f90c0
extern "C" int __cdecl FUN_005f90c0(int a4, int a8, int a12, int a16, int a20, int a24, int a28)
{
    int t1001;
    int t1002;
    int t1003;
    int t1004;
    int t1008;
    int t1009;
    int t1010;
    int t1011;
    int t1015;
    t1001 = (int)((int)(a4));
    t1002 = (int)((int)&a20);
    t1003 = (int)((int)&a8);
    t1004 = (int)(t1001);
    ((C_005f8700*)(t1004))->FUN_005f8700((unsigned int)(t1003), (unsigned int)(t1002));
    t1008 = (int)((int)(a28));
    t1009 = (int)((int)(a20));
    t1010 = (int)(t1008 - t1009);
    t1011 = (int)(t1010 & (int)(-2));
    if (t1011 > (int)2) {
        if (t1009 != (int)0) {
            FUN_00f47380((unsigned int)(t1009));
        }
    }
    t1015 = (int)(t1001);
    return (int)(t1015);
}
