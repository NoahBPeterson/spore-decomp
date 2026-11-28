// 0x005240e0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/SPSkinnerPaintSystem.cpp, match/slices/s00523690/s00523690.cpp.

struct il2c_bvni_ff { float m0; float m1; il2c_bvni_ff(const il2c_bvni_ff& o) : m0(o.m0), m1(o.m1) {} };
struct il2c_bvn_i_ff { int m0; il2c_bvni_ff n; il2c_bvn_i_ff(const il2c_bvn_i_ff& o) : m0(o.m0), n(o.n) {} };

struct C_00523900 { int FUN_00523900(unsigned int, unsigned int, il2c_bvn_i_ff, unsigned int); };
struct C_00525f40 { void FUN_00525f40(); };


struct D_005240e0 { void FUN_005240e0(int a4, int a8, int a12, int a16, int a20); };
// @ 0x005240e0
void D_005240e0::FUN_005240e0(int a4, int a8, int a12, int a16, int a20)
{
    int v_l8;
    int dead_0[15];
    int dead_1[8];
    ((C_00525f40*)((int)this + 60))->FUN_00525f40();
    v_l8 = (int)(int)((int)*(int*)((char*)(int)this + 64) - 56);
    ((C_00523900*)(((int)this)))->FUN_00523900((unsigned int)(v_l8), (unsigned int)(a4), (*(il2c_bvn_i_ff*)((int)&a8)), (unsigned int)(a20));
    return;
}
