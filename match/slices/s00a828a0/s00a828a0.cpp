// 0x00a828a0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/Swarm/VisualEffect.cpp, match/slices/s00a820e0/s00a820e0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7(int, int, int);
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual int s8(int, int, int);
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual int s9(int, int);
};

struct C_00a82500 { int FUN_00a82500(unsigned int); };

// @ 0x00a828a0
extern "C" void __fastcall FUN_00a828a0(char* self, int edx_unused)
{
    int t1002;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1010;
    int t1011;
    unsigned char t4;
    int t1012;
    int t1013;
    int t1014;
    int t1017;
    int t1018;
    int t6;
    int t1019;
    int t1023;
    int t1024;
    int t1025;
    int t1026;
    int t1027;
    unsigned char t15;
    int t1028;
    int t1029;
    int t1030;
    int t1033;
    int t1034;
    int t17;
    int t1035;
    int t1038;
    int t1039;
    int t1040;
    int t1041;
    int t1042;
    int t1045;
    int t1046;
    int t1047;
    int t1048;
    int t1049;
    int t1050;
    unsigned char t29;
    int t1051;
    int t1052;
    int t1053;
    t1002 = (int)((int)(self));
    if ((int)*(int*)((char*)(t1002) + 380) != (int)0) {
        t1006 = (int)((int)0);
        goto La828c0;
        t1006 = (int)(t1007);
        La828c0:;
        t1008 = (int)(*(int*)((char*)(t1002) + 380));
        if ((unsigned short)*(unsigned short*)((char*)(t1008) + (t1006)*4 + 2) > (unsigned short)0) {
            t1009 = (int)(*(int*)((char*)(t1002) + 324));
            if (t1009 != (int)*(int*)((char*)(t1002) + 328)) {
                do {
                    t1010 = (int)(*(int*)((char*)(t1009) + 68));
                    t1011 = (int)((unsigned int)(t1010) >> (int)5);
                    t4 = (unsigned char)((unsigned char)(t1011) & (unsigned char)1);
                    if (t4 == (unsigned char)0) {
                        t1012 = (int)(*(int*)((char*)(t1002) + 380));
                        t1013 = (int)(*(unsigned short*)((char*)(t1012) + (t1006)*4 + 2));
                        t1014 = (int)(*(int*)((char*)(t1009) + 56));
                        t1017 = (int)(*(unsigned short*)((char*)(t1012) + (t1006)*4));
                        t1018 = (int)(*(int*)((char*)(t1012) + 100));
                        t6 = (int)(t1017 << (int)2);
                        t1019 = (int)(t1018 + t6);
                        ((il2c_vc0*)(t1014))->s7((int)(t1006), (int)(t1019), (int)(t1013));
                    }
                    t1009 = (int)(t1009 + (int)92);
                } while (t1009 != (int)*(int*)((char*)(t1002) + 328));
            }
        }
        t1006 = (int)(t1006 + (int)1);
        if (t1006 < (int)25) goto La828c0;
        t1023 = (int)((int)0);
        do {
            t1024 = (int)(*(int*)((char*)(t1002) + 380));
            if ((unsigned short)*(unsigned short*)((char*)(t1024) + (t1023)*4 + 122) > (unsigned short)0) {
                t1025 = (int)(*(int*)((char*)(t1002) + 324));
                if (t1025 != (int)*(int*)((char*)(t1002) + 328)) {
                    do {
                        t1026 = (int)(*(int*)((char*)(t1025) + 68));
                        t1027 = (int)((unsigned int)(t1026) >> (int)5);
                        t15 = (unsigned char)((unsigned char)(t1027) & (unsigned char)1);
                        if (t15 == (unsigned char)0) {
                            t1028 = (int)(*(int*)((char*)(t1002) + 380));
                            t1029 = (int)(*(unsigned short*)((char*)(t1028) + (t1023)*4 + 122));
                            t1030 = (int)(*(int*)((char*)(t1025) + 56));
                            t1033 = (int)(*(unsigned short*)((char*)(t1028) + (t1023)*4 + 120));
                            t1034 = (int)(*(int*)((char*)(t1028) + 160));
                            t17 = (int)(t1033 << (int)2);
                            t1035 = (int)(t1034 + t17);
                            t1024 = (int)((il2c_vc1*)(t1030))->s8((int)(t1023), (int)(t1035), (int)(t1029));
                        }
                        t1025 = (int)(t1025 + (int)92);
                    } while (t1025 != (int)*(int*)((char*)(t1002) + 328));
                }
                if (t1023 == (int)3) {
                    t1038 = (int)(*(int*)((char*)(t1002) + 380));
                    t1039 = (int)(*(unsigned short*)((char*)(t1038) + 132));
                    t1040 = (int)(*(int*)((char*)(t1038) + 160));
                    t1041 = (int)(*(int*)((char*)(t1040) + (t1039)*4));
                    t1042 = (int)(t1002);
                    t1024 = (int)((C_00a82500*)(t1042))->FUN_00a82500((unsigned int)(t1041));
                }
            }
            t1023 = (int)(t1023 + (int)1);
        } while (t1023 < (int)10);
        t1045 = (int)((int)0);
        t1046 = (int)((int)180);
        do {
            t1047 = (int)(*(int*)((char*)(t1002) + 380));
            if ((int)*(int*)((char*)(t1046) + t1047) != (int)0) {
                t1048 = (int)(*(int*)((char*)(t1002) + 324));
                if (t1048 != (int)*(int*)((char*)(t1002) + 328)) {
                    do {
                        t1049 = (int)(*(int*)((char*)(t1048) + 68));
                        t1050 = (int)((unsigned int)(t1049) >> (int)5);
                        t29 = (unsigned char)((unsigned char)(t1050) & (unsigned char)1);
                        if (t29 == (unsigned char)0) {
                            t1051 = (int)(*(int*)((char*)(t1002) + 380));
                            t1052 = (int)(*(int*)((char*)(t1048) + 56));
                            t1053 = (int)(*(int*)((char*)(t1046) + t1051));
                            t1024 = (int)((il2c_vc2*)(t1052))->s9((int)(t1045), (int)(t1053));
                        }
                        t1048 = (int)(t1048 + (int)92);
                    } while (t1048 != (int)*(int*)((char*)(t1002) + 328));
                }
            }
            t1046 = (int)(t1046 + (int)4);
            t1045 = (int)(t1045 + (int)1);
        } while (t1046 < (int)216);
    }
    return;
}
