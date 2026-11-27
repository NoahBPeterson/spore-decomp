// 0x0047fc10: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0047f520/s0047f520.cpp, src/game/SPBake/SPEditorHandleDeform.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
};

extern "C" unsigned char g_013ef25c[];
extern "C" unsigned char g_013ef270[];
struct C_0047d870 { int FUN_0047d870(); };
struct C_0047fcb0 { void FUN_0047fcb0(); };
extern "C" void __cdecl FUN_00f47380(...);
#pragma pack(push, 1)
struct Fr0_0047fc10 {
    int v_l24;
    int v_l20;
    int v_l16;
    int v_l12;
    int v_l8;
};
#pragma pack(pop)


struct D_0047fc10 { void FUN_0047fc10(); };
// @ 0x0047fc10
void D_0047fc10::FUN_0047fc10()
{
    Fr0_0047fc10 fb;
    *(int*)(char*)(int)this = (int)g_013ef270;
    *(int*)((char*)(int)this + 4) = (int)g_013ef25c;
    ((C_0047fcb0*)(int)this)->FUN_0047fcb0();
    fb.v_l8 = (int)this + 396;
    if ((int)*(int*)(char*)fb.v_l8 != 0) {
        ((il2c_vc0*)(int)*(int*)(char*)fb.v_l8)->s1();
    }
    fb.v_l24 = (int)this + 284;
    if ((int)((int)*(int*)((char*)fb.v_l24 + 8) - (int)*(int*)(char*)fb.v_l24) > 1) {
        fb.v_l20 = (int)(int)((int)*(int*)((char*)fb.v_l24 + 8) - (int)*(int*)(char*)fb.v_l24);
        fb.v_l16 = (int)(int)*(int*)(char*)fb.v_l24;
        if (fb.v_l16 != 0) {
            fb.v_l12 = fb.v_l16;
            FUN_00f47380((unsigned int)fb.v_l12);
        }
    }
    ((C_0047d870*)(int)this)->FUN_0047d870();
    return;
}
