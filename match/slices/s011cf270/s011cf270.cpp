// 0x011cf270: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

// @ 0x011cf270
extern "C" int __cdecl FUN_011cf270(int a4, int a8)
{
    int t1000;
    int t1001;
    int t1002;
    int t1003;
    int t1004;
    t1000 = (int)((unsigned char)(a8));
    t1001 = (int)((int)(a4));
    t1002 = (int)(*(int*)((char*)(t1001) + 4));
    t1003 = (int)(*(unsigned short*)((char*)(t1002) + (t1000)*2));
    t1004 = (int)(t1003 & (int)1);
    return (int)(t1004);
}
