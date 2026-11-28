// 0x00eaeef0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPAudioPlayerCityMusic.cpp, match/slices/s00eae0f0/s00eae0f0.cpp.

struct C_00b968b0 { int FUN_00b968b0(unsigned int, unsigned int, unsigned int); };
extern "C" void __cdecl FUN_00f47380(...);
extern "C" int __cdecl FUN_011e0744(...);

// @ 0x00eaeef0
// @ 0x00eaeef0
extern "C" int __fastcall FUN_00eaeef0(char* self, int edx_unused, int a4, int a8, int a12)
{
    int t1000;
    int t1005;
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
    int t1020;
    int t1021;
    int t8;
    int t1025;
    int t1030;
    int t1031;
    int t1032;
    int t1033;
    int t13;
    int t1036;
    int t14;
    int t1041;
    int t1042;
    int t1043;
    int t1047;
    int t1048;
    int t1049;
    int t1052;
    int t21;
    int t1053;
    t1000 = (int)((int)(a4));
    t1005 = (int)((int)(a8));
    t1007 = (int)((int)(self));
    t1008 = (int)(*(int*)((char*)(t1007)));
    t1009 = (int)(*(int*)((char*)(t1007) + 8));
    t1010 = (int)(t1005);
    t1011 = (int)(t1010 - t1000);
    t1012 = (int)(t1009 - t1008);
    t1013 = (int)(t1011);
    t1014 = (int)(t1013 >> (int)2);
    t1015 = (int)(t1012 >> (int)2);
    if ((unsigned int)(t1014) > (unsigned int)(t1015)) {
        t1016 = (int)(t1007);
        t1017 = (int)((C_00b968b0*)(t1016))->FUN_00b968b0((unsigned int)(t1014), (unsigned int)(t1000), (unsigned int)(t1005));
        t1020 = (int)(t1017);
        t1021 = (int)(*(int*)((char*)(t1007)));
        if (t1021 != (int)0) {
            FUN_00f47380((unsigned int)(t1021));
        }
        t8 = (int)(t1014 * (int)4);
        t1025 = (int)(t1020 + t8);
        *(int*)((char*)(t1007)) = (int)(t1020);
        *(int*)((char*)(t1007) + 8) = (int)(t1025);
        *(int*)((char*)(t1007) + 4) = (int)(t1025);
        return (int)(t1025);
    }
    t1030 = (int)(*(int*)((char*)(t1007) + 4));
    t1031 = (int)(t1030 - t1008);
    t1032 = (int)(t1031 >> (int)2);
    if ((unsigned int)(t1014) <= (unsigned int)(t1032)) {
        t1033 = (int)FUN_011e0744((unsigned int)(t1008), (unsigned int)(t1000), (unsigned int)(t1011));
        t13 = (int)(t1014 * (int)4);
        t1036 = (int)(t1033 + t13);
        *(int*)((char*)(t1007) + 4) = (int)(t1036);
        return (int)(t1036);
    }
    t14 = (int)(t1032 * (int)4);
    t1041 = (int)(t1000 + t14);
    t1042 = (int)(t1041);
    t1043 = (int)(t1042 - t1000);
    FUN_011e0744((unsigned int)(t1008), (unsigned int)(t1000), (unsigned int)(t1043));
    t1047 = (int)(*(int*)((char*)(t1007) + 4));
    t1048 = (int)(t1005 - t1041);
    t1049 = (int)FUN_011e0744((unsigned int)(t1047), (unsigned int)(t1041), (unsigned int)(t1048));
    t1052 = (int)(t1048 >> (int)2);
    t21 = (int)(t1052 * (int)4);
    t1053 = (int)(t1049 + t21);
    *(int*)((char*)(t1007) + 4) = (int)(t1053);
    return (int)(t1053);
}
