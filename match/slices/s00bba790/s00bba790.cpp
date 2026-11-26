// 0x00bba790: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00bb9950/s00bb9950.cpp.

struct il2c_vc0 {
    virtual void s0();
};

struct C_00aea5d0 { void FUN_00aea5d0(unsigned int, unsigned int); };
struct C_00b8d970 { int FUN_00b8d970(); };
struct C_00bba640 { void FUN_00bba640(); };
struct C_00d01790 { void FUN_00d01790(unsigned int); };
struct C_00e25bd0 { void FUN_00e25bd0(unsigned int, unsigned int); };

// @ 0x00bba790
extern "C" int __fastcall FUN_00bba790(char* self, int edx_unused)
{
    int t1002;
    int t1006;
    int t1007;
    unsigned char t2;
    int t1008;
    int t1011;
    int t1012;
    int t1015;
    int t1016;
    int t1020;
    int t1021;
    int t1022;
    int t1023;
    int t1027;
    int t1028;
    int v_l4;
    int t1029;
    int t1031;
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
    int t1049;
    int t1053;
    int t1054;
    int t1056;
    t1002 = (int)((int)(self));
    ((C_00bba640*)((int)(self)))->FUN_00bba640();
    t1006 = (int)(*(int*)((char*)(t1002) + 92));
    t1007 = (int)((unsigned int)(t1006) >> (int)6);
    t2 = (unsigned char)((unsigned char)(t1007) & (unsigned char)1);
    if (t2 == (unsigned char)0) {
        t1008 = (int)(t1002 + (int)132);
        return (int)(t1008);
    }
    t1011 = (int)(*(int*)((char*)(t1002) + 156));
    t1012 = (int)(*(int*)((char*)(t1002) + 152));
    t1015 = (int)(t1002 + (int)152);
    t1016 = (int)(t1015);
    ((C_00e25bd0*)(t1016))->FUN_00e25bd0((unsigned int)(t1012), (unsigned int)(t1011));
    t1020 = (int)(*(int*)((char*)(t1002) + 136));
    t1021 = (int)(t1020 - (int)*(int*)((char*)(t1002) + 132));
    t1022 = (int)(t1015);
    t1023 = (int)(t1021 >> (int)2);
    ((C_00d01790*)(t1022))->FUN_00d01790((unsigned int)(t1023));
    t1027 = (int)(*(int*)((char*)(t1002) + 136));
    t1028 = (int)(t1027 - (int)*(int*)((char*)(t1002) + 132));
    v_l4 = (int)((int)0);
    t1029 = (int)(t1028 >> (int)2);
    if (t1029 > (int)0) {
        do {
            t1031 = (int)(v_l4);
            t1032 = (int)(*(int*)((char*)(t1002) + 132));
            t1033 = (int)(t1031 + t1031);
            t1034 = (int)(t1033 + t1033);
            t1035 = (int)(*(int*)((char*)(t1034) + t1032));
            t1038 = (int)((C_00b8d970*)(t1035))->FUN_00b8d970();
            if ((unsigned char)(t1038) == (unsigned char)0) {
                t1039 = (int)(*(int*)((char*)(t1002) + 132));
                t1040 = (int)(*(int*)((char*)(t1015) + 4));
                t1041 = (int)(t1039 + t1034);
                if ((unsigned int)(t1040) < (unsigned int)*(int*)((char*)(t1015) + 8)) {
                    t1042 = (int)(t1040 + (int)4);
                    *(int*)((char*)(t1015) + 4) = (int)(t1042);
                    if (t1040 == (int)0) goto Lbba84d;
                    t1043 = (int)(*(int*)((char*)(t1041)));
                    *(int*)((char*)(t1040)) = (int)(t1043);
                    if (t1043 == (int)0) goto Lbba84d;
                    ((il2c_vc0*)(t1043))->s0();
                    goto Lbba84d;
                }
                t1049 = (int)(t1015);
                ((C_00aea5d0*)(t1049))->FUN_00aea5d0((unsigned int)(t1040), (unsigned int)(t1041));
            }
            Lbba84d:;
            t1053 = (int)(v_l4);
            t1054 = (int)(t1053 + (int)1);
            v_l4 = (int)(t1054);
        } while (t1054 < t1029);
    }
    t1056 = (int)(t1015);
    return (int)(t1056);
}
