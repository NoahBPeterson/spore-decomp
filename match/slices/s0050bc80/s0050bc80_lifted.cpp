// 0x0050bc80: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0050bc80/s0050bc80.cpp.

#pragma pack(push, 1)
struct Fr0_0050bc80 {
    int v_l28;
    int v_l24;
    float v_l20;
    int v_l16;
    int v_l12;
    float v_l8;
};
#pragma pack(pop)


struct D_0050bc80 { void FUN_0050bc80(); };
// @ 0x0050bc80
void D_0050bc80::FUN_0050bc80()
{
    Fr0_0050bc80 fb;
    *(int*)((char*)(int)this + 104) = (int)(int)((int)*(int*)((char*)(int)this + 104) ^ 1);
    fb.v_l16 = (int)this + 100;
    fb.v_l12 = (int)this + 92;
    fb.v_l8 = *(float*)(char*)fb.v_l12;
    *(float*)(char*)fb.v_l12 = *(float*)(char*)fb.v_l16;
    *(float*)(char*)fb.v_l16 = (float)fb.v_l8;
    fb.v_l28 = (int)this + 96;
    fb.v_l24 = (int)this + 88;
    fb.v_l20 = *(float*)(char*)fb.v_l24;
    *(float*)(char*)fb.v_l24 = *(float*)(char*)fb.v_l28;
    *(float*)(char*)fb.v_l28 = (float)fb.v_l20;
    return;
}
