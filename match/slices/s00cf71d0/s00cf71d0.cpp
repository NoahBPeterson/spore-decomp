// 0x00cf71d0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/_at_00cf0000.cpp, match/slices/s00cf6df0/s00cf6df0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
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
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual int s12(int);
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
    virtual void s8(int, int, int);
};

extern "C" unsigned char g_00dbdba1[];
extern "C" unsigned char g_013ec4d0[];
extern "C" unsigned char g_014788a8[];
extern "C" unsigned char g_014788c8[];
extern "C" unsigned char g_0169cb78[];
extern "C" unsigned char g_0169cb7c[];
extern "C" unsigned char g_0169cb80[];
extern "C" unsigned char g_0169cb84[];
extern "C" int __stdcall FUN_0067cab0(unsigned int);
extern "C" int __cdecl FUN_0067dd30(...);
struct C_00801bb0 { void FUN_00801bb0(); };
struct C_00b22960 { void FUN_00b22960(); };
struct C_00b316d0 { int FUN_00b316d0(); };
extern "C" int __stdcall FUN_00b3d230(unsigned int);
extern "C" int __cdecl FUN_00b3d250(...);
extern "C" int __cdecl FUN_00b3d280(...);
extern "C" int __cdecl FUN_00b3d300(...);
extern "C" int __stdcall FUN_00b3d380(float, float, float, float);
struct C_00b5cde0 { void FUN_00b5cde0(); };
struct C_00cea090 { void FUN_00cea090(); };
struct C_00ceb090 { int FUN_00ceb090(unsigned int); };
struct C_00cf14d0 { void FUN_00cf14d0(); };
struct C_00cf1500 { void FUN_00cf1500(unsigned int); };
struct C_00cf28f0 { void FUN_00cf28f0(); };
struct C_00cf4c00 { void FUN_00cf4c00(unsigned int); };
struct C_00cf4ca0 { int FUN_00cf4ca0(unsigned int); };
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x00cf71d0
extern "C" void __fastcall FUN_00cf71d0(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1005;
    int t1006;
    int t1009;
    int t1010;
    int t1012;
    int t1018;
    int t1024;
    int t1026;
    int t1030;
    int t1031;
    int t1037;
    int t1038;
    int t1041;
    int t1042;
    int t1048;
    int t1049;
    int t1055;
    int t1056;
    int t1059;
    int t1060;
    int t1065;
    int t1071;
    int t1072;
    int t1078;
    int t1079;
    int t1085;
    float t1086;
    int t1089;
    int t1090;
    int t1096;
    int t1097;
    t1002 = (int)((int)(self));
    if ((int)*(int*)((char*)(t1002) + 232) == (int)0) {
        t1005 = (int)FUN_00f473a0((unsigned int)((int)328), (unsigned int)((int)g_014788c8), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
        if (t1005 != (int)0) {
            t1006 = (int)(t1005);
            t1009 = (int)((C_00cf4ca0*)(t1006))->FUN_00cf4ca0((unsigned int)(t1002));
        } else {
            t1009 = (int)((int)0);
        }
        *(int*)((char*)(t1002) + 232) = (int)(t1009);
    }
    t1010 = (int)(*(int*)((char*)(t1002) + 232));
    t1012 = (int)((int)(a4));
    if (t1010 != (int)0) {
        ((il2c_vc0*)(t1010))->s1();
        if (t1012 == (int)g_00dbdba1) {
            t1018 = (int)(*(int*)((char*)(t1002) + 232));
            ((C_00cf14d0*)(t1018))->FUN_00cf14d0();
        }
        t1024 = (int)FUN_0067dd30();
        t1026 = (int)(t1024);
        t1030 = (int)((il2c_vc1*)(t1026))->s12((int)((int)108640371));
        t1031 = (int)(*(int*)((char*)(t1002) + 232));
        ((C_00cf4c00*)(t1031))->FUN_00cf4c00((unsigned int)(t1030));
    }
    t1037 = (int)FUN_00b3d250();
    t1038 = (int)(*(int*)((char*)(t1002) + 232));
    t1041 = (int)(t1038 + (int)4);
    t1042 = (int)(t1037);
    ((il2c_vc2*)(t1042))->s8((int)(t1041), (int)((int)0), (int)((int)0));
    t1048 = (int)FUN_00b3d300();
    t1049 = (int)(t1048);
    ((C_00b22960*)(t1049))->FUN_00b22960();
    if ((int)*(int*)((char*)(t1002) + 236) == (int)0) {
        t1055 = (int)FUN_00f473a0((unsigned int)((int)288), (unsigned int)((int)g_014788a8), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
        if (t1055 != (int)0) {
            t1056 = (int)(t1055);
            t1059 = (int)((C_00ceb090*)(t1056))->FUN_00ceb090((unsigned int)(t1002));
        } else {
            t1059 = (int)((int)0);
        }
        t1060 = (int)(t1059);
        *(int*)((char*)(t1002) + 236) = (int)(t1059);
        ((C_00cea090*)(t1060))->FUN_00cea090();
    }
    if (t1012 != (int)g_00dbdba1) {
        t1065 = (int)(*(int*)((char*)(t1002) + 232));
        ((C_00cf1500*)(t1065))->FUN_00cf1500((unsigned int)((int)1));
    }
    t1071 = (int)FUN_0067cab0((unsigned int)((int)4098));
    t1072 = (int)(t1071);
    ((C_00801bb0*)(t1072))->FUN_00801bb0();
    t1078 = (int)FUN_00b3d230((unsigned int)((int)(-486181354)));
    t1079 = (int)(t1078);
    ((C_00b5cde0*)(t1079))->FUN_00b5cde0();
    t1085 = (int)FUN_00b3d280();
    t1086 = (float)((float)(*(float*)g_013ec4d0));
    *(float*)((char*)(t1085) + 896) = (float)(t1086);
    t1089 = (int)FUN_00b3d280();
    *(int*)((char*)(t1089) + 900) = (int)((int)1001);
    t1090 = (int)(*(int*)((char*)(t1002) + 232));
    ((C_00cf28f0*)(t1090))->FUN_00cf28f0();
    t1096 = (int)FUN_00b3d380((float)((float)(*(float*)g_0169cb78)), (float)((float)(*(float*)g_0169cb7c)), (float)((float)(*(float*)g_0169cb80)), (float)((float)(*(float*)g_0169cb84)));
    t1097 = (int)(t1096);
    ((C_00b316d0*)(t1097))->FUN_00b316d0();
    return;
}
