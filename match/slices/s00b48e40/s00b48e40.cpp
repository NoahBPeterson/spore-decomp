// 0x00b48e40: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00b48110/s00b48110.cpp.

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

extern "C" int __cdecl FUN_00c83c90(...);

// @ 0x00b48e40
extern "C" int __fastcall FUN_00b48e40(char* self, int edx_unused, int a4, int a8)
{
    int t1001;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1012;
    int t1013;
    int t1014;
    int t1020;
    int t1021;
    int t1022;
    int t1023;
    int t1024;
    int t1025;
    t1001 = (int)((int)(a8));
    t1006 = (int)((int)(self));
    t1007 = (int)((int)(a4));
    t1008 = (int)(*(int*)((char*)(t1006) + 4));
    t1009 = (int)FUN_00c83c90((unsigned int)(t1001), (unsigned int)(t1008), (unsigned int)(t1007));
    t1012 = (int)(*(int*)((char*)(t1006) + 4));
    t1013 = (int)(t1009);
    if ((unsigned int)(t1009) < (unsigned int)(t1012)) {
        do {
            t1014 = (int)(*(int*)((char*)(t1013)));
            if (t1014 != (int)0) {
                ((il2c_vc0*)(t1014))->s48();
            }
            t1013 = (int)(t1013 + (int)4);
        } while ((unsigned int)(t1013) < (unsigned int)(t1012));
    }
    t1020 = (int)((int)(a4));
    t1021 = (int)(t1001 - t1020);
    t1022 = (int)(t1021 >> (int)2);
    t1023 = (int)(-t1022);
    t1024 = (int)(t1023 + t1023);
    t1025 = (int)(t1024 + t1024);
    *(int*)((char*)(t1006) + 4) += t1025;
    return (int)(t1020);
}
