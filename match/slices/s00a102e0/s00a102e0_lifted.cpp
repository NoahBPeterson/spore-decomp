// 0x00a102e0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPAudio/_at_00a10000.cpp, match/slices/s00a102e0/s00a102e0.cpp.

struct C_00a0ff50 { int FUN_00a0ff50(unsigned int); };

// @ 0x00a102e0
extern "C" int __fastcall FUN_00a102e0(char* self, int edx_unused, int a4)
{
    int t1003;
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
    int t1018;
    int t1019;
    int t1020;
    int t1021;
    int t1022;
    int t1023;
    int t1024;
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
    int t1039;
    int t1040;
    int t1041;
    int t1044;
    t1003 = (int)((int)(self));
    t1004 = (int)((int)0);
    if ((int)*(int*)((char*)(t1003) + 56) != t1004) {
        t1005 = (int)(*(int*)((char*)(t1003) + 52));
        if (t1005 != t1004) {
            *(int*)((char*)(t1003) + 44) = (int)(t1005);
            *(int*)((char*)(t1003) + 52) = (int)(t1004);
            *(int*)((char*)(t1003) + 56) = (int)(t1004);
            *(int*)((char*)(t1003) + 60) = (int)(t1004);
        }
    }
    t1006 = (int)(*(int*)((char*)(t1003)));
    t1007 = (int)(*(int*)((char*)(t1003) + 44));
    t1008 = (int)(t1006);
    t1009 = (int)(t1008 - t1007);
    t1010 = (int)(t1009 + (int)*(int*)((char*)(t1003) + 68));
    *(int*)((char*)(t1003) + 52) = (int)(t1007);
    if ((unsigned int)(t1010) < (unsigned int)4) {
        t1011 = (int)(*(int*)((char*)(t1003) + 4));
        t1012 = (int)(t1011 - t1006);
        t1013 = (int)(t1012 + t1012);
        t1014 = (int)(t1003);
        ((C_00a0ff50*)(t1014))->FUN_00a0ff50((unsigned int)(t1013));
    }
    t1018 = (int)(*(int*)((char*)(t1003) + 44));
    t1019 = (int)((int)(a4));
    *(int*)((char*)(t1018)) = (int)(t1019);
    *(int*)((char*)(t1003) + 44) += (int)4;
    t1020 = (int)(*(int*)((char*)(t1003)));
    t1021 = (int)(*(int*)((char*)(t1003) + 44));
    t1022 = (int)(t1020);
    t1023 = (int)(t1022 - t1021);
    t1024 = (int)(t1023 + (int)*(int*)((char*)(t1003) + 68));
    *(int*)((char*)(t1003) + 56) = (int)(t1021);
    if ((unsigned int)(t1024) < (unsigned int)4) {
        t1025 = (int)(*(int*)((char*)(t1003) + 4));
        t1026 = (int)(t1025 - t1020);
        t1027 = (int)(t1026 + t1026);
        t1028 = (int)(t1003);
        ((C_00a0ff50*)(t1028))->FUN_00a0ff50((unsigned int)(t1027));
    }
    t1032 = (int)(*(int*)((char*)(t1003) + 44));
    *(int*)((char*)(t1032)) = (int)(t1004);
    *(int*)((char*)(t1003) + 44) += (int)4;
    t1033 = (int)(*(int*)((char*)(t1003)));
    t1034 = (int)(*(int*)((char*)(t1003) + 44));
    t1035 = (int)(t1033);
    t1036 = (int)(t1035 - t1034);
    t1037 = (int)(t1036 + (int)*(int*)((char*)(t1003) + 68));
    *(int*)((char*)(t1003) + 60) = (int)(t1034);
    if ((unsigned int)(t1037) < (unsigned int)4) {
        t1038 = (int)(*(int*)((char*)(t1003) + 4));
        t1039 = (int)(t1038 - t1033);
        t1040 = (int)(t1039 + t1039);
        t1041 = (int)(t1003);
        t1034 = (int)((C_00a0ff50*)(t1041))->FUN_00a0ff50((unsigned int)(t1040));
    }
    t1044 = (int)(*(int*)((char*)(t1003) + 44));
    *(int*)((char*)(t1044)) = (int)(t1004);
    *(int*)((char*)(t1003) + 44) += (int)4;
    *(int*)((char*)(t1003) + 72) = (int)(t1004);
    return (int)(t1034);
}
