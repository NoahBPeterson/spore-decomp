// 0x00f09580: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00f08c20/s00f08c20.cpp.

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
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual void s29();
    virtual void s30();
    virtual void s31();
    virtual void s32();
    virtual void s33();
    virtual void s34();
    virtual void s35();
    virtual void s36();
    virtual void s37();
    virtual void s38();
    virtual void s39();
    virtual void s40();
    virtual void s41();
    virtual void s42();
    virtual void s43();
    virtual void s44();
    virtual void s45();
    virtual void s46();
    virtual void s47();
    virtual void s48();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
};
struct il2c_vc3 {
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
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual void s29();
    virtual void s30();
    virtual void s31();
    virtual void s32();
    virtual void s33();
    virtual void s34();
    virtual void s35();
    virtual void s36();
    virtual void s37();
    virtual void s38();
    virtual void s39();
    virtual void s40();
    virtual void s41();
    virtual void s42();
    virtual void s43();
    virtual void s44();
    virtual void s45();
    virtual void s46();
    virtual void s47();
    virtual void s48();
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
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual int s14();
};

extern "C" unsigned char g_0148bab4[];
extern "C" unsigned char g_0148bad0[];
extern "C" unsigned char g_015ad538[];
extern "C" unsigned char g_015ad53c[];
extern "C" unsigned char g_015ad540[];
extern "C" unsigned char g_015ad544[];
extern "C" unsigned char g_016c7d88[];
extern "C" unsigned char g_016c7df0[];
extern "C" unsigned char g_016c7f30[];
struct C_007f8f00 { void FUN_007f8f00(); };
struct C_00810000 { int FUN_00810000(); };
struct C_00810590 { void FUN_00810590(unsigned int); };
struct C_008105b0 { int FUN_008105b0(unsigned int, unsigned int); };
struct C_00812160 { void FUN_00812160(unsigned int, unsigned int, unsigned int, unsigned int); };
extern "C" void __cdecl FUN_00f07c90(...);
struct C_00f09090 { void FUN_00f09090(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x00f09580
extern "C" void __cdecl FUN_00f09580(void)
{
    int t1008;
    int t1011;
    int t1012;
    int t1018;
    int t1019;
    int t1020;
    int t1024;
    int t1028;
    int t1032;
    int t1033;
    int t1036;
    int t1037;
    int t1038;
    int t1041;
    int t1047;
    int t1051;
    int t1055;
    int t1059;
    float t1066;
    int t1067;
    int t1070;
    int t1072;
    int t1075;
    float t1076;
    float t1065;
    FUN_00f07c90();
    t1008 = (int)((int)0);
    t1011 = (int)FUN_00f473a0((unsigned int)((int)8), (unsigned int)((int)g_0148bad0), (unsigned int)(t1008), (unsigned int)(t1008), (unsigned int)(t1008), (unsigned int)(t1008));
    if (t1011 != t1008) {
        *(int*)((char*)(t1011)) = (int)(t1008);
    } else {
        t1011 = (int)((int)0);
    }
    t1012 = (int)(*(int*)((char*)(t1011)));
    *(int*)g_016c7d88 = (int)(t1011);
    if (t1012 != t1008) {
        *(int*)((char*)(t1011)) = (int)(t1008);
        ((il2c_vc0*)(t1012))->s48();
        t1011 = (int)((int)(*(int*)g_016c7d88));
    }
    *(int*)((char*)(t1011) + 4) = (int)(t1008);
    t1018 = (int)((int)(*(int*)g_015ad540));
    t1019 = (int)((int)(*(int*)g_015ad53c));
    t1020 = (int)((int)g_015ad538);
    ((C_00f09090*)(t1020))->FUN_00f09090((unsigned int)(t1019), (unsigned int)(t1018));
    t1024 = (int)((int)g_016c7f30);
    *(int*)g_015ad544 = (int)(t1008);
    ((C_007f8f00*)(t1024))->FUN_007f8f00();
    t1028 = (int)((int)g_016c7df0);
    do {
        t1032 = (int)FUN_00f473a0((unsigned int)((int)24), (unsigned int)((int)g_0148bad0), (unsigned int)(t1008), (unsigned int)(t1008), (unsigned int)(t1008), (unsigned int)(t1008));
        if (t1032 != t1008) {
            t1033 = (int)(t1032);
            t1036 = (int)((C_00810000*)(t1033))->FUN_00810000();
            t1037 = (int)(t1036);
        } else {
            t1037 = (int)((int)0);
        }
        t1038 = (int)(*(int*)((char*)(t1028)));
        if (t1037 != t1038) {
            if (t1037 != t1008) {
                t1041 = (int)(t1037);
                ((il2c_vc1*)(t1041))->s1();
            }
            *(int*)((char*)(t1028)) = (int)(t1037);
            if (t1038 != t1008) {
                t1047 = (int)(t1038);
                ((il2c_vc2*)(t1047))->s2();
            }
        }
        t1051 = (int)(*(int*)((char*)(t1028)));
        ((C_00812160*)(t1051))->FUN_00812160((unsigned int)((int)g_0148bab4), (unsigned int)((int)1078345984), (unsigned int)((int)1), (unsigned int)((int)1063291710));
        t1055 = (int)(*(int*)((char*)(t1028)));
        ((C_00810590*)(t1055))->FUN_00810590((unsigned int)(t1008));
        t1059 = (int)(*(int*)((char*)(t1028) + 4));
        if (t1059 != t1008) {
            *(int*)((char*)(t1028) + 4) = (int)(t1008);
            ((il2c_vc3*)(t1059))->s48();
        }
        t1066 = (float)((float)0);
        t1067 = (int)(*(int*)((char*)(t1028)));
        *(float*)((char*)(t1028) + 8) = (float)(t1066);
        *(int*)((char*)(t1028) + 28) = (int)(t1008);
        t1070 = (int)((C_008105b0*)(t1067))->FUN_008105b0((unsigned int)((int)121187800), (unsigned int)((int)1));
        t1072 = (int)(t1070);
        t1075 = (int)((il2c_vc4*)(t1072))->s14();
        t1076 = (float)(*(float*)((char*)(t1075) + 12));
        t1065 = (float)(t1076 - (float)*(float*)((char*)(t1075) + 4));
        *(float*)((char*)(t1028) + 24) = (float)(t1065);
        t1028 = (int)(t1028 + (int)32);
    } while (t1028 < (int)g_016c7f30);
    return;
}
