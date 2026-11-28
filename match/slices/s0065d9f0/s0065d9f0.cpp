// 0x0065d9f0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEditors/SPUIFeedEdit.cpp, match/slices/s0065d050/s0065d050.cpp.

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
    virtual int s31(int, int);
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
    virtual int s31(int, int);
};

extern "C" unsigned char g_01667bac[];
extern "C" unsigned char g_01667bae[];
extern "C" void __cdecl FUN_006214c0(...);
struct C_00997730 { void FUN_00997730(unsigned int, unsigned int, unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00f47380(...);

// @ 0x0065d9f0
extern "C" void __fastcall FUN_0065d9f0(char* self, int edx_unused, int a4)
{
    int t1001;
    int t1004;
    int t1005;
    int t1008;
    int t1011;
    int t1016;
    int v_l16[4];
    int t1017;
    int t1021;
    int t1022;
    int t1023;
    int t1027;
    int t1028;
    int t1029;
    t1001 = (int)((int)(a4));
    t1004 = (int)((int)(self));
    if ((unsigned char)(t1001) != (unsigned char)0) {
        t1005 = (int)(*(int*)((char*)(t1004) + 124));
        if (t1005 != (int)0) {
            t1008 = (int)((il2c_vc0*)(t1005))->s31((int)((int)1), (int)((int)1));
        }
    }
    t1011 = (int)(*(int*)((char*)(t1004) + 128));
    if (t1011 != (int)0) {
        t1008 = (int)((il2c_vc1*)(t1011))->s31((int)((int)1), (int)(t1001));
        if ((unsigned char)(t1001) != (unsigned char)0) {
            t1016 = (int)((int)g_01667bac);
            (*(int*)&v_l16[0]) = (int)(t1016);
            (*(int*)&v_l16[1]) = (int)(t1016);
            t1017 = (int)((int)&v_l16);
            *(int*)((char*)(t1004) + 140) = (int)((int)0);
            (*(int*)&v_l16[2]) = (int)((int)g_01667bae);
            FUN_006214c0((unsigned int)((int)93359858), (unsigned int)(t1017));
            t1021 = (int)((*(int*)&v_l16[0]));
            t1022 = (int)(*(int*)((char*)(t1004) + 132));
            t1023 = (int)(t1004 + (int)24);
            ((C_00997730*)(t1023))->FUN_00997730((unsigned int)(t1022), (unsigned int)(t1021), (unsigned int)((int)0), (unsigned int)((int)0));
            t1027 = (int)((*(int*)&v_l16[2]));
            t1008 = (int)((*(int*)&v_l16[0]));
            t1028 = (int)(t1027 - t1008);
            t1029 = (int)(t1028 & (int)(-2));
            if (t1029 > (int)2) {
                if (t1008 != (int)0) {
                    t1008 = (int)FUN_00f47380((unsigned int)(t1008));
                }
            }
        }
    }
    return;
}
