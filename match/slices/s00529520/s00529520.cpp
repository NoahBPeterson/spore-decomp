// 0x00529520: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s005288f0/s005288f0.cpp, src/game/SPBake/SPSkinnerRTT_SporeApp.cpp.

extern "C" unsigned char g_015dec08[];
extern "C" void __cdecl FUN_004cdd70(...);
struct C_005293a0 { int FUN_005293a0(); };
extern "C" int __cdecl FUN_011fd790(...);
extern "C" void __cdecl FUN_011fd7b0(...);
#pragma pack(push, 1)
struct Fr0_00529520 {
    int dead0[2];
    int v_l20;
    int v_l16;
    int v_l12;
    int v_l8;
};
#pragma pack(pop)


struct D_00529520 { int FUN_00529520(int a4); };
// @ 0x00529520
int D_00529520::FUN_00529520(int a4)
{
    Fr0_00529520 fb;
    fb.v_l12 = ((C_005293a0*)(int)this)->FUN_005293a0();
    fb.v_l16 = (int)(unsigned int)((unsigned int)(int)FUN_011fd790((unsigned int)fb.v_l12) / (unsigned int)3);
    fb.v_l20 = (int)(int)((unsigned int)fb.v_l16 < (unsigned int)a4 ? (int)&fb.v_l16 : (int)&a4);
    *(int*)&a4 = (int)(int)*(int*)(char*)fb.v_l20;
    FUN_011fd7b0((unsigned int)fb.v_l12, (unsigned int)(int)&fb.v_l8);
    *(int*)g_015dec08 = a4 * 3;
    FUN_004cdd70((unsigned int)(a4 * 3), (unsigned int)(int)g_015dec08);
    return a4;
}
