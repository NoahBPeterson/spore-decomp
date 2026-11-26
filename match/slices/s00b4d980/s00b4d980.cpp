// 0x00b4d980: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/_at_00b40000.cpp, match/slices/s00b4d220/s00b4d220.cpp.

struct C_00b4d3f0 { void FUN_00b4d3f0(unsigned int); };

// @ 0x00b4d980
extern "C" int __fastcall FUN_00b4d980(char* self, int edx_unused, int a4)
{
    int t1002;
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
    int t1021;
    t1002 = (int)((int)(self));
    t1004 = (int)((int)(a4));
    t1005 = (int)(*(int*)((char*)(t1004)));
    *(int*)((char*)(t1002)) = (int)(t1005);
    t1006 = (int)(*(int*)((char*)(t1004) + 4));
    *(int*)((char*)(t1002) + 4) = (int)(t1006);
    t1007 = (int)(*(int*)((char*)(t1004) + 8));
    *(int*)((char*)(t1002) + 8) = (int)(t1007);
    t1008 = (int)(*(int*)((char*)(t1004) + 16));
    *(int*)((char*)(t1002) + 16) = (int)(t1008);
    t1009 = (int)(*(int*)((char*)(t1004) + 20));
    *(int*)((char*)(t1002) + 20) = (int)(t1009);
    t1010 = (int)(*(int*)((char*)(t1004) + 24));
    *(int*)((char*)(t1002) + 24) = (int)(t1010);
    t1011 = (int)(*(int*)((char*)(t1004) + 28));
    *(int*)((char*)(t1002) + 28) = (int)(t1011);
    *(float*)((char*)(t1002) + 32) = (float)(*(float*)((char*)(t1004) + 32));
    t1012 = (int)(*(int*)((char*)(t1004) + 36));
    *(int*)((char*)(t1002) + 36) = (int)(t1012);
    t1013 = (int)(*(int*)((char*)(t1004) + 40));
    t1014 = (int)(t1004 + (int)48);
    t1015 = (int)(t1002 + (int)48);
    *(int*)((char*)(t1002) + 40) = (int)(t1013);
    ((C_00b4d3f0*)(t1015))->FUN_00b4d3f0((unsigned int)(t1014));
    t1019 = (int)(*(int*)((char*)(t1004) + 128));
    *(int*)((char*)(t1002) + 128) = (int)(t1019);
    t1021 = (int)(t1002);
    return (int)(t1021);
}
