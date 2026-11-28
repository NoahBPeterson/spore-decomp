// 0x00adb1b0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00adaad0/s00adaad0.cpp.

struct C_00ad91a0 { int FUN_00ad91a0(unsigned int, unsigned int); };

// @ 0x00adb1b0
extern "C" bool __fastcall FUN_00adb1b0(char* self, int edx_unused, int a4, int a8)
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
    int t1015;
    bool t1017;
    int t1019;
    int t1020;
    int t1021;
    int t1022;
    int t1023;
    int t1026;
    int t1027;
    int t1028;
    int t1029;
    int t1030;
    int t1031;
    bool t1033;
    int t1035;
    bool t1037;
    t1003 = (int)((int)(self));
    t1004 = (int)((int)&a4);
    t1005 = (int)((int)&v_l8);
    t1006 = (int)(t1003 + (int)144);
    t1007 = (int)(t1006);
    ((C_00ad91a0*)(t1007))->FUN_00ad91a0((unsigned int)(t1005), (unsigned int)(t1004));
    t1011 = (int)(*(int*)((char*)(t1006) + 8));
    t1012 = (int)(*(int*)((char*)(t1006) + 4));
    t1013 = (int)((*(int*)&v_l8[0]));
    if (t1013 != (int)*(int*)((char*)(t1012) + (t1011)*4)) {
        t1014 = (int)(*(int*)((char*)(t1013) + 16));
        t1015 = (int)((int)(a8));
        *(int*)((char*)(t1015)) = (int)(t1014);
        t1017 = true;
        return (bool)(t1017);
    }
    t1019 = (int)((int)&a4);
    t1020 = (int)((int)&v_l8);
    t1021 = (int)(t1003 + (int)176);
    t1022 = (int)(t1021);
    t1023 = (int)((C_00ad91a0*)(t1022))->FUN_00ad91a0((unsigned int)(t1020), (unsigned int)(t1019));
    t1026 = (int)(*(int*)((char*)(t1023)));
    t1027 = (int)(*(int*)((char*)(t1023) + 4));
    t1028 = (int)(*(int*)((char*)(t1021) + 8));
    (*(int*)&v_l8[1]) = (int)(t1027);
    t1029 = (int)(*(int*)((char*)(t1021) + 4));
    if (t1026 != (int)*(int*)((char*)(t1029) + (t1028)*4)) {
        t1030 = (int)(*(int*)((char*)(t1026) + 16));
        t1031 = (int)((int)(a8));
        *(int*)((char*)(t1031)) = (int)(t1030);
        t1033 = true;
        return (bool)(t1033);
    }
    t1035 = (int)((int)(a8));
    *(int*)((char*)(t1035)) = (int)((int)0);
    t1037 = false;
    return (bool)(t1037);
}
