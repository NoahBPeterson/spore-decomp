// 0x00ac8130: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPCityVisualizer.cpp, match/slices/s00ac7ab0/s00ac7ab0.cpp.

extern "C" unsigned char g_013eb95c[];
extern "C" unsigned char g_013eecd8[];
extern "C" unsigned char g_013eeda0[];
extern "C" unsigned char g_013f09b4[];
extern "C" unsigned char g_013f8698[];
extern "C" unsigned char g_014007f4[];
extern "C" unsigned char g_0147b9f0[];
extern "C" unsigned char g_014853bc[];
extern "C" unsigned char g_014853e0[];
extern "C" unsigned char g_01486110[];
struct C_00b93810 { int FUN_00b93810(float, float); };
struct C_00b93840 { int FUN_00b93840(float, float); };
struct C_00b94a90 { int FUN_00b94a90(float, float); };
struct C_00b95050 { int FUN_00b95050(); };
struct C_00b981a0 { int FUN_00b981a0(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x00ac8130
extern "C" void __fastcall FUN_00ac8130(char* self, int edx_unused)
{
    int t1003;
    int t1006;
    int t1007;
    int t1010;
    int t1011;
    int t1014;
    int t1015;
    int t1018;
    int t1019;
    int t1025;
    int t1026;
    int t1029;
    int t1030;
    int t1034;
    int t1040;
    int t1041;
    int t1044;
    int t1045;
    int t1048;
    int t1049;
    int t1052;
    int t1053;
    int t1059;
    int t1060;
    int t1063;
    int t1064;
    int t1070;
    int t1071;
    int t1074;
    int t1075;
    int t1081;
    int t1082;
    int t1085;
    int t1086;
    int t1090;
    int t1091;
    int t1097;
    int t1098;
    int t1101;
    int t1102;
    int t1105;
    int t1106;
    int t1109;
    int t1110;
    int t1116;
    int t1117;
    int t1120;
    int t1121;
    int t1125;
    int t1131;
    int t1132;
    int t1135;
    int t1136;
    int t1139;
    int t1140;
    int t1143;
    int t1144;
    int t1150;
    int t1151;
    int t1154;
    int t1155;
    int t1159;
    t1003 = (int)((int)(self));
    t1006 = (int)FUN_00f473a0((unsigned int)((int)52), (unsigned int)((int)g_013f09b4), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
    if (t1006 != (int)0) {
        t1007 = (int)(t1006);
        t1010 = (int)((C_00b95050*)(t1007))->FUN_00b95050();
        t1011 = (int)(t1010);
    } else {
        t1011 = (int)((int)0);
    }
    t1014 = (int)FUN_00f473a0((unsigned int)((int)16), (unsigned int)((int)g_013f09b4), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
    if (t1014 != (int)0) {
        t1015 = (int)(t1014);
        t1018 = (int)((C_00b93810*)(t1015))->FUN_00b93810((float)((float)(*(float*)g_013eecd8)), (float)((float)(*(float*)g_014853bc)));
    } else {
        t1018 = (int)((int)0);
    }
    t1019 = (int)(t1011);
    ((C_00b981a0*)(t1019))->FUN_00b981a0((unsigned int)((int)1), (unsigned int)(t1018));
    t1025 = (int)FUN_00f473a0((unsigned int)((int)16), (unsigned int)((int)g_013f09b4), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
    if (t1025 != (int)0) {
        t1026 = (int)(t1025);
        t1029 = (int)((C_00b93840*)(t1026))->FUN_00b93840((float)((float)(*(float*)g_01486110)), (float)((float)(*(float*)g_013eeda0)));
    } else {
        t1029 = (int)((int)0);
    }
    t1030 = (int)(t1011);
    ((C_00b981a0*)(t1030))->FUN_00b981a0((unsigned int)((int)3), (unsigned int)(t1029));
    t1034 = (int)(t1003 + (int)352);
    ((C_00b981a0*)(t1034))->FUN_00b981a0((unsigned int)((int)1), (unsigned int)(t1011));
    t1040 = (int)FUN_00f473a0((unsigned int)((int)52), (unsigned int)((int)g_013f09b4), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
    if (t1040 != (int)0) {
        t1041 = (int)(t1040);
        t1044 = (int)((C_00b95050*)(t1041))->FUN_00b95050();
        t1045 = (int)(t1044);
    } else {
        t1045 = (int)((int)0);
    }
    t1048 = (int)FUN_00f473a0((unsigned int)((int)16), (unsigned int)((int)g_013f09b4), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
    if (t1048 != (int)0) {
        t1049 = (int)(t1048);
        t1052 = (int)((C_00b93810*)(t1049))->FUN_00b93810((float)((float)(*(float*)g_014007f4)), (float)((float)(*(float*)g_013eecd8)));
    } else {
        t1052 = (int)((int)0);
    }
    t1053 = (int)(t1045);
    ((C_00b981a0*)(t1053))->FUN_00b981a0((unsigned int)((int)1), (unsigned int)(t1052));
    t1059 = (int)FUN_00f473a0((unsigned int)((int)16), (unsigned int)((int)g_013f09b4), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
    if (t1059 != (int)0) {
        t1060 = (int)(t1059);
        t1063 = (int)((C_00b93840*)(t1060))->FUN_00b93840((float)((float)(*(float*)g_014853e0)), (float)((float)(*(float*)g_013eeda0)));
    } else {
        t1063 = (int)((int)0);
    }
    t1064 = (int)(t1045);
    ((C_00b981a0*)(t1064))->FUN_00b981a0((unsigned int)((int)6), (unsigned int)(t1063));
    t1070 = (int)FUN_00f473a0((unsigned int)((int)16), (unsigned int)((int)g_013f09b4), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
    if (t1070 != (int)0) {
        t1071 = (int)(t1070);
        t1074 = (int)((C_00b94a90*)(t1071))->FUN_00b94a90((float)((float)(*(float*)g_014853e0)), (float)((float)(*(float*)g_0147b9f0)));
    } else {
        t1074 = (int)((int)0);
    }
    t1075 = (int)(t1045);
    ((C_00b981a0*)(t1075))->FUN_00b981a0((unsigned int)((int)6), (unsigned int)(t1074));
    t1081 = (int)FUN_00f473a0((unsigned int)((int)16), (unsigned int)((int)g_013f09b4), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
    if (t1081 != (int)0) {
        t1082 = (int)(t1081);
        t1085 = (int)((C_00b93810*)(t1082))->FUN_00b93810((float)((float)(*(float*)g_013eb95c)), (float)((float)(*(float*)g_013f8698)));
    } else {
        t1085 = (int)((int)0);
    }
    t1086 = (int)(t1045);
    ((C_00b981a0*)(t1086))->FUN_00b981a0((unsigned int)((int)1), (unsigned int)(t1085));
    t1090 = (int)(t1003 + (int)300);
    t1091 = (int)(t1090);
    ((C_00b981a0*)(t1091))->FUN_00b981a0((unsigned int)((int)1), (unsigned int)(t1045));
    t1097 = (int)FUN_00f473a0((unsigned int)((int)52), (unsigned int)((int)g_013f09b4), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
    if (t1097 != (int)0) {
        t1098 = (int)(t1097);
        t1101 = (int)((C_00b95050*)(t1098))->FUN_00b95050();
        t1102 = (int)(t1101);
    } else {
        t1102 = (int)((int)0);
    }
    t1105 = (int)FUN_00f473a0((unsigned int)((int)16), (unsigned int)((int)g_013f09b4), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
    if (t1105 != (int)0) {
        t1106 = (int)(t1105);
        t1109 = (int)((C_00b93810*)(t1106))->FUN_00b93810((float)((float)(*(float*)g_013eb95c)), (float)((float)(*(float*)g_013f8698)));
    } else {
        t1109 = (int)((int)0);
    }
    t1110 = (int)(t1102);
    ((C_00b981a0*)(t1110))->FUN_00b981a0((unsigned int)((int)1), (unsigned int)(t1109));
    t1116 = (int)FUN_00f473a0((unsigned int)((int)16), (unsigned int)((int)g_013f09b4), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
    if (t1116 != (int)0) {
        t1117 = (int)(t1116);
        t1120 = (int)((C_00b94a90*)(t1117))->FUN_00b94a90((float)((float)(*(float*)g_014853e0)), (float)((float)(*(float*)g_0147b9f0)));
    } else {
        t1120 = (int)((int)0);
    }
    t1121 = (int)(t1102);
    ((C_00b981a0*)(t1121))->FUN_00b981a0((unsigned int)((int)4), (unsigned int)(t1120));
    t1125 = (int)(t1090);
    ((C_00b981a0*)(t1125))->FUN_00b981a0((unsigned int)((int)1), (unsigned int)(t1102));
    t1131 = (int)FUN_00f473a0((unsigned int)((int)52), (unsigned int)((int)g_013f09b4), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
    if (t1131 != (int)0) {
        t1132 = (int)(t1131);
        t1135 = (int)((C_00b95050*)(t1132))->FUN_00b95050();
        t1136 = (int)(t1135);
    } else {
        t1136 = (int)((int)0);
    }
    t1139 = (int)FUN_00f473a0((unsigned int)((int)16), (unsigned int)((int)g_013f09b4), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
    if (t1139 != (int)0) {
        t1140 = (int)(t1139);
        t1143 = (int)((C_00b93810*)(t1140))->FUN_00b93810((float)((float)(*(float*)g_014007f4)), (float)((float)(*(float*)g_013eecd8)));
    } else {
        t1143 = (int)((int)0);
    }
    t1144 = (int)(t1136);
    ((C_00b981a0*)(t1144))->FUN_00b981a0((unsigned int)((int)1), (unsigned int)(t1143));
    t1150 = (int)FUN_00f473a0((unsigned int)((int)16), (unsigned int)((int)g_013f09b4), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
    if (t1150 != (int)0) {
        t1151 = (int)(t1150);
        t1154 = (int)((C_00b93840*)(t1151))->FUN_00b93840((float)((float)(*(float*)g_013eeda0)), (float)((float)(*(float*)g_0147b9f0)));
    } else {
        t1154 = (int)((int)0);
    }
    t1155 = (int)(t1136);
    ((C_00b981a0*)(t1155))->FUN_00b981a0((unsigned int)((int)6), (unsigned int)(t1154));
    t1159 = (int)(t1090);
    ((C_00b981a0*)(t1159))->FUN_00b981a0((unsigned int)((int)1), (unsigned int)(t1136));
    return;
}
