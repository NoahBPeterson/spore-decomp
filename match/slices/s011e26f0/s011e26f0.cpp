// 0x011e26f0: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s011e0560/s011e0560.cpp.

// lifted by il2c_lift + l2c_search (ref@t1008); CI scorer MATCH; corpus status nonmatching/residual
struct C_011e4610 { int FUN_011e4610(); };
struct C_011e4620 { int FUN_011e4620(); };
struct C_011eb150 { int FUN_011eb150(); };
struct C_011eb160 { int FUN_011eb160(); };
struct C_011eb170 { int FUN_011eb170(); };

// @ 0x011e26f0
extern "C" void __fastcall FUN_011e26f0(char* self, int edx_unused)
{
    int t1003;
    int t1004;
    int t1005;
    int t1008;
    int t1010;
    int t1011;
    int t1012;
    int t1014;
    int t1016;
    int t1017;
    int t1019;
    int t1021;
    int t1022;
    int t1024;
    int t1026;
    int t1027;
    int t1029;
    int t1031;
    int t1032;
    int t1034;
    int t1036;
    int t1037;
    int t1039;
    int t1041;
    int t1042;
    int t1044;
    int t1046;
    t1003 = (int)((int)(self));
    t1004 = (int)(*(int*)((char*)(t1003) + 120));
    t1005 = (int)(*(int*)((char*)(t1004) + 52));
    t1008 = (int)((C_011e4620*)(t1005))->FUN_011e4620();
    int& t1008_r = t1008;
    t1010 = (int)(t1003 + (int)228);
    t1011 = (int)(t1010);
    t1012 = (int)(t1008_r);
    t1014 = (int)((C_011eb170*)(t1011))->FUN_011eb170();
    *(int*)((char*)(t1012) + 24) = (int)(t1014);
    t1016 = (int)(*(int*)((char*)(t1003) + 120));
    t1017 = (int)(*(int*)((char*)(t1016) + 52));
    t1019 = (int)((C_011e4620*)(t1017))->FUN_011e4620();
    t1021 = (int)(t1010);
    t1022 = (int)(t1019);
    t1024 = (int)((C_011eb160*)(t1021))->FUN_011eb160();
    *(int*)((char*)(t1022) + 16) = (int)(t1024);
    t1026 = (int)(*(int*)((char*)(t1003) + 120));
    t1027 = (int)(*(int*)((char*)(t1026) + 52));
    t1029 = (int)((C_011e4620*)(t1027))->FUN_011e4620();
    t1031 = (int)(t1010);
    t1032 = (int)(t1029);
    t1034 = (int)((C_011eb150*)(t1031))->FUN_011eb150();
    *(int*)((char*)(t1032) + 20) = (int)(t1034);
    t1036 = (int)(*(int*)((char*)(t1003) + 120));
    t1037 = (int)(*(int*)((char*)(t1036) + 52));
    t1039 = (int)((C_011e4610*)(t1037))->FUN_011e4610();
    t1041 = (int)(t1010);
    t1042 = (int)(t1039);
    t1044 = (int)((C_011eb160*)(t1041))->FUN_011eb160();
    t1046 = (int)(*(int*)((char*)(t1042) + 8));
    *(int*)((char*)(t1046) + 8) = (int)(t1044);
    return;
}
