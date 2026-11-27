// 0x004fd520: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004fcae0/s004fcae0.cpp.

struct C_0050e690 { void FUN_0050e690(unsigned int, unsigned int); };
struct C_00548690 { int FUN_00548690(unsigned int, unsigned int); };
#pragma pack(push, 1)
struct Fr0_004fd520 {
    int v_l60;
    int dead0[6];
    int v_l32;
    int dead1[6];
};
#pragma pack(pop)


struct D_004fd520 { void FUN_004fd520(); };
// @ 0x004fd520
void D_004fd520::FUN_004fd520()
{
    Fr0_004fd520 fb;
    fb.v_l32 = (int)this + 8;
    ((C_0050e690*)fb.v_l32)->FUN_0050e690((unsigned int)(int)*(int*)(char*)fb.v_l32, (unsigned int)(int)*(int*)((char*)fb.v_l32 + 4));
    fb.v_l60 = (int)this + 28;
    ((C_00548690*)fb.v_l60)->FUN_00548690((unsigned int)(int)*(int*)(char*)fb.v_l60, (unsigned int)(int)*(int*)((char*)fb.v_l60 + 4));
    return;
}
