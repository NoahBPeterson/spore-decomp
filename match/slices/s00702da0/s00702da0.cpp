// 0x00702da0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00702980/s00702980.cpp, src/game/SPEngine/SPGraphicsHierGrid.cpp.

struct C_00700ff0 { int FUN_00700ff0(unsigned int); };
struct C_00702af0 { int FUN_00702af0(unsigned int); };

// @ 0x00702da0
extern "C" void __fastcall FUN_00702da0(char* self, int edx_unused, int a4)
{
    int t1003;
    int t1004;
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
    int t1017;
    int t1018;
    int t1019;
    int t1020;
    int t1023;
    int t1024;
    t1003 = (int)((int)(self));
    t1004 = (int)(*(int*)((char*)(t1003) + 96));
    t1006 = (int)((int)(a4));
    t1007 = (int)(t1003 + (int)96);
    t1008 = (int)(t1006);
    t1009 = (int)(t1008 & (int)127);
    t1010 = (int)(t1006);
    t1011 = (int)((unsigned int)(t1010) >> (int)7);
    t1012 = (int)(t1009 << (int)4);
    t1013 = (int)(t1012 + (int)*(int*)((char*)(t1004) + (t1011)*4));
    t1014 = (int)(*(int*)((char*)(t1007) + 28));
    t1015 = (int)(*(int*)((char*)(t1013)));
    t1016 = (int)(t1014 & (int)1073741823);
    t1017 = (int)(t1015 & (int)(-1073741824));
    t1018 = (int)(t1016 | t1017);
    t1019 = (int)(t1018 | (int)(-2147483648));
    *(int*)((char*)(t1013)) = (int)(t1019);
    *(int*)((char*)(t1007) + 28) = (int)(t1006);
    if ((int)*(int*)((char*)(t1007) + 24) == t1006) {
        t1020 = (int)(t1007);
        t1023 = (int)((C_00700ff0*)(t1020))->FUN_00700ff0((unsigned int)(t1006));
        *(int*)((char*)(t1007) + 24) = (int)(t1023);
    }
    *(int*)((char*)(t1003) + 32) -= (int)1;
    t1024 = (int)(t1003);
    ((C_00702af0*)(t1024))->FUN_00702af0((unsigned int)(t1006));
    return;
}
