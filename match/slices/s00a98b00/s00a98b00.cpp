// 0x00a98b00: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/Swarm/LightDescription.cpp, match/slices/s00a987c0/s00a987c0.cpp.

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
    virtual int s44(int, int);
};

struct C_007ed1b0 { void FUN_007ed1b0(unsigned int, unsigned int); };
struct C_00838020 { int FUN_00838020(unsigned int, unsigned int, unsigned int); };
struct C_009e0480 { void FUN_009e0480(unsigned int, unsigned int); };

// @ 0x00a98b00
// @ 0x00a98b00
extern "C" int __fastcall FUN_00a98b00(char* self, int edx_unused, int a4)
{
    int t1003;
    int t1005;
    int t1006;
    int t1007;
    int t1010;
    int t1012;
    int t1011;
    int t1013;
    int t1014;
    int t1018;
    int t1019;
    int t1021;
    int t1022;
    int t1025;
    int v_l12[3];
    int t1026;
    int t1029;
    int t1031;
    int t1030;
    int t1032;
    int t1037;
    int t1038;
    t1003 = (int)((int)&a4);
    t1005 = (int)((int)(self));
    t1006 = (int)((int)(a4));
    t1007 = (int)((C_00838020*)(t1006))->FUN_00838020((unsigned int)(t1003), (unsigned int)((int)1), (unsigned int)((int)2147483647));
    t1010 = (int)(*(int*)((char*)(t1005) + 12));
    t1012 = (int)(t1010 + (int)28);
    t1011 = (int)(*(int*)((char*)(t1012) + 4));
    t1013 = (int)(t1007);
    t1014 = (int)(*(int*)((char*)(t1012)));
    ((C_009e0480*)(t1012))->FUN_009e0480((unsigned int)(t1014), (unsigned int)(t1011));
    t1018 = (int)((int)(a4));
    t1019 = (int)((int)0);
    if (t1018 > (int)0) {
        do {
            t1021 = (int)(*(int*)((char*)(t1013) + (t1019)*4));
            t1022 = (int)(*(int*)((char*)(t1005) + 4));
            t1025 = (int)((int)&v_l12);
            t1026 = (int)((il2c_vc0*)(t1022))->s44((int)(t1025), (int)(t1021));
            t1029 = (int)(*(int*)((char*)(t1005) + 12));
            t1031 = (int)(t1029 + (int)28);
            t1030 = (int)(*(int*)((char*)(t1031) + 4));
            if ((unsigned int)(t1030) < (unsigned int)*(int*)((char*)(t1031) + 8)) {
                t1032 = (int)(t1030 + (int)12);
                *(int*)((char*)(t1031) + 4) = (int)(t1032);
                if (t1030 == (int)0) goto La98b87;
                *(float*)((char*)(t1030)) = (float)(*(float*)((char*)(t1026)));
                *(float*)((char*)(t1030) + 4) = (float)(*(float*)((char*)(t1026) + 4));
                *(float*)((char*)(t1030) + 8) = (float)(*(float*)((char*)(t1026) + 8));
                goto La98b87;
            }
            ((C_007ed1b0*)(t1031))->FUN_007ed1b0((unsigned int)(t1030), (unsigned int)(t1026));
            La98b87:;
            t1018 = (int)((int)(a4));
            t1019 = (int)(t1019 + (int)1);
        } while (t1019 < t1018);
    }
    t1037 = (int)(*(int*)((char*)(t1005) + 12));
    t1038 = (int)(t1037 + (int)12);
    if (t1018 > (int)0) {
        *(int*)((char*)(t1038)) |= (int)1;
        return (int)(t1018);
    }
    *(int*)((char*)(t1038)) &= (int)(-2);
    return (int)(t1018);
}
