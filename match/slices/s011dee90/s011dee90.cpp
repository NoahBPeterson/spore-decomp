// 0x011dee90: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

// @ 0x011dee90
extern "C" int __cdecl FUN_011dee90(int a4)
{
    int t1000;
    unsigned char t2;
    int t1001;
    int t1002;
    t1000 = (int)((int)(a4));
    if (t1000 == (int)0) {
        return (int)(t1000);
    }
    t2 = (unsigned char)((unsigned char)*(unsigned char*)((char*)(t1000) + 20) & (unsigned char)2);
    if (t2 != (unsigned char)0) {
        t1001 = (int)(*(int*)((char*)(t1000) + 12));
        return (int)(t1001);
    }
    t1002 = (int)(*(int*)((char*)(t1000) + 16));
    return (int)(t1002);
}
