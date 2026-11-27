// 0x0051d010: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0051c470/s0051c470.cpp, src/game/SPBake/SPSkinnerPaintRender.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
};

extern "C" unsigned char g_013eb394[];
extern "C" unsigned char g_013eb918[];
extern "C" unsigned char g_013eb938[];
extern "C" unsigned char g_013ef094[];
struct C_004039f0 { void FUN_004039f0(); };
#pragma pack(push, 1)
struct Fr0_0051d010 {
    int v_l48;
    int v_l44;
    int v_l40;
    int dead0[8];
};
#pragma pack(pop)


struct D_0051d010 { void FUN_0051d010(); };
// @ 0x0051d010
void D_0051d010::FUN_0051d010()
{
    Fr0_0051d010 fb;
    fb.v_l40 = (int)this + 52;
    if ((int)*(int*)(char*)fb.v_l40 != 0) {
        ((C_004039f0*)fb.v_l40)->FUN_004039f0();
    }
    fb.v_l44 = (int)this + 48;
    if ((int)*(int*)(char*)fb.v_l44 != 0) {
        ((il2c_vc0*)(int)*(int*)(char*)fb.v_l44)->s1();
    }
    fb.v_l48 = (int)this + 8;
    *(int*)((char*)fb.v_l48 + 4) = (int)g_013ef094;
    *(int*)(char*)fb.v_l48 = (int)g_013eb938;
    *(int*)((char*)(int)this + 4) = (int)g_013eb918;
    *(int*)(char*)(int)this = (int)g_013eb394;
    return;
}
