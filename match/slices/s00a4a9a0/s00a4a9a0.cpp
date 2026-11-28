// 0x00a4a9a0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00a4a500/s00a4a500.cpp.

extern "C" unsigned char g_014544c0[];
extern "C" unsigned char g_014544d8[];
extern "C" int __cdecl FUN_00a4d410(...);
extern "C" int __cdecl FUN_00c2e4e0(...);

// @ 0x00a4a9a0
extern "C" void __cdecl FUN_00a4a9a0(int a4, int a8)
{
    int t1000;
    int t1001;
    int t1002;
    int t1004;
    int t1006;
    int t1007;
    int t1008;
    int t1018;
    t1000 = (int)((int)(a4));
    if ((int)(a8) != (int)0) {
        t1001 = (int)(*(int*)((char*)(t1000) + 92));
        t1002 = (int)(*(int*)((char*)(t1000) + 88));
        t1004 = (int)(*(int*)((char*)(t1000) + 52));
        t1006 = (int)(*(int*)((char*)(t1000) + 48));
        t1007 = (int)(t1004 + t1001);
        t1008 = (int)(t1006 + t1002);
        FUN_00c2e4e0((unsigned int)((int)g_014544d8), (unsigned int)((int)FUN_00a4d410((unsigned int)(t1000))), (unsigned int)(t1002), (unsigned int)(t1001), (unsigned int)(t1008), (unsigned int)(t1001), (unsigned int)(t1008), (unsigned int)(t1007), (unsigned int)(t1002), (unsigned int)(t1007), (unsigned int)(t1002), (unsigned int)(t1001));
        return;
    }
    t1018 = (int)FUN_00a4d410((unsigned int)(t1000));
    *(int*)&(a8) = (int)(t1018);
    *(int*)&(a4) = (int)((int)g_014544c0);
    FUN_00c2e4e0((unsigned int)((int)(a4)), (unsigned int)((int)(a8)));
    return;
}
