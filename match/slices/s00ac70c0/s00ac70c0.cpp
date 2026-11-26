// 0x00ac70c0: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00ac6b90/s00ac6b90.cpp.

// lifted by il2c_lift + l2c_search (ref@t1003); CI scorer MATCH; corpus status nonmatching/residual
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
    virtual int s20(int);
};

struct C_0067dd50 { int FUN_0067dd50(); };
extern "C" void __cdecl FUN_00ac6da0(...);

// @ 0x00ac70c0
extern "C" void __fastcall FUN_00ac70c0(char* self, int edx_unused)
{
    int t1003;
    int t1005;
    int t1006;
    int t1010;
    int t1018;
    int t1019;
    int t1020;
    int t1021;
    int t1022;
    int t1023;
    int t1024;
    int t1028;
    t1003 = (int)((int)(self));
    int& t1003_r = t1003;
    *(int*)((char*)(t1003_r) + 36) = (int)((int)0);
    t1005 = (int)(*(int*)((char*)(t1003_r) + 68));
    t1006 = (int)(*(int*)((char*)(t1003_r) + 72));
    FUN_00ac6da0((unsigned int)(t1006), (unsigned int)(t1006), (unsigned int)(t1005));
    t1010 = (int)(t1006 - t1005);
    t1018 = (int)(t1010 / (int)(-60));
    t1019 = (int)(t1018);
    t1020 = (int)(t1019 << (int)4);
    t1021 = (int)(t1020 - t1018);
    t1022 = (int)(t1021 + t1021);
    t1023 = (int)(t1022 + t1022);
    *(int*)((char*)(t1003_r) + 72) += t1023;
    t1024 = (int)((C_0067dd50*)(t1023))->FUN_0067dd50();
    t1028 = (int)(t1024);
    ((il2c_vc0*)(t1028))->s20((int)((int)11));
    return;
}
