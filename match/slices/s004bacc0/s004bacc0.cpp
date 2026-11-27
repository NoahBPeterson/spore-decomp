// 0x004bacc0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004ba150/s004ba150.cpp.

#pragma pack(push, 1)
struct Fr0_004bacc0 {
    int v_l24;
    int v_l20;
    int v_l16;
    int v_l12;
    int dead0[1];
};
#pragma pack(pop)


struct D_004bacc0 { int FUN_004bacc0(); };
// @ 0x004bacc0
int D_004bacc0::FUN_004bacc0()
{
    Fr0_004bacc0 fb;
    *(int*)(char*)(int)this = 0;
    fb.v_l12 = (int)this + 4;
    *(int*)(char*)fb.v_l12 = 0;
    fb.v_l16 = (int)this + 8;
    *(int*)(char*)fb.v_l16 = 0;
    fb.v_l20 = (int)this + 12;
    *(int*)(char*)fb.v_l20 = 0;
    *(int*)((char*)fb.v_l20 + 4) = 0;
    *(int*)((char*)fb.v_l20 + 8) = 0;
    fb.v_l24 = (int)this + 32;
    *(int*)(char*)fb.v_l24 = 0;
    *(int*)((char*)fb.v_l24 + 4) = 0;
    *(int*)((char*)fb.v_l24 + 8) = 0;
    return (int)this;
}
