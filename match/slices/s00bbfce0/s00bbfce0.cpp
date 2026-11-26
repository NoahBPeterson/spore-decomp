// 0x00bbfce0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/_at_00bb0000.cpp, match/slices/s00bbf630/s00bbf630.cpp.

struct C_009a9600 { void FUN_009a9600(unsigned int); };
extern "C" void __cdecl FUN_00f47380(...);
struct C_0103de50 { int FUN_0103de50(unsigned int); };

// @ 0x00bbfce0
extern "C" int __cdecl FUN_00bbfce0(int a4, int a8, int a12, int a16, int a20, int a24, int a28, int a32, int a36)
{
    int t1002;
    int t1004;
    int t1007;
    int t1010;
    int t1011;
    int t1012;
    int t1013;
    int t1016;
    int t1017;
    int t1018;
    int t1021;
    int t1022;
    int t1023;
    int t1024;
    int t1027;
    int t1028;
    int t1029;
    int t1032;
    int t1033;
    int t1034;
    int t1035;
    int t1038;
    int t1039;
    int t1040;
    int t1041;
    int t1042;
    int t1043;
    int t1044;
    int t1045;
    int t1046;
    int t1047;
    int t1048;
    int t1052;
    int t1056;
    t1002 = (int)((int)(a8));
    t1004 = (int)((int)(a4));
    goto Lbbfcf0;
    Lbbfcf0:;
    t1007 = (int)((int)&a24);
    t1010 = (int)((C_0103de50*)(t1007))->FUN_0103de50((unsigned int)(t1004));
    t1011 = (int)(t1010);
    t1012 = (int)((int)&a12);
    t1013 = (int)((int)&a24);
    t1016 = (int)((C_0103de50*)(t1013))->FUN_0103de50((unsigned int)(t1012));
    t1017 = (int)(*(int*)((char*)(t1011)));
    if (t1017 > (int)*(int*)((char*)(t1016))) {
        t1004 = (int)(t1004 + (int)12);
        goto Lbbfcf0;
    }
    t1002 = (int)(t1002 - (int)12);
    t1018 = (int)((int)&a24);
    t1021 = (int)((C_0103de50*)(t1018))->FUN_0103de50((unsigned int)(t1002));
    t1022 = (int)((int)&a12);
    t1023 = (int)((int)&a24);
    t1024 = (int)(t1021);
    t1027 = (int)((C_0103de50*)(t1023))->FUN_0103de50((unsigned int)(t1022));
    t1028 = (int)(*(int*)((char*)(t1027)));
    if (t1028 > (int)*(int*)((char*)(t1024))) {
        do {
            t1002 = (int)(t1002 - (int)12);
            t1029 = (int)((int)&a24);
            t1032 = (int)((C_0103de50*)(t1029))->FUN_0103de50((unsigned int)(t1002));
            t1033 = (int)((int)&a12);
            t1034 = (int)((int)&a24);
            t1035 = (int)(t1032);
            t1038 = (int)((C_0103de50*)(t1034))->FUN_0103de50((unsigned int)(t1033));
            t1039 = (int)(*(int*)((char*)(t1038)));
        } while (t1039 > (int)*(int*)((char*)(t1035)));
    }
    if ((unsigned int)(t1004) < (unsigned int)(t1002)) {
        t1040 = (int)(*(int*)((char*)(t1002)));
        t1041 = (int)(*(int*)((char*)(t1004)));
        t1042 = (int)(*(int*)((char*)(t1004) + 4));
        t1043 = (int)(*(int*)((char*)(t1004) + 8));
        *(int*)((char*)(t1004)) = (int)(t1040);
        t1044 = (int)(*(int*)((char*)(t1002) + 4));
        *(int*)((char*)(t1004) + 4) = (int)(t1044);
        t1045 = (int)(*(int*)((char*)(t1002) + 8));
        *(int*)((char*)(t1004) + 8) = (int)(t1045);
        *(int*)((char*)(t1002)) = (int)(t1041);
        *(int*)((char*)(t1002) + 4) = (int)(t1042);
        *(int*)((char*)(t1002) + 8) = (int)(t1043);
        t1004 = (int)(t1004 + (int)12);
        goto Lbbfcf0;
    }
    t1046 = (int)((int)(a36));
    if (t1046 != (int)0) {
        do {
            t1047 = (int)(*(int*)((char*)(t1046)));
            t1048 = (int)((int)&a24);
            ((C_009a9600*)(t1048))->FUN_009a9600((unsigned int)(t1047));
            t1052 = (int)(*(int*)((char*)(t1046) + 4));
            FUN_00f47380((unsigned int)(t1046));
            t1046 = (int)(t1052);
        } while (t1052 != (int)0);
    }
    t1056 = (int)(t1004);
    return (int)(t1056);
}
