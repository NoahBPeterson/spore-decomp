// 0x00571720: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s005709b0/s005709b0.cpp, src/game/SPEditors/TraitVector.cpp.

struct C_0050f740 { void FUN_0050f740(unsigned int, unsigned int); };
struct C_00571840 { void FUN_00571840(unsigned int, unsigned int); };
#pragma pack(push, 1)
struct Fr0_00571720 {
    int dead0[10];
    int v_l44[2];
    int v_l36;
    int v_l32;
    int dead1[6];
};
struct Fr1_00571720 {
    int v_l88;
};
#pragma pack(pop)


struct D_00571720 { void FUN_00571720(int a4); };
// @ 0x00571720
void D_00571720::FUN_00571720(int a4)
{
    Fr0_00571720 fb;
    Fr1_00571720 fa;
    ((C_0050f740*)(int)this)->FUN_0050f740((unsigned int)(int)*(int*)(char*)(int)this, (unsigned int)(int)*(int*)((char*)(int)this + 4));
    fb.v_l32 = (int)(int)*(int*)((char*)a4 + 4);
    fb.v_l36 = (int)(int)*(int*)(char*)a4;
    fa.v_l88 = fb.v_l36;
    for (; fa.v_l88 != fb.v_l32; fa.v_l88 = fa.v_l88 + 12) {
        ((C_00571840*)(int)this)->FUN_00571840((unsigned int)(int)&fb.v_l44, (unsigned int)fa.v_l88);
    }
    *(float*)((char*)(int)this + 24) = *(float*)((char*)a4 + 24);
    return;
}
