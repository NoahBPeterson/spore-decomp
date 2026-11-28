// 0x0045cd90: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0045c350/s0045c350.cpp.

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
    virtual int s14(int, int);
};

struct C_00429300 { int FUN_00429300(); };
struct C_0045d6f0 { void FUN_0045d6f0(); };
struct C_0045da50 { void FUN_0045da50(unsigned int, unsigned int); };

// @ 0x0045cd90
// @ 0x0045cd90
extern "C" bool __cdecl FUN_0045cd90(int a4, int a8, int a12)
{
    int v_l8;
    int dead_5_b[15];
    int dead_4[15];
    int dead_3_46[15];
    int dead_2_10[15];
    int dead_1_33[15];
    int dead_0[15];
    int dead_6[15];
    int dead_8_39[15];
    int dead_7[15];
    int dead_10_j[15];
    int dead_9[15];
    int v_l800_18;
    int dead_13_b[2];
    int dead_12_h[15];
    int dead_11[15];
    int v_l804;
    int dead_18_i[3];
    int v_l828_c;
    int v_l824_11;
    int dead_17[3];
    char dead_16_d;
    char dead_15_i;
    char dead_14;
    unsigned char v_l805;
    ((C_0045d6f0*)(int)&v_l804)->FUN_0045d6f0();
    v_l8 = (int)&a12;
    ((C_0045da50*)(int)&v_l804)->FUN_0045da50((unsigned int)a8, (unsigned int)v_l8);
    v_l8 = 0;
    v_l824_11 = v_l800_18 - v_l804;
    v_l828_c = v_l804;
    v_l805 = (unsigned char)(unsigned char)((il2c_vc0*)a4)->s14(v_l828_c, v_l824_11);
    ((C_00429300*)(int)&v_l804)->FUN_00429300();
    return *(bool*)&v_l805;
}
