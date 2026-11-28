// 0x0111cf00: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0111c7f0/s0111c7f0.cpp.

// @ 0x0111cf00
extern "C" int __stdcall FUN_0111cf00(int a4, int a8, int a12)
{
    int t1000;
    int t1001;
    int t1002;
    int t1005;
    int t1006;
    int t1008;
    int t1009;
    int t1010;
    int t1011;
    int t1012;
    t1000 = (int)((int)(a8));
    t1001 = (int)(*(int*)((char*)(t1000) + 52));
    t1002 = (int)((int)(a4));
    t1005 = (int)((int)(a12));
    *(int*)((char*)(t1005) + 52) = (int)(t1001);
    t1006 = (int)(*(int*)((char*)(t1000) + 52));
    t1008 = (int)(*(int*)((char*)(t1002) + 36));
    t1009 = (int)(*(int*)((char*)(t1005) + 56));
    t1010 = (int)(t1009);
    t1011 = (int)(t1010 - t1006);
    t1012 = (int)(t1011 + t1008);
    if ((unsigned int)(t1012) >= (unsigned int)32) {
        if ((unsigned int)(t1009) <= (unsigned int)2) {
            if ((unsigned int)(t1012) < (unsigned int)256) goto L111cf65;
        }
        if ((unsigned int)(t1009) < (unsigned int)32) {
            if ((unsigned int)*(int*)((char*)(t1000) + 56) >= (unsigned int)32) goto L111cf62;
        }
        if ((unsigned int)(t1009) < (unsigned int)256) {
            if ((unsigned int)*(int*)((char*)(t1000) + 56) >= (unsigned int)256) goto L111cf62;
        }
        if ((unsigned int)(t1009) >= (unsigned int)65536) goto L111cf65;
        if ((unsigned int)*(int*)((char*)(t1000) + 56) < (unsigned int)65536) goto L111cf65;
        L111cf62:;
        *(int*)((char*)(t1005) + 52) = (int)(t1008);
    }
    L111cf65:;
    return (int)(t1012);
}
