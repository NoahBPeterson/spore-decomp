// 0x00c4ea70: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00c4dbf0/s00c4dbf0.cpp, src/game/SPGonzago/_at_00c40000.cpp.

struct C_0057cb60 { int FUN_0057cb60(unsigned int); };
struct C_00970b30 { int FUN_00970b30(); };
struct C_00b8de30 { int FUN_00b8de30(); };
struct C_00c487d0 { void FUN_00c487d0(unsigned int, unsigned int); };
struct C_00c48d40 { int FUN_00c48d40(unsigned int); };
struct C_01021080 { int FUN_01021080(); };
extern "C" int __cdecl FUN_01021080(...);
extern "C" int __cdecl FUN_01021240(...);
extern "C" int __cdecl FUN_010212a0(...);

// @ 0x00c4ea70
extern "C" void __fastcall FUN_00c4ea70(char* self, int edx_unused, int a4)
{
    int t1003;
    int t1004;
    int t1005;
    int t1009;
    int t1012;
    int t1013;
    int t1014;
    int t1017;
    int t1018;
    int t1021;
    int t1022;
    int t1023;
    int t1024;
    int t1028;
    int t1037;
    int t1038;
    int t1039;
    int t1042;
    int t1043;
    int t1046;
    int t1047;
    int t1050;
    int t1051;
    int t1052;
    int t1056;
    int t1065;
    int t1068;
    int t1069;
    int t1070;
    int t1073;
    int t1074;
    int t1077;
    int t1078;
    int t1079;
    int t1080;
    int t1084;
    int t1091;
    int t1092;
    t1003 = (int)((int)(self));
    t1004 = (int)(*(int*)((char*)(t1003) + 332));
    t1005 = (int)(t1003 + (int)332);
    if (t1004 == (int)*(int*)((char*)(t1005) + 4)) {
        if ((int)*(int*)((char*)(t1003) + 496) == (int)0) {
            if ((int)*(int*)((char*)(t1003) + 120) == (int)965397086) {
                t1009 = (int)((C_01021080*)((int)(self)))->FUN_01021080();
                if (t1009 == (int)1) {
                    t1012 = (int)FUN_010212a0();
                    t1013 = (int)(t1012);
                    if (t1013 != (int)0) {
                        t1014 = (int)(t1003);
                        t1017 = (int)((C_00970b30*)(t1014))->FUN_00970b30();
                        if (t1017 != (int)0) {
                            t1018 = (int)(t1003);
                            t1021 = (int)((C_00970b30*)(t1018))->FUN_00970b30();
                            t1022 = (int)(*(int*)((char*)(t1021) + 316));
                        } else {
                            t1022 = (int)((int)0);
                        }
                        if (t1013 == t1022) {
                            t1023 = (int)((int)(a4));
                            t1024 = (int)(t1003);
                            ((C_00c487d0*)(t1024))->FUN_00c487d0((unsigned int)((int)2031942262), (unsigned int)(t1023));
                            t1028 = (int)(t1005);
                            ((C_0057cb60*)(t1028))->FUN_0057cb60((unsigned int)(t1023));
                            return;
                        }
                    }
                    t1037 = (int)FUN_01021240();
                    t1038 = (int)(t1003);
                    t1039 = (int)(t1037);
                    t1042 = (int)((C_00970b30*)(t1038))->FUN_00970b30();
                    if (t1042 != (int)0) {
                        t1043 = (int)(t1003);
                        t1046 = (int)((C_00970b30*)(t1043))->FUN_00970b30();
                        t1047 = (int)(*(int*)((char*)(t1046) + 316));
                        t1050 = (int)((C_00b8de30*)(t1047))->FUN_00b8de30();
                    } else {
                        t1050 = (int)((int)0);
                    }
                    if (t1039 == (int)0) goto Lc4eb9e;
                    if (t1039 != t1050) goto Lc4eb9e;
                    t1051 = (int)((int)(a4));
                    t1052 = (int)(t1003);
                    ((C_00c487d0*)(t1052))->FUN_00c487d0((unsigned int)((int)1671367424), (unsigned int)(t1051));
                    t1056 = (int)(t1005);
                    ((C_0057cb60*)(t1056))->FUN_0057cb60((unsigned int)(t1051));
                    return;
                }
                t1065 = (int)FUN_01021080();
                if (t1065 == (int)0) {
                    t1068 = (int)FUN_010212a0();
                    t1069 = (int)(t1068);
                    if (t1069 != (int)0) {
                        t1070 = (int)(t1003);
                        t1073 = (int)((C_00970b30*)(t1070))->FUN_00970b30();
                        if (t1073 != (int)0) {
                            t1074 = (int)(t1003);
                            t1077 = (int)((C_00970b30*)(t1074))->FUN_00970b30();
                            t1078 = (int)(*(int*)((char*)(t1077) + 316));
                        } else {
                            t1078 = (int)((int)0);
                        }
                        if (t1069 == t1078) {
                            t1079 = (int)((int)(a4));
                            t1080 = (int)(t1003);
                            ((C_00c487d0*)(t1080))->FUN_00c487d0((unsigned int)((int)1872530419), (unsigned int)(t1079));
                            t1084 = (int)(t1005);
                            ((C_0057cb60*)(t1084))->FUN_0057cb60((unsigned int)(t1079));
                            return;
                        }
                    }
                }
            }
        }
    }
    Lc4eb9e:;
    t1091 = (int)((int)(a4));
    t1092 = (int)(t1003);
    ((C_00c48d40*)(t1092))->FUN_00c48d40((unsigned int)(t1091));
    return;
}
