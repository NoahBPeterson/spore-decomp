// 0x00537d90: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00537d90/s00537d90.cpp, src/game/SPGonzago/SPBlobShadow.cpp.

struct C_00434040 { int FUN_00434040(); };
struct C_00537dc0 { void FUN_00537dc0(unsigned int); };
#pragma pack(push, 1)
struct Fr0_00537d90 {
    int dead0[12];
    int v_l60[14];
};
#pragma pack(pop)


struct D_00537d90 { void FUN_00537d90(int a4, int a8, int a12); };
// @ 0x00537d90
void D_00537d90::FUN_00537d90(int a4, int a8, int a12)
{
    Fr0_00537d90 fb;
    ((C_00537dc0*)((int)this + 12))->FUN_00537dc0((unsigned int)((C_00434040*)(int)&fb.v_l60)->FUN_00434040());
    *(unsigned char*)((char*)(int)this + 68) = (unsigned char)0;
    return;
}
