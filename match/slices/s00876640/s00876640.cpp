// 0x00876640: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

// @ 0x00876640
extern "C" void __cdecl FUN_00876640(int a4, int a8, int a12, int a16, int a20)
{
    int t1000;
    int t1001;
    int t1002;
    unsigned char t1003;
    if ((int)(a4) != (int)0) {
        t1000 = (int)((int)(a8));
        if (t1000 != (int)0) {
            t1001 = (int)((int)(a12));
            t1002 = (int)((int)(a16));
            *(int*)((char*)(t1000) + 8) |= (int)128;
            *(int*)((char*)(t1000) + 112) = (int)(t1001);
            t1003 = (unsigned char)((unsigned char)(a20));
            *(int*)((char*)(t1000) + 116) = (int)(t1002);
            *(unsigned char*)((char*)(t1000) + 120) = (unsigned char)(t1003);
        }
    }
    return;
}
