// 0x00c14e70: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPCreatureBase.cpp, match/slices/s00c14350/s00c14350.cpp.

struct C_00645ed0 { int FUN_00645ed0(unsigned int, unsigned int); };

// @ 0x00c14e70
extern "C" int __fastcall FUN_00c14e70(char* self, int edx_unused, int a4)
{
    int t1003;
    int t1004;
    int t1005;
    int v_l8[2];
    int t1006;
    int t1007;
    int t1011;
    int t1012;
    int t1013;
    int t1014;
    int t1017;
    int t1018;
    int t1019;
    int t1020;
    int t1021;
    int t1024;
    int t1025;
    int t1026;
    int t1027;
    int t1028;
    int t1032;
    t1003 = (int)((int)(self));
    t1004 = (int)((int)&a4);
    t1005 = (int)((int)&v_l8);
    t1006 = (int)(t1003 + (int)3272);
    t1007 = (int)(t1006);
    ((C_00645ed0*)(t1007))->FUN_00645ed0((unsigned int)(t1005), (unsigned int)(t1004));
    t1011 = (int)(*(int*)((char*)(t1006) + 8));
    t1012 = (int)(*(int*)((char*)(t1006) + 4));
    t1013 = (int)((*(int*)&v_l8[0]));
    if (t1013 != (int)*(int*)((char*)(t1012) + (t1011)*4)) {
        t1014 = (int)(*(int*)((char*)(t1013) + 4));
        return (int)(t1014);
    }
    t1017 = (int)((int)&a4);
    t1018 = (int)((int)&v_l8);
    t1019 = (int)(t1003 + (int)3432);
    t1020 = (int)(t1019);
    t1021 = (int)((C_00645ed0*)(t1020))->FUN_00645ed0((unsigned int)(t1018), (unsigned int)(t1017));
    t1024 = (int)(*(int*)((char*)(t1021) + 4));
    t1025 = (int)(*(int*)((char*)(t1021)));
    t1026 = (int)(*(int*)((char*)(t1019) + 8));
    (*(int*)&v_l8[1]) = (int)(t1024);
    t1027 = (int)(*(int*)((char*)(t1019) + 4));
    if (t1025 != (int)*(int*)((char*)(t1027) + (t1026)*4)) {
        t1028 = (int)(*(int*)((char*)(t1025) + 4));
        return (int)(t1028);
    }
    t1032 = (int)((int)0);
    return (int)(t1032);
}
