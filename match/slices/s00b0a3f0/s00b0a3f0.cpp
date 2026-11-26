// 0x00b0a3f0: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00b09570/s00b09570.cpp, src/game/SPGonzago/SPPlanet.cpp.

// lifted by il2c_lift + l2c_search (bind@t1002); CI scorer MATCH; corpus status nonmatching/residual
struct C_00b07050 { void FUN_00b07050(unsigned int); };
struct C_01011cc0 { void FUN_01011cc0(unsigned int); };

template<class HsT> __forceinline HsT& hs_bind(HsT& x) { HsT& r = x; return r; }
// @ 0x00b0a3f0
extern "C" int __fastcall FUN_00b0a3f0(char* self, int edx_unused, int a4)
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
    int t1016;
    int t1017;
    int t1018;
    int t1019;
    int t1020;
    int t1021;
    int t1022;
    int t1026;
    int t1027;
    int t1031;
    int t1032;
    int t1036;
    int t1037;
    int t1041;
    int t1042;
    int t1046;
    int t1047;
    int t1052;
    t1002 = (int)((int)(self));
    t1004 = (int)((int)(a4));
    t1005 = (int)(*(int*)((char*)(t1004)));
    *(int*)((char*)(hs_bind(t1002))) = (int)(t1005);
    t1006 = (int)(*(int*)((char*)(t1004) + 4));
    *(int*)((char*)(t1002) + 4) = (int)(t1006);
    t1007 = (int)(*(int*)((char*)(t1004) + 8));
    *(int*)((char*)(t1002) + 8) = (int)(t1007);
    *(float*)((char*)(t1002) + 12) = (float)(*(float*)((char*)(t1004) + 12));
    t1008 = (int)(*(int*)((char*)(t1004) + 16));
    *(int*)((char*)(t1002) + 16) = (int)(t1008);
    t1009 = (int)(*(int*)((char*)(t1004) + 20));
    *(int*)((char*)(t1002) + 20) = (int)(t1009);
    t1010 = (int)(*(int*)((char*)(t1004) + 24));
    *(int*)((char*)(t1002) + 24) = (int)(t1010);
    t1011 = (int)(*(int*)((char*)(t1004) + 28));
    *(int*)((char*)(t1002) + 28) = (int)(t1011);
    t1012 = (int)(*(int*)((char*)(t1004) + 32));
    *(int*)((char*)(t1002) + 32) = (int)(t1012);
    t1013 = (int)(*(int*)((char*)(t1004) + 36));
    *(int*)((char*)(t1002) + 36) = (int)(t1013);
    t1014 = (int)(*(int*)((char*)(t1004) + 40));
    *(int*)((char*)(t1002) + 40) = (int)(t1014);
    t1015 = (int)(*(int*)((char*)(t1004) + 44));
    *(int*)((char*)(t1002) + 44) = (int)(t1015);
    t1016 = (int)(*(int*)((char*)(t1004) + 48));
    *(int*)((char*)(t1002) + 48) = (int)(t1016);
    t1017 = (int)(*(int*)((char*)(t1004) + 52));
    *(int*)((char*)(t1002) + 52) = (int)(t1017);
    t1018 = (int)(*(int*)((char*)(t1004) + 56));
    *(int*)((char*)(t1002) + 56) = (int)(t1018);
    t1019 = (int)(*(int*)((char*)(t1004) + 60));
    *(int*)((char*)(t1002) + 60) = (int)(t1019);
    t1020 = (int)(*(int*)((char*)(t1004) + 64));
    t1021 = (int)(t1004 + (int)68);
    t1022 = (int)(t1002 + (int)68);
    *(int*)((char*)(t1002) + 64) = (int)(t1020);
    ((C_01011cc0*)(t1022))->FUN_01011cc0((unsigned int)(t1021));
    t1026 = (int)(t1004 + (int)156);
    t1027 = (int)(t1002 + (int)156);
    ((C_01011cc0*)(t1027))->FUN_01011cc0((unsigned int)(t1026));
    t1031 = (int)(t1004 + (int)244);
    t1032 = (int)(t1002 + (int)244);
    ((C_01011cc0*)(t1032))->FUN_01011cc0((unsigned int)(t1031));
    *(float*)((char*)(t1002) + 332) = (float)(*(float*)((char*)(t1004) + 332));
    t1036 = (int)(t1004 + (int)344);
    t1037 = (int)(t1002 + (int)344);
    *(float*)((char*)(t1002) + 336) = (float)(*(float*)((char*)(t1004) + 336));
    ((C_00b07050*)(t1037))->FUN_00b07050((unsigned int)(t1036));
    t1041 = (int)(t1004 + (int)2416);
    t1042 = (int)(t1002 + (int)2416);
    ((C_00b07050*)(t1042))->FUN_00b07050((unsigned int)(t1041));
    t1046 = (int)(t1004 + (int)4488);
    t1047 = (int)(t1002 + (int)4488);
    ((C_00b07050*)(t1047))->FUN_00b07050((unsigned int)(t1046));
    t1052 = (int)(t1002);
    return (int)(t1052);
}
