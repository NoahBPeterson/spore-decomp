// 0x012009c0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s01200010/s01200010.cpp.

struct C_011e2300 { int FUN_011e2300(unsigned int); };

// @ 0x012009c0
extern "C" void __cdecl FUN_012009c0(int a4, int a8, int a12)
{
    int t1001;
    int t1002;
    int t1004;
    int t1005;
    int t1006;
    int t1009;
    int t1010;
    int t1011;
    int t1014;
    int t1015;
    int t1016;
    int t1019;
    int t1020;
    int t1021;
    t1001 = (int)((int)(a4));
    t1002 = (int)(*(int*)((char*)(t1001)));
    t1004 = (int)((int)(a12));
    t1005 = (int)(*(int*)((char*)(t1004) + 120));
    t1006 = (int)((C_011e2300*)(t1005))->FUN_011e2300((unsigned int)(t1002));
    *(int*)((char*)(t1001)) = (int)(t1006);
    t1009 = (int)(*(int*)((char*)(t1001) + 8));
    t1010 = (int)(*(int*)((char*)(t1004) + 120));
    t1011 = (int)((C_011e2300*)(t1010))->FUN_011e2300((unsigned int)(t1009));
    *(int*)((char*)(t1001) + 8) = (int)(t1011);
    t1014 = (int)(*(int*)((char*)(t1001) + 12));
    t1015 = (int)(*(int*)((char*)(t1004) + 120));
    t1016 = (int)((C_011e2300*)(t1015))->FUN_011e2300((unsigned int)(t1014));
    *(int*)((char*)(t1001) + 12) = (int)(t1016);
    t1019 = (int)(*(int*)((char*)(t1001) + 16));
    t1020 = (int)(*(int*)((char*)(t1004) + 120));
    t1021 = (int)((C_011e2300*)(t1020))->FUN_011e2300((unsigned int)(t1019));
    *(int*)((char*)(t1001) + 16) = (int)(t1021);
    return;
}
