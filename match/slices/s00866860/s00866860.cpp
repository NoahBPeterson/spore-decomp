// 0x00866860: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

// @ 0x00866860
extern "C" int __cdecl FUN_00866860(int a4, int a8)
{
    int t1000;
    int t1002;
    int t1;
    int t1003;
    int t1004;
    int t1006;
    int t1008;
    int t1010;
    t1000 = (int)((int)(a4));
    t1002 = (int)((int)(a8));
    t1 = (int)(t1000 + t1002);
    t1003 = (int)(t1 + (int)(-1));
    t1004 = (int)(t1003);
    t1006 = (int)(t1004 % t1002);
    t1008 = (int)(t1003);
    t1010 = (int)(t1008 - t1006);
    return (int)(t1010);
}
