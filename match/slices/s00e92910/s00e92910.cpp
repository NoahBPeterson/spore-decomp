// 0x00e92910: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPSpatialObjectView.cpp, match/slices/s00e91ce0/s00e91ce0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual int s3(int);
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
    virtual int s47();
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
    virtual int s48();
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
    virtual int s43();
};
struct il2c_vc4 {
    virtual void s0();
};
struct il2c_vc5 {
    virtual void s0();
    virtual void s1();
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

extern "C" unsigned char g_01186577[];

// @ 0x00e92910
extern "C" void __fastcall FUN_00e92910(char* self, int edx_unused, int a4)
{
    int t1004;
    int t1006;
    int t1009;
    int t1012;
    int t1013;
    int t1014;
    int t1017;
    int t1022;
    int t1025;
    int t1030;
    int t1031;
    int t1034;
    int t1040;
    int t1046;
    t1004 = (int)((int)(a4));
    t1006 = (int)((int)(self));
    if (t1004 != (int)0) {
        t1009 = (int)(t1004);
        t1012 = (int)((il2c_vc0*)(t1009))->s3((int)((int)g_01186577));
        t1013 = (int)(t1012);
    } else {
        t1013 = (int)((int)0);
    }
    t1014 = (int)(*(int*)((char*)(t1006) + 12));
    if (t1013 != t1014) {
        if (t1013 != (int)0) {
            t1017 = (int)(t1013);
            t1012 = (int)((il2c_vc1*)(t1017))->s47();
        }
        *(int*)((char*)(t1006) + 12) = (int)(t1013);
        if (t1014 != (int)0) {
            t1022 = (int)(t1014);
            t1012 = (int)((il2c_vc2*)(t1022))->s48();
        }
    }
    t1025 = (int)(*(int*)((char*)(t1006) + 12));
    if (t1025 != (int)0) {
        t1012 = (int)((il2c_vc3*)(t1025))->s43();
        t1030 = (int)(t1012);
        if (t1030 != (int)0) {
            t1031 = (int)(*(int*)((char*)(t1030) + 100));
            if (t1004 != t1031) {
                if (t1004 != (int)0) {
                    t1034 = (int)(t1004);
                    ((il2c_vc4*)(t1034))->s0();
                }
                *(int*)((char*)(t1030) + 100) = (int)(t1004);
                if (t1031 != (int)0) {
                    t1040 = (int)(t1031);
                    ((il2c_vc5*)(t1040))->s1();
                }
            }
            t1046 = (int)(t1004);
            t1012 = (int)((il2c_vc6*)(t1046))->s8();
            *(int*)((char*)(t1030) + 96) = (int)(t1012);
        }
    }
    return;
}
