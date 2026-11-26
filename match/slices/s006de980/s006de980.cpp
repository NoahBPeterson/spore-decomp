// 0x006de980: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEngine/SPGraphicsChartPacker.cpp, match/slices/s006de020/s006de020.cpp.

extern "C" int __cdecl FUN_006de4e0(...);

// @ 0x006de980
extern "C" void __cdecl FUN_006de980(int a4, int a8, int a12, int a16, int a20, int a24)
{
    int t1000;
    int t1001;
    int t1003;
    int t1;
    int t1004;
    int t1007;
    int t1008;
    int t1009;
    int t1010;
    int t4;
    int t1013;
    int t1014;
    int t1015;
    int t1016;
    t1000 = (int)((int)(a16));
    t1001 = (int)((int)(a4));
    t1003 = (int)((int)(a12));
    t1 = (int)(t1000 + t1000);
    t1004 = (int)(t1 + (int)2);
    if (t1004 < t1003) {
        goto L6de9a0;
        L6de9a0:;
        t1007 = (int)(*(int*)((char*)(t1001) + (t1004)*4));
        t1008 = (int)(*(int*)((char*)(t1001) + (t1004)*4 - 4));
        t1009 = (int)(*(int*)((char*)(t1007) + 4));
        if ((unsigned int)(t1009) > (unsigned int)*(int*)((char*)(t1008) + 4)) {
            t1004 = (int)(t1004 - (int)1);
        }
        t1010 = (int)(*(int*)((char*)(t1001) + (t1004)*4));
        *(int*)((char*)(t1001) + (t1000)*4) = (int)(t1010);
        t1000 = (int)(t1004);
        t4 = (int)(t1004 + t1004);
        t1004 = (int)(t4 + (int)2);
        if (t1004 < t1003) goto L6de9a0;
    }
    if (t1004 == t1003) {
        t1013 = (int)(*(int*)((char*)(t1001) + (t1004)*4 - 4));
        *(int*)((char*)(t1001) + (t1000)*4) = (int)(t1013);
        t1000 = (int)(t1004 + (int)(-1));
    }
    t1014 = (int)((int)(a24));
    t1015 = (int)((int)(a20));
    t1016 = (int)((int)(a8));
    FUN_006de4e0((unsigned int)(t1001), (unsigned int)(t1016), (unsigned int)(t1000), (unsigned int)(t1015), (unsigned int)(t1014));
    return;
}
