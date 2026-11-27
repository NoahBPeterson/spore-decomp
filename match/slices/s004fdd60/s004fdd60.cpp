// 0x004fdd60: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004fd9a0/s004fd9a0.cpp.

struct C_00425990 { int FUN_00425990(); };
struct C_00926640 { void FUN_00926640(); };
#pragma pack(push, 1)
struct Fr0_004fdd60 {
    int v_l24;
    int dead0[3];
    int v_l8;
};
#pragma pack(pop)


struct D_004fdd60 { void FUN_004fdd60(); };
// @ 0x004fdd60
void D_004fdd60::FUN_004fdd60()
{
    Fr0_004fdd60 fb;
    ((C_00926640*)((int)this + 36))->FUN_00926640();
    fb.v_l24 = (int)this + 16;
    fb.v_l8 = (int)(int)*(int*)(char*)fb.v_l24;
    for (; (unsigned int)fb.v_l8 < (unsigned int)*(int*)((char*)fb.v_l24 + 4); fb.v_l8 = fb.v_l8 + 4) {
    }
    ((C_00425990*)fb.v_l24)->FUN_00425990();
    return;
}
