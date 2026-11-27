// 0x0053a1a0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00539d70/s00539d70.cpp, src/game/SPBake/SPSkinPaintParticleDescription.cpp.

struct C_0053b160 { int FUN_0053b160(unsigned int); };
struct C_00a6f9c0 { void FUN_00a6f9c0(unsigned int, unsigned int, unsigned int); };
#pragma pack(push, 1)
struct Fr0_0053a1a0 {
    int dead0[1];
    int v_l12;
    int v_l8;
};
#pragma pack(pop)


struct D_0053a1a0 { void FUN_0053a1a0(int a4); };
// @ 0x0053a1a0
void D_0053a1a0::FUN_0053a1a0(int a4)
{
    Fr0_0053a1a0 fb;
    if ((int)(unsigned char)a4 == 0) {
        fb.v_l8 = (int)(int)*(int*)((char*)(int)this + 72);
        fb.v_l12 = (int)(int)*(int*)((char*)(int)this + 56);
        ((C_00a6f9c0*)(int)*(int*)((char*)(int)this + 48))->FUN_00a6f9c0((unsigned int)fb.v_l12, (unsigned int)38, (unsigned int)fb.v_l8);
    }
    ((C_0053b160*)((int)this + 72))->FUN_0053b160((unsigned int)0);
    return;
}
