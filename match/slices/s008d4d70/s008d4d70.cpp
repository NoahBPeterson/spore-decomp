// 0x008d4d70: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s008d4520/s008d4520.cpp.

struct C_007e2ea0 { int FUN_007e2ea0(unsigned int, unsigned int); };

// @ 0x008d4d70
extern "C" bool __fastcall FUN_008d4d70(char* self, int edx_unused, int a4, int a8)
{
    int t1001;
    int t1005;
    int t1006;
    int v_l8[2];
    int t1007;
    int t1008;
    int t1011;
    int t1012;
    int t1013;
    int t1014;
    int t1015;
    int t1016;
    int t1017;
    int t1020;
    int t1021;
    int t1022;
    int t1023;
    int t1024;
    bool t1027;
    bool t1031;
    t1001 = (int)((int)(a4));
    t1005 = (int)((int)(self));
    t1006 = (int)((int)&v_l8);
    t1007 = (int)(t1005 + (int)28);
    t1008 = (int)(t1007);
    t1011 = (int)((C_007e2ea0*)(t1008))->FUN_007e2ea0((unsigned int)(t1006), (unsigned int)(t1001));
    t1012 = (int)(*(int*)((char*)(t1011)));
    t1013 = (int)(*(int*)((char*)(t1007) + 8));
    t1014 = (int)(*(int*)((char*)(t1007) + 4));
    if (t1012 == (int)*(int*)((char*)(t1014) + (t1013)*4)) {
        do {
            t1005 = (int)(*(int*)((char*)(t1005) + 4));
            if (t1005 == (int)0) goto L8d4dd8;
            t1015 = (int)((int)&v_l8);
            t1016 = (int)(t1005 + (int)28);
            t1017 = (int)(t1016);
            t1020 = (int)((C_007e2ea0*)(t1017))->FUN_007e2ea0((unsigned int)(t1015), (unsigned int)(t1001));
            t1012 = (int)(*(int*)((char*)(t1020)));
            t1021 = (int)(*(int*)((char*)(t1016) + 8));
            t1022 = (int)(*(int*)((char*)(t1016) + 4));
        } while (t1012 == (int)*(int*)((char*)(t1022) + (t1021)*4));
    }
    t1023 = (int)(*(int*)((char*)(t1012) + 16));
    t1024 = (int)((int)(a8));
    *(int*)((char*)(t1024)) = (int)(t1023);
    t1027 = true;
    return (bool)(t1027);
    L8d4dd8:;
    t1031 = false;
    return (bool)(t1031);
}
