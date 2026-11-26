// 0x0065b1b0: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0065af90/s0065af90.cpp, src/game/SPEditors/SPUIAssetWebBrowser.cpp.

// lifted by il2c_lift + l2c_search (bind@t1004); CI scorer MATCH; corpus status nonmatching/residual
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
    virtual void s11(int, int, int);
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual int s2();
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
    virtual void s58();
    virtual void s59();
    virtual void s60();
    virtual void s61();
    virtual void s62();
    virtual void s63();
    virtual void s64();
    virtual void s65();
    virtual int s66(int);
};
struct il2c_vc3 {
    virtual void s0();
    virtual int s1();
};
struct il2c_vc4 {
    virtual void s0();
    virtual int s1();
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
    virtual void s11(int, int, int);
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
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual int s11(int, int, int);
};

struct C_005febf0 { int FUN_005febf0(); };
struct C_0067dcc0 { int FUN_0067dcc0(); };
extern "C" int __cdecl FUN_0067dcc0(...);
struct C_00811ad0 { int FUN_00811ad0(unsigned int); };
struct C_00997140 { int FUN_00997140(); };

template<class HsT> __forceinline HsT& hs_bind(HsT& x) { HsT& r = x; return r; }
// @ 0x0065b1b0
extern "C" bool __fastcall FUN_0065b1b0(char* self, int edx_unused)
{
    int t1002;
    int t1004;
    int t1006;
    int t1009;
    int t1015;
    int t1019;
    int t1022;
    int t1027;
    int t1032;
    int t1037;
    int t1040;
    int t1045;
    int t1047;
    int t1050;
    int t1056;
    int t1059;
    bool t1063;
    t1002 = (int)((int)(self));
    if ((int)*(int*)((char*)(t1002) + 28) == (int)0) {
        t1004 = (int)(t1002 + (int)8);
        t1006 = (int)((C_0067dcc0*)((int)(self)))->FUN_0067dcc0();
        t1009 = (int)(t1006);
        ((il2c_vc0*)(t1009))->s11((int)(hs_bind(t1004)), (int)((int)(-735898304)), (int)((int)(-9999)));
    }
    t1015 = (int)(t1002 + (int)32);
    ((C_00997140*)(t1015))->FUN_00997140();
    t1019 = (int)(*(int*)((char*)(t1002) + 20));
    if (t1019 != (int)0) {
        ((C_00811ad0*)(t1019))->FUN_00811ad0((unsigned int)((int)1));
        t1022 = (int)(*(int*)((char*)(t1002) + 20));
        if (t1022 != (int)0) {
            *(int*)((char*)(t1002) + 20) = (int)((int)0);
            ((il2c_vc1*)(t1022))->s2();
        }
    }
    t1027 = (int)(*(int*)((char*)(t1002) + 152));
    if (t1027 != (int)0) {
        ((il2c_vc2*)(t1027))->s66((int)(t1002));
        t1032 = (int)(*(int*)((char*)(t1002) + 152));
        if (t1032 != (int)0) {
            *(int*)((char*)(t1002) + 152) = (int)((int)0);
            ((il2c_vc3*)(t1032))->s1();
        }
    }
    t1037 = (int)(*(int*)((char*)(t1002) + 160));
    if (t1037 != (int)0) {
        ((C_005febf0*)(t1037))->FUN_005febf0();
        t1040 = (int)(*(int*)((char*)(t1002) + 160));
        if (t1040 != (int)0) {
            *(int*)((char*)(t1002) + 160) = (int)((int)0);
            ((il2c_vc4*)(t1040))->s1();
        }
    }
    if ((unsigned char)*(unsigned char*)((char*)(t1002) + 148) != (unsigned char)0) {
        t1045 = (int)(t1002 + (int)8);
        t1047 = (int)FUN_0067dcc0();
        t1050 = (int)(t1047);
        ((il2c_vc5*)(t1050))->s11((int)(t1045), (int)((int)64081163), (int)((int)(-9999)));
        t1056 = (int)FUN_0067dcc0();
        t1059 = (int)(t1056);
        ((il2c_vc6*)(t1059))->s11((int)(t1045), (int)((int)67098825), (int)((int)(-9999)));
    }
    t1063 = true;
    return (bool)(t1063);
}
