// 0x00e4cfc0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00e4c9e0/s00e4c9e0.cpp, src/game/SPGonzago/SPCellData.cpp.

// @ 0x00e4cfc0
extern "C" int __stdcall FUN_00e4cfc0(int a4, int a8)
{
    int t1000;
    int t1001;
    int t1002;
    int t1003;
    int t1004;
    t1000 = (int)((int)(a4));
    if (t1000 != (int)0) {
        t1001 = (int)((int)(a8));
        if ((unsigned int)(t1001) <= (unsigned int)0) {
            t1002 = (int)((int)0);
            return (int)(t1002);
        }
        *(int*)((char*)(t1000)) = (int)((int)1551159691);
        if ((unsigned int)(t1001) <= (unsigned int)1) {
            t1003 = (int)((int)1);
            return (int)(t1003);
        }
        *(int*)((char*)(t1000) + 4) = (int)((int)75519620);
    }
    t1004 = (int)((int)2);
    return (int)(t1004);
}
