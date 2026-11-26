// 0x0073b980: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0073afb0/s0073afb0.cpp.

struct il2c_vc0 {
    virtual int s0();
};

struct C_00762380 { int FUN_00762380(); };
struct C_007f54d0 { int FUN_007f54d0(); };

// @ 0x0073b980
extern "C" bool __fastcall FUN_0073b980(char* self, int edx_unused, int a4, int a8, int a12, int a16, int a20, int a24, int a28)
{
    int t1002;
    int t1003;
    int t1007;
    int t1008;
    int t1009;
    int t1010;
    int t1011;
    int t1012;
    int t1013;
    int t1014;
    int t1015;
    int t1018;
    int t1019;
    int t1020;
    int t1021;
    int t1022;
    int t1023;
    int t1029;
    int t1030;
    bool t1032;
    int t1034;
    int t1035;
    int t1036;
    int t1037;
    int t1038;
    int t1039;
    int t1040;
    bool t1041;
    t1002 = (int)((int)(self));
    t1003 = (int)(*(int*)((char*)(t1002) + 204));
    if (t1003 != (int)0) {
        t1007 = (int)((C_007f54d0*)(t1003))->FUN_007f54d0();
        t1008 = (int)((int)(a8));
        t1009 = (int)(t1007);
        t1010 = (int)((int)(a4));
        *(int*)((char*)(t1010)) = (int)((int)16);
        t1011 = (int)((int)(a20));
        *(int*)((char*)(t1008)) = (int)((int)16);
        t1012 = (int)(*(int*)((char*)(t1009) + 56));
        *(int*)((char*)(t1011)) = (int)(t1012);
        t1013 = (int)(*(int*)((char*)(t1009) + 52));
        t1014 = (int)((int)(a24));
        *(int*)((char*)(t1014)) = (int)(t1013);
        t1015 = (int)(*(int*)((char*)(t1002) + 204));
        t1018 = (int)((C_00762380*)(t1015))->FUN_00762380();
        t1019 = (int)((int)(a12));
        *(int*)((char*)(t1019)) = (int)(t1018);
        t1020 = (int)(*(int*)((char*)(t1009) + 60));
        t1021 = (int)(*(int*)((char*)(t1020) + 8));
        t1022 = (int)((int)(a16));
        *(int*)((char*)(t1022)) = (int)(t1021);
        t1023 = (int)(*(int*)((char*)(t1002) + 204));
        ((il2c_vc0*)(t1023))->s0();
        t1029 = (int)(*(int*)((char*)(t1002) + 204));
        t1030 = (int)((int)(a28));
        *(int*)((char*)(t1030)) = (int)(t1029);
        t1032 = true;
        return (bool)(t1032);
    }
    t1034 = (int)((int)(a8));
    t1035 = (int)((int)(a4));
    t1036 = (int)((int)(a20));
    *(int*)((char*)(t1034)) = (int)((int)0);
    t1037 = (int)((int)(a24));
    *(int*)((char*)(t1035)) = (int)((int)0);
    t1038 = (int)((int)(a16));
    *(int*)((char*)(t1036)) = (int)((int)0);
    t1039 = (int)((int)(a12));
    *(int*)((char*)(t1037)) = (int)((int)0);
    t1040 = (int)((int)(a28));
    *(int*)((char*)(t1038)) = (int)((int)0);
    *(int*)((char*)(t1039)) = (int)((int)0);
    *(int*)((char*)(t1040)) = (int)((int)0);
    t1041 = false;
    return (bool)(t1041);
}
