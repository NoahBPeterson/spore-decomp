// 0x007fc690: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/Spui/SPUIBehavior.cpp, match/slices/s007fb7b0/s007fb7b0.cpp.

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
    virtual int s11();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1(int, int);
};

struct C_00423650 { void FUN_00423650(unsigned int, unsigned int); };
struct C_004237d0 { int FUN_004237d0(); };
struct C_0056e2d0 { void FUN_0056e2d0(unsigned int); };
extern "C" int __cdecl FUN_00571e00(...);
struct C_007f93d0 { int FUN_007f93d0(unsigned int); };
extern "C" int __cdecl FUN_007fa4c0(...);
struct C_007fbce0 { void FUN_007fbce0(); };
struct C_007fc2a0 { void FUN_007fc2a0(); };


struct D_007fc690 { bool FUN_007fc690(int a4); };
// @ 0x007fc690
bool D_007fc690::FUN_007fc690(int a4)
{
    int dead_0_15[3];
    int dead_2_66[5];
    int v_l44_b;
    int dead_1_12[5];
    int v_l20;
    unsigned char v_l101_d;
    int v_l100_b;
    int v_l96_a;
    int v_l92[4];
    int v_l76_c;
    int dead_3_16;
    int v_l68;
    char dead_5_b;
    char dead_4;
    char dead_6;
    int dead_7;
    int dead_8_28[3];
    int v_l112;
    ((C_0056e2d0*)(int)&v_l20)->FUN_0056e2d0((unsigned int)((int)this + 80));
    ((C_00423650*)((int)this + 80))->FUN_00423650((unsigned int)a4, (unsigned int)(int)(a4 + (int)((int)FUN_00571e00((unsigned int)a4) << 1)));
    ((C_007fc2a0*)(int)&v_l92)->FUN_007fc2a0();
    v_l96_a = (int)(int)FUN_007fa4c0((unsigned int)(int)&v_l92, (unsigned int)38760187);
    v_l112 = (int)(int)*(int*)((char*)(int)this + 80);
    v_l76_c = v_l112;
    v_l68 = v_l20;
    v_l100_b = 0;
    for (; v_l100_b < 4; v_l100_b = v_l100_b + 1) {
        if ((int)*(int*)(char*)((C_007f93d0*)((int)this - 24))->FUN_007f93d0((unsigned int)v_l100_b) != 0) {
            ((il2c_vc1*)(int)(int)(int)((il2c_vc0*)(int)(int)(int)*(int*)(char*)((C_007f93d0*)((int)this - 24))->FUN_007f93d0((unsigned int)v_l100_b))->s11())->s1(v_l44_b, v_l96_a);
        }
    }
    v_l101_d = (unsigned char)1;
    ((C_007fbce0*)(int)&v_l92)->FUN_007fbce0();
    ((C_004237d0*)(int)&v_l20)->FUN_004237d0();
    return *(bool*)&v_l101_d;
}
