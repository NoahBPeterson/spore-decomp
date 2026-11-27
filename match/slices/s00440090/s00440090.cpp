// 0x00440090: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0043f3a0/s0043f3a0.cpp, src/game/SPBake/SPEditorBlock.cpp.

struct C_00440520 { int FUN_00440520(float, unsigned int, unsigned int); };
struct C_004adc40 { int FUN_004adc40(); };
#pragma pack(push, 1)
struct Fr0_00440090 {
    int v_l12;
    int v_l8;
};
#pragma pack(pop)


struct D_00440090 { void FUN_00440090(float a4, int a8); };
// @ 0x00440090
void D_00440090::FUN_00440090(float a4, int a8)
{
    Fr0_00440090 fb;
    ((C_00440520*)(int)this)->FUN_00440520((float)a4, (unsigned int)(int)(unsigned char)a8, (unsigned int)0);
    if ((int)*(int*)((char*)(int)this + 40) != 0) {
        if ((int)(unsigned char)(int)((C_004adc40*)(int)*(int*)((char*)(int)this + 40))->FUN_004adc40() != 0) {
            fb.v_l8 = (int)(int)*(int*)((char*)(int)this + 992);
            if (fb.v_l8 != 0) {
                fb.v_l12 = (int)(int)*(int*)((char*)(int)this + 992);
                ((C_00440520*)fb.v_l12)->FUN_00440520((float)a4, (unsigned int)(int)(unsigned char)a8, (unsigned int)0);
            }
        }
    }
    return;
}
