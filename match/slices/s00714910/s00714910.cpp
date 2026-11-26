// 0x00714910: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00713e40/s00713e40.cpp, src/game/SPEngine/_at_00710000.cpp.

// @ 0x00714910
extern "C" int __cdecl FUN_00714910(int a4, int a8, int a12)
{
    int t1000;
    int t1001;
    int t1002;
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    t1000 = (int)((int)(a8));
    t1001 = (int)((int)(a4));
    if ((unsigned int)(t1000) > (unsigned int)0) {
        t1002 = (int)((int)(a12));
        do {
            if (t1001 != (int)0) {
                t1004 = (int)(*(int*)((char*)(t1002)));
                *(int*)((char*)(t1001)) = (int)(t1004);
                t1005 = (int)(*(int*)((char*)(t1002) + 4));
                *(int*)((char*)(t1001) + 4) = (int)(t1005);
                t1006 = (int)(*(int*)((char*)(t1002) + 8));
                *(int*)((char*)(t1001) + 8) = (int)(t1006);
                t1007 = (int)(*(int*)((char*)(t1002) + 12));
                *(int*)((char*)(t1001) + 12) = (int)(t1007);
                t1008 = (int)(*(int*)((char*)(t1002) + 16));
                *(int*)((char*)(t1001) + 16) = (int)(t1008);
                t1009 = (int)(*(int*)((char*)(t1002) + 20));
                *(int*)((char*)(t1001) + 20) = (int)(t1009);
            }
            t1000 = (int)(t1000 - (int)1);
            t1001 = (int)(t1001 + (int)24);
        } while ((unsigned int)(t1000) > (unsigned int)0);
    }
    return (int)(t1001);
}
