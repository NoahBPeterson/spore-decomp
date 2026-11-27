// 0x004aff80: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004af210/s004af210.cpp.

struct C_00409c00 { void FUN_00409c00(); };
struct C_004b0490 { int FUN_004b0490(unsigned int, unsigned int); };
struct C_004b1800 { int FUN_004b1800(unsigned int, unsigned int, unsigned int); };
#pragma pack(push, 1)
struct Fr0_004aff80 {
    int dead0[6];
    int v_l84;
    int v_l80;
    int dead1[12];
    int v_l28[6];
};
#pragma pack(pop)


struct D_004aff80 { void FUN_004aff80(int a4); };
// @ 0x004aff80
void D_004aff80::FUN_004aff80(int a4)
{
    Fr0_004aff80 fb;
    if ((unsigned int)a4 > (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 24)) {
        ((C_00409c00*)(int)&fb.v_l28)->FUN_00409c00();
        fb.v_l84 = (int)(int)(a4 - (int)((int)(int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 24));
        fb.v_l80 = (int)(int)*(int*)((char*)(int)this + 4);
        ((C_004b1800*)(int)this)->FUN_004b1800((unsigned int)fb.v_l80, (unsigned int)fb.v_l84, (unsigned int)(int)&fb.v_l28);
    } else {
        ((C_004b0490*)(int)this)->FUN_004b0490((unsigned int)(int)(a4 * 24 + (int)*(int*)(char*)(int)this), (unsigned int)(int)*(int*)((char*)(int)this + 4));
    }
    return;
}
