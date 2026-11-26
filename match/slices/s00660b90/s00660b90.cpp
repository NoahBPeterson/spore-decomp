// 0x00660b90: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEditors/SPUIFeedFilter.cpp, match/slices/s0065f970/s0065f970.cpp.

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
    virtual void s56(int);
};

extern "C" int __cdecl FUN_00921580(...);
struct C_00d0c930 { void FUN_00d0c930(unsigned int); };

// @ 0x00660b90
extern "C" int __fastcall FUN_00660b90(char* self, int edx_unused)
{
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1012;
    int t1013;
    int t1016;
    int t1022;
    int t1023;
    int t1024;
    int t1025;
    int t1029;
    t1004 = (int)((int)(self));
    t1005 = (int)(*(int*)((char*)(t1004) + 164));
    t1006 = (int)(t1004 + (int)160);
    if (t1005 != t1006) {
        do {
            t1007 = (int)(*(int*)((char*)(t1005) + 20));
            if (t1007 != (int)0) {
                t1012 = (int)((il2c_vc0*)(t1007))->s4();
                t1013 = (int)(*(int*)((char*)(t1005) + 20));
                t1016 = (int)(t1012);
                ((il2c_vc1*)(t1016))->s56((int)(t1013));
            }
            t1022 = (int)FUN_00921580((unsigned int)(t1005));
            t1005 = (int)(t1022);
        } while (t1005 != t1006);
    }
    t1023 = (int)(*(int*)((char*)(t1004) + 168));
    t1024 = (int)(t1004 + (int)156);
    t1025 = (int)(t1024);
    ((C_00d0c930*)(t1025))->FUN_00d0c930((unsigned int)(t1023));
    t1029 = (int)(t1024 + (int)4);
    *(int*)((char*)(t1024) + 8) = (int)(t1029);
    *(int*)((char*)(t1024) + 12) = (int)((int)0);
    *(unsigned char*)((char*)(t1024) + 16) = (unsigned char)((int)0);
    *(int*)((char*)(t1024) + 20) = (int)((int)0);
    *(int*)((char*)(t1029)) = (int)(t1029);
    return (int)(t1029);
}
