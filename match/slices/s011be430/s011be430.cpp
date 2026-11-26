// 0x011be430: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" void __cdecl FUN_011c6c40(...);

// @ 0x011be430
extern "C" int __cdecl FUN_011be430(int a4, int a8)
{
    int t1001;
    int t1003;
    int t1004;
    int t1009;
    int t1010;
    int t1011;
    int t1012;
    int t1013;
    int t1014;
    int t1016;
    t1001 = (int)((int)(a8));
    t1003 = (int)((int)(a4));
    t1004 = (int)(*(int*)((char*)(t1003) + 96));
    FUN_011c6c40((unsigned int)(t1001), (unsigned int)(t1004));
    t1009 = (int)(*(int*)((char*)(t1003) + 96));
    t1010 = (int)(*(int*)((char*)(t1001) + 8));
    *(int*)((char*)(t1009) + 128) = (int)(t1010);
    t1011 = (int)(*(int*)((char*)(t1001) + 12));
    *(int*)((char*)(t1009) + 132) = (int)(t1011);
    t1012 = (int)(*(int*)((char*)(t1001) + 16));
    t1013 = (int)(*(int*)((char*)(t1003) + 96));
    *(int*)((char*)(t1013) + 136) = (int)(t1012);
    t1014 = (int)(*(int*)((char*)(t1001) + 20));
    *(int*)((char*)(t1013) + 140) = (int)(t1014);
    t1016 = (int)((int)1);
    return (int)(t1016);
}
