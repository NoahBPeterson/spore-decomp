// 0x005292d0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/SPSkinnerRTT_SporeApp.cpp, match/slices/s005288f0/s005288f0.cpp.

extern "C" unsigned char g_015dea68[];
extern "C" void __cdecl FUN_00529350(...);
struct C_011f3d40 { int FUN_011f3d40(unsigned int, unsigned int); };
template<class T> __forceinline T il2c_k(T v) { return v; }


struct D_005292d0 { void FUN_005292d0(int a4, float a8); };
// @ 0x005292d0
// @ 0x005292d0
void D_005292d0::FUN_005292d0(int a4, float a8)
{
    float v_l8;
    float v_l20_j;
    float v_l16;
    float v_l12;
    FUN_00529350((unsigned int)168, (unsigned int)(int)((int)*(int*)((char*)(int)this + 8) & *(int*)g_015dea68));
    v_l20_j = *(float*)((char*)a4 + (il2c_k(0) << 2));
    v_l16 = *(float*)((char*)a4 + (il2c_k(1) << 2));
    v_l12 = *(float*)((char*)a4 + (il2c_k(2) << 2));
    v_l8 = (float)a8;
    ((C_011f3d40*)(int)*(int*)(char*)(int)this)->FUN_011f3d40((unsigned int)(int)(int)&v_l20_j, (unsigned int)1);
    return;
}
