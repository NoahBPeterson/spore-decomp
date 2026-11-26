// 0x01201050: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s01200010/s01200010.cpp.

// @ 0x01201050
extern "C" int __cdecl FUN_01201050(int a4, int a8)
{
    int t1000;
    int t1001;
    int t1002;
    int t1004;
    int t1005;
    int t1006;
    t1000 = (int)((int)(a8));
    t1001 = (int)((int)(a4));
    t1002 = (int)(*(int*)((char*)(t1000) + 32));
    t1004 = (int)(*(int*)((char*)(t1001)));
    t1005 = (int)(t1002 - t1001);
    t1006 = (int)(t1004 + t1005);
    *(int*)((char*)(t1001)) = (int)(t1006);
    return (int)(t1000);
}
