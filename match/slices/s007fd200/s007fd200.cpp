// 0x007fd200: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/Spui/_at_007f0000.cpp, match/slices/s007fc880/s007fc880.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual int s7();
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
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual int s21();
};

extern "C" int __cdecl FUN_007fcff0(...);
extern "C" int __cdecl FUN_007fd140(...);


struct D_007fd200 { void FUN_007fd200(int a4, int a8); };
// @ 0x007fd200
// @ 0x007fd200
void D_007fd200::FUN_007fd200(int a4, int a8)
{
    int v_l8;
    int v_l16;
    int v_l12;
    v_l8 = (int)(int)*(int*)((char*)(int)this + 16);
    v_l12 = (int)(int)(~a4 & (int)*(int*)((char*)(int)this + 16));
    if ((int)(unsigned char)a8 != 0) {
        v_l12 = v_l12 | a4;
    }
    if (v_l8 == v_l12) {
    } else {
        *(int*)((char*)(int)this + 16) = v_l12;
        v_l16 = (int)(int)((int)*(int*)((char*)(int)this + 56) != 0 ? (int)(int)((il2c_vc0*)(int)*(int*)((char*)(int)this + 56))->s7() : 0);
        if (v_l16 != 0) {
            if (((v_l8 ^ v_l12) & 1) != 0) {
                if ((int)(unsigned char)(int)((il2c_vc1*)(int)(int)*(int*)((char*)(int)this + 56))->s21() != 0) {
                    if ((int)((int)*(int*)((char*)(int)this + 16) & 1) != 0) {
                        FUN_007fd140((unsigned int)v_l16);
                    } else {
                        FUN_007fcff0((unsigned int)v_l16);
                    }
                }
            }
        }
    }
    return;
}
