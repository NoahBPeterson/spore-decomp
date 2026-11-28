// 0x009a9680: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s009a9600/s009a9600.cpp.

struct C_005d9320 { void FUN_005d9320(unsigned int); };
extern "C" int __cdecl FUN_00921580(...);
struct C_009a3c40 { void FUN_009a3c40(unsigned int); };
struct C_009a3c80 { void FUN_009a3c80(unsigned int); };
struct C_009a9600 { void FUN_009a9600(unsigned int); };
struct C_009a9640 { void FUN_009a9640(); };
struct C_009ab880 { int FUN_009ab880(); };
struct C_009abce0 { void FUN_009abce0(); };
extern "C" void __cdecl FUN_009cabb0(...);
struct C_009e1710 { void FUN_009e1710(); };
extern "C" int __cdecl FUN_00f47380(...);

// @ 0x009a9680
extern "C" void __fastcall FUN_009a9680(char* self, int edx_unused)
{
    int t1002;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1016;
    int t1017;
    int t1018;
    int t1025;
    int t1026;
    int t1033;
    int t1034;
    int t1035;
    int t1036;
    int t1037;
    int t1038;
    int t1039;
    int t1040;
    int t1044;
    int t1045;
    int t1052;
    int t1053;
    int t1054;
    int t1055;
    int t1056;
    int t1063;
    int t1066;
    int t1067;
    int t1068;
    int t1069;
    int t1073;
    int t1080;
    int t1081;
    int t1082;
    int t1083;
    int t1084;
    int t1085;
    int t1089;
    int t1096;
    int t1097;
    int t1098;
    int t1099;
    int t1103;
    int t1110;
    int t1111;
    int t1112;
    int t1113;
    int t1114;
    int t1121;
    int t1124;
    int t1125;
    int t1126;
    int t1127;
    int t1128;
    int t1138;
    int t1139;
    int t1146;
    int t1147;
    int t1148;
    int t1155;
    int t1159;
    int t1160;
    t1002 = (int)((int)(self));
    if ((unsigned char)*(unsigned char*)((char*)(t1002) + 48) != (unsigned char)0) {
        t1006 = (int)(*(int*)((char*)(t1002)));
        t1007 = (int)((int)0);
        if (t1006 != t1007) {
            t1008 = (int)(*(int*)((char*)(t1006) + 12));
            t1009 = (int)(t1006);
            ((C_009a3c40*)(t1009))->FUN_009a3c40((unsigned int)(t1008));
            FUN_00f47380((unsigned int)(t1006));
        }
        t1016 = (int)(*(int*)((char*)(t1002) + 4));
        *(int*)((char*)(t1002)) = (int)(t1007);
        if (t1016 != t1007) {
            t1017 = (int)(*(int*)((char*)(t1016) + 12));
            t1018 = (int)(t1016);
            ((C_009a3c80*)(t1018))->FUN_009a3c80((unsigned int)(t1017));
            FUN_00f47380((unsigned int)(t1016));
        }
        t1025 = (int)(*(int*)((char*)(t1002) + 12));
        *(int*)((char*)(t1002) + 4) = (int)(t1007);
        if (t1025 != t1007) {
            t1026 = (int)(t1025);
            ((C_009a9640*)(t1026))->FUN_009a9640();
            FUN_00f47380((unsigned int)(t1025));
        }
        t1033 = (int)(*(int*)((char*)(t1002) + 16));
        *(int*)((char*)(t1002) + 12) = (int)(t1007);
        t1034 = (int)(*(int*)((char*)(t1033) + 4));
        t1035 = (int)(t1034 - (int)*(int*)((char*)(t1033)));
        t1036 = (int)((int)0);
        t1037 = (int)(t1035 >> (int)2);
        if ((unsigned int)(t1037) > (unsigned int)(t1007)) {
            do {
                t1038 = (int)(*(int*)((char*)(t1002) + 16));
                t1039 = (int)(*(int*)((char*)(t1038)));
                t1040 = (int)(*(int*)((char*)(t1039) + (t1036)*4));
                FUN_009cabb0((unsigned int)(t1040));
                t1036 = (int)(t1036 + (int)1);
            } while ((unsigned int)(t1036) < (unsigned int)(t1037));
        }
        t1044 = (int)(*(int*)((char*)(t1002) + 16));
        if (t1044 != t1007) {
            t1045 = (int)(*(int*)((char*)(t1044)));
            if (t1045 != t1007) {
                if ((int)*(int*)((char*)(t1045) - 4) != t1007) {
                    FUN_00f47380((unsigned int)(t1045));
                }
            }
            FUN_00f47380((unsigned int)(t1044));
        }
        t1052 = (int)(*(int*)((char*)(t1002) + 20));
        *(int*)((char*)(t1002) + 16) = (int)(t1007);
        t1053 = (int)(*(int*)((char*)(t1052) + 8));
        t1054 = (int)(t1052 + (int)4);
        if (t1053 != t1054) {
            do {
                t1055 = (int)(*(int*)((char*)(t1053) + 20));
                if (t1055 != (int)0) {
                    t1056 = (int)(t1055);
                    ((C_009e1710*)(t1056))->FUN_009e1710();
                    FUN_00f47380((unsigned int)(t1055));
                }
                t1063 = (int)FUN_00921580((unsigned int)(t1053));
                t1053 = (int)(t1063);
            } while (t1053 != t1054);
        }
        t1066 = (int)(*(int*)((char*)(t1002) + 20));
        if (t1066 != (int)0) {
            t1067 = (int)(*(int*)((char*)(t1066) + 12));
            if (t1067 != (int)0) {
                do {
                    t1068 = (int)(*(int*)((char*)(t1067)));
                    t1069 = (int)(t1066);
                    ((C_009a9600*)(t1069))->FUN_009a9600((unsigned int)(t1068));
                    t1073 = (int)(*(int*)((char*)(t1067) + 4));
                    FUN_00f47380((unsigned int)(t1067));
                    t1067 = (int)(t1073);
                } while (t1073 != (int)0);
            }
            FUN_00f47380((unsigned int)(t1066));
        }
        t1080 = (int)(*(int*)((char*)(t1002) + 24));
        *(int*)((char*)(t1002) + 20) = (int)((int)0);
        if (t1080 != (int)0) {
            t1081 = (int)(*(int*)((char*)(t1080) + 4));
            t1082 = (int)(*(int*)((char*)(t1080)));
            if ((unsigned int)(t1082) < (unsigned int)(t1081)) {
                do {
                    t1083 = (int)(*(int*)((char*)(t1082)));
                    t1084 = (int)(*(int*)((char*)(t1082) + 8));
                    t1085 = (int)(t1084 - t1083);
                    if (t1085 > (int)1) {
                        if (t1083 != (int)0) {
                            FUN_00f47380((unsigned int)(t1083));
                        }
                    }
                    t1082 = (int)(t1082 + (int)20);
                } while ((unsigned int)(t1082) < (unsigned int)(t1081));
            }
            t1089 = (int)(*(int*)((char*)(t1080)));
            if (t1089 != (int)0) {
                if ((int)*(int*)((char*)(t1089) - 4) != (int)0) {
                    FUN_00f47380((unsigned int)(t1089));
                }
            }
            FUN_00f47380((unsigned int)(t1080));
        }
        t1096 = (int)(*(int*)((char*)(t1002) + 28));
        *(int*)((char*)(t1002) + 24) = (int)((int)0);
        if (t1096 != (int)0) {
            t1097 = (int)(*(int*)((char*)(t1096) + 12));
            if (t1097 != (int)0) {
                do {
                    t1098 = (int)(*(int*)((char*)(t1097)));
                    t1099 = (int)(t1096);
                    ((C_009a9600*)(t1099))->FUN_009a9600((unsigned int)(t1098));
                    t1103 = (int)(*(int*)((char*)(t1097) + 4));
                    FUN_00f47380((unsigned int)(t1097));
                    t1097 = (int)(t1103);
                } while (t1103 != (int)0);
            }
            FUN_00f47380((unsigned int)(t1096));
        }
        t1110 = (int)(*(int*)((char*)(t1002) + 32));
        *(int*)((char*)(t1002) + 28) = (int)((int)0);
        t1111 = (int)(*(int*)((char*)(t1110) + 8));
        t1112 = (int)(t1110 + (int)4);
        if (t1111 != t1112) {
            do {
                t1113 = (int)(*(int*)((char*)(t1111) + 20));
                if (t1113 != (int)0) {
                    t1114 = (int)(*(int*)((char*)(t1113)));
                    if (t1114 != (int)0) {
                        if ((int)*(int*)((char*)(t1114) - 4) != (int)0) {
                            FUN_00f47380((unsigned int)(t1114));
                        }
                    }
                    FUN_00f47380((unsigned int)(t1113));
                }
                t1121 = (int)FUN_00921580((unsigned int)(t1111));
                t1111 = (int)(t1121);
            } while (t1111 != t1112);
        }
        t1124 = (int)(*(int*)((char*)(t1002) + 32));
        t1125 = (int)((int)0);
        if (t1124 != t1125) {
            t1126 = (int)(*(int*)((char*)(t1124) + 12));
            if (t1126 != t1125) {
                do {
                    t1127 = (int)(*(int*)((char*)(t1126)));
                    t1128 = (int)(t1124);
                    ((C_009a9600*)(t1128))->FUN_009a9600((unsigned int)(t1127));
                    t1125 = (int)(*(int*)((char*)(t1126) + 4));
                    FUN_00f47380((unsigned int)(t1126));
                    t1126 = (int)(t1125);
                } while (t1125 != (int)0);
            }
            FUN_00f47380((unsigned int)(t1124));
        }
        t1138 = (int)(*(int*)((char*)(t1002) + 36));
        *(int*)((char*)(t1002) + 32) = (int)(t1125);
        if (t1138 != t1125) {
            t1139 = (int)(*(int*)((char*)(t1138)));
            if (t1139 != t1125) {
                if ((int)*(int*)((char*)(t1139) - 4) != t1125) {
                    FUN_00f47380((unsigned int)(t1139));
                }
            }
            FUN_00f47380((unsigned int)(t1138));
        }
        t1146 = (int)(*(int*)((char*)(t1002) + 40));
        *(int*)((char*)(t1002) + 36) = (int)(t1125);
        if (t1146 != t1125) {
            t1147 = (int)(*(int*)((char*)(t1146) + 12));
            t1148 = (int)(t1146);
            ((C_005d9320*)(t1148))->FUN_005d9320((unsigned int)(t1147));
            FUN_00f47380((unsigned int)(t1146));
        }
        t1155 = (int)(*(int*)((char*)(t1002) + 44));
        *(int*)((char*)(t1002) + 40) = (int)(t1125);
        ((C_009ab880*)(t1155))->FUN_009ab880();
        t1159 = (int)(*(int*)((char*)(t1002) + 44));
        if (t1159 != t1125) {
            t1160 = (int)(t1159);
            ((C_009abce0*)(t1160))->FUN_009abce0();
            FUN_00f47380((unsigned int)(t1159));
        }
        *(int*)((char*)(t1002) + 44) = (int)(t1125);
        *(unsigned char*)((char*)(t1002) + 48) = (unsigned char)((int)0);
    }
    return;
}
