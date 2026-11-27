// 0x0053ece0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0053e120/s0053e120.cpp.

#pragma pack(push, 1)
struct Fr0_0053ece0 {
    int v_l28;
    int v_l24;
    int v_l20;
    int v_l16;
    int v_l12;
    int dead0[1];
};
#pragma pack(pop)


struct D_0053ece0 { int FUN_0053ece0(int a4, int a8); };
// @ 0x0053ece0
int D_0053ece0::FUN_0053ece0(int a4, int a8)
{
    Fr0_0053ece0 fb;
    *(int*)((char*)(int)this + 28) = (int)(int)((int)((int)*(int*)((char*)(int)this + 56) & -16384) | (int)*(int*)((char*)(int)this + 28));
    *(int*)((char*)(int)this + 56) = (int)(int)((int)*(int*)((char*)(int)this + 56) & 16383);
    *(int*)((char*)(int)*(int*)((char*)(int)this + 32) + (int)*(int*)((char*)(int)this + 56) * 8) = a4;
    fb.v_l12 = (int)&fb.v_l16;
    *(int*)(char*)fb.v_l12 = a4;
    fb.v_l24 = (int)(int)*(int*)((char*)(int)this + 56);
    fb.v_l20 = (int)this + 60;
    *(int*)((char*)(int)*(int*)(char*)fb.v_l20 + (a8 & 16383) * 8) = fb.v_l16;
    *(int*)((char*)(int)*(int*)(char*)fb.v_l20 + (a8 & 16383) * 8 + 4) = fb.v_l24;
    fb.v_l28 = (int)(int)*(int*)((char*)(int)this + 56);
    *(int*)((char*)(int)this + 56) = (int)(int)((int)*(int*)((char*)(int)this + 56) + 1);
    return (int)(int)((int)*(int*)((char*)(int)this + 32) + (fb.v_l28 << 3));
}
