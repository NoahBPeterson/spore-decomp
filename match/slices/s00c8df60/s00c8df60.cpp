// 0x00c8df60: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPOrnament.cpp, match/slices/s00c8db30/s00c8db30.cpp.

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
    virtual void s52();
    virtual void s53();
    virtual void s54();
    virtual void s55();
    virtual void s56();
    virtual void s57();
    virtual void s58();
    virtual void s59();
    virtual void s60();
    virtual void s61();
    virtual void s62();
    virtual void s63();
    virtual void s64();
    virtual void s65();
    virtual void s66();
    virtual void s67();
    virtual void s68();
    virtual void s69();
    virtual void s70();
    virtual void s71();
    virtual void s72();
    virtual void s73();
    virtual void s74();
    virtual void s75();
    virtual void s76();
    virtual void s77();
    virtual void s78();
    virtual void s79();
    virtual void s80();
    virtual void s81();
    virtual void s82();
    virtual void s83();
    virtual void s84();
    virtual void s85();
    virtual void s86();
    virtual void s87();
    virtual void s88();
    virtual void s89();
    virtual void s90();
    virtual void s91(int, int);
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
};

struct C_005f3680 { void FUN_005f3680(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_005f4e10(...);
struct C_00c898f0 { void FUN_00c898f0(); };

// @ 0x00c8df60
// @ 0x00c8df60
extern "C" void __fastcall FUN_00c8df60(char* self, int edx_unused)
{
    int t1004;
    int t1005;
    int t1006;
    int t1008;
    int v_l4;
    int t1009;
    int t1010;
    int t1016;
    int t1022;
    int t1023;
    int t1024;
    int t1027;
    int t1028;
    int t1032;
    int t1033;
    int t1034;
    int t1035;
    int t1036;
    int t1039;
    t1004 = (int)((int)(self));
    t1005 = (int)(*(int*)((char*)(t1004) + 216));
    t1006 = (int)(*(int*)((char*)(t1004) + 212));
    t1008 = (int)(t1004 + (int)212);
    v_l4 = (int)(t1005);
    if (t1006 != t1005) {
        do {
            t1009 = (int)(*(int*)((char*)(t1006)));
            if (t1009 != (int)0) {
                t1010 = (int)(*(int*)((char*)(t1009)));
                ((il2c_vc0*)(t1010))->s91((int)(t1009), (int)((int)0));
                t1016 = (int)(*(int*)((char*)(t1009) + 100));
                if (t1016 != (int)0) {
                    *(int*)((char*)(t1009) + 100) = (int)((int)0);
                    ((il2c_vc1*)(t1016))->s1();
                }
            }
            t1006 = (int)(t1006 + (int)4);
        } while (t1006 != v_l4);
    }
    t1022 = (int)(*(int*)((char*)(t1008)));
    t1023 = (int)(*(int*)((char*)(t1008) + 4));
    t1024 = (int)FUN_005f4e10((unsigned int)(t1023), (unsigned int)(t1023), (unsigned int)(t1022));
    t1027 = (int)(*(int*)((char*)(t1008) + 4));
    t1028 = (int)(t1008);
    ((C_005f3680*)(t1028))->FUN_005f3680((unsigned int)(t1024), (unsigned int)(t1027));
    t1032 = (int)(t1023 - t1022);
    t1033 = (int)(t1032 >> (int)2);
    t1034 = (int)(-t1033);
    t1035 = (int)(t1034 + t1034);
    t1036 = (int)(t1035 + t1035);
    *(int*)((char*)(t1008) + 4) += t1036;
    t1039 = (int)(t1004);
    ((C_00c898f0*)(t1039))->FUN_00c898f0();
    return;
}
