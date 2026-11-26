// 0x00e2fc40: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPUIShared.cpp, match/slices/s00e2f6e0/s00e2f6e0.cpp.

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
    virtual int s10(int);
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
    virtual int s10(int);
};

extern "C" unsigned char g_00f62def[];
struct C_00e2f980 { int FUN_00e2f980(); };

// @ 0x00e2fc40
extern "C" bool __fastcall FUN_00e2fc40(char* self, int edx_unused, int a4, int a8)
{
    int t1000;
    int t1003;
    int t1004;
    bool t1009;
    int t1011;
    int t1012;
    bool t1017;
    int t1019;
    int t1020;
    bool t1023;
    t1000 = (int)((int)(a4));
    t1003 = (int)((int)(self));
    if (t1000 != (int)g_00f62def) {
        if (t1000 != (int)1396402852) {
            if (t1000 == (int)(-751080798)) {
                t1000 = (int)(*(int*)((char*)(t1003) + 52));
                if (t1000 != (int)0) {
                    t1004 = (int)(*(int*)((char*)(t1000) + 16));
                    t1000 = (int)((il2c_vc0*)(t1004))->s10((int)((int)0));
                }
                *(int*)((char*)(t1003) + 56) += (int)1;
            }
            t1009 = false;
            return (bool)(t1009);
        }
        t1011 = (int)(*(int*)((char*)(t1003) + 52));
        if (t1011 != (int)0) {
            t1012 = (int)(*(int*)((char*)(t1011) + 16));
            t1011 = (int)((il2c_vc1*)(t1012))->s10((int)((int)1));
        }
        *(int*)((char*)(t1003) + 56) -= (int)1;
        t1017 = false;
        return (bool)(t1017);
    }
    t1019 = (int)((int)(a8));
    if ((int)*(int*)((char*)(t1019) + 24) == (int)1551306167) {
        t1020 = (int)(t1003 + (int)(-28));
        t1019 = (int)((C_00e2f980*)(t1020))->FUN_00e2f980();
    }
    t1023 = true;
    return (bool)(t1023);
}
