// 0x0040ce80: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0040ccb0/s0040ccb0.cpp.

struct C_0041cb40 { void FUN_0041cb40(unsigned int); };
#pragma pack(push, 1)
struct Fr0_0040ce80 {
    int v_l60;
    int dead0[11];
    int v_l12;
    int v_l8;
};
#pragma pack(pop)


struct D_0040ce80 { int FUN_0040ce80(int a4); };
// @ 0x0040ce80
int D_0040ce80::FUN_0040ce80(int a4)
{
    Fr0_0040ce80 fb;
    *(unsigned short*)(char*)(int)this = (unsigned short)(unsigned short)*(unsigned short*)(char*)a4;
    *(unsigned short*)((char*)(int)this + 2) = (unsigned short)(unsigned short)*(unsigned short*)((char*)a4 + 2);
    fb.v_l12 = a4 + 4;
    fb.v_l8 = (int)this + 4;
    *(float*)(char*)fb.v_l8 = *(float*)(char*)fb.v_l12;
    *(float*)((char*)fb.v_l8 + 4) = *(float*)((char*)fb.v_l12 + 4);
    *(float*)((char*)fb.v_l8 + 8) = *(float*)((char*)fb.v_l12 + 8);
    *(float*)((char*)(int)this + 16) = *(float*)((char*)a4 + 16);
    fb.v_l60 = (int)this + 20;
    ((C_0041cb40*)fb.v_l60)->FUN_0041cb40((unsigned int)(a4 + 20));
    return (int)this;
}
