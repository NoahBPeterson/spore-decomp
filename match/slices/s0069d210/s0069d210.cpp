// 0x0069d210: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEngine/SPObjectDatabase.cpp.

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
    virtual int s13(int, int);
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
    virtual int s13(int, int);
};


// @ 0x0069d210
// @ 0x0069d210
extern "C" bool __fastcall FUN_0069d210(char* self, int edx_unused, int a4)
{
    int t1000;
    int t1004;
    int t1005;
    int t1007;
    int t1008;
    int t1009;
    int t1010;
    int t1011;
    int t1013;
    int t1016;
    int v_l1024[256];
    int t1017;
    int t1025;
    bool t1028;
    t1000 = (int)((int)(a4));
    t1004 = (int)((int)(self));
    t1005 = (int)(t1000);
    if (t1000 >= (int)1024) {
        t1007 = (int)(t1000);
        t1008 = (int)((unsigned int)(t1007) >> (int)10);
        t1009 = (int)(t1008);
        t1010 = (int)(t1009 << (int)10);
        t1011 = (int)(t1000 - t1010);
        t1013 = (int)(t1004 + (int)8);
        t1005 = (int)(t1011);
        do {
            t1016 = (int)((int)&v_l1024);
            t1017 = (int)(t1013);
            t1000 = (int)((il2c_vc0*)(t1017))->s13((int)(t1016), (int)((int)1024));
            t1008 = (int)(t1008 - (int)1);
        } while (t1008 != (int)0);
    }
    if (t1005 > (int)0) {
        t1025 = (int)((int)&v_l1024);
        t1000 = (int)((il2c_vc1*)((t1004 + (int)(8))))->s13((int)(t1025), (int)(t1005));
    }
    t1028 = *(bool*)((char*)(t1004) + 12);
    return t1028;
}
