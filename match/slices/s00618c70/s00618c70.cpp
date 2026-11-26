// 0x00618c70: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEditors/SPPollinatorTransactions.cpp, match/slices/s00618150/s00618150.cpp.

struct C_00423650 { void FUN_00423650(unsigned int, unsigned int); };
struct C_00454cb0 { void FUN_00454cb0(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_005419c0(...);
extern "C" int __cdecl FUN_00932e80(...);

// @ 0x00618c70
extern "C" int __cdecl FUN_00618c70(int a4, int a8)
{
    int t1003;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1010;
    int t1014;
    int t1017;
    int t1018;
    int t1019;
    int t1020;
    int t1021;
    int t1025;
    int t1026;
    int t1027;
    int t1028;
    int t1032;
    int t1033;
    int t1034;
    int t1035;
    int t1036;
    int t1037;
    int t1038;
    int t1042;
    int t1045;
    int t1046;
    int t1047;
    int t1048;
    int t1049;
    int t1050;
    int t1054;
    int t1055;
    t1003 = (int)((int)(a8));
    t1005 = (int)((int)(a4));
    t1006 = (int)(t1005 + (int)8);
    t1007 = (int)(t1003 + (int)84);
    if (t1006 != t1007) {
        t1008 = (int)(*(int*)((char*)(t1006) + 4));
        t1009 = (int)(*(int*)((char*)(t1006)));
        t1010 = (int)(t1007);
        ((C_00454cb0*)(t1010))->FUN_00454cb0((unsigned int)(t1009), (unsigned int)(t1008));
    }
    t1014 = (int)(*(int*)((char*)(t1007)));
    t1017 = (int)FUN_00932e80((unsigned int)(t1014), (unsigned int)((int)(-2128831035)), (unsigned int)((int)1));
    *(int*)((char*)(t1003) + 100) = (int)(t1017);
    t1018 = (int)(t1005 + (int)28);
    t1019 = (int)(t1003 + (int)24);
    if (t1018 != t1019) {
        t1020 = (int)(*(int*)((char*)(t1018) + 4));
        t1021 = (int)(*(int*)((char*)(t1018)));
        ((C_00423650*)(t1019))->FUN_00423650((unsigned int)(t1021), (unsigned int)(t1020));
    }
    t1025 = (int)(t1005 + (int)44);
    t1026 = (int)(t1003 + (int)40);
    if (t1025 != t1026) {
        t1027 = (int)(*(int*)((char*)(t1025) + 4));
        t1028 = (int)(*(int*)((char*)(t1025)));
        ((C_00423650*)(t1026))->FUN_00423650((unsigned int)(t1028), (unsigned int)(t1027));
    }
    t1032 = (int)(*(int*)((char*)(t1005) + 64));
    *(int*)((char*)(t1003) + 56) = (int)(t1032);
    t1033 = (int)(*(int*)((char*)(t1005) + 68));
    *(int*)((char*)(t1003) + 60) = (int)(t1033);
    t1034 = (int)(*(int*)((char*)(t1005) + 72));
    *(int*)((char*)(t1003) + 64) = (int)(t1034);
    t1035 = (int)(t1005 + (int)80);
    t1036 = (int)(t1003 + (int)68);
    if (t1035 != t1036) {
        t1037 = (int)(*(int*)((char*)(t1035) + 4));
        t1038 = (int)(*(int*)((char*)(t1035)));
        ((C_00454cb0*)(t1036))->FUN_00454cb0((unsigned int)(t1038), (unsigned int)(t1037));
    }
    t1042 = (int)(*(int*)((char*)(t1006)));
    t1045 = (int)FUN_005419c0((unsigned int)(t1042));
    *(int*)((char*)(t1003) + 104) = (int)(t1045);
    t1046 = (int)(*(int*)((char*)(t1005) + 76));
    if (t1046 != (int)0) {
        t1047 = (int)(t1046 + (int)8);
        if (t1047 != t1003) {
            t1048 = (int)(*(int*)((char*)(t1047) + 4));
            t1049 = (int)(*(int*)((char*)(t1047)));
            t1050 = (int)(t1003);
            ((C_00423650*)(t1050))->FUN_00423650((unsigned int)(t1049), (unsigned int)(t1048));
        }
        t1054 = (int)(*(int*)((char*)(t1005) + 76));
        t1046 = (int)(*(int*)((char*)(t1054) + 24));
        *(int*)((char*)(t1003) + 16) = (int)(t1046);
        t1055 = (int)(*(int*)((char*)(t1054) + 28));
        *(int*)((char*)(t1003) + 20) = (int)(t1055);
    }
    return (int)(t1046);
}
