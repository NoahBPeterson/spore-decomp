// 0x0104fa90: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPToolManager.cpp, match/slices/s0104f2a0/s0104f2a0.cpp.

struct il2c_vc0 {
    virtual void s0();
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
    virtual void s12();
    virtual void s13();
    virtual void s14(int);
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3(int);
};
struct il2c_vc3 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc4 {
    virtual void s0();
    virtual int s1();
};

extern "C" unsigned char g_01654c05[];
struct C_00a1ad60 { int FUN_00a1ad60(); };
extern "C" int __stdcall FUN_00b3d390(unsigned int);
extern "C" int __cdecl FUN_00b5b800(...);
struct C_00bc3170 { void FUN_00bc3170(); };
struct C_00ff4540 { void FUN_00ff4540(unsigned int); };
extern "C" int __cdecl FUN_00ffbe50(...);
extern "C" int __cdecl FUN_01002bd0(...);
struct C_0104cc40 { int FUN_0104cc40(); };
struct C_0104f850 { int FUN_0104f850(); };
struct C_01065ed0 { void FUN_01065ed0(); };
extern "C" int __cdecl FUN_010666a0(...);

// @ 0x0104fa90
extern "C" bool __stdcall FUN_0104fa90(int a4)
{
    int t1001;
    int t1002;
    int t1008;
    int t1009;
    int t1012;
    int t1013;
    int t1016;
    int t1017;
    int t1020;
    int t1023;
    int t1029;
    int t1033;
    int t1036;
    int t1039;
    int t1040;
    int t1043;
    int t1044;
    int t1048;
    int t1054;
    int t1057;
    int t1058;
    int t1061;
    int t1062;
    int t1065;
    int t1066;
    int t1070;
    int t1071;
    int t1072;
    int t1078;
    int t1086;
    bool t1092;
    bool t1095;
    t1001 = (int)((int)(a4));
    if (t1001 != (int)0) {
        t1002 = (int)(*(int*)((char*)(t1001) + 376));
        if (t1002 != (int)0) {
            t1008 = (int)FUN_00b3d390((unsigned int)(t1002));
            t1009 = (int)(t1008);
            t1012 = (int)((C_0104f850*)(t1009))->FUN_0104f850();
            t1013 = (int)(t1012);
            if (t1013 != (int)0) goto L104fad3;
        }
        t1016 = (int)FUN_00b3d390((unsigned int)((int)(-1327871527)));
        t1017 = (int)(t1016);
        t1020 = (int)((C_0104f850*)(t1017))->FUN_0104f850();
        t1013 = (int)(t1020);
        if (t1013 == (int)0) goto L104fadb;
        L104fad3:;
        t1023 = (int)(t1013);
        ((il2c_vc0*)(t1023))->s0();
        L104fadb:;
        t1029 = (int)(t1013);
        ((il2c_vc1*)(t1029))->s14((int)(t1001));
        t1033 = (int)(t1001);
        t1036 = (int)((C_0104cc40*)(t1033))->FUN_0104cc40();
        if ((unsigned char)(t1036) != (unsigned char)0) {
            t1039 = (int)FUN_01002bd0();
            t1040 = (int)(t1039);
            t1043 = (int)((C_00a1ad60*)(t1040))->FUN_00a1ad60();
            if (t1043 != (int)0) {
                t1044 = (int)(t1043);
                ((C_00ff4540*)(t1044))->FUN_00ff4540((unsigned int)(t1001));
            }
        }
        t1048 = (int)(t1001 + (int)200);
        *(unsigned char*)((char*)(t1001) + 128) = (unsigned char)((int)0);
        ((C_00bc3170*)(t1048))->FUN_00bc3170();
        t1054 = (int)FUN_00b5b800();
        if (t1054 == (int)g_01654c05) {
            t1057 = (int)FUN_00ffbe50();
            t1058 = (int)(t1057);
            t1061 = (int)((C_00a1ad60*)(t1058))->FUN_00a1ad60();
            if (t1061 != (int)0) {
                t1062 = (int)(t1061 + (int)52);
            } else {
                t1062 = (int)((int)0);
            }
            if ((int)*(int*)((char*)(t1001) + 276) == t1062) {
                t1065 = (int)FUN_010666a0();
                t1066 = (int)(t1065);
                ((C_01065ed0*)(t1066))->FUN_01065ed0();
            }
        }
        t1070 = (int)(t1001 + (int)264);
        t1071 = (int)((int)3);
        do {
            t1072 = (int)(*(int*)((char*)(t1070)));
            if (t1072 != (int)0) {
                ((il2c_vc2*)(t1072))->s3((int)((int)0));
                t1078 = (int)(*(int*)((char*)(t1070)));
                if (t1078 != (int)0) {
                    *(int*)((char*)(t1070)) = (int)((int)0);
                    ((il2c_vc3*)(t1078))->s1();
                }
            }
            t1070 = (int)(t1070 + (int)4);
            t1071 = (int)(t1071 - (int)1);
        } while (t1071 != (int)0);
        t1086 = (int)(t1013);
        ((il2c_vc4*)(t1086))->s1();
        t1092 = true;
        return (bool)(t1092);
    }
    t1095 = false;
    return (bool)(t1095);
}
