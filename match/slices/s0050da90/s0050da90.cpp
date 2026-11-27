// 0x0050da90: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0050d750/s0050d750.cpp.

extern "C" int __cdecl FUN_0042dee0(...);
extern "C" void __cdecl FUN_0050f7f0(...);
#pragma pack(push, 1)
struct Fr0_0050da90 {
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


struct D_0050da90 { int FUN_0050da90(int a4); };
// @ 0x0050da90
int D_0050da90::FUN_0050da90(int a4)
{
    Fr0_0050da90 fb;
    fb.v_l8 = (int)(int)((int)((int)*(int*)((char*)a4 + 4) - (int)*(int*)(char*)a4) / 20);
    *(int*)(char*)(int)this = (int)(int)(fb.v_l8 != 0 ? (int)(int)FUN_0042dee0((unsigned int)((int)this + 12), (unsigned int)(fb.v_l8 * 20), (unsigned int)4, (unsigned int)0) : 0);
    *(int*)((char*)(int)this + 4) = (int)(int)*(int*)(char*)(int)this;
    *(int*)((char*)(int)this + 8) = (int)(int)(fb.v_l8 * 20 + (int)*(int*)(char*)(int)this);
    fb.v_l64 = (int)(int)*(int*)(char*)(int)this;
    fb.v_l60 = (int)(int)*(int*)((char*)a4 + 4);
    fb.v_l56 = (int)(int)*(int*)(char*)a4;
    fb.v_l20 = fb.v_l64;
    fb.v_l24 = fb.v_l60;
    fb.v_l28 = fb.v_l56;
    FUN_0050f7f0((unsigned int)(int)&fb.v_l12, (unsigned int)fb.v_l28, (unsigned int)fb.v_l24, (unsigned int)fb.v_l20, (unsigned int)(int)fb.v_l14);
    *(int*)((char*)(int)this + 4) = fb.v_l12;
    return (int)this;
}
