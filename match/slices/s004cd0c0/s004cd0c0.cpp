// 0x004cd0c0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004cc190/s004cc190.cpp.

struct C_004cd790 { void FUN_004cd790(unsigned int); };
#pragma pack(push, 1)
struct Fr0_004cd0c0 {
    int dead0[9];
    int v_l16;
    int dead1[1];
    int v_l8;
};
#pragma pack(pop)


struct D_004cd0c0 { int FUN_004cd0c0(int a4); };
// @ 0x004cd0c0
int D_004cd0c0::FUN_004cd0c0(int a4)
{
    Fr0_004cd0c0 fb;
    fb.v_l8 = (int)this + 24;
    *(int*)(char*)(int)this = 0;
    *(int*)((char*)(int)this + 4) = 0;
    *(int*)((char*)(int)this + 8) = 0;
    fb.v_l16 = (int)this + 12;
    *(int*)((char*)fb.v_l16 + 4) = fb.v_l8;
    *(int*)((char*)(int)this + 4) = (int)this + 24;
    *(int*)(char*)(int)this = (int)(int)*(int*)((char*)(int)this + 4);
    *(int*)((char*)(int)this + 8) = (int)(int)((int)*(int*)(char*)(int)this + 256);
    ((C_004cd790*)(int)this)->FUN_004cd790((unsigned int)a4);
    return (int)this;
}
