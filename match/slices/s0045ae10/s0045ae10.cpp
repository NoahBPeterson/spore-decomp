// 0x0045ae10: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0045aa70/s0045aa70.cpp.

struct C_00434040 { int FUN_00434040(unsigned int); };
struct C_0045ac20 { int FUN_0045ac20(unsigned int, unsigned int, unsigned int); };
#pragma pack(push, 1)
struct Fr0_0045ae10 {
    int dead0[12];
    int v_l60[14];
};
#pragma pack(pop)


struct D_0045ae10 { void FUN_0045ae10(int a4, int a8); };
// @ 0x0045ae10
void D_0045ae10::FUN_0045ae10(int a4, int a8)
{
    Fr0_0045ae10 fb;
    ((C_0045ac20*)(int)this)->FUN_0045ac20((unsigned int)a4, (unsigned int)a8, (unsigned int)((C_00434040*)(int)&fb.v_l60)->FUN_00434040((unsigned int)0));
    return;
}
