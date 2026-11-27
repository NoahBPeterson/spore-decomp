// 0x00548e70: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00548d90/s00548d90.cpp.

struct C_00423650 { void FUN_00423650(unsigned int, unsigned int); };
struct C_00542b80 { void FUN_00542b80(unsigned int); };
#pragma pack(push, 1)
struct Fr0_00548e70 {
    int v_l12;
    int v_l8;
};
#pragma pack(pop)


struct D_00548e70 { int FUN_00548e70(int a4); };
// @ 0x00548e70
int D_00548e70::FUN_00548e70(int a4)
{
    Fr0_00548e70 fb;
    if (a4 != (int)this) {
        ((C_00423650*)(int)this)->FUN_00423650((unsigned int)(int)*(int*)(char*)a4, (unsigned int)(int)*(int*)((char*)a4 + 4));
    }
    fb.v_l12 = a4 + 16;
    fb.v_l8 = (int)this + 16;
    if (fb.v_l12 != fb.v_l8) {
        ((C_00423650*)fb.v_l8)->FUN_00423650((unsigned int)(int)*(int*)(char*)fb.v_l12, (unsigned int)(int)*(int*)((char*)fb.v_l12 + 4));
    }
    ((C_00542b80*)((int)this + 32))->FUN_00542b80((unsigned int)(a4 + 32));
    return (int)this;
}
