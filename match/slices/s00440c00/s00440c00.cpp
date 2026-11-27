// 0x00440c00: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00440110/s00440110.cpp, src/game/SPBake/SPEditorBlock.cpp.

#pragma pack(push, 1)
struct Fr0_00440c00 {
    int v_l12;
    int v_l8;
};
#pragma pack(pop)


struct D_00440c00 { void FUN_00440c00(float a4); };
// @ 0x00440c00
void D_00440c00::FUN_00440c00(float a4)
{
    Fr0_00440c00 fb;
    fb.v_l8 = (int)(int)*(int*)((char*)(int)this + 16);
    if (fb.v_l8 != 0) {
        fb.v_l12 = (int)(int)*(int*)((char*)(int)this + 16);
        *(float*)((char*)fb.v_l12 + 88) = (float)a4;
    }
    return;
}
