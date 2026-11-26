// 0x00c0fe30: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPCreatureBase.cpp, match/slices/s00c0fa70/s00c0fa70.cpp.

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


template<class HsT> __forceinline HsT& hs_bind(HsT& x) { HsT& r = x; return r; }
// @ 0x00c0fe30
extern "C" int __fastcall FUN_00c0fe30(char* self, int edx_unused, int a4)
{
    int t1000;
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    unsigned char t1010;
    int t1011;
    int t1012;
    int t1014;
    int t1017;
    int t1023;
    int t1028;
    t1000 = (int)((int)(a4));
    t1004 = (int)((int)(self));
    t1005 = (int)(*(int*)((char*)(t1000)));
    *(int*)((char*)(hs_bind(t1004))) = (int)(t1005);
    t1006 = (int)(*(int*)((char*)(t1000) + 4));
    *(int*)((char*)(t1004) + 4) = (int)(t1006);
    t1007 = (int)(*(int*)((char*)(t1000) + 8));
    *(int*)((char*)(t1004) + 8) = (int)(t1007);
    t1008 = (int)(*(int*)((char*)(t1000) + 12));
    *(int*)((char*)(t1004) + 12) = (int)(t1008);
    t1009 = (int)(*(int*)((char*)(t1000) + 16));
    *(int*)((char*)(t1004) + 16) = (int)(t1009);
    *(float*)((char*)(t1004) + 20) = (float)(*(float*)((char*)(t1000) + 20));
    t1010 = (unsigned char)(*(unsigned char*)((char*)(t1000) + 24));
    *(unsigned char*)((char*)(t1004) + 24) = (unsigned char)(t1010);
    t1011 = (int)(*(int*)((char*)(t1000) + 28));
    *(int*)((char*)(t1004) + 28) = (int)(t1011);
    t1012 = (int)(*(int*)((char*)(t1004) + 32));
    t1014 = (int)(*(int*)((char*)(t1000) + 32));
    if (t1014 != t1012) {
        if (t1014 != (int)0) {
            t1017 = (int)(t1014);
            ((il2c_vc0*)(t1017))->s47();
        }
        *(int*)((char*)(t1004) + 32) = (int)(t1014);
        if (t1012 != (int)0) {
            t1023 = (int)(t1012);
            ((il2c_vc1*)(t1023))->s48();
        }
    }
    t1028 = (int)(t1004);
    return (int)(t1028);
}
