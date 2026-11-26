// 0x00682be0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEngine/_at_00680000.cpp, match/slices/s00681f10/s00681f10.cpp.

struct C_006826c0 { int FUN_006826c0(unsigned int); };
struct C_00682be0 { int FUN_00682be0(unsigned int, unsigned int); };

// @ 0x00682be0
extern "C" int __fastcall FUN_00682be0(char* self, int edx_unused, int a4, int a8)
{
    int t1005;
    int t1006;
    int t1007;
    int v_l4;
    int t1010;
    int t1011;
    int t1012;
    unsigned char t1013;
    int t1014;
    int t1015;
    int t1018;
    int t1019;
    int t1020;
    int t1021;
    int t1022;
    int t1025;
    int t1026;
    unsigned char t1027;
    int t1028;
    int t1029;
    int t1032;
    int t1035;
    t1005 = (int)((int)(a4));
    t1006 = (int)(t1005 + (int)16);
    t1007 = (int)((int)(self));
    v_l4 = (int)(t1007);
    t1010 = (int)((C_006826c0*)((int)(self)))->FUN_006826c0((unsigned int)(t1006));
    t1011 = (int)((int)(a8));
    t1012 = (int)(t1010);
    *(int*)((char*)(t1012)) = (int)((int)0);
    *(int*)((char*)(t1012) + 4) = (int)((int)0);
    *(int*)((char*)(t1012) + 8) = (int)(t1011);
    t1013 = (unsigned char)(*(unsigned char*)((char*)(t1005) + 12));
    *(unsigned char*)((char*)(t1012) + 12) = (unsigned char)(t1013);
    t1014 = (int)(*(int*)((char*)(t1005)));
    if (t1014 != (int)0) {
        t1015 = (int)(t1007);
        t1018 = (int)((C_00682be0*)(t1015))->FUN_00682be0((unsigned int)(t1014), (unsigned int)(t1012));
        *(int*)((char*)(t1012)) = (int)(t1018);
    }
    t1019 = (int)(*(int*)((char*)(t1005) + 4));
    t1020 = (int)(t1012);
    if (t1019 != (int)0) {
        goto L682c36;
        L682c32:;
        t1007 = (int)(v_l4);
        L682c36:;
        t1021 = (int)(t1019 + (int)16);
        t1022 = (int)(t1007);
        t1025 = (int)((C_006826c0*)(t1022))->FUN_006826c0((unsigned int)(t1021));
        t1026 = (int)(t1025);
        *(int*)((char*)(t1026)) = (int)((int)0);
        *(int*)((char*)(t1026) + 4) = (int)((int)0);
        *(int*)((char*)(t1026) + 8) = (int)(t1020);
        t1027 = (unsigned char)(*(unsigned char*)((char*)(t1019) + 12));
        *(unsigned char*)((char*)(t1026) + 12) = (unsigned char)(t1027);
        *(int*)((char*)(t1020) + 4) = (int)(t1026);
        t1028 = (int)(*(int*)((char*)(t1019)));
        if (t1028 != (int)0) {
            t1029 = (int)(v_l4);
            t1032 = (int)((C_00682be0*)(t1029))->FUN_00682be0((unsigned int)(t1028), (unsigned int)(t1026));
            *(int*)((char*)(t1026)) = (int)(t1032);
        }
        t1019 = (int)(*(int*)((char*)(t1019) + 4));
        t1020 = (int)(t1026);
        if (t1019 != (int)0) goto L682c32;
    }
    t1035 = (int)(t1012);
    return (int)(t1035);
}
