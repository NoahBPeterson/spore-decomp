// 0x0095f090: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/UTFSpore_Win32/Types.cpp, match/slices/s0095eeb0/s0095eeb0.cpp.

// @ 0x0095f090
extern "C" int __fastcall FUN_0095f090(char* self, int edx_unused, int a4, int a8, int a12)
{
    int t1001;
    int t1002;
    int t1003;
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1010;
    int t1011;
    int t1012;
    int t1013;
    int t1014;
    int t1015;
    int t1016;
    t1001 = (int)((int)(self));
    t1002 = (int)((int)(a4));
    t1003 = (int)(*(int*)((char*)(t1002)));
    *(int*)((char*)(t1001)) = (int)(t1003);
    t1004 = (int)(*(int*)((char*)(t1002) + 4));
    *(int*)((char*)(t1001) + 4) = (int)(t1004);
    t1005 = (int)(*(int*)((char*)(t1002) + 8));
    *(int*)((char*)(t1001) + 8) = (int)(t1005);
    t1006 = (int)(*(int*)((char*)(t1002) + 12));
    *(int*)((char*)(t1001) + 12) = (int)(t1006);
    t1007 = (int)((int)(a8));
    t1008 = (int)(*(int*)((char*)(t1007)));
    *(int*)((char*)(t1001) + 16) = (int)(t1008);
    t1009 = (int)(*(int*)((char*)(t1007) + 4));
    *(int*)((char*)(t1001) + 20) = (int)(t1009);
    t1010 = (int)(*(int*)((char*)(t1007) + 8));
    *(int*)((char*)(t1001) + 24) = (int)(t1010);
    t1011 = (int)(*(int*)((char*)(t1007) + 12));
    *(int*)((char*)(t1001) + 28) = (int)(t1011);
    t1012 = (int)((int)(a12));
    t1013 = (int)(*(int*)((char*)(t1012)));
    *(int*)((char*)(t1001) + 32) = (int)(t1013);
    t1014 = (int)(*(int*)((char*)(t1012) + 4));
    *(int*)((char*)(t1001) + 36) = (int)(t1014);
    t1015 = (int)(*(int*)((char*)(t1012) + 8));
    *(int*)((char*)(t1001) + 40) = (int)(t1015);
    t1016 = (int)(*(int*)((char*)(t1012) + 12));
    *(int*)((char*)(t1001) + 44) = (int)(t1016);
    return (int)(t1001);
}
