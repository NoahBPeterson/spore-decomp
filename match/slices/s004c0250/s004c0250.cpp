// 0x004c0250: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004bf430/s004bf430.cpp.

extern "C" int __cdecl FUN_0042dee0(...);
extern "C" void __cdecl FUN_004b03f0(...);
extern "C" void __cdecl FUN_00f47380(...);
#pragma pack(push, 1)
struct Fr0_004c0250 {
    int v_l56;
    int v_l52;
    int v_l48;
    int dead0[8];
    int v_l12;
    int v_l8;
};
#pragma pack(pop)


struct D_004c0250 { void FUN_004c0250(int a4); };
// @ 0x004c0250
void D_004c0250::FUN_004c0250(int a4)
{
    Fr0_004c0250 fb;
    if ((unsigned int)a4 > (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) / 472)) {
        fb.v_l12 = (int)(int)(a4 != 0 ? (int)(int)FUN_0042dee0((unsigned int)((int)this + 12), (unsigned int)(a4 * 472), (unsigned int)4, (unsigned int)0) : 0);
        FUN_004b03f0((unsigned int)(int)*(int*)(char*)(int)this, (unsigned int)(int)*(int*)((char*)(int)this + 4), (unsigned int)fb.v_l12);
        fb.v_l56 = (int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) / 472);
        fb.v_l52 = (int)(int)*(int*)(char*)(int)this;
        if (fb.v_l52 != 0) {
            if ((int)*(int*)((char*)fb.v_l52 - 4) != 0) {
                fb.v_l48 = fb.v_l52;
                FUN_00f47380((unsigned int)fb.v_l48);
            }
        }
        fb.v_l8 = (int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 472);
        *(int*)(char*)(int)this = fb.v_l12;
        *(int*)((char*)(int)this + 4) = fb.v_l8 * 472 + fb.v_l12;
        *(int*)((char*)(int)this + 8) = (int)(int)(a4 * 472 + (int)*(int*)(char*)(int)this);
    }
    return;
}
