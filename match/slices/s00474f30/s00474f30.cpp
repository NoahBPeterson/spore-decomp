// 0x00474f30: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00474bd0/s00474bd0.cpp, src/game/SPGonzago/_at_00470000.cpp.

struct C_00476e60 { int FUN_00476e60(); };
struct C_004c0b80 { void FUN_004c0b80(); };
extern "C" void __cdecl FUN_00f47380(...);
#pragma pack(push, 1)
struct Fr0_00474f30 {
    int dead0[3];
    int v_l32;
    int v_l28;
    int v_l24;
    int dead1[3];
    int v_l8;
};
#pragma pack(pop)
__forceinline void il2c_d_FUN_00f47380(int p, int fl) { if (fl & 1) FUN_00f47380((unsigned int)(p)); }


struct D_00474f30 { void FUN_00474f30(); };
// @ 0x00474f30
void D_00474f30::FUN_00474f30()
{
    Fr0_00474f30 fb;
    fb.v_l32 = (int)(int)*(int*)((char*)(int)this + 4);
    fb.v_l28 = (int)(int)*(int*)(char*)(int)this;
    for (; (unsigned int)fb.v_l28 < (unsigned int)fb.v_l32; fb.v_l28 = fb.v_l28 + 72) {
        fb.v_l24 = fb.v_l28 + 12;
        fb.v_l8 = (int)(int)*(int*)(char*)fb.v_l24;
        for (; (unsigned int)fb.v_l8 < (unsigned int)*(int*)((char*)fb.v_l24 + 4); fb.v_l8 = fb.v_l8 + 4) {
        }
        ((C_004c0b80*)fb.v_l24)->FUN_004c0b80();
        il2c_d_FUN_00f47380(fb.v_l28, 0);
    }
    ((C_00476e60*)(int)this)->FUN_00476e60();
    return;
}
