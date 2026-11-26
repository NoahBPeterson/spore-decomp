// 0x00876eb0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

// @ 0x00876eb0
extern "C" int __cdecl FUN_00876eb0(int a4)
{
    int t1000;
    int t1001;
    int t1002;
    t1000 = (int)((int)(a4));
    if (t1000 != (int)0) {
        if ((unsigned char)*(unsigned char*)((char*)(t1000) + 291) != (unsigned char)0) {
            *(int*)((char*)(t1000) + 112) |= (int)2;
            t1001 = (int)((int)7);
            return (int)(t1001);
        }
    }
    t1002 = (int)((int)1);
    return (int)(t1002);
}
