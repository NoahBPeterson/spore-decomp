// 0x00675700: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s006755c0/s006755c0.cpp.

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
    virtual int s11(int, int, int);
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
    virtual int s9(int, int);
};
struct il2c_vc2 {
    virtual void s0();
    virtual int s1();
};

struct C_0041e920 { int FUN_0041e920(); };
extern "C" int __cdecl FUN_0067de30(...);

// @ 0x00675700
extern "C" bool __stdcall FUN_00675700(int a4)
{
    int v_l4;
    int t1002;
    int t1007;
    int t1008;
    int t1009;
    int t1010;
    int t1013;
    bool t1014;
    int t1017;
    int t1020;
    int t1023;
    bool t1028;
    v_l4 = (int)((int)0);
    t1002 = (int)FUN_0067de30();
    t1007 = (int)((int)&v_l4);
    t1008 = (int)((int)(a4));
    t1009 = (int)(t1002);
    t1010 = (int)((il2c_vc0*)(t1009))->s11((int)(t1008), (int)((int)96402727), (int)(t1007));
    t1013 = (int)(v_l4);
    t1014 = false;
    if (t1013 != (int)0) {
        t1017 = (int)((int)&a4);
        t1010 = (int)((il2c_vc1*)(t1013))->s9((int)((int)96400077), (int)(t1017));
        if ((unsigned char)(t1010) != (unsigned char)0) {
            t1020 = (int)((int)(a4));
            if ((unsigned short)*(unsigned short*)((char*)(t1020) + 18) == (unsigned short)1) {
                t1010 = (int)((C_0041e920*)(t1020))->FUN_0041e920();
                t1014 = *(bool*)((char*)(t1010));
            }
        }
        t1023 = (int)(v_l4);
        if (t1023 != (int)0) {
            t1010 = (int)((il2c_vc2*)(t1023))->s1();
        }
    }
    t1028 = t1014;
    return t1028;
}
