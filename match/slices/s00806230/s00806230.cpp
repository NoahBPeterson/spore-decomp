// 0x00806230: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/Spui/SPUIHelpers.cpp, match/slices/s00805940/s00805940.cpp.

struct il2c_vc0 {
    virtual void s0();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual int s3(int);
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
    virtual void s13(int);
};

extern "C" unsigned char g_014178f4[];
extern "C" unsigned char g_0147d84e[];
extern "C" int __cdecl FUN_0067dd60(...);
struct C_007f54d0 { int FUN_007f54d0(); };
struct C_00833790 { void FUN_00833790(); };
struct C_00833a80 { int FUN_00833a80(); };
struct C_00833ba0 { int FUN_00833ba0(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int); };

// @ 0x00806230
extern "C" bool __cdecl FUN_00806230(int a4, int a8, int a12, int a16, int a20)
{
    int t1000;
    int t1003;
    int t1004;
    int t1005;
    int t1006;
    int v_l36[3];
    int t1007;
    int v_l12[3];
    int v_l24[3];
    int t1011;
    int t1012;
    int t1013;
    int t1014;
    int t1015;
    int t1016;
    bool t1019;
    int t1020;
    int t1026;
    int t1027;
    int t1030;
    int t1033;
    int t1034;
    int t1037;
    unsigned char t19;
    int t1038;
    int t1042;
    int t1047;
    bool t1052;
    t1000 = (int)((int)(a4));
    t1003 = (int)((int)(a8));
    *(int*)((char*)(t1003)) = (int)((int)0);
    t1004 = (int)(*(int*)((char*)(t1000)));
    t1005 = (int)(*(int*)((char*)(t1000) + 4));
    t1006 = (int)(*(int*)((char*)(t1000) + 8));
    (*(int*)&v_l36[0]) = (int)(t1004);
    t1007 = (int)((int)&v_l12);
    (*(int*)&v_l36[1]) = (int)(t1005);
    (*(int*)&v_l36[2]) = (int)(t1006);
    ((C_00833790*)(t1007))->FUN_00833790();
    (*(int*)&v_l24[1]) = (int)(t1003);
    (*(int*)&v_l24[0]) = (int)((int)g_014178f4);
    (*(int*)&v_l24[2]) = (int)((int)1);
    *(int*)((char*)(t1003)) = (int)((int)0);
    if ((*(int*)&v_l36[1]) != (int)0) {
        if ((*(int*)&v_l36[0]) != (int)0) {
            t1011 = (int)((int)(a20));
            t1012 = (int)((int)(a16));
            t1013 = (int)((int)&v_l36);
            t1014 = (int)((int)&v_l24);
            t1015 = (int)((int)&v_l12);
            t1016 = (int)((C_00833ba0*)(t1015))->FUN_00833ba0((unsigned int)(t1014), (unsigned int)((int)1021), (unsigned int)(t1013), (unsigned int)(t1012), (unsigned int)(t1011));
            if ((unsigned char)(t1016) != (unsigned char)0) {
                t1019 = true;
                goto L8062b4;
            }
        }
    }
    t1019 = false;
    L8062b4:;
    t1020 = (int)(*(int*)((char*)(t1003)));
    if (t1020 != (int)0) {
        ((il2c_vc0*)(t1020))->s0();
    }
    if (t1019 != (unsigned char)0) {
        if ((unsigned char)(a12) != (unsigned char)0) {
            t1026 = (int)(*(int*)((char*)(t1003)));
            t1027 = (int)(*(int*)((char*)(t1026) + 4));
            if (t1027 != (int)0) {
                t1030 = (int)((il2c_vc1*)(t1027))->s3((int)((int)g_0147d84e));
            } else {
                t1030 = (int)((int)0);
            }
            t1033 = (int)(t1030);
            t1034 = (int)((C_007f54d0*)(t1033))->FUN_007f54d0();
            t1037 = (int)(t1034);
            t19 = (unsigned char)((unsigned char)*(unsigned char*)((char*)(t1037) + 4) & (unsigned char)1);
            if (t19 == (unsigned char)0) {
                t1038 = (int)FUN_0067dd60();
                t1042 = (int)(t1038);
                ((il2c_vc2*)(t1042))->s13((int)(t1037));
            }
        }
    }
    t1047 = (int)((int)&v_l12);
    ((C_00833a80*)(t1047))->FUN_00833a80();
    t1052 = t1019;
    return t1052;
}
