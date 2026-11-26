// 0x00b41e20: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00b41900/s00b41900.cpp, src/game/SPGonzago/_at_00b40000.cpp.

// lifted by il2c_lift + l2c_search (swap@18); CI scorer MATCH; corpus status nonmatching/residual
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
    virtual int s48();
};

extern "C" int __cdecl FUN_00f47380(...);

// @ 0x00b41e20
extern "C" void __fastcall FUN_00b41e20(char* self, int edx_unused, int a4, int a8)
{
    int t1002;
    int t1004;
    int t1008;
    int t1009;
    int t1012;
    int t1013;
    int t1018;
    int t1021;
    t1002 = (int)((int)0);
    t1004 = (int)((int)(self));
    if ((unsigned int)((int)(a8)) > (unsigned int)(t1002)) {
        do {
            t1008 = (int)((int)(a4));
            t1009 = (int)(*(int*)((char*)(t1008) + (t1002)*4));
            if (t1009 != (int)0) {
                goto Lb41e40;
                Lb41e40:;
                t1012 = (int)(t1009);
                t1009 = (int)(*(int*)((char*)(t1009) + 4));
                t1013 = (int)(*(int*)((char*)(t1012)));
                if (t1013 != (int)0) {
                    t1008 = (int)((il2c_vc0*)(t1013))->s48();
                }
                if (t1012 != (int)*(int*)((char*)(t1004) + 48)) {
                    if ((unsigned int)(t1012) >= (unsigned int)*(int*)((char*)(t1004) + 36)) {
                        if ((unsigned int)(t1012) < (unsigned int)*(int*)((char*)(t1004) + 40)) {
                            t1018 = (int)(*(int*)((char*)(t1004) + 28));
                            *(int*)((char*)(t1012)) = (int)(t1018);
                            *(int*)((char*)(t1004) + 28) = (int)(t1012);
                            goto Lb41e77;
                        }
                    }
                    t1008 = (int)FUN_00f47380((unsigned int)(t1012));
                }
                Lb41e77:;
                if (t1009 != (int)0) goto Lb41e40;
            }
            t1021 = (int)((int)(a4));
            *(int*)((char*)(t1021) + (t1002)*4) = (int)((int)0);
            t1002 = (int)(t1002 + (int)1);
        } while ((unsigned int)(t1002) < (unsigned int)((int)(a8)));
    }
    return;
}
