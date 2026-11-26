// 0x008a5840: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

// @ 0x008a5840
extern "C" int __fastcall FUN_008a5840(char* self, int edx_unused, int a4, int a8)
{
    int t1001;
    int t1003;
    int t1004;
    int t1006;
    int t1007;
    unsigned char t1008;
    t1001 = (int)((int)(a8));
    t1003 = (int)((int)(a4));
    t1004 = (int)((int)0);
    t1006 = (int)((int)(self) + (int)260);
    do {
        t1007 = (int)(*(int*)((char*)(t1006)));
        if (t1007 == (int)(-1)) {
            *(unsigned char*)((char*)(t1004) + t1001) = (unsigned char)((int)3);
        } else {
            t1008 = (unsigned char)(*(unsigned char*)((char*)(t1007) + t1003));
            *(unsigned char*)((char*)(t1004) + t1001) = (unsigned char)(t1008);
        }
        t1004 = (int)(t1004 + (int)1);
        t1006 = (int)(t1006 + (int)4);
    } while (t1004 < (int)16);
    return (int)(t1004);
}
