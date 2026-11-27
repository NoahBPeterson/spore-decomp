// 0x0050cec0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0050c6c0/s0050c6c0.cpp.

struct C_0050e310 { void FUN_0050e310(unsigned int); };
#pragma pack(push, 1)
struct Fr0_0050cec0 {
    int dead0[43];
    int v_l16;
    int dead1[1];
    int v_l8;
};
struct Fr1_0050cec0 {
    int dead0[1];
};
#pragma pack(pop)


struct D_0050cec0 { int FUN_0050cec0(int a4); };
// @ 0x0050cec0
int D_0050cec0::FUN_0050cec0(int a4)
{
    Fr0_0050cec0 fb;
    Fr1_0050cec0 fa;
    fb.v_l8 = (int)this + 24;
    *(int*)(char*)(int)this = 0;
    *(int*)((char*)(int)this + 4) = 0;
    *(int*)((char*)(int)this + 8) = 0;
    fb.v_l16 = (int)this + 12;
    *(int*)((char*)fb.v_l16 + 4) = fb.v_l8;
    *(int*)((char*)(int)this + 4) = (int)this + 24;
    *(int*)(char*)(int)this = (int)(int)*(int*)((char*)(int)this + 4);
    *(int*)((char*)(int)this + 8) = (int)(int)((int)*(int*)(char*)(int)this + 1600);
    ((C_0050e310*)(int)this)->FUN_0050e310((unsigned int)a4);
    return (int)this;
}
