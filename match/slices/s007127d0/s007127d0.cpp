// 0x007127d0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEngine/SPGraphicsMaterialManager.cpp, match/slices/s00711de0/s00711de0.cpp.

struct C_00712760 { void FUN_00712760(unsigned int); };

// @ 0x007127d0
extern "C" int __fastcall FUN_007127d0(char* self, int edx_unused, int a4)
{
    int t1000;
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
    int t1018;
    t1000 = (int)((int)(a4));
    t1003 = (int)((int)(self));
    t1004 = (int)(*(int*)((char*)(t1000)));
    *(int*)((char*)(t1003)) = (int)(t1004);
    t1005 = (int)(*(int*)((char*)(t1000) + 4));
    *(int*)((char*)(t1003) + 4) = (int)(t1005);
    t1006 = (int)(*(int*)((char*)(t1000) + 8));
    *(int*)((char*)(t1003) + 8) = (int)(t1006);
    t1007 = (int)(*(int*)((char*)(t1000) + 12));
    *(int*)((char*)(t1003) + 12) = (int)(t1007);
    t1008 = (int)(*(int*)((char*)(t1000) + 16));
    *(int*)((char*)(t1003) + 16) = (int)(t1008);
    t1009 = (int)(*(int*)((char*)(t1000) + 20));
    *(int*)((char*)(t1003) + 20) = (int)(t1009);
    t1010 = (int)(*(int*)((char*)(t1000) + 24));
    *(int*)((char*)(t1003) + 24) = (int)(t1010);
    t1011 = (int)(*(int*)((char*)(t1000) + 28));
    *(int*)((char*)(t1003) + 28) = (int)(t1011);
    t1012 = (int)(*(int*)((char*)(t1000) + 32));
    t1013 = (int)(t1000 + (int)36);
    *(int*)((char*)(t1003) + 32) = (int)(t1012);
    t1014 = (int)(t1003 + (int)36);
    ((C_00712760*)(t1014))->FUN_00712760((unsigned int)(t1013));
    t1018 = (int)(t1003);
    return (int)(t1018);
}
