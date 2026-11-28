// 0x005fdaa0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s005fd260/s005fd260.cpp.

extern "C" void __cdecl FUN_00dbdba1(...);
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
    virtual int s14();
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
    virtual int s14();
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
    virtual void s28(float, float);
};
struct il2c_vc3 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual int s4();
};
struct il2c_vc4 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual int s4();
};
struct il2c_vc5 {
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
    virtual void s49();
    virtual void s50();
    virtual void s51();
    virtual void s52();
    virtual void s53();
    virtual void s54();
    virtual void s55();
    virtual void s56();
    virtual void s57();
    virtual void s58(int);
};
struct il2c_vc6 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual int s8();
};
struct il2c_vc7 {
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
    virtual int s31(int, int);
};

extern "C" void __cdecl FUN_00435ed0(...);
extern "C" int __cdecl FUN_0067dd10(...);
struct C_008105b0 { int FUN_008105b0(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00a206f0(...);

// @ 0x005fdaa0
extern "C" void __fastcall FUN_005fdaa0(char* self, int edx_unused, int a4)
{
    int t1003;
    int t1004;
    int t1005;
    int t1008;
    int t1010;
    int t1012;
    int t1016;
    int t1018;
    int t1021;
    int t1022;
    int t1023;
    int t1028;
    int t1030;
    int t1034;
    int t1041;
    int t1042;
    int t1047;
    int t1048;
    int t1052;
    int t1057;
    int t1061;
    int t1063;
    int t1071;
    t1003 = (int)((int)(self));
    t1004 = (int)(*(int*)((char*)(t1003) + 68));
    t1005 = (int)((C_008105b0*)(t1004))->FUN_008105b0((unsigned int)((int)103042128), (unsigned int)((int)1));
    t1008 = (int)(t1005);
    if (t1008 != (int)0) {
        t1010 = (int)((int)(a4));
        if ((unsigned char)(t1010) != (unsigned char)0) {
            t1012 = (int)FUN_0067dd10();
            t1016 = (int)(t1012);
            t1018 = (int)((il2c_vc0*)(t1016))->s14();
            if (t1018 != (int)&FUN_00dbdba1) {
                t1021 = (int)((int)107899792);
                if (t1018 != (int)46977490) goto L5fdaf1;
            }
            t1021 = (int)((int)107899800);
            L5fdaf1:;
            t1022 = (int)(*(int*)((char*)(t1003) + 68));
            t1023 = (int)((C_008105b0*)(t1022))->FUN_008105b0((unsigned int)(t1021), (unsigned int)((int)1));
            if (t1021 != (int)0) {
                t1028 = (int)(t1023);
                t1030 = (int)((il2c_vc1*)(t1028))->s14();
                t1034 = (int)(t1008);
                ((il2c_vc2*)(t1034))->s28((float)(*(float*)((char*)(t1030))), (float)(*(float*)((char*)(t1030) + 4)));
            }
            t1041 = (int)(t1008);
            t1042 = (int)((il2c_vc3*)(t1041))->s4();
            if (t1042 != (int)0) {
                t1047 = (int)(t1008);
                t1048 = (int)((il2c_vc4*)(t1047))->s4();
                t1052 = (int)(t1048);
                ((il2c_vc5*)(t1052))->s58((int)(t1008));
            }
            t1057 = (int)FUN_00a206f0();
            if (t1057 != (int)0) {
                t1061 = (int)(t1057);
                t1063 = (int)((il2c_vc6*)(t1061))->s8();
            } else {
                t1063 = (int)((int)0);
            }
            FUN_00435ed0((unsigned int)((int)316742427), (unsigned int)(t1063));
        }
        t1071 = (int)(t1008);
        t1005 = (int)((il2c_vc7*)(t1071))->s31((int)((int)1), (int)(t1010));
    }
    return;
}
