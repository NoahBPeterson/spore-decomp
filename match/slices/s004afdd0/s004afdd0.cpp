// 0x004afdd0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004af210/s004af210.cpp.

extern "C" int __cdecl FUN_0042dee0(...);
struct C_004afd00 { void FUN_004afd00(unsigned int); };
struct C_004b00a0 { void FUN_004b00a0(unsigned int); };
struct C_004b0140 { int FUN_004b0140(); };
struct C_004b0180 { void FUN_004b0180(unsigned int); };
extern "C" void __cdecl FUN_004b03f0(...);
extern "C" void __cdecl FUN_00f47380(...);
#pragma pack(push, 1)
struct Fr0_004afdd0 {
    int v_l652;
    int v_l648;
    int v_l644;
    int dead0[152];
    int v_l32;
    int v_l28;
    int v_l24[5];
};
#pragma pack(pop)


struct D_004afdd0 { void FUN_004afdd0(int a4); };
// @ 0x004afdd0
void D_004afdd0::FUN_004afdd0(int a4)
{
    Fr0_004afdd0 fb;
    if (a4 == -1 || (unsigned int)a4 <= (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 472)) {
        if ((unsigned int)a4 < (unsigned int)(int)((int)(int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 472)) {
            ((C_004afd00*)(int)this)->FUN_004afd00((unsigned int)a4);
        }
        ((C_004b00a0*)(int)&fb.v_l24)->FUN_004b00a0((unsigned int)(int)this);
        ((C_004b0180*)(int)this)->FUN_004b0180((unsigned int)(int)&fb.v_l24);
        ((C_004b0140*)(int)&fb.v_l24)->FUN_004b0140();
    } else {
        fb.v_l32 = (int)(int)(a4 != 0 ? (int)(int)FUN_0042dee0((unsigned int)((int)this + 12), (unsigned int)(a4 * 472), (unsigned int)4, (unsigned int)0) : 0);
        FUN_004b03f0((unsigned int)(int)*(int*)(char*)(int)this, (unsigned int)(int)*(int*)((char*)(int)this + 4), (unsigned int)fb.v_l32);
        fb.v_l652 = (int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) / 472);
        fb.v_l648 = (int)(int)*(int*)(char*)(int)this;
        if (fb.v_l648 != 0) {
            if ((int)*(int*)((char*)fb.v_l648 - 4) != 0) {
                fb.v_l644 = fb.v_l648;
                FUN_00f47380((unsigned int)fb.v_l644);
            }
        }
        fb.v_l28 = (int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 472);
        *(int*)(char*)(int)this = fb.v_l32;
        *(int*)((char*)(int)this + 4) = fb.v_l28 * 472 + fb.v_l32;
        *(int*)((char*)(int)this + 8) = (int)(int)(a4 * 472 + (int)*(int*)(char*)(int)this);
    }
    return;
}
