// 0x009587d0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/UTFSpore_Win32/manager2.cpp, match/slices/s009579f0/s009579f0.cpp.

// @ 0x009587d0
extern "C" int __fastcall FUN_009587d0(char* self, int edx_unused, int a4)
{
    int t1001;
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1011;
    int t1012;
    int t1013;
    t1001 = (int)(*(int*)((char*)((int)(self)) + 32));
    t1004 = (int)((int)(a4));
    t1005 = (int)(t1004 + (int)24);
    if (t1001 == t1005) {
        *(unsigned char*)((char*)((int)(self)) + 36) = (unsigned char)((int)1);
        t1006 = (int)(*(int*)((char*)(t1001) + 4));
        t1007 = (int)(*(int*)((char*)(t1001)));
        *(int*)((char*)(t1006)) = (int)(t1007);
        *(int*)((char*)(t1007) + 4) = (int)(t1006);
        t1008 = (int)((int)0);
        *(int*)((char*)(t1001)) = (int)(t1008);
        *(int*)((char*)(t1001) + 4) = (int)(t1008);
        *(int*)((char*)((int)(self)) + 32) = (int)(t1007);
        *(int*)((char*)(t1004) + 28) = (int)(t1008);
        return (int)(t1001);
    }
    t1011 = (int)(*(int*)((char*)(t1005) + 4));
    t1012 = (int)(*(int*)((char*)(t1005)));
    *(int*)((char*)(t1011)) = (int)(t1012);
    t1013 = (int)((int)0);
    *(int*)((char*)(t1012) + 4) = (int)(t1011);
    *(int*)((char*)(t1005)) = (int)(t1013);
    *(int*)((char*)(t1005) + 4) = (int)(t1013);
    *(int*)((char*)(t1004) + 28) = (int)(t1013);
    return (int)(t1011);
}
