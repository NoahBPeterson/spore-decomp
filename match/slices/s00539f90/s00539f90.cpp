// 0x00539f90: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00539d70/s00539d70.cpp, src/game/SPBake/SPSkinPaintParticleDescription.cpp.

extern "C" unsigned char g_013f25d0[];
extern "C" unsigned char g_013f3394[];
extern "C" unsigned char g_01667bac[];
struct C_0083cdd0 { void FUN_0083cdd0(); };
#pragma pack(push, 1)
struct Fr0_00539f90 {
    int v_l20;
    int v_l16;
    int v_l12;
    int dead0[1];
};
#pragma pack(pop)


struct D_00539f90 { int FUN_00539f90(); };
// @ 0x00539f90
int D_00539f90::FUN_00539f90()
{
    Fr0_00539f90 fb;
    ((C_0083cdd0*)(int)this)->FUN_0083cdd0();
    *(int*)(char*)(int)this = (int)g_013f25d0;
    *(int*)(char*)(int)this = (int)g_013f25d0;
    fb.v_l12 = (int)this + 52;
    *(int*)(char*)fb.v_l12 = 46754855;
    *(int*)(char*)(int)this = (int)g_013f3394;
    fb.v_l16 = (int)this + 56;
    *(int*)(char*)fb.v_l16 = 0;
    *(int*)((char*)fb.v_l16 + 4) = 0;
    *(int*)((char*)fb.v_l16 + 8) = 0;
    *(int*)(char*)fb.v_l16 = (int)g_01667bac;
    *(int*)((char*)fb.v_l16 + 4) = (int)(int)*(int*)(char*)fb.v_l16;
    *(int*)((char*)fb.v_l16 + 8) = (int)(int)((int)*(int*)(char*)fb.v_l16 + 1);
    fb.v_l20 = (int)this + 72;
    *(int*)(char*)fb.v_l20 = 0;
    return (int)this;
}
