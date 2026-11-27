// 0x0045f0e0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0045edf0/s0045edf0.cpp.

struct C_0045f140 { int FUN_0045f140(unsigned int); };
#pragma pack(push, 1)
struct Fr0_0045f0e0 {
    int dead0[16];
    int v_l12;
    int v_l8;
};
struct Fr1_0045f0e0 {
    int dead0[1];
};
#pragma pack(pop)


struct D_0045f0e0 { void FUN_0045f0e0(int a4); };
// @ 0x0045f0e0
void D_0045f0e0::FUN_0045f0e0(int a4)
{
    Fr0_0045f0e0 fb;
    Fr1_0045f0e0 fa;
    fb.v_l8 = (int)(int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this);
    fb.v_l12 = (int)(int)((unsigned int)a4 < (unsigned int)fb.v_l8 ? (int)&fb.v_l8 : (int)&a4);
    *(int*)&a4 = (int)(int)((int)*(int*)(char*)fb.v_l12 + 1);
    if ((unsigned int)a4 > (unsigned int)(int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this)) {
        ((C_0045f140*)(int)this)->FUN_0045f140((unsigned int)a4);
    }
    return;
}
