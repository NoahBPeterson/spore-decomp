// 0x00f43830: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00f42a50/s00f42a50.cpp.

extern "C" int __stdcall FUN_00f3be60(unsigned int);
struct C_00f43740 { int FUN_00f43740(unsigned int); };

// @ 0x00f43830
extern "C" int __stdcall FUN_00f43830(int a4, int a8)
{
    int t1000;
    int t1004;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1016;
    int t1017;
    t1000 = (int)((int)(a4));
    t1004 = (int)FUN_00f3be60((unsigned int)(t1000));
    if (t1004 != (int)0) {
        t1006 = (int)((int)(a8));
        if (t1006 >= (int)0) {
            t1007 = (int)(*(int*)((char*)(t1004) + 136));
            t1008 = (int)(t1007 - (int)*(int*)((char*)(t1004) + 132));
            t1009 = (int)(t1004 + (int)132);
            t1004 = (int)(t1008 / (int)392);
            if (t1006 < t1004) {
                t1016 = (int)(t1006 * (int)392);
                t1017 = (int)(t1016 + (int)*(int*)((char*)(t1009)));
                t1004 = (int)((C_00f43740*)(t1009))->FUN_00f43740((unsigned int)(t1017));
            }
        }
    }
    return (int)(t1004);
}
