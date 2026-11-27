// 0x00475320: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00474bd0/s00474bd0.cpp, src/game/SPGonzago/_at_00470000.cpp.

extern "C" void __cdecl FUN_0042a730(...);
extern "C" int __cdecl FUN_0042dee0(...);
extern "C" void __cdecl FUN_00f47380(...);
#pragma pack(push, 1)
struct Fr0_00475320 {
    int v_l52;
    int v_l48;
    int v_l44;
    int dead0[7];
    int v_l12;
    int v_l8;
};
#pragma pack(pop)


struct D_00475320 { void FUN_00475320(int a4); };
// @ 0x00475320
void D_00475320::FUN_00475320(int a4)
{
    Fr0_00475320 fb;
    if ((unsigned int)a4 > (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) >> 5)) {
        fb.v_l12 = (int)(int)(a4 != 0 ? (int)(int)FUN_0042dee0((unsigned int)((int)this + 12), (unsigned int)(a4 << 5), (unsigned int)4, (unsigned int)0) : 0);
        FUN_0042a730((unsigned int)(int)*(int*)(char*)(int)this, (unsigned int)(int)*(int*)((char*)(int)this + 4), (unsigned int)fb.v_l12);
        fb.v_l52 = (int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) >> 5);
        fb.v_l48 = (int)(int)*(int*)(char*)(int)this;
        if (fb.v_l48 != 0) {
            if ((int)*(int*)((char*)fb.v_l48 - 4) != 0) {
                fb.v_l44 = fb.v_l48;
                FUN_00f47380((unsigned int)fb.v_l44);
            }
        }
        fb.v_l8 = (int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) >> 5);
        *(int*)(char*)(int)this = fb.v_l12;
        *(int*)((char*)(int)this + 4) = (fb.v_l8 << 5) + fb.v_l12;
        *(int*)((char*)(int)this + 8) = (int)(int)((a4 << 5) + (int)*(int*)(char*)(int)this);
    }
    return;
}
