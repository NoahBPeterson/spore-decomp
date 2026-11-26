// 0x00a987c0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/Swarm/LightDescription.cpp, match/slices/s00a987c0/s00a987c0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6(int, int);
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6(int, int);
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6(int, int);
};
struct il2c_vc3 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6(int, int);
};
struct il2c_vc4 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6(int, int);
};
struct il2c_vc5 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual int s6(int, int);
};

extern "C" unsigned char g_01458870[];
extern "C" unsigned char g_01458888[];
extern "C" unsigned char g_014588a0[];
extern "C" unsigned char g_014588b8[];
extern "C" unsigned char g_014588d0[];
extern "C" unsigned char g_014588e8[];
extern "C" unsigned char g_01458900[];
extern "C" unsigned char g_0145891c[];
extern "C" unsigned char g_01458930[];
extern "C" unsigned char g_01458948[];
extern "C" unsigned char g_01458960[];
extern "C" unsigned char g_01458974[];
extern "C" unsigned char g_01565230[];
extern "C" unsigned char g_01565234[];
extern "C" unsigned char g_01565238[];
extern "C" unsigned char g_0156523c[];
extern "C" unsigned char g_01565240[];
extern "C" unsigned char g_01565244[];
struct C_0083c780 { void FUN_0083c780(unsigned int, unsigned int); };
struct C_0083c800 { void FUN_0083c800(); };
extern "C" int __cdecl FUN_00f473a0(...);
struct C_00fd9450 { void FUN_00fd9450(unsigned int); };

// @ 0x00a987c0
extern "C" void __fastcall FUN_00a987c0(char* self, int edx_unused, int a4, int a8)
{
    int t1002;
    int t1003;
    int t1005;
    int t1006;
    int t1007;
    int t1011;
    int t1012;
    int t1018;
    int t1019;
    int t1020;
    int t1025;
    int t1027;
    int t1033;
    int t1034;
    int t1035;
    int t1039;
    int t1042;
    int t1048;
    int t1049;
    int t1050;
    int t1054;
    int t1057;
    int t1063;
    int t1064;
    int t1065;
    int t1069;
    int t1072;
    int t1078;
    int t1079;
    int t1080;
    int t1084;
    int t1087;
    int t1093;
    int t1094;
    int t1095;
    int t1099;
    int t1102;
    t1002 = (int)((int)(self));
    t1003 = (int)((int)(a8));
    if (t1003 != (int)0) {
        t1005 = (int)(t1003 + (int)(-12));
    } else {
        t1005 = (int)((int)0);
    }
    *(int*)((char*)(t1002) + 48) = (int)(t1005);
    t1006 = (int)((int)(a4));
    t1007 = (int)(t1002);
    ((C_0083c780*)(t1007))->FUN_0083c780((unsigned int)(t1006), (unsigned int)(t1003));
    t1011 = (int)(t1002 + (int)52);
    t1012 = (int)(t1002);
    ((C_00fd9450*)(t1012))->FUN_00fd9450((unsigned int)(t1011));
    t1018 = (int)FUN_00f473a0((unsigned int)((int)16), (unsigned int)((int)g_01458974), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
    t1019 = (int)(t1018);
    if (t1019 != (int)0) {
        t1020 = (int)(t1019);
        ((C_0083c800*)(t1020))->FUN_0083c800();
        *(int*)((char*)(t1019)) = (int)((int)g_01458870);
    } else {
        t1019 = (int)((int)0);
    }
    t1025 = (int)((int)(*(int*)g_01565230));
    t1027 = (int)(t1002);
    ((il2c_vc0*)(t1027))->s6((int)(t1025), (int)(t1019));
    t1033 = (int)FUN_00f473a0((unsigned int)((int)16), (unsigned int)((int)g_01458960), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
    t1034 = (int)(t1033);
    if (t1034 != (int)0) {
        t1035 = (int)(t1034);
        ((C_0083c800*)(t1035))->FUN_0083c800();
        *(int*)((char*)(t1034)) = (int)((int)g_01458888);
    } else {
        t1034 = (int)((int)0);
    }
    t1039 = (int)((int)(*(int*)g_01565234));
    t1042 = (int)(t1002);
    ((il2c_vc1*)(t1042))->s6((int)(t1039), (int)(t1034));
    t1048 = (int)FUN_00f473a0((unsigned int)((int)16), (unsigned int)((int)g_01458948), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
    t1049 = (int)(t1048);
    if (t1049 != (int)0) {
        t1050 = (int)(t1049);
        ((C_0083c800*)(t1050))->FUN_0083c800();
        *(int*)((char*)(t1049)) = (int)((int)g_014588a0);
    } else {
        t1049 = (int)((int)0);
    }
    t1054 = (int)((int)(*(int*)g_01565238));
    t1057 = (int)(t1002);
    ((il2c_vc2*)(t1057))->s6((int)(t1054), (int)(t1049));
    t1063 = (int)FUN_00f473a0((unsigned int)((int)16), (unsigned int)((int)g_01458930), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
    t1064 = (int)(t1063);
    if (t1064 != (int)0) {
        t1065 = (int)(t1064);
        ((C_0083c800*)(t1065))->FUN_0083c800();
        *(int*)((char*)(t1064)) = (int)((int)g_014588b8);
    } else {
        t1064 = (int)((int)0);
    }
    t1069 = (int)((int)(*(int*)g_0156523c));
    t1072 = (int)(t1002);
    ((il2c_vc3*)(t1072))->s6((int)(t1069), (int)(t1064));
    t1078 = (int)FUN_00f473a0((unsigned int)((int)16), (unsigned int)((int)g_0145891c), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
    t1079 = (int)(t1078);
    if (t1079 != (int)0) {
        t1080 = (int)(t1079);
        ((C_0083c800*)(t1080))->FUN_0083c800();
        *(int*)((char*)(t1079)) = (int)((int)g_014588d0);
    } else {
        t1079 = (int)((int)0);
    }
    t1084 = (int)((int)(*(int*)g_01565240));
    t1087 = (int)(t1002);
    ((il2c_vc4*)(t1087))->s6((int)(t1084), (int)(t1079));
    t1093 = (int)FUN_00f473a0((unsigned int)((int)16), (unsigned int)((int)g_01458900), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
    t1094 = (int)(t1093);
    if (t1094 != (int)0) {
        t1095 = (int)(t1094);
        ((C_0083c800*)(t1095))->FUN_0083c800();
        *(int*)((char*)(t1094)) = (int)((int)g_014588e8);
    } else {
        t1094 = (int)((int)0);
    }
    t1099 = (int)((int)(*(int*)g_01565244));
    t1102 = (int)(t1002);
    ((il2c_vc5*)(t1102))->s6((int)(t1099), (int)(t1094));
    return;
}
