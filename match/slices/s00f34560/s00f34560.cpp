// 0x00f34560: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00f338c0/s00f338c0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual int s3(int);
};
struct il2c_vc1 {
    virtual void s0();
};
struct il2c_vc2 {
    virtual void s0();
};
struct il2c_vc3 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc4 {
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
    virtual void s11(int);
};
struct il2c_vc5 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc6 {
    virtual void s0();
    virtual void s1();
};

extern "C" unsigned char g_013f09b4[];
extern "C" unsigned char g_016065d8[];
extern "C" unsigned char g_016065f8[];
extern "C" unsigned char g_016065fc[];
struct C_006a1710 { void FUN_006a1710(unsigned int); };
struct C_006a1c40 { int FUN_006a1c40(); };
struct C_00f32d10 { void FUN_00f32d10(); };
struct C_00f342d0 { void FUN_00f342d0(unsigned int); };
struct C_00f41180 { void FUN_00f41180(unsigned int); };
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x00f34560
extern "C" void __fastcall FUN_00f34560(char* self, int edx_unused)
{
    int t1002;
    int t1003;
    int t1009;
    int t1010;
    int t1014;
    int t1020;
    int t1021;
    int t1024;
    int t1025;
    int t1027;
    int t1030;
    int t1036;
    int t1040;
    int t1041;
    int t1045;
    int t1049;
    int t1053;
    int t1054;
    int t1055;
    int t1059;
    int t1060;
    int t1064;
    int t1068;
    int t1077;
    t1002 = (int)((int)(self));
    t1003 = (int)((int)(*(int*)g_016065fc));
    if (t1003 != (int)0) {
        t1009 = (int)((il2c_vc0*)(t1003))->s3((int)((int)121523972));
        t1010 = (int)(t1009);
        if (t1010 != (int)0) {
            t1014 = (int)(t1010);
            ((il2c_vc1*)(t1014))->s0();
            t1020 = (int)FUN_00f473a0((unsigned int)((int)56), (unsigned int)((int)g_013f09b4), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
            if (t1020 != (int)0) {
                t1021 = (int)(t1020);
                t1024 = (int)((C_006a1c40*)(t1021))->FUN_006a1c40();
                t1025 = (int)(t1024);
            } else {
                t1025 = (int)((int)0);
            }
            t1027 = (int)(*(int*)((char*)(t1010) + 36));
            if (t1025 != t1027) {
                if (t1025 != (int)0) {
                    t1030 = (int)(t1025);
                    ((il2c_vc2*)(t1030))->s0();
                }
                *(int*)((char*)(t1010) + 36) = (int)(t1025);
                if (t1027 != (int)0) {
                    t1036 = (int)(t1027);
                    ((il2c_vc3*)(t1036))->s1();
                }
            }
            t1040 = (int)(*(int*)((char*)(t1010) + 36));
            t1041 = (int)(t1002);
            ((C_00f32d10*)(t1041))->FUN_00f32d10();
            t1045 = (int)(*(int*)((char*)(t1002) + 12));
            if (t1040 != t1045) {
                t1049 = (int)(t1040);
                ((il2c_vc4*)(t1049))->s11((int)(t1045));
                t1053 = (int)(*(int*)((char*)(t1002) + 12));
                t1054 = (int)(*(int*)((char*)(t1053) + 48));
                t1055 = (int)(t1040);
                ((C_006a1710*)(t1055))->FUN_006a1710((unsigned int)(t1054));
            }
            t1059 = (int)(*(int*)((char*)(t1002) + 408));
            t1060 = (int)(t1010 + (int)40);
            ((C_00f41180*)(t1059))->FUN_00f41180((unsigned int)(t1060));
            t1064 = (int)((int)g_016065d8);
            *(unsigned char*)g_016065f8 = (unsigned char)((int)1);
            ((C_00f342d0*)(t1064))->FUN_00f342d0((unsigned int)(t1010));
            t1068 = (int)((int)(*(int*)g_016065fc));
            if (t1068 != (int)0) {
                *(int*)g_016065fc = (int)((int)0);
                ((il2c_vc5*)(t1068))->s1();
            }
            t1077 = (int)(t1010);
            ((il2c_vc6*)(t1077))->s1();
            return;
        }
    }
    return;
}
