// 0x00898580: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

// @ 0x00898580
extern "C" int __cdecl FUN_00898580(int a4, int a8, int a12)
{
    int t1000;
    int t1001;
    int t1002;
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    t1000 = (int)((int)(a4));
    t1001 = (int)((int)(a8));
    if (t1000 != t1001) {
        t1002 = (int)((int)(a12));
        do {
            t1004 = (int)(*(int*)((char*)(t1002)));
            *(int*)((char*)(t1000)) = (int)(t1004);
            t1005 = (int)(*(int*)((char*)(t1002) + 4));
            *(int*)((char*)(t1000) + 4) = (int)(t1005);
            t1006 = (int)(*(int*)((char*)(t1002) + 8));
            *(int*)((char*)(t1000) + 8) = (int)(t1006);
            t1007 = (int)(*(int*)((char*)(t1002) + 12));
            *(int*)((char*)(t1000) + 12) = (int)(t1007);
            t1000 = (int)(t1000 + (int)16);
        } while (t1000 != t1001);
    }
    return (int)(t1000);
}
