// 0x00d04670: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00d03860/s00d03860.cpp.

extern "C" unsigned char g_013ebb38[];
extern "C" unsigned char g_013f09b4[];
struct C_00d01a40 { int FUN_00d01a40(unsigned int); };
struct C_00d03e90 { int FUN_00d03e90(unsigned int); };
struct C_00d04670 { int FUN_00d04670(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x00d04670
// @ 0x00d04670
extern "C" int __fastcall FUN_00d04670(char* self, int edx_unused, int a4, int a8)
{
    int t1004;
    int t1006;
    int t1007;
    int v_l4;
    int t1008;
    int t1011;
    int t1012;
    unsigned char t1013;
    int t1014;
    int t1015;
    int t1016;
    int t1019;
    int t1020;
    int t1021;
    int t1024;
    int t1025;
    int t1026;
    int t1027;
    int t1028;
    int t1029;
    int t1030;
    unsigned char t1033;
    int t1034;
    int t1035;
    int t1036;
    int t1041;
    t1004 = (int)((int)(a4));
    t1006 = (int)(t1004 + (int)16);
    t1007 = (int)((int)(self));
    v_l4 = (int)(t1007);
    t1008 = (int)((C_00d03e90*)((int)(self)))->FUN_00d03e90((unsigned int)(t1006));
    t1011 = (int)((int)(a8));
    t1012 = (int)(t1008);
    *(int*)((char*)(t1012)) = (int)((int)0);
    *(int*)((char*)(t1012) + 4) = (int)((int)0);
    *(int*)((char*)(t1012) + 8) = (int)(t1011);
    t1013 = (unsigned char)(*(unsigned char*)((char*)(t1004) + 12));
    *(unsigned char*)((char*)(t1012) + 12) = (unsigned char)(t1013);
    t1014 = (int)(*(int*)((char*)(t1004)));
    if (t1014 != (int)0) {
        t1015 = (int)(t1007);
        t1016 = (int)((C_00d04670*)(t1015))->FUN_00d04670((unsigned int)(t1014), (unsigned int)(t1012));
        *(int*)((char*)(t1012)) = (int)(t1016);
    }
    t1019 = (int)(*(int*)((char*)(t1004) + 4));
    t1020 = (int)(t1012);
    if (t1019 != (int)0) {
        do {
            t1021 = (int)FUN_00f473a0((unsigned int)((int)60), (unsigned int)((int)g_013f09b4), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)g_013ebb38), (unsigned int)((int)209));
            t1024 = (int)(t1021);
            t1025 = (int)(t1024 + (int)16);
            if (t1025 != (int)0) {
                t1026 = (int)(*(int*)((char*)(t1019) + 16));
                *(int*)((char*)(t1025)) = (int)(t1026);
                t1027 = (int)(*(int*)((char*)(t1019) + 20));
                *(int*)((char*)(t1025) + 4) = (int)(t1027);
                *(float*)((char*)(t1025) + 8) = (float)(*(float*)((char*)(t1019) + 24));
                t1028 = (int)(*(int*)((char*)(t1019) + 28));
                t1029 = (int)(t1019 + (int)32);
                *(int*)((char*)(t1025) + 12) = (int)(t1028);
                t1030 = (int)(t1025 + (int)16);
                t1025 = (int)((C_00d01a40*)(t1030))->FUN_00d01a40((unsigned int)(t1029));
            }
            *(int*)((char*)(t1024)) = (int)((int)0);
            *(int*)((char*)(t1024) + 4) = (int)((int)0);
            *(int*)((char*)(t1024) + 8) = (int)(t1020);
            t1033 = (unsigned char)(*(unsigned char*)((char*)(t1019) + 12));
            *(unsigned char*)((char*)(t1024) + 12) = (unsigned char)(t1033);
            *(int*)((char*)(t1020) + 4) = (int)(t1024);
            t1034 = (int)(*(int*)((char*)(t1019)));
            if (t1034 != (int)0) {
                t1035 = (int)(v_l4);
                t1036 = (int)((C_00d04670*)(t1035))->FUN_00d04670((unsigned int)(t1034), (unsigned int)(t1024));
                *(int*)((char*)(t1024)) = (int)(t1036);
            }
            t1019 = (int)(*(int*)((char*)(t1019) + 4));
            t1020 = (int)(t1024);
        } while (t1019 != (int)0);
    }
    t1041 = (int)(t1012);
    return (int)(t1041);
}
