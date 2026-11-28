// 0x00c56360: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPMissionGenericPressure.cpp, match/slices/s00c562b0/s00c562b0.cpp.

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
    virtual int s9(int, int);
};

extern "C" unsigned char g_01667bac[];
extern "C" unsigned char g_01667bae[];
struct C_0041e990 { int FUN_0041e990(); };
struct C_004558a0 { void FUN_004558a0(unsigned int, unsigned int); };
struct C_00b3d3e0 { int FUN_00b3d3e0(unsigned int, unsigned int); };
extern "C" int __stdcall FUN_00b3d3e0(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
struct C_00c45cf0 { void FUN_00c45cf0(unsigned int); };
struct C_00c485b0 { void FUN_00c485b0(); };
struct C_00c487d0 { void FUN_00c487d0(unsigned int, unsigned int); };
struct C_00c4ad50 { bool FUN_00c4ad50(); };
struct C_00c71430 { void FUN_00c71430(unsigned int, unsigned int); };
struct C_00dd6df0 { void FUN_00dd6df0(); };
struct C_00dd8640 { int FUN_00dd8640(); };
extern "C" int __cdecl FUN_00f47380(...);

// @ 0x00c56360
extern "C" bool __fastcall FUN_00c56360(char* self, int edx_unused)
{
    int t1003;
    int t1004;
    int t1007;
    int v_l20;
    int t1008;
    int t1011;
    int t1012;
    int t1015;
    int t1016;
    int t1017;
    int t1020;
    bool t1021;
    int t1025;
    int t1026;
    int t1030;
    int v_l16[4];
    int t1031;
    int t1032;
    int t1036;
    int t1039;
    int t1040;
    int t1043;
    int t1044;
    int t1047;
    int t1051;
    int t1052;
    int t1053;
    int t1055;
    int t1057;
    int t1061;
    int t1065;
    int t1066;
    int t1067;
    int t1068;
    int t1069;
    bool t1073;
    t1003 = (int)((int)(self));
    t1004 = (int)(*(int*)((char*)(t1003) + 384));
    if (t1004 != (int)0) {
        t1007 = (int)((int)&v_l20);
        t1008 = (int)((il2c_vc0*)(t1004))->s9((int)((int)51980651), (int)(t1007));
        if ((unsigned char)(t1008) != (unsigned char)0) {
            t1011 = (int)(v_l20);
            if ((unsigned short)*(unsigned short*)((char*)(t1011) + 18) == (unsigned short)9) {
                t1012 = (int)((C_0041e990*)(t1011))->FUN_0041e990();
                t1015 = (int)(*(int*)((char*)(t1012)));
                *(int*)((char*)(t1003) + 496) = (int)(t1015);
            }
        }
    }
    t1016 = (int)(t1003);
    t1021 = ((C_00c4ad50*)(t1016))->FUN_00c4ad50();
    t1020 = (int)(t1003);
    ((C_00c485b0*)(t1020))->FUN_00c485b0();
    t1025 = (int)(*(int*)((char*)(t1003) + 156));
    t1026 = (int)(t1003);
    ((C_00c45cf0*)(t1026))->FUN_00c45cf0((unsigned int)(t1025));
    t1030 = (int)((int)g_01667bac);
    (*(int*)&v_l16[0]) = (int)(t1030);
    (*(int*)&v_l16[1]) = (int)(t1030);
    t1031 = (int)((int)&v_l16);
    t1032 = (int)(t1003);
    (*(int*)&v_l16[2]) = (int)((int)g_01667bae);
    ((C_00c487d0*)(t1032))->FUN_00c487d0((unsigned int)((int)(-169274508)), (unsigned int)(t1031));
    t1036 = (int)FUN_00b3d3e0((unsigned int)((int)1581317305), (unsigned int)((int)320511828), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)1), (unsigned int)((int)0));
    t1039 = (int)(t1036);
    t1040 = (int)((C_00dd8640*)(t1039))->FUN_00dd8640();
    t1043 = (int)((*(int*)&v_l16[0]));
    *(int*)((char*)(t1003) + 500) = (int)(t1040);
    t1044 = (int)((C_00b3d3e0*)(t1043))->FUN_00b3d3e0((unsigned int)(t1040), (unsigned int)(t1043));
    t1047 = (int)(t1044);
    ((C_00dd6df0*)(t1047))->FUN_00dd6df0();
    t1051 = (int)(*(int*)((char*)(t1003) + 312));
    t1052 = (int)(*(int*)((char*)(t1003) + 500));
    t1053 = (int)(t1003 + (int)308);
    v_l20 = (int)(t1052);
    if ((unsigned int)(t1051) < (unsigned int)*(int*)((char*)(t1053) + 8)) {
        t1055 = (int)(t1051 + (int)4);
        *(int*)((char*)(t1053) + 4) = (int)(t1055);
        if (t1051 == (int)0) goto Lc5644e;
        *(int*)((char*)(t1051)) = (int)(t1052);
        goto Lc5644e;
    }
    t1057 = (int)((int)&v_l20);
    ((C_004558a0*)(t1053))->FUN_004558a0((unsigned int)(t1051), (unsigned int)(t1057));
    Lc5644e:;
    t1061 = (int)(*(int*)((char*)(t1003) + 156));
    ((C_00c71430*)(t1061))->FUN_00c71430((unsigned int)((int)3), (unsigned int)((int)1));
    t1065 = (int)(*(int*)((char*)(t1003) + 156));
    *(unsigned char*)((char*)(t1065) + 440) += (unsigned char)1;
    t1066 = (int)((*(int*)&v_l16[2]));
    t1067 = (int)((*(int*)&v_l16[0]));
    t1068 = (int)(t1066 - t1067);
    t1069 = (int)(t1068 & (int)(-2));
    if (t1069 > (int)2) {
        if (t1067 != (int)0) {
            t1067 = (int)FUN_00f47380((unsigned int)(t1067));
        }
    }
    t1073 = t1021;
    return t1073;
}
