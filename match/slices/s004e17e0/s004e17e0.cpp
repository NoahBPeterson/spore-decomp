// 0x004e17e0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004e12c0/s004e12c0.cpp.

extern "C" int __cdecl FUN_0042dee0(...);
extern "C" void __cdecl FUN_004e3d90(...);
extern "C" void __cdecl FUN_00f47380(...);
#pragma pack(push, 1)
struct Fr0_004e17e0 {
    int v_l68;
    int v_l64;
    int v_l60;
    int dead0[11];
    int v_l12;
    int v_l8;
};
#pragma pack(pop)


struct D_004e17e0 { void FUN_004e17e0(int a4); };
// @ 0x004e17e0
void D_004e17e0::FUN_004e17e0(int a4)
{
    Fr0_004e17e0 fb;
    if ((unsigned int)a4 > (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) / 36)) {
        fb.v_l12 = (int)(int)(a4 != 0 ? (int)(int)FUN_0042dee0((unsigned int)((int)this + 12), (unsigned int)(a4 * 36), (unsigned int)0, (unsigned int)0) : 0);
        FUN_004e3d90((unsigned int)(int)*(int*)(char*)(int)this, (unsigned int)(int)*(int*)((char*)(int)this + 4), (unsigned int)fb.v_l12);
        fb.v_l68 = (int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) / 36);
        fb.v_l64 = (int)(int)*(int*)(char*)(int)this;
        if (fb.v_l64 != 0) {
            if ((int)*(int*)((char*)fb.v_l64 - 4) != 0) {
                fb.v_l60 = fb.v_l64;
                FUN_00f47380((unsigned int)fb.v_l60);
            }
        }
        fb.v_l8 = (int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 36);
        *(int*)(char*)(int)this = fb.v_l12;
        *(int*)((char*)(int)this + 4) = fb.v_l8 * 36 + fb.v_l12;
        *(int*)((char*)(int)this + 8) = (int)(int)(a4 * 36 + (int)*(int*)(char*)(int)this);
    }
    return;
}
