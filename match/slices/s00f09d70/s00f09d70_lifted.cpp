// 0x00f09d70: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00f09d70/s00f09d70.cpp.

struct C_00dfb280 { int FUN_00dfb280(unsigned int); };

// @ 0x00f09d70
extern "C" void __cdecl FUN_00f09d70(int a4, int a8, int a12)
{
    int t1001;
    int t1003;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1012;
    t1001 = (int)((int)(a4));
    t1003 = (int)((int)(a8));
    if ((unsigned int)(t1003) > (unsigned int)0) {
        t1005 = (int)((int)(a12));
        do {
            if (t1001 != (int)0) {
                t1006 = (int)(*(int*)((char*)(t1005)));
                t1007 = (int)(t1005 + (int)4);
                t1008 = (int)(t1001 + (int)4);
                *(int*)((char*)(t1001)) = (int)(t1006);
                ((C_00dfb280*)(t1008))->FUN_00dfb280((unsigned int)(t1007));
                t1012 = (int)(*(int*)((char*)(t1005) + 64));
                *(int*)((char*)(t1001) + 64) = (int)(t1012);
            }
            t1003 = (int)(t1003 - (int)1);
            t1001 = (int)(t1001 + (int)68);
        } while ((unsigned int)(t1003) > (unsigned int)0);
    }
    return;
}
