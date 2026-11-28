// 0x00ba6ab0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00ba6750/s00ba6750.cpp, src/game/SPGonzago/_at_00ba0000.cpp.

extern "C" unsigned char g_01601760[];
struct C_00a68fb0 { int FUN_00a68fb0(unsigned int); };

// @ 0x00ba6ab0
extern "C" int __cdecl FUN_00ba6ab0(int a4)
{
    int t1001;
    int t1002;
    int t1003;
    unsigned char t1;
    int t1004;
    int t1005;
    unsigned char t3;
    int t1006;
    int t1007;
    unsigned char t5;
    int t1008;
    unsigned char t7;
    int t1009;
    int t1010;
    int t1013;
    unsigned char t12;
    int t1015;
    int t1016;
    int t1017;
    int t1018;
    unsigned char t15;
    int t1019;
    int t1020;
    int t1021;
    int t1022;
    unsigned char t18;
    int t1023;
    int t1024;
    unsigned char t1025;
    int t1026;
    int t1029;
    t1001 = (int)((int)(a4));
    t1002 = (int)(*(int*)((char*)(t1001)));
    t1003 = (int)((int)0);
    t1 = (unsigned char)((unsigned char)(t1002) & (unsigned char)1);
    if (t1 != (unsigned char)0) {
        t1003 = (int)((int)1);
    }
    t1004 = (int)(t1002);
    t1005 = (int)((unsigned int)(t1004) >> (int)1);
    t3 = (unsigned char)((unsigned char)(t1005) & (unsigned char)1);
    if (t3 != (unsigned char)0) {
        t1003 = (int)(t1003 + (int)1);
    }
    t1006 = (int)(t1002);
    t1007 = (int)((unsigned int)(t1006) >> (int)2);
    t5 = (unsigned char)((unsigned char)(t1007) & (unsigned char)1);
    if (t5 != (unsigned char)0) {
        t1003 = (int)(t1003 + (int)1);
    }
    t1008 = (int)((unsigned int)(t1002) >> (int)3);
    t7 = (unsigned char)((unsigned char)(t1008) & (unsigned char)1);
    if (t7 != (unsigned char)0) {
        t1003 = (int)(t1003 + (int)1);
    }
    if (t1003 > (int)1) {
        t1009 = (int)((int)g_01601760);
        t1010 = (int)((C_00a68fb0*)(t1009))->FUN_00a68fb0((unsigned int)(t1003));
    } else {
        t1010 = (int)((int)0);
    }
    t1013 = (int)(*(int*)((char*)(t1001)));
    t12 = (unsigned char)((unsigned char)(t1013) & (unsigned char)1);
    if (t12 != (unsigned char)0) {
        t1015 = (int)(t1010);
        t1010 = (int)(t1010 - (int)1);
        if (t1015 == (int)0) {
            t1016 = (int)((int)0);
            return (int)(t1016);
        }
    }
    t1017 = (int)(t1013);
    t1018 = (int)((unsigned int)(t1017) >> (int)1);
    t15 = (unsigned char)((unsigned char)(t1018) & (unsigned char)1);
    if (t15 != (unsigned char)0) {
        t1019 = (int)(t1010);
        t1010 = (int)(t1010 - (int)1);
        if (t1019 == (int)0) {
            t1020 = (int)(t1019 + (int)1);
            return (int)(t1020);
        }
    }
    t1021 = (int)(t1013);
    t1022 = (int)((unsigned int)(t1021) >> (int)2);
    t18 = (unsigned char)((unsigned char)(t1022) & (unsigned char)1);
    if (t18 != (unsigned char)0) {
        if (t1010 == (int)0) {
            t1023 = (int)((int)2);
            return (int)(t1023);
        }
    }
    t1024 = (int)((unsigned int)(t1013) >> (int)3);
    t1025 = (unsigned char)((unsigned char)(t1024) & (unsigned char)1);
    t1026 = (int)(t1025);
    t1029 = (int)(((int)(t1026) != (int)((int)0)) ? (int)((int)3) : (int)((int)0));
    return (int)(t1029);
}
