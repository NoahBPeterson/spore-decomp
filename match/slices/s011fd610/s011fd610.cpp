// 0x011fd610: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s011fd3a0/s011fd3a0.cpp.

struct il2c_gm0 { void m(unsigned int, unsigned int, unsigned int, unsigned int); };
typedef void (il2c_gm0::*il2c_gp0)(unsigned int, unsigned int, unsigned int, unsigned int);

extern "C" unsigned char g_013cc1c8[];
extern "C" unsigned char g_015d0938[];

// @ 0x011fd610
extern "C" int __fastcall FUN_011fd610(char* self, int edx_unused)
{
    int t1002;
    int t1003;
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1011;
    int t1013;
    int t1016;
    int t1017;
    int t1018;
    int t1019;
    int t1020;
    int t1021;
    int t1022;
    int t1023;
    int t1024;
    int t1028;
    int t1029;
    int t1030;
    int t1031;
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
    t1002 = (int)((int)(self));
    t1003 = (int)(*(int*)((char*)(t1002) + 12));
    t1004 = (int)((int)0);
    if (t1003 != (int)0) {
        t1005 = (int)(t1003 + (int)(-1));
        t1006 = (int)(*(int*)((char*)(t1002) + 16));
        *(int*)((char*)(t1002) + 12) = (int)(t1005);
        t1007 = (int)(*(unsigned short*)((char*)(t1006) + (t1005)*2));
        t1008 = (int)(t1007 * (int)*(int*)((char*)(t1002)));
        t1009 = (int)(t1008 + (int)*(int*)((char*)(t1002) + 8));
        return (int)(t1009);
    }
    t1011 = (int)((int)(*(int*)g_015d0938));
    t1013 = (int)(*(int*)((char*)(t1002) + 4));
    if ((unsigned int)(t1013) < (unsigned int)(t1011)) {
        t1016 = (int)(t1013);
        t1017 = (int)((unsigned int)(t1016) >> (int)1);
        t1018 = (int)(t1017 + (int)1);
        t1019 = (int)(t1018 + t1013);
        if ((unsigned int)(t1019) > (unsigned int)(t1011)) {
            t1020 = (int)(t1011);
            t1018 = (int)(t1020 - t1013);
            t1019 = (int)(t1011);
        }
        t1021 = (int)(*(int*)((char*)(t1002)));
        t1022 = (int)(*(int*)((char*)(t1002) + 8));
        t1023 = (int)(t1021 + (int)2);
        t1024 = (int)(t1023 * t1019);
        *(int*)((char*)(t1002) + 4) = (int)(t1019);
        *(int*)((char*)(t1002) + 12) = (int)(t1018);
        (((il2c_gm0*)(t1011))->*(*(il2c_gp0*)g_013cc1c8))((unsigned int)(t1022), (unsigned int)(t1024), (unsigned int)((int)1052672), (unsigned int)((int)4));
        t1028 = (int)(*(int*)((char*)(t1002)));
        t1029 = (int)(*(int*)((char*)(t1002) + 8));
        t1030 = (int)(t1028 * t1019);
        t1031 = (int)(t1030 + t1029);
        t1032 = (int)((int)0);
        *(int*)((char*)(t1002) + 16) = (int)(t1031);
        if ((unsigned int)(t1018) > (unsigned int)0) {
            do {
                t1033 = (int)(*(int*)((char*)(t1002) + 16));
                t1034 = (int)(t1019);
                t1035 = (int)(t1034 - t1032);
                t1036 = (int)(t1035 - (int)1);
                *(unsigned short*)((char*)(t1033) + (t1032)*2) = (unsigned short)((unsigned short)(t1036));
                t1032 = (int)(t1032 + (int)1);
            } while ((unsigned int)(t1032) < (unsigned int)(t1018));
        }
        t1037 = (int)(*(int*)((char*)(t1002)));
        t1038 = (int)(*(int*)((char*)(t1002) + 12));
        t1039 = (int)(t1037 * t1013);
        t1040 = (int)(*(int*)((char*)(t1002) + 8));
        t1041 = (int)(t1038 - (int)1);
        *(int*)((char*)(t1002) + 12) = (int)(t1041);
        t1004 = (int)(t1039 + t1040);
    }
    return (int)(t1004);
}
