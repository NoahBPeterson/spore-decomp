// 0x004afd00: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004af210/s004af210.cpp, src/game/SPBake/SPEditorResourceFactory.cpp.

struct C_004b0040 { int FUN_004b0040(); };
struct C_004b0340 { int FUN_004b0340(unsigned int, unsigned int); };
struct C_004b11f0 { int FUN_004b11f0(unsigned int, unsigned int, unsigned int); };
#pragma pack(push, 1)
struct Fr0_004afd00 {
    int dead0[5];
    int v_l504;
    int v_l500;
    int v_l496;
    int dead1[4];
    int v_l476[118];
};
struct Fr1_004afd00 {
    int dead0[1];
};
#pragma pack(pop)


struct D_004afd00 { void FUN_004afd00(int a4); };
// @ 0x004afd00
void D_004afd00::FUN_004afd00(int a4)
{
    Fr0_004afd00 fb;
    Fr1_004afd00 fa;
    if ((unsigned int)a4 > (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 472)) {
        fb.v_l504 = ((C_004b0040*)(int)&fb.v_l476)->FUN_004b0040();
        fb.v_l500 = (int)(int)(a4 - (int)((int)(int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 472));
        fb.v_l496 = (int)(int)*(int*)((char*)(int)this + 4);
        ((C_004b11f0*)(int)this)->FUN_004b11f0((unsigned int)fb.v_l496, (unsigned int)fb.v_l500, (unsigned int)fb.v_l504);
    } else {
        ((C_004b0340*)(int)this)->FUN_004b0340((unsigned int)(int)(a4 * 472 + (int)*(int*)(char*)(int)this), (unsigned int)(int)*(int*)((char*)(int)this + 4));
    }
    return;
}
