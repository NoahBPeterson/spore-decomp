// 0x0090c6b0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" unsigned char g_0090c5b0[];
extern "C" unsigned char g_00e31100[];

// @ 0x0090c6b0
extern "C" int __cdecl FUN_0090c6b0(int a4, int a8)
{
    int t1000;
    int t1001;
    int t1002;
    int t1003;
    int t1004;
    int t1005;
    int t1006;
    t1000 = (int)((int)(a8));
    if (t1000 != (int)15) {
        if (t1000 != (int)18) {
            if (t1000 != (int)41) {
                t1001 = (int)((int)(a4));
                if ((int)*(int*)((char*)(t1001) + 16) == (int)0) {
                    if (t1000 == (int)28) {
                        t1002 = (int)((int)59);
                        return (int)(t1002);
                    }
                }
                *(int*)((char*)(t1001)) = (int)((int)g_00e31100);
                t1003 = (int)(t1000 | (int)(-1));
                return (int)(t1003);
            }
        }
        t1004 = (int)((int)(a4));
        *(int*)((char*)(t1004)) = (int)((int)g_0090c5b0);
        t1005 = (int)((int)4);
        return (int)(t1005);
    }
    t1006 = (int)((int)3);
    return (int)(t1006);
}
