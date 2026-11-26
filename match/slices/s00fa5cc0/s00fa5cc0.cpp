// 0x00fa5cc0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPTerrain/SPTerrainSphere.cpp, match/slices/s00fa5610/s00fa5610.cpp.

extern "C" unsigned char g_015b14e8[];
extern "C" unsigned char g_015fd918[];
extern "C" unsigned char g_016c9e68[];
extern "C" unsigned char g_016c9f58[];
extern "C" unsigned char g_016c9f5c[];
extern "C" unsigned char g_016f6ee0[];
extern "C" unsigned char g_016f9554[];
extern "C" unsigned char g_016f9674[];
extern "C" unsigned char g_016fa1c4[];
extern "C" unsigned char g_016fa1c8[];
extern "C" unsigned char g_016fa1d4[];
extern "C" unsigned char g_016fa1d8[];
extern "C" unsigned char g_016fa1dc[];
extern "C" unsigned char g_016fa3a8[];
struct C_006a25a0 { int FUN_006a25a0(unsigned int); };
struct C_007c3c50 { int FUN_007c3c50(unsigned int); };
extern "C" void __cdecl FUN_00f96b40(...);
extern "C" void __cdecl FUN_00f96c60(...);
struct C_00f998f0 { void FUN_00f998f0(); };
struct C_00f9c470 { void FUN_00f9c470(unsigned int, unsigned int); };
struct C_00f9df20 { void FUN_00f9df20(unsigned int, unsigned int, unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00f9e280(...);
extern "C" int __cdecl FUN_00f9e350(...);
struct C_00fa3860 { void FUN_00fa3860(unsigned int, unsigned int); };

// @ 0x00fa5cc0
extern "C" int __fastcall FUN_00fa5cc0(char* self, int edx_unused, int a4, int a8, int a12)
{
    int t1005;
    int t1006;
    int t1007;
    int t1010;
    int t1011;
    unsigned char t1012;
    int t1015;
    int t1016;
    unsigned char v_l2;
    int t1019;
    int t1020;
    int t1021;
    unsigned char v_l1;
    int t1022;
    int t1026;
    int t1027;
    int t1031;
    int t1032;
    int t1039;
    int t1042;
    int t1043;
    int t1049;
    int t1052;
    int t1053;
    int t1054;
    int t1055;
    int t1056;
    int t1057;
    int t1061;
    int t1062;
    int t1063;
    t1005 = (int)((int)(*(int*)g_015fd918));
    t1006 = (int)((int)(self));
    t1007 = (int)(t1005);
    t1010 = (int)((C_006a25a0*)(t1007))->FUN_006a25a0((unsigned int)((int)538594896));
    t1011 = (int)(t1005);
    t1012 = (unsigned char)((unsigned char)(t1010));
    t1015 = (int)((C_006a25a0*)(t1011))->FUN_006a25a0((unsigned int)((int)(-240577702)));
    t1016 = (int)(t1005);
    v_l2 = (unsigned char)((unsigned char)(t1015));
    t1019 = (int)((C_006a25a0*)(t1016))->FUN_006a25a0((unsigned int)((int)2038418828));
    t1020 = (int)((int)(a8));
    t1021 = (int)((int)(a4));
    v_l1 = (unsigned char)((unsigned char)(t1019));
    t1022 = (int)((int)(*(int*)g_016f6ee0));
    *(int*)((char*)(t1022)) &= (int)(-3);
    if (t1012 != (unsigned char)0) {
        if ((int)(*(int*)g_016c9e68) == (int)0) {
            FUN_00f96b40();
        }
        if ((unsigned char)*(unsigned char*)((char*)(t1006) + 272) != (unsigned char)0) goto Lfa5d59;
        t1026 = (int)(*(int*)((char*)(t1021)));
        t1027 = (int)(t1006);
        ((C_00fa3860*)(t1027))->FUN_00fa3860((unsigned int)(t1026), (unsigned int)(t1020));
        t1031 = (int)((int)(*(int*)g_016f6ee0));
        *(int*)((char*)(t1031)) |= (int)2;
        goto Lfa5d59;
    }
    if ((int)*(int*)((char*)(t1006) + 2268) != (int)0) {
        t1032 = (int)(t1006);
        ((C_00f998f0*)(t1032))->FUN_00f998f0();
    }
    if ((int)(*(int*)g_016c9e68) != (int)0) {
        FUN_00f96c60();
    }
    Lfa5d59:;
    t1039 = (int)((int)(*(int*)g_016f6ee0));
    *(int*)((char*)(t1039)) &= (int)(-9);
    if (v_l2 != (unsigned char)0) {
        if ((int)(*(int*)g_016c9f5c) == (int)0) {
            t1039 = (int)FUN_00f9e280();
        }
        if ((unsigned char)*(unsigned char*)((char*)(t1006) + 272) != (unsigned char)0) goto Lfa5da2;
        t1042 = (int)(*(int*)((char*)(t1021)));
        t1043 = (int)(t1006);
        ((C_00f9c470*)(t1043))->FUN_00f9c470((unsigned int)(t1042), (unsigned int)(t1020));
        t1039 = (int)((int)(*(int*)g_016f6ee0));
        *(int*)((char*)(t1039)) |= (int)8;
        goto Lfa5da2;
    }
    if ((int)(*(int*)g_016c9f5c) != (int)0) {
        t1039 = (int)FUN_00f9e350();
    }
    Lfa5da2:;
    if ((unsigned char)(*(unsigned char*)g_015b14e8) != (unsigned char)0) {
        if (v_l2 == (unsigned char)0) {
            if (t1012 == (unsigned char)0) goto Lfa5dbf;
        }
        t1049 = (int)(*(int*)((char*)(t1021)));
        t1039 = (int)((C_007c3c50*)(t1049))->FUN_007c3c50((unsigned int)((int)6));
    }
    Lfa5dbf:;
    if (v_l1 != (unsigned char)0) {
        t1052 = (int)((int)(*(int*)g_016c9f58));
        t1053 = (int)((int)512);
        *(int*)g_016fa3a8 = (int)((int)(*(int*)g_016fa3a8) | t1053);
        *(int*)g_016f9674 = (int)((int)0);
        t1054 = (int)(*(int*)((char*)(t1052)));
        t1055 = (int)(t1006 + (int)812);
        t1056 = (int)(*(int*)((char*)(t1021)));
        t1057 = (int)(t1006);
        ((C_00f9df20*)(t1057))->FUN_00f9df20((unsigned int)(t1056), (unsigned int)(t1054), (unsigned int)(t1055), (unsigned int)(t1020));
        t1061 = (int)((int)(*(int*)g_016c9f58));
        t1062 = (int)(*(int*)((char*)(t1061)));
        *(int*)g_016fa3a8 = (int)((int)(*(int*)g_016fa3a8) | t1053);
        *(int*)g_016f9554 = (int)((int)(*(int*)g_016f9554) | (int)115);
        *(int*)g_016f9674 = (int)(t1062);
        t1063 = (int)((int)3);
        *(int*)g_016fa1c4 = (int)(t1063);
        *(int*)g_016fa1c8 = (int)(t1063);
        t1039 = (int)((int)2);
        *(int*)g_016fa1d8 = (int)(t1039);
        *(int*)g_016fa1d4 = (int)(t1039);
        *(int*)g_016fa1dc = (int)(t1039);
    }
    return (int)(t1039);
}
