// 0x0086b400: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

// @ 0x0086b400
extern "C" int __cdecl FUN_0086b400(int a4, int a8)
{
    int t1000;
    unsigned char t3;
    int t1001;
    int t1002;
    if ((int)(a4) != (int)0) {
        t1000 = (int)((int)(a8));
        if (t1000 != (int)0) {
            t3 = (unsigned char)((unsigned char)*(unsigned char*)((char*)(t1000) + 8) & (unsigned char)128);
            if (t3 != (unsigned char)0) {
                if ((unsigned char)*(unsigned char*)((char*)(t1000) + 120) == (unsigned char)1) {
                    t1001 = (int)(*(int*)((char*)(t1000) + 112));
                    return (int)(t1001);
                }
            }
        }
    }
    t1002 = (int)((int)0);
    return (int)(t1002);
}
