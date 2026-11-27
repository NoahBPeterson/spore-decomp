// 0x0048c720: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0048c0f0/s0048c0f0.cpp, src/game/SPBake/_at_00480000.cpp.

extern "C" void __cdecl FUN_011e0744(...);
#pragma pack(push, 1)
struct Fr0_0048c720 {
    int v_l16;
    int v_l12;
    char dead0;
    unsigned char v_l7;
    unsigned char v_l6;
    unsigned char v_l5;
};
#pragma pack(pop)


struct D_0048c720 { int FUN_0048c720(int a4); };
// @ 0x0048c720
int D_0048c720::FUN_0048c720(int a4)
{
    Fr0_0048c720 fb;
    if ((unsigned int)(a4 + 4) < (unsigned int)*(int*)((char*)(int)this + 4)) {
        fb.v_l16 = (int)(int)*(int*)((char*)(int)this + 4);
        fb.v_l12 = a4 + 4;
        fb.v_l6 = (unsigned char)0;
        fb.v_l5 = (unsigned char)0;
        fb.v_l7 = (unsigned char)1;
        FUN_011e0744((unsigned int)a4, (unsigned int)fb.v_l12, (unsigned int)(fb.v_l16 - fb.v_l12));
    }
    *(int*)((char*)(int)this + 4) = (int)(int)((int)*(int*)((char*)(int)this + 4) - 4);
    return a4;
}
