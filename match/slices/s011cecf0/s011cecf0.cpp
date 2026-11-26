// 0x011cecf0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" unsigned char g_0149c9a0[];
extern "C" unsigned char g_015cf7c0[];

// @ 0x011cecf0
extern "C" int __cdecl FUN_011cecf0(int a4)
{
    int t1000;
    int t1001;
    int t1002;
    t1000 = (int)((int)(a4));
    if (t1000 != (int)258) {
        if (t1000 != (int)266) goto L11ced07;
    }
    t1000 = (int)(t1000 & (int)(-257));
    L11ced07:;
    if ((unsigned int)(t1000) <= (unsigned int)30) {
        t1001 = (int)(*(int*)((char*)((t1000)*4) + (int)g_015cf7c0));
        return (int)(t1001);
    }
    t1002 = (int)((int)g_0149c9a0);
    return (int)(t1002);
}
