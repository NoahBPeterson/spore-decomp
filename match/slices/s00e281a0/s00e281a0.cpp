// 0x00e281a0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00e27310/s00e27310.cpp, src/game/SPGonzago/SPUIPosse.cpp.

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
    virtual void s49();
    virtual void s50();
    virtual void s51();
};

struct C_00e23870 { void FUN_00e23870(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00e24290(...);
struct C_00e25bd0 { int FUN_00e25bd0(unsigned int, unsigned int); };

// @ 0x00e281a0
extern "C" void __fastcall FUN_00e281a0(char* self, int edx_unused, int a4)
{
    int t1005;
    int t1006;
    int t1007;
    int t1009;
    int t1015;
    int t1016;
    int t1017;
    int t1020;
    int t1021;
    int t1022;
    int t1026;
    int t1027;
    int t1028;
    int t1029;
    int t1030;
    int t1031;
    int t1032;
    int t1033;
    int t1034;
    t1005 = (int)((int)(self));
    if ((unsigned char)(a4) != (unsigned char)0) {
        t1006 = (int)(*(int*)((char*)(t1005) + 164));
        t1007 = (int)(*(int*)((char*)(t1005) + 168));
        if (t1006 != t1007) {
            do {
                t1009 = (int)(*(int*)((char*)(t1006) + 4));
                ((il2c_vc0*)(t1009))->s51();
                t1006 = (int)(t1006 + (int)8);
            } while (t1006 != t1007);
        }
    }
    t1015 = (int)(*(int*)((char*)(t1005) + 164));
    t1016 = (int)(*(int*)((char*)(t1005) + 168));
    t1017 = (int)(t1005 + (int)164);
    t1020 = (int)FUN_00e24290((unsigned int)(t1016), (unsigned int)(t1016), (unsigned int)(t1015));
    t1021 = (int)(*(int*)((char*)(t1017) + 4));
    t1022 = (int)(t1017);
    ((C_00e23870*)(t1022))->FUN_00e23870((unsigned int)(t1020), (unsigned int)(t1021));
    t1026 = (int)(t1016 - t1015);
    t1027 = (int)(t1026 >> (int)3);
    t1028 = (int)(-t1027);
    t1029 = (int)(t1028 + t1028);
    t1030 = (int)(t1029 + t1029);
    t1031 = (int)(t1005 + (int)12);
    t1032 = (int)(t1030 + t1030);
    *(int*)((char*)(t1017) + 4) += t1032;
    t1033 = (int)(*(int*)((char*)(t1031) + 4));
    t1034 = (int)(*(int*)((char*)(t1031)));
    ((C_00e25bd0*)(t1031))->FUN_00e25bd0((unsigned int)(t1034), (unsigned int)(t1033));
    *(unsigned char*)((char*)(t1005) + 468) = (unsigned char)((int)1);
    return;
}
