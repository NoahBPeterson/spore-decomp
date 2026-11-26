// 0x011c84c0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" int __cdecl FUN_0117a970(...);
extern "C" int __cdecl FUN_011835c0(...);

// @ 0x011c84c0
extern "C" void __cdecl FUN_011c84c0(int a4)
{
    int t1001;
    int t1006;
    unsigned char t4;
    t1001 = (int)((int)(a4));
    if (t1001 != (int)0) {
        FUN_0117a970((unsigned int)(t1001));
        t1006 = (int)(t1001 + (int)20);
        FUN_0117a970((unsigned int)(t1006));
        t4 = (unsigned char)((unsigned char)*(unsigned char*)((char*)(t1001) + 48) & (unsigned char)1);
        if (t4 != (unsigned char)0) {
            FUN_011835c0((unsigned int)(t1001));
        }
    }
    return;
}
