// 0x0086aa50: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" int __cdecl FUN_00866e60(...);

// @ 0x0086aa50
extern "C" void __cdecl FUN_0086aa50(int a4, int a8, int a12)
{
    int t1001;
    unsigned char t1;
    int t1002;
    int t1003;
    int t4;
    int t1005;
    int t1006;
    int t1007;
    int t1010;
    t1001 = (int)((int)(a4));
    t1 = (unsigned char)((unsigned char)*(unsigned char*)((char*)(t1001) + 284) & (unsigned char)32);
    if (t1 != (unsigned char)0) {
        t1002 = (int)(*(int*)((char*)(t1001) + 108));
        t1003 = (int)(t1002 & (int)768);
        if (t1003 != (int)768) goto L86aa78;
        return;
    }
    t4 = (int)((int)*(int*)((char*)(t1001) + 108) & (int)2048);
    if (t4 != (int)0) goto L86aa97;
    L86aa78:;
    t1005 = (int)((int)(a12));
    t1006 = (int)((int)(a8));
    t1007 = (int)(*(int*)((char*)(t1001) + 272));
    t1010 = (int)FUN_00866e60((unsigned int)(t1007), (unsigned int)(t1006), (unsigned int)(t1005));
    *(int*)((char*)(t1001) + 272) = (int)(t1010);
    L86aa97:;
    return;
}
