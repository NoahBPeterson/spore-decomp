// 0x00f14090: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/_at_00f10000.cpp, match/slices/s00f13330/s00f13330.cpp.

// @ 0x00f14090
extern "C" int __cdecl FUN_00f14090(int a4, int a8, int a12)
{
    int t1000;
    int t1001;
    int t1002;
    int t1004;
    int t1005;
    t1000 = (int)((int)(a8));
    t1001 = (int)((int)(a4));
    t1002 = (int)((int)(a12));
    if (t1000 != t1001) {
        do {
            t1000 = (int)(*(int*)((char*)(t1000) + 4));
            t1004 = (int)(*(int*)((char*)(t1000) + 8));
            t1002 = (int)(t1002 - (int)8);
            *(int*)((char*)(t1002)) = (int)(t1004);
            t1005 = (int)(*(int*)((char*)(t1000) + 12));
            *(int*)((char*)(t1002) + 4) = (int)(t1005);
        } while (t1000 != t1001);
    }
    return (int)(t1002);
}
