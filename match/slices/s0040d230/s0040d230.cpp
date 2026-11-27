// 0x0040d230: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0040ccb0/s0040ccb0.cpp.

struct C_0040d260 { void FUN_0040d260(); };
extern "C" void __cdecl FUN_00f47380(...);
#pragma pack(push, 1)
struct Fr0_0040d230 {
    int dead0[18];
};
struct Fr1_0040d230 {
    int dead0[1];
};
#pragma pack(pop)


struct D_0040d230 { int FUN_0040d230(int a4); };
// @ 0x0040d230
int D_0040d230::FUN_0040d230(int a4)
{
    Fr0_0040d230 fb;
    Fr1_0040d230 fa;
    ((C_0040d260*)(int)this)->FUN_0040d260();
    if ((a4 & 1) != 0) {
        FUN_00f47380((unsigned int)(int)this);
    }
    return (int)this;
}
