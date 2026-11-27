// 0x007fa060: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s007f9550/s007f9550_od.cpp, src/game/Spui/SPUIBehavior.cpp.

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
    virtual void s10(int);
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
};

struct C_007f93d0 { int FUN_007f93d0(unsigned int); };
#pragma pack(push, 1)
struct Fr0_007fa060 {
    int v_l12;
    int v_l8;
};
#pragma pack(pop)


struct D_007fa060 { bool FUN_007fa060(); };
// @ 0x007fa060
bool D_007fa060::FUN_007fa060()
{
    Fr0_007fa060 fb;
    fb.v_l8 = 0;
    for (; fb.v_l8 < 4; fb.v_l8 = fb.v_l8 + 1) {
        fb.v_l12 = (int)((C_007f93d0*)((int)this - 24))->FUN_007f93d0((unsigned int)fb.v_l8);
        if ((int)*(int*)(char*)fb.v_l12 != 0) {
            ((il2c_vc0*)(int)(int)*(int*)(char*)fb.v_l12)->s10(0);
            ((il2c_vc1*)(int)*(int*)(char*)fb.v_l12)->s1();
            *(int*)(char*)fb.v_l12 = 0;
        }
    }
    return (bool)(unsigned char)1;
}
