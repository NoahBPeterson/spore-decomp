// 0x005407a0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0053f960/s0053f960.cpp.

struct C_004cef00 { int FUN_004cef00(unsigned int, unsigned int, unsigned int); };
struct C_00530c80 { int FUN_00530c80(unsigned int, unsigned int); };
#pragma pack(push, 1)
struct Fr0_005407a0 {
    int dead0[6];
    int v_l20;
    int v_l16;
    int v_l12[2];
};
#pragma pack(pop)


struct D_005407a0 { void FUN_005407a0(int a4); };
// @ 0x005407a0
void D_005407a0::FUN_005407a0(int a4)
{
    Fr0_005407a0 fb;
    if ((unsigned int)a4 > (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) >> 3)) {
        fb.v_l20 = (int)(int)(a4 - (int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) >> 3));
        fb.v_l16 = (int)(int)*(int*)((char*)(int)this + 4);
        ((C_004cef00*)(int)this)->FUN_004cef00((unsigned int)fb.v_l16, (unsigned int)fb.v_l20, (unsigned int)(int)&fb.v_l12);
    } else {
        ((C_00530c80*)(int)this)->FUN_00530c80((unsigned int)(int)((int)*(int*)(char*)(int)this + (a4 << 3)), (unsigned int)(int)*(int*)((char*)(int)this + 4));
    }
    return;
}
