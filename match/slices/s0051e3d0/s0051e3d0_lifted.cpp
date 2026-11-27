// 0x0051e3d0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0051e3d0/s0051e3d0.cpp, src/game/SPBake/SPSkinnerPaintSystem.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc2 {
    virtual void s0();
    virtual int s1();
};

extern "C" unsigned char g_013eb394[];
extern "C" unsigned char g_013ef094[];
extern "C" unsigned char g_013f1c70[];
extern "C" unsigned char g_013f1c74[];
struct C_00402420 { void FUN_00402420(); };
struct C_00453540 { int FUN_00453540(); };
struct C_004e1bf0 { void FUN_004e1bf0(); };
struct C_00525e10 { int FUN_00525e10(); };
struct C_00526a40 { void FUN_00526a40(); };
struct C_00690120 { void FUN_00690120(); };
#pragma pack(push, 1)
struct Fr0_0051e3d0 {
    int v_l124;
    int dead0[3];
    int v_l108;
    int dead1[3];
    int v_l92;
    int v_l88;
    int dead2[3];
    int v_l72;
    int dead3[8];
    int v_l36;
    int v_l32;
    int v_l28;
    int v_l24;
    int v_l20;
    int v_l16;
    int v_l12;
    int v_l8;
};
#pragma pack(pop)


struct D_0051e3d0 { void FUN_0051e3d0(); };
// @ 0x0051e3d0
void D_0051e3d0::FUN_0051e3d0()
{
    Fr0_0051e3d0 fb;
    *(int*)(char*)(int)this = (int)g_013f1c74;
    *(int*)((char*)(int)this + 4) = (int)g_013f1c70;
    fb.v_l8 = (int)this + 260;
    if ((int)*(int*)(char*)fb.v_l8 != 0) {
        ((C_00453540*)(int)*(int*)(char*)fb.v_l8)->FUN_00453540();
    }
    fb.v_l12 = (int)this + 256;
    if ((int)*(int*)(char*)fb.v_l12 != 0) {
        ((C_00402420*)(int)*(int*)(char*)fb.v_l12)->FUN_00402420();
    }
    fb.v_l16 = (int)this + 252;
    if ((int)*(int*)(char*)fb.v_l16 != 0) {
        ((C_00690120*)(int)*(int*)(char*)fb.v_l16)->FUN_00690120();
    }
    fb.v_l20 = (int)this + 248;
    if ((int)*(int*)(char*)fb.v_l20 != 0) {
        ((C_00690120*)(int)*(int*)(char*)fb.v_l20)->FUN_00690120();
    }
    fb.v_l24 = (int)this + 244;
    if ((int)*(int*)(char*)fb.v_l24 != 0) {
        ((il2c_vc0*)(int)*(int*)(char*)fb.v_l24)->s1();
    }
    fb.v_l28 = (int)this + 240;
    if ((int)*(int*)(char*)fb.v_l28 != 0) {
        ((il2c_vc1*)(int)(int)*(int*)(char*)fb.v_l28)->s1();
    }
    fb.v_l36 = (int)this + 148;
    fb.v_l32 = (int)(int)*(int*)(char*)fb.v_l36;
    for (; (unsigned int)fb.v_l32 < (unsigned int)*(int*)((char*)fb.v_l36 + 4); fb.v_l32 = fb.v_l32 + 8) {
    }
    ((C_00526a40*)fb.v_l36)->FUN_00526a40();
    ((C_004e1bf0*)((int)this + 128))->FUN_004e1bf0();
    ((C_00525e10*)((int)this + 60))->FUN_00525e10();
    fb.v_l72 = (int)this + 28;
    if ((int)*(int*)(char*)fb.v_l72 != 0) {
        ((C_00453540*)(int)*(int*)(char*)fb.v_l72)->FUN_00453540();
    }
    fb.v_l88 = (int)this + 24;
    if ((int)*(int*)(char*)fb.v_l88 != 0) {
        ((C_00453540*)(int)*(int*)(char*)fb.v_l88)->FUN_00453540();
    }
    fb.v_l92 = (int)this + 20;
    if ((int)*(int*)(char*)fb.v_l92 != 0) {
        ((il2c_vc2*)(int)(int)*(int*)(char*)fb.v_l92)->s1();
    }
    fb.v_l108 = (int)this + 16;
    if ((int)*(int*)(char*)fb.v_l108 != 0) {
        ((C_00453540*)(int)*(int*)(char*)fb.v_l108)->FUN_00453540();
    }
    fb.v_l124 = (int)this + 12;
    if ((int)*(int*)(char*)fb.v_l124 != 0) {
        ((C_00453540*)(int)*(int*)(char*)fb.v_l124)->FUN_00453540();
    }
    *(int*)((char*)(int)this + 4) = (int)g_013ef094;
    *(int*)(char*)(int)this = (int)g_013eb394;
    return;
}
