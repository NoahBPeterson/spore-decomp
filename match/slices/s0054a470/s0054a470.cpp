// 0x0054a470: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00549e40/s00549e40.cpp.

struct C_0047d390 { void FUN_0047d390(unsigned int, unsigned int); };
#pragma pack(push, 1)
struct Fr0_0054a470 {
    int v_l12;
    int v_l8;
};
#pragma pack(pop)


struct D_0054a470 { int FUN_0054a470(int a4); };
// @ 0x0054a470
int D_0054a470::FUN_0054a470(int a4)
{
    Fr0_0054a470 fb;
    *(int*)(char*)(int)this = (int)(int)*(int*)(char*)a4;
    fb.v_l12 = a4 + 4;
    fb.v_l8 = (int)this + 4;
    *(int*)(char*)fb.v_l8 = 0;
    *(int*)((char*)fb.v_l8 + 4) = 0;
    *(int*)((char*)fb.v_l8 + 8) = 0;
    ((C_0047d390*)fb.v_l8)->FUN_0047d390((unsigned int)(int)*(int*)(char*)fb.v_l12, (unsigned int)(int)*(int*)((char*)fb.v_l12 + 4));
    return (int)this;
}
