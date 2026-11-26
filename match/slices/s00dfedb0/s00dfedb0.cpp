// 0x00dfedb0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPGalaxyGameEntry.cpp, match/slices/s00dfe460/s00dfe460.cpp.

struct C_00423650 { void FUN_00423650(unsigned int, unsigned int); };
struct C_006b5430 { void FUN_006b5430(unsigned int); };
struct C_00dfeb00 { void FUN_00dfeb00(unsigned int); };

// @ 0x00dfedb0
extern "C" int __fastcall FUN_00dfedb0(char* self, int edx_unused, int a4)
{
    int t1001;
    int t1004;
    int t1008;
    int t1009;
    int t1010;
    int t1011;
    int t1015;
    int t1016;
    int t1017;
    int t1018;
    int t1019;
    int t1020;
    int t1026;
    int t1027;
    int t1028;
    int t1032;
    int t1033;
    int t1034;
    int t1035;
    int t1039;
    int t1040;
    int t1041;
    int t1042;
    int t1045;
    int t1046;
    int t1049;
    unsigned char t1050;
    int t1051;
    int t1052;
    int t1053;
    int t1057;
    t1001 = (int)((int)(a4));
    t1004 = (int)((int)(self));
    ((C_006b5430*)((int)(self)))->FUN_006b5430((unsigned int)(t1001));
    t1008 = (int)(t1001 + (int)20);
    t1009 = (int)(t1004 + (int)20);
    if (t1008 != t1009) {
        t1010 = (int)(*(int*)((char*)(t1008) + 4));
        t1011 = (int)(*(int*)((char*)(t1008)));
        ((C_00423650*)(t1009))->FUN_00423650((unsigned int)(t1011), (unsigned int)(t1010));
    }
    t1015 = (int)(*(int*)((char*)(t1001) + 36));
    *(int*)((char*)(t1004) + 36) = (int)(t1015);
    t1016 = (int)(*(int*)((char*)(t1001) + 40));
    t1017 = (int)(t1001 + (int)44);
    t1018 = (int)(t1004 + (int)44);
    *(int*)((char*)(t1004) + 40) = (int)(t1016);
    if (t1017 != t1018) {
        t1019 = (int)(*(int*)((char*)(t1017) + 4));
        t1020 = (int)(*(int*)((char*)(t1017)));
        ((C_00423650*)(t1018))->FUN_00423650((unsigned int)(t1020), (unsigned int)(t1019));
    }
    t1026 = (int)(t1001 + (int)60);
    t1027 = (int)(t1004 + (int)60);
    t1028 = (int)(t1027);
    ((C_006b5430*)(t1028))->FUN_006b5430((unsigned int)(t1026));
    t1032 = (int)(t1026 + (int)20);
    t1033 = (int)(t1027 + (int)20);
    if (t1032 != t1033) {
        t1034 = (int)(*(int*)((char*)(t1032) + 4));
        t1035 = (int)(*(int*)((char*)(t1032)));
        ((C_00423650*)(t1033))->FUN_00423650((unsigned int)(t1035), (unsigned int)(t1034));
    }
    t1039 = (int)(*(int*)((char*)(t1026) + 36));
    *(int*)((char*)(t1027) + 36) = (int)(t1039);
    t1040 = (int)(*(int*)((char*)(t1026) + 40));
    t1041 = (int)(t1026 + (int)44);
    t1042 = (int)(t1027 + (int)44);
    *(int*)((char*)(t1027) + 40) = (int)(t1040);
    if (t1041 != t1042) {
        t1045 = (int)(*(int*)((char*)(t1041) + 4));
        t1046 = (int)(*(int*)((char*)(t1041)));
        ((C_00423650*)(t1042))->FUN_00423650((unsigned int)(t1046), (unsigned int)(t1045));
    }
    t1049 = (int)(*(int*)((char*)(t1001) + 120));
    *(int*)((char*)(t1004) + 120) = (int)(t1049);
    t1050 = (unsigned char)(*(unsigned char*)((char*)(t1001) + 124));
    *(unsigned char*)((char*)(t1004) + 124) = (unsigned char)(t1050);
    t1051 = (int)(*(int*)((char*)(t1001) + 128));
    t1052 = (int)(t1001 + (int)132);
    t1053 = (int)(t1004 + (int)132);
    *(int*)((char*)(t1004) + 128) = (int)(t1051);
    ((C_00dfeb00*)(t1053))->FUN_00dfeb00((unsigned int)(t1052));
    t1057 = (int)(t1004);
    return (int)(t1057);
}
