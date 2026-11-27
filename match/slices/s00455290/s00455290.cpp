// 0x00455290: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00454330/s00454330.cpp.

extern "C" int __cdecl FUN_00f47380(...);
#pragma pack(push, 1)
struct Fr0_00455290 {
    int v_l16;
    int v_l12;
    int v_l8;
};
#pragma pack(pop)


struct D_00455290 { void FUN_00455290(); };
// @ 0x00455290
void D_00455290::FUN_00455290()
{
    Fr0_00455290 fb;
    if ((int)*(int*)(char*)(int)this != 0) {
        fb.v_l16 = (int)(int)((int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) >> 5) << 5);
        fb.v_l12 = (int)(int)*(int*)(char*)(int)this;
        if (fb.v_l12 != (int)*(int*)((char*)(int)this + 16)) {
            fb.v_l8 = fb.v_l12;
            FUN_00f47380((unsigned int)fb.v_l8);
        }
    }
    return;
}
