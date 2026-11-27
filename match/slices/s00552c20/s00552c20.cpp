// 0x00552c20: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00552af0/s00552af0.cpp, src/game/SPBake/SPPollinatorAssetDirectory.cpp.

extern "C" void __cdecl FUN_00f47380(...);
#pragma pack(push, 1)
struct Fr0_00552c20 {
    int v_l44;
    int v_l40;
    int v_l36;
    int v_l32;
    int v_l28;
    int v_l24;
    int v_l20;
    int v_l16;
    int v_l12;
    int v_l8;
};
#pragma pack(pop)


struct D_00552c20 { int FUN_00552c20(int a4, int a8, int a12); };
// @ 0x00552c20
int D_00552c20::FUN_00552c20(int a4, int a8, int a12)
{
    Fr0_00552c20 fb;
    fb.v_l32 = a12;
    fb.v_l28 = a8;
    fb.v_l16 = fb.v_l28;
    fb.v_l12 = fb.v_l32;
    fb.v_l16 = (int)(int)*(int*)((char*)fb.v_l16 + 24);
    while (fb.v_l16 == 0) {
        fb.v_l12 = fb.v_l12 + 4;
        fb.v_l16 = (int)(int)*(int*)(char*)fb.v_l12;
    }
    fb.v_l20 = a8;
    fb.v_l8 = (int)(int)*(int*)(char*)a12;
    if (fb.v_l8 == fb.v_l20) {
        *(int*)(char*)a12 = (int)(int)*(int*)((char*)fb.v_l8 + 24);
    } else {
        fb.v_l24 = (int)(int)*(int*)((char*)fb.v_l8 + 24);
        while (fb.v_l24 != fb.v_l20) {
            fb.v_l8 = fb.v_l24;
            fb.v_l24 = (int)(int)*(int*)((char*)fb.v_l8 + 24);
        }
        *(int*)((char*)fb.v_l8 + 24) = (int)(int)*(int*)((char*)fb.v_l24 + 24);
    }
    fb.v_l36 = fb.v_l20;
    FUN_00f47380((unsigned int)fb.v_l36);
    *(int*)((char*)(int)this + 12) = (int)(int)((int)*(int*)((char*)(int)this + 12) - 1);
    fb.v_l44 = fb.v_l12;
    fb.v_l40 = fb.v_l16;
    *(int*)(char*)a4 = fb.v_l40;
    *(int*)((char*)a4 + 4) = fb.v_l44;
    return a4;
}
