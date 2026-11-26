// 0x00ba6d80: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/_at_00ba0000.cpp, match/slices/s00ba6750/s00ba6750.cpp.

// @ 0x00ba6d80
extern "C" int __fastcall FUN_00ba6d80(char* self, int edx_unused, int a4)
{
    int t1000;
    int t1002;
    int t1003;
    int t1004;
    int t1005;
    int t1006;
    int t3;
    int t1007;
    int t1008;
    int t1009;
    int t1010;
    t1000 = (int)((int)(a4));
    if (t1000 == (int)0) {
        t1002 = (int)(*(int*)((char*)((int)(self)) + 332));
        return (int)(t1002);
    }
    if (t1000 == (int)(-1)) {
        t1003 = (int)((int)0);
        return (int)(t1003);
    }
    t1004 = (int)(*(int*)((char*)((int)(self)) + 200));
    t1005 = (int)(t1000);
    t1006 = (int)((unsigned int)(t1005) >> (int)12);
    t3 = (int)(t1006 << (int)2);
    t1007 = (int)(t1006 + t3);
    t1008 = (int)(*(int*)((char*)(t1004) + (t1007)*4));
    t1009 = (int)(t1000 & (int)4095);
    t1010 = (int)(*(int*)((char*)(t1008) + (t1009)*4));
    return (int)(t1010);
}
