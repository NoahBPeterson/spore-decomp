// 0x0051a930: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0051a350/s0051a350.cpp, src/game/SPBake/SPSkinnerPaintRender.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
};

extern "C" unsigned char g_013ef094[];
extern "C" unsigned char g_013f1ac0[];
struct C_0051d180 { int FUN_0051d180(); };
struct C_00690120 { void FUN_00690120(); };
#pragma pack(push, 1)
struct Fr0_0051a930 {
    int dead0[5];
    int v_l12;
    int v_l8;
};
#pragma pack(pop)


struct D_0051a930 { void FUN_0051a930(); };
// @ 0x0051a930
void D_0051a930::FUN_0051a930()
{
    Fr0_0051a930 fb;
    *(int*)(char*)(int)this = (int)g_013f1ac0;
    fb.v_l8 = (int)this + 820;
    if ((int)*(int*)(char*)fb.v_l8 != 0) {
        ((C_00690120*)(int)*(int*)(char*)fb.v_l8)->FUN_00690120();
    }
    fb.v_l12 = (int)this + 816;
    if ((int)*(int*)(char*)fb.v_l12 != 0) {
        ((il2c_vc0*)(int)(int)*(int*)(char*)fb.v_l12)->s1();
    }
    ((C_0051d180*)((int)this + 8))->FUN_0051d180();
    *(int*)(char*)(int)this = (int)g_013ef094;
    return;
}
