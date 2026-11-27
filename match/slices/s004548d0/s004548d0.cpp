// 0x004548d0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00454330/s00454330.cpp.

struct C_0050f740 { int FUN_0050f740(unsigned int, unsigned int); };
struct C_00541030 { int FUN_00541030(unsigned int, unsigned int, unsigned int); };
#pragma pack(push, 1)
struct Fr0_004548d0 {
    int dead0[6];
    int v_l24;
    int v_l20;
    int v_l16;
    int v_l12;
    int v_l8;
};
#pragma pack(pop)


struct D_004548d0 { void FUN_004548d0(int a4); };
// @ 0x004548d0
void D_004548d0::FUN_004548d0(int a4)
{
    Fr0_004548d0 fb;
    if ((unsigned int)a4 > (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 12)) {
        fb.v_l16 = 0;
        fb.v_l12 = 0;
        fb.v_l8 = 0;
        fb.v_l24 = (int)(int)(a4 - (int)((int)(int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 12));
        fb.v_l20 = (int)(int)*(int*)((char*)(int)this + 4);
        ((C_00541030*)(int)this)->FUN_00541030((unsigned int)fb.v_l20, (unsigned int)fb.v_l24, (unsigned int)(int)&fb.v_l16);
    } else {
        ((C_0050f740*)(int)this)->FUN_0050f740((unsigned int)(int)(a4 * 12 + (int)*(int*)(char*)(int)this), (unsigned int)(int)*(int*)((char*)(int)this + 4));
    }
    return;
}
