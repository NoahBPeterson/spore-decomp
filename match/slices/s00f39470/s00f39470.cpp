// 0x00f39470: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00f392b0/s00f392b0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual int s1();
};
struct il2c_vc1 {
    virtual void s0();
    virtual int s1();
};

extern "C" unsigned char g_013ec468[];
extern "C" void __cdecl FUN_00593960(...);
struct C_00595230 { int FUN_00595230(unsigned int); };
struct C_00595a90 { void FUN_00595a90(unsigned int); };
extern "C" int __cdecl FUN_005bf0e0(...);
extern "C" int __cdecl FUN_005bf1e0(...);
struct C_005c3d90 { int FUN_005c3d90(unsigned int); };
struct C_006b5240 { int FUN_006b5240(); };
struct C_006b55c0 { int FUN_006b55c0(); };
struct C_006b5770 { void FUN_006b5770(unsigned int, unsigned int, unsigned int); };

// @ 0x00f39470
// @ 0x00f39470
extern "C" bool __cdecl FUN_00f39470(int a4, int a8)
{
    int t1003;
    int v_l40;
    bool t1004;
    int t1006;
    int t1009;
    int t1010;
    int v_l44;
    int t1013;
    int t1017;
    int t1018;
    int v_l28[2];
    int t1019;
    int t1022;
    int t1023;
    int v_l36;
    int t1024;
    int t1025;
    int v_l32;
    int t1029;
    int t1030;
    int v_l20[5];
    int t1034;
    int t1035;
    int t1038;
    int t1042;
    int t1045;
    int t1048;
    int t1053;
    bool t1059;
    t1003 = (int)((int)&v_l40);
    t1004 = false;
    v_l40 = (int)((int)0);
    t1006 = (int)FUN_005bf0e0((unsigned int)(a4), (unsigned int)(t1003));
    if ((unsigned char)(t1006) != (unsigned char)0) {
        t1009 = (int)(v_l40);
        t1010 = (int)((int)&v_l44);
        v_l44 = (int)((int)0);
        t1006 = (int)FUN_005bf1e0((unsigned int)(t1009), (unsigned int)(t1010));
        if ((unsigned char)(t1006) != (unsigned char)0) {
            t1013 = (int)(v_l44);
            ((C_00595a90*)(t1013))->FUN_00595a90((unsigned int)(a4));
            t1017 = (int)(v_l44);
            t1018 = (int)((int)&v_l28);
            t1019 = (int)((C_00595230*)(t1017))->FUN_00595230((unsigned int)(t1018));
            if ((unsigned char)(t1019) != (unsigned char)0) {
                t1022 = (int)((*(int*)&v_l28[1]));
                t1023 = (int)((int)&v_l36);
                t1024 = (int)((*(int*)&v_l28[0]));
                t1025 = (int)((int)&v_l32);
                FUN_00593960((unsigned int)(t1024), (unsigned int)(t1022), (unsigned int)(t1025), (unsigned int)(t1023));
                t1029 = (int)(v_l36);
                t1030 = (int)((int)&v_l20);
                ((C_006b5770*)(t1030))->FUN_006b5770((unsigned int)((int)1648177088), (unsigned int)(t1029), (unsigned int)((int)0));
                t1034 = (int)((int)&v_l20);
                t1035 = (int)((C_006b55c0*)(t1034))->FUN_006b55c0();
                t1038 = (int)((int)(a8));
                ((C_005c3d90*)(t1038))->FUN_005c3d90((unsigned int)(t1035));
                t1042 = (int)((int)&v_l20);
                t1006 = (int)((C_006b5240*)(t1042))->FUN_006b5240();
            } else {
                t1045 = (int)((int)(a8));
                t1006 = (int)((C_005c3d90*)(t1045))->FUN_005c3d90((unsigned int)((int)g_013ec468));
            }
            t1004 = true;
        }
        t1048 = (int)(v_l44);
        if (t1048 != (int)0) {
            t1006 = (int)((il2c_vc0*)(t1048))->s1();
        }
    }
    t1053 = (int)(v_l40);
    if (t1053 != (int)0) {
        t1006 = (int)((il2c_vc1*)(t1053))->s1();
    }
    t1059 = t1004;
    return t1059;
}
