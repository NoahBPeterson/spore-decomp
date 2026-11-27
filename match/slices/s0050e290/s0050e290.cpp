// 0x0050e290: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0050d750/s0050d750.cpp, src/game/UTFSpore_Win32/instantiate.cpp.

struct C_004c0b80 { void FUN_004c0b80(); };
struct C_0050f070 { int FUN_0050f070(); };
extern "C" void __cdecl FUN_00f47380(...);
#pragma pack(push, 1)
struct Fr0_0050e290 {
    int dead0[3];
    int v_l28;
    int v_l24;
    int dead1[3];
    int v_l8;
};
#pragma pack(pop)
__forceinline void il2c_d_FUN_00f47380(int p, int fl) { if (fl & 1) FUN_00f47380((unsigned int)(p)); }


struct D_0050e290 { void FUN_0050e290(); };
// @ 0x0050e290
void D_0050e290::FUN_0050e290()
{
    Fr0_0050e290 fb;
    fb.v_l28 = (int)(int)*(int*)((char*)(int)this + 4);
    fb.v_l24 = (int)(int)*(int*)(char*)(int)this;
    for (; (unsigned int)fb.v_l24 < (unsigned int)fb.v_l28; fb.v_l24 = fb.v_l24 + 100) {
        fb.v_l8 = (int)(int)*(int*)(char*)fb.v_l24;
        for (; (unsigned int)fb.v_l8 < (unsigned int)*(int*)((char*)fb.v_l24 + 4); fb.v_l8 = fb.v_l8 + 4) {
        }
        ((C_004c0b80*)fb.v_l24)->FUN_004c0b80();
        il2c_d_FUN_00f47380(fb.v_l24, 0);
    }
    ((C_0050f070*)(int)this)->FUN_0050f070();
    return;
}
