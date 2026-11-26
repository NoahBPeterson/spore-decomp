// 0x008076f0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/Spui/SPUIHelpers.cpp, match/slices/s008068d0/s008068d0.cpp.

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
    virtual int s45(int);
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual int s3(int);
};
struct il2c_vc2 {
    virtual void s0();
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
    virtual void s46(int, int);
};
struct il2c_vc4 {
    virtual void s0();
    virtual int s1();
};

struct C_0082a450 { void FUN_0082a450(); };

// @ 0x008076f0
extern "C" bool __cdecl FUN_008076f0(int a4)
{
    int t1002;
    int t1005;
    int t1008;
    int t1010;
    int t1014;
    int t1017;
    int t1023;
    int t1027;
    int t1033;
    bool t1038;
    bool t1041;
    t1002 = (int)((int)(a4));
    if (t1002 != (int)0) {
        t1005 = (int)(t1002);
        t1008 = (int)((il2c_vc0*)(t1005))->s45((int)((int)77994736));
        if (t1008 != (int)0) {
            t1010 = (int)(t1008);
            t1008 = (int)((il2c_vc1*)(t1010))->s3((int)((int)77994738));
            t1014 = (int)(t1008);
            if (t1014 != (int)0) {
                t1017 = (int)(t1014);
                ((il2c_vc2*)(t1017))->s0();
                t1023 = (int)(t1002);
                ((il2c_vc3*)(t1023))->s46((int)((int)77994736), (int)((int)0));
                t1027 = (int)(t1014);
                ((C_0082a450*)(t1027))->FUN_0082a450();
                t1033 = (int)(t1014);
                ((il2c_vc4*)(t1033))->s1();
                t1038 = true;
                return (bool)(t1038);
            }
        }
    }
    t1041 = false;
    return (bool)(t1041);
}
