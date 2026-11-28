// 0x01137150: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s011369e0/s011369e0.cpp.

// @ 0x01137150
extern "C" int __cdecl FUN_01137150(int a4)
{
    int t1000;
    int t1001;
    int t1;
    int t1002;
    int t1003;
    int t2;
    int t1004;
    t1000 = (int)((int)(a4));
    t1001 = (int)(*(unsigned char*)((char*)(t1000) + 8));
    t1 = (int)(t1001 << (int)3);
    t1002 = (int)(t1);
    t1003 = (int)(t1002 - t1001);
    t2 = (int)(t1003 << (int)2);
    t1004 = (int)(t2 + (int)128);
    return (int)(t1004);
}
