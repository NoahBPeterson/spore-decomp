// 0x0047d870: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0047d450/s0047d450.cpp, src/game/SPBake/SPEditorHandle.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual int s1();
};

extern "C" unsigned char g_013eb938[];
extern "C" unsigned char g_013ec458[];
extern "C" unsigned char g_013ef0fc[];
extern "C" unsigned char g_013ef110[];
struct C_0040f360 { void FUN_0040f360(); };
struct C_0047e2c0 { void FUN_0047e2c0(); };
#pragma pack(push, 1)
struct Fr0_0047d870 {
    int v_l32;
    int v_l28;
    int dead0[2];
    int v_l16;
    int dead1[2];
};
#pragma pack(pop)


struct D_0047d870 { void FUN_0047d870(); };
// @ 0x0047d870
void D_0047d870::FUN_0047d870()
{
    Fr0_0047d870 fb;
    *(int*)(char*)(int)this = (int)g_013ef110;
    *(int*)((char*)(int)this + 4) = (int)g_013ef0fc;
    ((C_0047e2c0*)(int)this)->FUN_0047e2c0();
    fb.v_l16 = (int)this + 24;
    if ((int)*(int*)(char*)fb.v_l16 != 0) {
        ((C_0040f360*)(int)*(int*)(char*)fb.v_l16)->FUN_0040f360();
    }
    fb.v_l28 = (int)this + 20;
    if ((int)*(int*)(char*)fb.v_l28 != 0) {
        ((C_0040f360*)(int)*(int*)(char*)fb.v_l28)->FUN_0040f360();
    }
    fb.v_l32 = (int)this + 12;
    if ((int)*(int*)(char*)fb.v_l32 != 0) {
        ((il2c_vc0*)(int)*(int*)(char*)fb.v_l32)->s1();
    }
    *(int*)((char*)(int)this + 4) = (int)g_013ec458;
    *(int*)(char*)(int)this = (int)g_013eb938;
    return;
}
