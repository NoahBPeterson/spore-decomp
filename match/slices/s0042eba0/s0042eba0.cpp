// 0x0042eba0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0042e860/s0042e860.cpp.

extern "C" int __cdecl FUN_0042dee0(...);
extern "C" void __cdecl FUN_0042ec30(...);
#pragma pack(push, 1)
struct Fr0_0042eba0 {
    int v_l64;
    int v_l60;
    int v_l56;
    int dead0[6];
    int v_l28;
    int v_l24;
    int v_l20;
    char dead1;
    char dead2;
    unsigned char v_l14;
    char dead3;
    int v_l12;
    int v_l8;
};
#pragma pack(pop)


struct D_0042eba0 { int FUN_0042eba0(int a4, int a8, int a12); };
// @ 0x0042eba0
int D_0042eba0::FUN_0042eba0(int a4, int a8, int a12)
{
    Fr0_0042eba0 fb;
    fb.v_l8 = (int)(int)(a4 != 0 ? (int)(int)FUN_0042dee0((unsigned int)((int)this + 12), (unsigned int)(a4 << 3), (unsigned int)4, (unsigned int)0) : 0);
    fb.v_l64 = fb.v_l8;
    fb.v_l60 = a12;
    fb.v_l56 = a8;
    fb.v_l20 = fb.v_l64;
    fb.v_l24 = fb.v_l60;
    fb.v_l28 = fb.v_l56;
    FUN_0042ec30((unsigned int)(int)&fb.v_l12, (unsigned int)fb.v_l28, (unsigned int)fb.v_l24, (unsigned int)fb.v_l20, (unsigned int)(int)fb.v_l14);
    return fb.v_l8;
}
