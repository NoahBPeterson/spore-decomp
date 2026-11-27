// 0x00454640: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00454330/s00454330.cpp.

extern "C" int __cdecl FUN_0042dee0(...);
extern "C" void __cdecl FUN_004554f0(...);
extern "C" void __cdecl FUN_00f47380(...);
#pragma pack(push, 1)
struct Fr0_00454640 {
    int v_l56;
    int v_l52;
    int v_l48;
    int dead0[8];
    int v_l12;
    int v_l8;
};
#pragma pack(pop)


struct D_00454640 { void FUN_00454640(int a4); };
// @ 0x00454640
void D_00454640::FUN_00454640(int a4)
{
    Fr0_00454640 fb;
    if ((unsigned int)a4 > (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) >> 3)) {
        fb.v_l12 = (int)(int)(a4 != 0 ? (int)(int)FUN_0042dee0((unsigned int)((int)this + 12), (unsigned int)(a4 << 3), (unsigned int)4, (unsigned int)0) : 0);
        FUN_004554f0((unsigned int)(int)*(int*)(char*)(int)this, (unsigned int)(int)*(int*)((char*)(int)this + 4), (unsigned int)fb.v_l12);
        fb.v_l56 = (int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) >> 3);
        fb.v_l52 = (int)(int)*(int*)(char*)(int)this;
        if (fb.v_l52 != 0) {
            if (fb.v_l52 != (int)*(int*)((char*)(int)this + 16)) {
                fb.v_l48 = fb.v_l52;
                FUN_00f47380((unsigned int)fb.v_l48);
            }
        }
        fb.v_l8 = (int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) >> 3);
        *(int*)(char*)(int)this = fb.v_l12;
        *(int*)((char*)(int)this + 4) = fb.v_l12 + (fb.v_l8 << 3);
        *(int*)((char*)(int)this + 8) = (int)(int)((int)*(int*)(char*)(int)this + (a4 << 3));
    }
    return;
}
