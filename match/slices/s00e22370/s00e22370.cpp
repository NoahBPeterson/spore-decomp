// 0x00e22370: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00e21880/s00e21880.cpp, src/game/SPGonzago/SPUIPosse.cpp.

// lifted by il2c_lift + l2c_search (bind@t1007); CI scorer MATCH; corpus status nonmatching/residual
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
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
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
    virtual void s66(int);
};
struct il2c_vc4 {
    virtual void s0();
    virtual void s1();
};

struct C_0067dcc0 { int FUN_0067dcc0(); };
extern "C" int __cdecl FUN_0067dcc0(...);
struct C_00811ad0 { int FUN_00811ad0(unsigned int); };

template<class HsT> __forceinline HsT& hs_bind(HsT& x) { HsT& r = x; return r; }
// @ 0x00e22370
extern "C" bool __fastcall FUN_00e22370(char* self, int edx_unused)
{
    int t1002;
    int t1005;
    int t1007;
    int t1010;
    int t1012;
    int t1018;
    int t1024;
    int t1030;
    int t1036;
    int t1042;
    bool t1046;
    t1002 = (int)((int)(self));
    if ((int)*(int*)((char*)(t1002) + 316) != (int)0) {
        t1005 = (int)((C_0067dcc0*)((int)(self)))->FUN_0067dcc0();
        if (t1005 != (int)0) {
            t1007 = (int)(t1002 + (int)12);
            t1010 = (int)FUN_0067dcc0();
            t1012 = (int)(t1010);
            ((il2c_vc0*)(t1012))->s11((int)(hs_bind(t1007)), (int)((int)65280278), (int)((int)(-9999)));
        }
    }
    t1018 = (int)(*(int*)((char*)(t1002) + 156));
    if (t1018 != (int)0) {
        *(int*)((char*)(t1002) + 156) = (int)((int)0);
        ((il2c_vc1*)(t1018))->s1();
    }
    t1024 = (int)(*(int*)((char*)(t1002) + 80));
    if (t1024 != (int)0) {
        *(int*)((char*)(t1002) + 80) = (int)((int)0);
        ((il2c_vc2*)(t1024))->s1();
    }
    t1030 = (int)(*(int*)((char*)(t1002) + 316));
    if (t1030 != (int)0) {
        ((il2c_vc3*)(t1030))->s66((int)(t1002));
        t1036 = (int)(*(int*)((char*)(t1002) + 316));
        if (t1036 != (int)0) {
            *(int*)((char*)(t1002) + 316) = (int)((int)0);
            ((il2c_vc4*)(t1036))->s1();
        }
    }
    t1042 = (int)(t1002 + (int)124);
    ((C_00811ad0*)(t1042))->FUN_00811ad0((unsigned int)((int)1));
    t1046 = true;
    return (bool)(t1046);
}
