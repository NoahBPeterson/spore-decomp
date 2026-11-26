// 0x00876b00: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

// @ 0x00876b00
extern "C" void __cdecl FUN_00876b00(int a4, int a8, int a12)
{
    int t1000;
    int t1001;
    int t1002;
    int t3;
    int t1003;
    int t1005;
    int t1006;
    t1000 = (int)((int)(a4));
    if (t1000 != (int)0) {
        t1001 = (int)((int)(a8));
        if (t1001 != (int)0) {
            t1002 = (int)((int)512);
            t3 = (int)((int)*(int*)((char*)(t1000) + 104) & t1002);
            if (t3 == (int)0) {
                t1003 = (int)((int)(a12));
                t1005 = (int)(*(int*)((char*)(t1003)));
                *(int*)((char*)(t1001) + 60) = (int)(t1005);
                t1006 = (int)(*(int*)((char*)(t1003) + 4));
                *(int*)((char*)(t1001) + 8) |= t1002;
                *(int*)((char*)(t1001) + 64) = (int)(t1006);
            }
        }
    }
    return;
}
