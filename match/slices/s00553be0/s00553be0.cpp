// 0x00553be0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00552af0/s00552af0.cpp, src/game/SPBake/SPPollinatorAssetDirectory.cpp.

extern "C" unsigned char g_01667bac[];
struct C_00554760 { int FUN_00554760(unsigned int, unsigned int); };
struct C_005550a0 { int FUN_005550a0(unsigned int, unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00f47380(...);
#pragma pack(push, 1)
struct Fr0_00553be0 {
    int dead0[10];
    int v_l44;
    int v_l40;
    int v_l36;
    int v_l32;
    int v_l28;
    int dead1[1];
    int v_l20;
    int v_l16;
    int v_l12;
    int dead2[1];
};
#pragma pack(pop)


struct D_00553be0 { void FUN_00553be0(int a4); };
// @ 0x00553be0
void D_00553be0::FUN_00553be0(int a4)
{
    Fr0_00553be0 fb;
    if ((unsigned int)a4 > (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) >> 4)) {
        fb.v_l20 = 0;
        fb.v_l16 = 0;
        fb.v_l12 = 0;
        fb.v_l20 = (int)g_01667bac;
        fb.v_l16 = fb.v_l20;
        fb.v_l12 = fb.v_l20 + 1;
        fb.v_l32 = (int)(int)(a4 - (int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) >> 4));
        fb.v_l28 = (int)(int)*(int*)((char*)(int)this + 4);
        ((C_005550a0*)(int)this)->FUN_005550a0((unsigned int)fb.v_l28, (unsigned int)fb.v_l32, (unsigned int)(int)&fb.v_l20);
        if (fb.v_l12 - fb.v_l20 > 1) {
            fb.v_l44 = fb.v_l12 - fb.v_l20;
            fb.v_l40 = fb.v_l20;
            if (fb.v_l40 != 0) {
                fb.v_l36 = fb.v_l40;
                FUN_00f47380((unsigned int)fb.v_l36);
            }
        }
    } else {
        ((C_00554760*)(int)this)->FUN_00554760((unsigned int)(int)((a4 << 4) + (int)*(int*)(char*)(int)this), (unsigned int)(int)*(int*)((char*)(int)this + 4));
    }
    return;
}
