// 0x0062c7e0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0062bb40/s0062bb40.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22(int, int, int, int);
};

extern "C" unsigned char g_013fe160[];
struct C_00582fe0 { int FUN_00582fe0(unsigned int, unsigned int); };
struct C_0059aea0 { void FUN_0059aea0(unsigned int); };
struct C_0059ca70 { int FUN_0059ca70(unsigned int); };
struct C_0059cac0 { int FUN_0059cac0(unsigned int); };
struct C_00628f10 { void FUN_00628f10(unsigned int); };
struct C_00629110 { int FUN_00629110(); };
struct C_006298b0 { int FUN_006298b0(unsigned int); };
struct C_0062bb40 { void FUN_0062bb40(unsigned int, unsigned int); };
struct C_0062f6c0 { int FUN_0062f6c0(); };
struct C_0063b570 { int FUN_0063b570(unsigned int, unsigned int); };
struct C_00a04a90 { void FUN_00a04a90(unsigned int); };

// @ 0x0062c7e0
extern "C" bool __fastcall FUN_0062c7e0(char* self, int edx_unused, int a4, int a8)
{
    int t1002;
    int t1003;
    int t1004;
    int t1007;
    int t1009;
    int t1012;
    int t1013;
    int t1014;
    int t1015;
    int t1019;
    float t1020;
    int t1021;
    float t1022;
    int t1023;
    int t1026;
    int t1027;
    int t1028;
    int t1032;
    int t1033;
    int t1036;
    int t1037;
    int t1041;
    int t1045;
    int t1046;
    int t1050;
    int t1051;
    int t1052;
    int t1053;
    int t1056;
    int t1059;
    int v_l4;
    int t1060;
    int t1064;
    int t1065;
    int t1069;
    bool t1073;
    bool t1076;
    t1002 = (int)((int)(self));
    if ((unsigned char)*(unsigned char*)((char*)(t1002) + 14032) < (unsigned char)3) {
        t1003 = (int)((int)(a8));
        t1004 = (int)(*(int*)((char*)(t1002) + 13844));
        t1007 = (int)((C_00582fe0*)(t1004))->FUN_00582fe0((unsigned int)((int)1), (unsigned int)(t1003));
        if ((unsigned char)(t1007) != (unsigned char)0) {
            *(unsigned char*)((char*)(t1002) + 14032) += (unsigned char)1;
            t1009 = (int)(t1002);
            t1012 = (int)((C_00629110*)(t1009))->FUN_00629110();
            t1013 = (int)(t1012);
            if (t1013 != (int)(-1)) {
                t1014 = (int)(*(int*)((char*)(t1002) + 13844));
                t1015 = (int)(*(int*)((char*)(t1014) + 864));
                t1019 = (int)((C_0059cac0*)(t1015))->FUN_0059cac0((unsigned int)(t1013));
                t1020 = (float)((float)(*(float*)g_013fe160));
                t1021 = (int)(t1019);
                *(float*)((char*)(t1021) + 116) = (float)(t1020);
                t1022 = (float)((float)0);
                t1023 = (int)(t1002 + (int)13848);
                *(float*)((char*)(t1021) + 120) = (float)(t1022);
                t1026 = (int)((C_0062f6c0*)(t1023))->FUN_0062f6c0();
                *(unsigned char*)&(a8) = (unsigned char)((unsigned char)(t1026));
                t1027 = (int)((int)(a8));
                t1028 = (int)(t1021);
                ((C_0059aea0*)(t1028))->FUN_0059aea0((unsigned int)(t1027));
                t1032 = (int)(*(int*)((char*)(t1002) + 13844));
                t1033 = (int)(*(int*)((char*)(t1032) + 864));
                t1036 = (int)((C_0059ca70*)(t1033))->FUN_0059ca70((unsigned int)(t1013));
                t1037 = (int)(t1036);
                ((C_00a04a90*)(t1037))->FUN_00a04a90((unsigned int)((int)1));
                t1041 = (int)(t1002);
                ((C_00628f10*)(t1041))->FUN_00628f10((unsigned int)(t1013));
                t1045 = (int)((int)(a4));
                *(unsigned char*)((char*)(t1002) + 31) = (unsigned char)((int)1);
                *(int*)((char*)(t1002) + (t1045)*4 + 14040) = (int)(t1013);
                t1046 = (int)(t1002);
                ((C_0062bb40*)(t1046))->FUN_0062bb40((unsigned int)(t1013), (unsigned int)((int)1));
                t1050 = (int)(*(int*)((char*)(t1002) + 13844));
                t1051 = (int)(*(int*)((char*)(t1050) + 868));
                t1052 = (int)(*(int*)((char*)(t1050) + 864));
                t1053 = (int)(t1052);
                t1056 = (int)((C_0059ca70*)(t1053))->FUN_0059ca70((unsigned int)(t1051));
                t1059 = (int)((int)&v_l4);
                t1060 = (int)(t1056);
                ((il2c_vc0*)(t1060))->s22((int)(t1059), (int)((int)0), (int)((int)0), (int)((int)0));
                t1064 = (int)(v_l4);
                t1065 = (int)(t1002 + (int)4528);
                t1012 = (int)((C_0063b570*)(t1065))->FUN_0063b570((unsigned int)(t1064), (unsigned int)((int)0));
                if ((unsigned char)(t1012) != (unsigned char)0) {
                    t1069 = (int)(t1002);
                    t1012 = (int)((C_006298b0*)(t1069))->FUN_006298b0((unsigned int)(t1013));
                }
            }
            t1073 = true;
            return (bool)(t1073);
        }
    }
    t1076 = false;
    return (bool)(t1076);
}
