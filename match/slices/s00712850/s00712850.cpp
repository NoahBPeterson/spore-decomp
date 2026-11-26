// 0x00712850: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEngine/SPGraphicsMaterialManager.cpp, match/slices/s00711de0/s00711de0.cpp.

struct C_00712760 { void FUN_00712760(unsigned int); };

// @ 0x00712850
extern "C" int __fastcall FUN_00712850(char* self, int edx_unused, int a4, int a8)
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
    int t1015;
    int t1019;
    t1000 = (int)((int)(a4));
    t1003 = (int)((int)(self));
    t1004 = (int)(*(int*)((char*)(t1000)));
    t1005 = (int)((int)(a8));
    *(int*)((char*)(t1003)) = (int)(t1004);
    t1006 = (int)(*(int*)((char*)(t1005)));
    *(int*)((char*)(t1003) + 4) = (int)(t1006);
    t1007 = (int)(*(int*)((char*)(t1005) + 4));
    *(int*)((char*)(t1003) + 8) = (int)(t1007);
    t1008 = (int)(*(int*)((char*)(t1005) + 8));
    *(int*)((char*)(t1003) + 12) = (int)(t1008);
    t1009 = (int)(*(int*)((char*)(t1005) + 12));
    *(int*)((char*)(t1003) + 16) = (int)(t1009);
    t1010 = (int)(*(int*)((char*)(t1005) + 16));
    *(int*)((char*)(t1003) + 20) = (int)(t1010);
    t1011 = (int)(*(int*)((char*)(t1005) + 20));
    *(int*)((char*)(t1003) + 24) = (int)(t1011);
    t1012 = (int)(*(int*)((char*)(t1005) + 24));
    *(int*)((char*)(t1003) + 28) = (int)(t1012);
    t1013 = (int)(*(int*)((char*)(t1005) + 28));
    t1014 = (int)(t1005 + (int)32);
    *(int*)((char*)(t1003) + 32) = (int)(t1013);
    t1015 = (int)(t1003 + (int)36);
    ((C_00712760*)(t1015))->FUN_00712760((unsigned int)(t1014));
    t1019 = (int)(t1003);
    return (int)(t1019);
}
