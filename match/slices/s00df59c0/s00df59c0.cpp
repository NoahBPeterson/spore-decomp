// 0x00df59c0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPGalaxyGameEntry.cpp, match/slices/s00df5670/s00df5670.cpp.

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
    virtual void s65(int);
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
    virtual int s13();
};

struct C_008105b0 { int FUN_008105b0(unsigned int, unsigned int); };
struct C_00811ad0 { int FUN_00811ad0(unsigned int); };
struct C_008120d0 { int FUN_008120d0(unsigned int, unsigned int, unsigned int); };
struct C_00b5f950 { void FUN_00b5f950(unsigned int); };
struct C_00df5610 { void FUN_00df5610(float); };

// @ 0x00df59c0
extern "C" bool __fastcall FUN_00df59c0(char* self, int edx_unused, int a4)
{
    int t1003;
    int t1004;
    int v_l12[3];
    int t1005;
    int t1006;
    int t1007;
    int t1010;
    int t1011;
    int t1015;
    int t1020;
    int t1021;
    int t1024;
    int t1027;
    int t1028;
    int t1031;
    float t1036;
    int t1037;
    int t1041;
    int t1042;
    bool t1044;
    int t1046;
    bool t1050;
    t1003 = (int)((int)(self));
    t1004 = (int)((int)&v_l12);
    t1005 = (int)(t1003 + (int)84);
    t1006 = (int)(t1005);
    (*(int*)&v_l12[0]) = (int)((int)(-579956677));
    (*(int*)&v_l12[1]) = (int)((int)84978011);
    (*(int*)&v_l12[2]) = (int)((int)1078345984);
    t1007 = (int)((C_008120d0*)(t1006))->FUN_008120d0((unsigned int)(t1004), (unsigned int)((int)1), (unsigned int)((int)95787258));
    if ((unsigned char)(t1007) != (unsigned char)0) {
        t1010 = (int)(t1005);
        t1011 = (int)((C_008105b0*)(t1010))->FUN_008105b0((unsigned int)((int)70378808), (unsigned int)((int)1));
        if (t1011 != (int)0) {
            t1015 = (int)(t1011);
            ((il2c_vc0*)(t1015))->s65((int)(t1003));
            t1020 = (int)(t1005);
            t1021 = (int)((C_008105b0*)(t1020))->FUN_008105b0((unsigned int)((int)97947368), (unsigned int)((int)1));
            t1024 = (int)(t1021);
            if (t1024 != (int)0) {
                t1027 = (int)(t1024);
                t1028 = (int)((il2c_vc1*)(t1027))->s13();
                *(float*)((char*)(t1003) + 52) = (float)(*(float*)((char*)(t1028)));
                t1031 = (int)(t1003 + (int)48);
                *(float*)((char*)(t1003) + 56) = (float)(*(float*)((char*)(t1028) + 4));
                *(float*)((char*)(t1003) + 60) = (float)(*(float*)((char*)(t1028) + 8));
                *(float*)((char*)(t1003) + 64) = (float)(*(float*)((char*)(t1028) + 12));
                ((C_00b5f950*)(t1031))->FUN_00b5f950((unsigned int)(t1024));
                t1036 = (float)((float)0);
                t1037 = (int)(t1003);
                *(float*)((char*)(t1003) + 68) = (float)(t1036);
                ((C_00df5610*)(t1037))->FUN_00df5610((float)((float)0));
            }
            t1041 = (int)((int)(a4));
            *(int*)((char*)(t1003) + 72) = (int)(t1041);
            t1042 = (int)(*(int*)((char*)(t1041) + 88));
            *(int*)((char*)(t1003) + 76) = (int)(t1042);
            t1044 = true;
            return (bool)(t1044);
        }
        t1046 = (int)(t1005);
        t1007 = (int)((C_00811ad0*)(t1046))->FUN_00811ad0((unsigned int)((int)1));
    }
    t1050 = false;
    return (bool)(t1050);
}
