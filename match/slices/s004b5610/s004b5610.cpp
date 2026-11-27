// 0x004b5610: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004b4930/s004b4930.cpp, src/game/SPBake/SPEditorPaintTheme.cpp.

struct C_00455290 { void FUN_00455290(); };
struct C_004b6450 { int FUN_004b6450(); };
extern "C" void __cdecl FUN_00f47380(...);
#pragma pack(push, 1)
struct Fr0_004b5610 {
    int dead0[3];
    int v_l28;
    int v_l24;
    int dead1[3];
    int v_l8;
};
#pragma pack(pop)
__forceinline void il2c_d_FUN_00f47380(int p, int fl) { if (fl & 1) FUN_00f47380((unsigned int)(p)); }


struct D_004b5610 { void FUN_004b5610(); };
// @ 0x004b5610
void D_004b5610::FUN_004b5610()
{
    Fr0_004b5610 fb;
    fb.v_l28 = (int)(int)*(int*)((char*)(int)this + 4);
    fb.v_l24 = (int)(int)*(int*)(char*)(int)this;
    for (; (unsigned int)fb.v_l24 < (unsigned int)fb.v_l28; fb.v_l24 = fb.v_l24 + 284) {
        fb.v_l8 = (int)(int)*(int*)(char*)fb.v_l24;
        for (; (unsigned int)fb.v_l8 < (unsigned int)*(int*)((char*)fb.v_l24 + 4); fb.v_l8 = fb.v_l8 + 32) {
        }
        ((C_00455290*)fb.v_l24)->FUN_00455290();
        il2c_d_FUN_00f47380(fb.v_l24, 0);
    }
    ((C_004b6450*)(int)this)->FUN_004b6450();
    return;
}
