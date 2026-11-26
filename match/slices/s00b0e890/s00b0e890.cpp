// 0x00b0e890: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00b0e560/s00b0e560.cpp.

struct il2c_vc0 {
    virtual void s0();
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
    virtual int s22();
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
};
struct il2c_vc3 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc4 {
    virtual void s0();
    virtual void s1();
};

struct C_00b0e490 { void FUN_00b0e490(unsigned int); };
extern "C" void __cdecl FUN_00f47380(...);

// @ 0x00b0e890
extern "C" int __fastcall FUN_00b0e890(char* self, int edx_unused)
{
    int t1002;
    int t1003;
    int t1005;
    int t1008;
    int v_l4;
    int t1011;
    int t1017;
    int t1020;
    int t1023;
    int t1027;
    int t1028;
    int t1032;
    int t1033;
    int t1034;
    int t1035;
    int t1036;
    int t1037;
    int t1038;
    int t1049;
    t1002 = (int)((int)(self));
    t1003 = (int)(t1002 + (int)56);
    t1005 = (int)(*(int*)((char*)(t1003)));
    if (t1005 != t1003) {
        do {
            t1008 = (int)(*(int*)((char*)(t1005) + 8));
            v_l4 = (int)(t1008);
            if (t1008 != (int)0) {
                t1011 = (int)(t1008);
                ((il2c_vc0*)(t1011))->s0();
            }
            t1017 = (int)(t1008);
            t1020 = (int)((il2c_vc1*)(t1017))->s22();
            if (t1020 != (int)0) {
                t1023 = (int)(t1008);
                ((il2c_vc2*)(t1023))->s8();
                t1027 = (int)((int)&v_l4);
                t1028 = (int)(t1002 + (int)68);
                ((C_00b0e490*)(t1028))->FUN_00b0e490((unsigned int)(t1027));
                t1032 = (int)(*(int*)((char*)(t1005)));
                t1033 = (int)(*(int*)((char*)(t1032) + 4));
                t1034 = (int)(*(int*)((char*)(t1033) + 4));
                t1035 = (int)(*(int*)((char*)(t1033)));
                *(int*)((char*)(t1034)) = (int)(t1035);
                t1036 = (int)(*(int*)((char*)(t1033) + 4));
                t1037 = (int)(*(int*)((char*)(t1033)));
                *(int*)((char*)(t1037) + 4) = (int)(t1036);
                t1038 = (int)(*(int*)((char*)(t1033) + 8));
                if (t1038 != (int)0) {
                    ((il2c_vc3*)(t1038))->s1();
                }
                FUN_00f47380((unsigned int)(t1033));
                t1005 = (int)(t1032);
            } else {
                t1005 = (int)(*(int*)((char*)(t1005)));
            }
            t1049 = (int)(t1008);
            ((il2c_vc4*)(t1049))->s1();
            t1003 = (int)(t1002 + (int)56);
        } while (t1005 != t1003);
    }
    return (int)(t1003);
}
