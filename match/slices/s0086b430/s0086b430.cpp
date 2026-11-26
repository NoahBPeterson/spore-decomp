// 0x0086b430: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

// @ 0x0086b430
extern "C" int __cdecl FUN_0086b430(int a4, int a8, int a12, int a16)
{
    int t1000;
    int t1001;
    int t1002;
    int t1003;
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    if ((int)(a4) != (int)0) {
        t1000 = (int)((int)(a8));
        if (t1000 != (int)0) {
            if ((int)*(int*)((char*)(t1000) + 48) > (int)0) {
                t1001 = (int)((int)(a12));
                if (t1001 != (int)0) {
                    t1002 = (int)(*(int*)((char*)(t1000) + 56));
                    *(int*)((char*)(t1001)) = (int)(t1002);
                }
                t1003 = (int)((int)(a16));
                if (t1003 != (int)0) {
                    t1004 = (int)(*(int*)((char*)(t1000) + 48));
                    *(int*)((char*)(t1003)) = (int)(t1004);
                }
                t1005 = (int)(*(int*)((char*)(t1000) + 48));
                return (int)(t1005);
            }
        }
    }
    t1006 = (int)((int)(a16));
    if (t1006 != (int)0) {
        *(int*)((char*)(t1006)) = (int)((int)0);
    }
    t1007 = (int)((int)0);
    return (int)(t1007);
}
