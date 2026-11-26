// 0x00b04420: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPPlanet.cpp, match/slices/s00b03820/s00b03820.cpp.

// lifted by il2c_lift + l2c_search (ref@t1002); CI scorer MATCH; corpus status nonmatching/residual
struct il2c_vc0 {
    virtual void s0();
    virtual int s1();
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
    virtual int s14();
};
struct il2c_vc3 {
    virtual void s0();
    virtual int s1();
};

struct C_00b04420 { int FUN_00b04420(unsigned int); };
extern "C" int __cdecl FUN_00f47380(...);

// @ 0x00b04420
extern "C" void __fastcall FUN_00b04420(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1004;
    int t1006;
    int t1008;
    int t1009;
    int t1013;
    int t1014;
    int t1019;
    int t1024;
    int t1029;
    int t1034;
    t1002 = (int)((int)(a4));
    int& t1002_r = t1002;
    t1004 = (int)((int)0);
    t1006 = (int)((int)(self));
    if (t1002_r != t1004) {
        do {
            t1008 = (int)(*(int*)((char*)(t1002_r)));
            t1009 = (int)(t1006);
            ((C_00b04420*)(t1009))->FUN_00b04420((unsigned int)(t1008));
            t1013 = (int)(*(int*)((char*)(t1002_r) + 4));
            *(int*)((char*)(t1002_r) + 24) = (int)(t1004);
            *(int*)((char*)(t1002_r) + 32) = (int)(t1004);
            *(int*)((char*)(t1002_r) + 36) = (int)(t1004);
            t1014 = (int)(*(int*)((char*)(t1002_r) + 40));
            if (t1014 != t1004) {
                *(int*)((char*)(t1002_r) + 40) = (int)(t1004);
                ((il2c_vc0*)(t1014))->s1();
            }
            t1019 = (int)(*(int*)((char*)(t1002_r) + 44));
            if (t1019 != t1004) {
                *(int*)((char*)(t1002_r) + 44) = (int)(t1004);
                ((il2c_vc1*)(t1019))->s14();
            }
            *(int*)((char*)(t1002_r) + 48) = (int)(t1004);
            t1024 = (int)(*(int*)((char*)(t1002_r) + 44));
            if (t1024 != t1004) {
                ((il2c_vc2*)(t1024))->s14();
            }
            t1029 = (int)(*(int*)((char*)(t1002_r) + 40));
            if (t1029 != t1004) {
                ((il2c_vc3*)(t1029))->s1();
            }
            if ((unsigned int)(t1002_r) >= (unsigned int)*(int*)((char*)(t1006) + 32)) {
                if ((unsigned int)(t1002_r) < (unsigned int)*(int*)((char*)(t1006) + 36)) {
                    t1034 = (int)(*(int*)((char*)(t1006) + 24));
                    *(int*)((char*)(t1002_r)) = (int)(t1034);
                    *(int*)((char*)(t1006) + 24) = (int)(t1002_r);
                    goto Lb044a4;
                }
            }
            FUN_00f47380((unsigned int)(t1002_r));
            Lb044a4:;
            t1002_r = (int)(t1013);
        } while (t1013 != t1004);
    }
    return;
}
