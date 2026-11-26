// 0x00b0f9a0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPTerrain/SPTerrainCameraController.cpp, match/slices/s00b0f270/s00b0f270.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual int s6(int);
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual int s6(int);
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual int s6(int);
};
struct il2c_vc3 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual int s6(int);
};
struct il2c_vc4 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual int s6(int);
};
struct il2c_vc5 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual int s6(int);
};
struct il2c_vc6 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual int s6(int);
};
struct il2c_vc7 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual int s6(int);
};
struct il2c_vc8 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual int s6(int);
};
struct il2c_vc9 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual int s6(int);
};

struct C_00b3d250 { int FUN_00b3d250(); };

// @ 0x00b0f9a0
extern "C" bool __fastcall FUN_00b0f9a0(char* self, int edx_unused)
{
    int t1003;
    int t1006;
    int t1007;
    int t1010;
    int t1015;
    int t1020;
    int t1025;
    int t1030;
    int t1035;
    int t1040;
    int t1045;
    int t1050;
    int t1055;
    bool t1061;
    t1003 = (int)((int)(self));
    t1006 = (int)((C_00b3d250*)((int)(self)))->FUN_00b3d250();
    t1007 = (int)(t1006);
    if ((unsigned char)*(unsigned char*)((char*)(t1003) + 17) == (unsigned char)0) {
        if ((unsigned char)*(unsigned char*)((char*)(t1003) + 793) != (unsigned char)0) {
            t1010 = (int)(t1007);
            t1006 = (int)((il2c_vc0*)(t1010))->s6((int)((int)1));
            if ((unsigned char)(t1006) == (unsigned char)0) {
                t1015 = (int)(t1007);
                t1006 = (int)((il2c_vc1*)(t1015))->s6((int)((int)2));
                if ((unsigned char)(t1006) == (unsigned char)0) {
                    t1020 = (int)(t1007);
                    t1006 = (int)((il2c_vc2*)(t1020))->s6((int)((int)3));
                    if ((unsigned char)(t1006) == (unsigned char)0) {
                        t1025 = (int)(t1007);
                        t1006 = (int)((il2c_vc3*)(t1025))->s6((int)((int)4));
                        if ((unsigned char)(t1006) == (unsigned char)0) {
                            t1030 = (int)(t1007);
                            t1006 = (int)((il2c_vc4*)(t1030))->s6((int)((int)7));
                            if ((unsigned char)(t1006) == (unsigned char)0) {
                                t1035 = (int)(t1007);
                                t1006 = (int)((il2c_vc5*)(t1035))->s6((int)((int)8));
                                if ((unsigned char)(t1006) == (unsigned char)0) {
                                    t1040 = (int)(t1007);
                                    t1006 = (int)((il2c_vc6*)(t1040))->s6((int)((int)9));
                                    if ((unsigned char)(t1006) == (unsigned char)0) {
                                        t1045 = (int)(t1007);
                                        t1006 = (int)((il2c_vc7*)(t1045))->s6((int)((int)16));
                                        if ((unsigned char)(t1006) == (unsigned char)0) {
                                            t1050 = (int)(t1007);
                                            t1006 = (int)((il2c_vc8*)(t1050))->s6((int)((int)17));
                                            if ((unsigned char)(t1006) == (unsigned char)0) {
                                                t1055 = (int)(t1007);
                                                t1006 = (int)((il2c_vc9*)(t1055))->s6((int)((int)18));
                                                if ((unsigned char)(t1006) == (unsigned char)0) {
                                                    return 0;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    t1061 = true;
    return (bool)(t1061);
}
