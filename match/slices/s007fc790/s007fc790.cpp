// 0x007fc790: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
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

struct C_007f93d0 { int FUN_007f93d0(unsigned int); };
extern "C" int __cdecl FUN_007fa4c0(...);
struct C_007fbce0 { int FUN_007fbce0(); };
struct C_007fc2a0 { void FUN_007fc2a0(); };


struct D_007fc790 { bool FUN_007fc790(int a4); };
// @ 0x007fc790
// @ 0x007fc790
bool D_007fc790::FUN_007fc790(int a4)
{
    int v_l52_f;
    int dead_1_33[5];
    int v_l28_l;
    int dead_0[5];
    int dead_2;
    unsigned char v_l89_p;
    int v_l88;
    int v_l84_i;
    int v_l80_d;
    int v_l76[4];
    int v_l60;
    char dead_5_16;
    char dead_4_35;
    char dead_3;
    v_l84_i = (int)(int)*(int*)((char*)(int)this + 76);
    *(int*)((char*)(int)this + 76) = a4;
    ((C_007fc2a0*)(int)&v_l76)->FUN_007fc2a0();
    v_l80_d = (int)(int)FUN_007fa4c0((unsigned int)(int)&v_l76, (unsigned int)38760186);
    v_l60 = (int)(int)*(int*)((char*)(int)this + 76);
    v_l52_f = v_l84_i;
    v_l88 = 0;
    for (; v_l88 < 4; v_l88 = v_l88 + 1) {
        if ((int)*(int*)(char*)((C_007f93d0*)((int)this - 24))->FUN_007f93d0((unsigned int)v_l88) != 0) {
            ((il2c_vc1*)(int)(int)(int)((il2c_vc0*)(int)(int)(int)*(int*)(char*)((C_007f93d0*)((int)this - 24))->FUN_007f93d0((unsigned int)v_l88))->s11())->s1(v_l28_l, v_l80_d);
        }
    }
    v_l89_p = (unsigned char)1;
    ((C_007fbce0*)(int)&v_l76)->FUN_007fbce0();
    return *(bool*)&v_l89_p;
}
