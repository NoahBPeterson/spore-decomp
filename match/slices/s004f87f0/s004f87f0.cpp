// 0x004f87f0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004f85b0/s004f85b0.cpp.

extern "C" unsigned char g_013ef094[];
extern "C" unsigned char g_013f1140[];
struct C_004c0b80 { int FUN_004c0b80(); };
extern "C" void __cdecl FUN_004f80b0(...);
struct C_004fc320 { void FUN_004fc320(unsigned int); };
extern "C" void __cdecl FUN_00f47380(...);
#pragma pack(push, 1)
struct Fr0_004f87f0 {
    int v_l28;
    int dead0[3];
    int v_l12;
    int v_l8;
};
#pragma pack(pop)


struct D_004f87f0 { void FUN_004f87f0(); };
// @ 0x004f87f0
void D_004f87f0::FUN_004f87f0()
{
    Fr0_004f87f0 fb;
    *(int*)(char*)(int)this = (int)g_013f1140;
    ((C_004fc320*)(int)this)->FUN_004fc320((unsigned int)1);
    fb.v_l8 = (int)(int)*(int*)((char*)(int)this + 84);
    FUN_00f47380((unsigned int)fb.v_l8);
    FUN_004f80b0((unsigned int)(int)*(int*)((char*)(int)this + 72));
    FUN_004f80b0((unsigned int)(int)*(int*)((char*)(int)this + 28));
    fb.v_l28 = (int)this + 88;
    fb.v_l12 = (int)(int)*(int*)(char*)fb.v_l28;
    for (; (unsigned int)fb.v_l12 < (unsigned int)*(int*)((char*)fb.v_l28 + 4); fb.v_l12 = fb.v_l12 + 4) {
    }
    ((C_004c0b80*)fb.v_l28)->FUN_004c0b80();
    *(int*)(char*)(int)this = (int)g_013ef094;
    return;
}
