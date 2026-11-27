// 0x0050eca0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0050e850/s0050e850.cpp.

struct C_004c0b80 { void FUN_004c0b80(); };
struct C_0050f210 { void FUN_0050f210(unsigned int); };
extern "C" void __cdecl FUN_00f47380(...);
#pragma pack(push, 1)
struct Fr0_0050eca0 {
    int v_l60;
    int v_l56;
    int dead0[3];
    int v_l40;
    int v_l36;
    int v_l32;
    int v_l28;
    int dead1[3];
    char dead2;
    unsigned char v_l11;
    unsigned char v_l10;
    unsigned char v_l9;
    int v_l8;
};
#pragma pack(pop)
__forceinline void il2c_d_FUN_00f47380(int p, int fl) { if (fl & 1) FUN_00f47380((unsigned int)(p)); }


struct D_0050eca0 { int FUN_0050eca0(int a4, int a8); };
// @ 0x0050eca0
int D_0050eca0::FUN_0050eca0(int a4, int a8)
{
    Fr0_0050eca0 fb;
    fb.v_l36 = (int)(int)*(int*)((char*)(int)this + 4);
    fb.v_l10 = (unsigned char)0;
    fb.v_l9 = (unsigned char)0;
    fb.v_l11 = (unsigned char)0;
    fb.v_l32 = a4;
    fb.v_l28 = a8;
    for (; fb.v_l28 != fb.v_l36; fb.v_l32 = fb.v_l32 + 100, fb.v_l28 = fb.v_l28 + 100) {
        ((C_0050f210*)fb.v_l32)->FUN_0050f210((unsigned int)fb.v_l28);
    }
    fb.v_l8 = fb.v_l32;
    fb.v_l60 = (int)(int)*(int*)((char*)(int)this + 4);
    fb.v_l56 = fb.v_l8;
    for (; (unsigned int)fb.v_l56 < (unsigned int)fb.v_l60; fb.v_l56 = fb.v_l56 + 100) {
        fb.v_l40 = (int)(int)*(int*)(char*)fb.v_l56;
        for (; (unsigned int)fb.v_l40 < (unsigned int)*(int*)((char*)fb.v_l56 + 4); fb.v_l40 = fb.v_l40 + 4) {
        }
        ((C_004c0b80*)fb.v_l56)->FUN_004c0b80();
        il2c_d_FUN_00f47380(fb.v_l56, 0);
    }
    *(int*)((char*)(int)this + 4) = (int)(int)((int)*(int*)((char*)(int)this + 4) - (a8 - a4) / 100 * 100);
    return a4;
}
