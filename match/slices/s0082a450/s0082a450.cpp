// 0x0082a450: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/Spui/SPUIHelpers.cpp, match/slices/s00829bc0/s00829bc0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual int s4();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual int s4();
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
    virtual void s55(int);
};
struct il2c_vc3 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc4 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc5 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc6 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc7 {
    virtual void s0();
    virtual void s1();
};

struct C_00811ad0 { int FUN_00811ad0(unsigned int); };

// @ 0x0082a450
extern "C" void __fastcall FUN_0082a450(char* self, int edx_unused)
{
    int t1002;
    int t1003;
    int t1009;
    int t1010;
    int t1015;
    int t1016;
    int t1019;
    int t1023;
    int t1024;
    int t1030;
    int t1036;
    int t1042;
    int t1048;
    int t1054;
    t1002 = (int)((int)(self));
    t1003 = (int)(*(int*)((char*)(t1002) + 16));
    t1009 = (int)((il2c_vc0*)(t1003))->s4();
    if (t1009 != (int)0) {
        t1010 = (int)(*(int*)((char*)(t1002) + 16));
        t1015 = (int)((il2c_vc1*)(t1010))->s4();
        t1016 = (int)(*(int*)((char*)(t1002) + 16));
        t1019 = (int)(t1015);
        ((il2c_vc2*)(t1019))->s55((int)(t1016));
    }
    t1023 = (int)(*(int*)((char*)(t1002) + 16));
    t1024 = (int)((int)0);
    if (t1023 != t1024) {
        *(int*)((char*)(t1002) + 16) = (int)(t1024);
        ((il2c_vc3*)(t1023))->s1();
    }
    t1030 = (int)(*(int*)((char*)(t1002) + 20));
    if (t1030 != t1024) {
        *(int*)((char*)(t1002) + 20) = (int)(t1024);
        ((il2c_vc4*)(t1030))->s1();
    }
    t1036 = (int)(*(int*)((char*)(t1002) + 24));
    if (t1036 != t1024) {
        *(int*)((char*)(t1002) + 24) = (int)(t1024);
        ((il2c_vc5*)(t1036))->s1();
    }
    t1042 = (int)(*(int*)((char*)(t1002) + 28));
    if (t1042 != t1024) {
        *(int*)((char*)(t1002) + 28) = (int)(t1024);
        ((il2c_vc6*)(t1042))->s1();
    }
    t1048 = (int)(*(int*)((char*)(t1002) + 32));
    if (t1048 != t1024) {
        *(int*)((char*)(t1002) + 32) = (int)(t1024);
        ((il2c_vc7*)(t1048))->s1();
    }
    t1054 = (int)(*(int*)((char*)(t1002) + 12));
    ((C_00811ad0*)(t1054))->FUN_00811ad0((unsigned int)((int)1));
    return;
}
