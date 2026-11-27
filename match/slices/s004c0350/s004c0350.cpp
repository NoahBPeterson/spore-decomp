// 0x004c0350: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004bf430/s004bf430.cpp.

struct C_004c0680 { int FUN_004c0680(unsigned int, unsigned int); };
struct C_004c0bd0 { int FUN_004c0bd0(unsigned int, unsigned int, unsigned int); };
#pragma pack(push, 1)
struct Fr0_004c0350 {
    int dead0[5];
    int v_l152;
    int v_l148;
    int v_l144[35];
};
struct Fr1_004c0350 {
    int dead0[1];
};
#pragma pack(pop)


struct D_004c0350 { void FUN_004c0350(int a4); };
// @ 0x004c0350
void D_004c0350::FUN_004c0350(int a4)
{
    Fr0_004c0350 fb;
    Fr1_004c0350 fa;
    if ((unsigned int)a4 > (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 140)) {
        fb.v_l152 = (int)(int)(a4 - (int)((int)(int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 140));
        fb.v_l148 = (int)(int)*(int*)((char*)(int)this + 4);
        ((C_004c0bd0*)(int)this)->FUN_004c0bd0((unsigned int)fb.v_l148, (unsigned int)fb.v_l152, (unsigned int)(int)&fb.v_l144);
    } else {
        ((C_004c0680*)(int)this)->FUN_004c0680((unsigned int)(int)(a4 * 140 + (int)*(int*)(char*)(int)this), (unsigned int)(int)*(int*)((char*)(int)this + 4));
    }
    return;
}
