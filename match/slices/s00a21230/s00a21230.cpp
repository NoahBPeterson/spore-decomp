// 0x00a21230: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00a21130/s00a21130.cpp.

// @ 0x00a21230
extern "C" int __stdcall FUN_00a21230(int a4)
{
    int t1000;
    int t1001;
    int t1002;
    t1000 = (int)((int)(a4));
    if ((int)*(int*)((char*)(t1000) + 8) == (int)34867182) {
        if ((int)*(int*)((char*)(t1000) + 4) == (int)45741666) {
            t1001 = (int)((int)1);
            return (int)(t1001);
        }
    }
    t1002 = (int)((int)0);
    return (int)(t1002);
}
