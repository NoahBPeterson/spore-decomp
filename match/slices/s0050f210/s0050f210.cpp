// 0x0050f210: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0050e850/s0050e850.cpp, src/game/SPGonzago/SPStarManager.cpp.

struct C_0042c750 { void FUN_0042c750(unsigned int, unsigned int, unsigned int); };
struct C_004769b0 { void FUN_004769b0(unsigned int, unsigned int); };
#pragma pack(push, 1)
struct Fr0_0050f210 {
    char dead0;
    unsigned char v_l31;
    char dead1;
    char dead2;
    int v_l28;
    int v_l24;
    int dead3[4];
};
#pragma pack(pop)


struct D_0050f210 { int FUN_0050f210(int a4); };
// @ 0x0050f210
int D_0050f210::FUN_0050f210(int a4)
{
    Fr0_0050f210 fb;
    if ((int)this != a4) {
        ((C_004769b0*)(int)this)->FUN_004769b0((unsigned int)(int)*(int*)(char*)(int)this, (unsigned int)(int)*(int*)((char*)(int)this + 4));
        fb.v_l24 = (int)(int)*(int*)((char*)a4 + 4);
        fb.v_l28 = (int)(int)*(int*)(char*)a4;
        ((C_0042c750*)(int)this)->FUN_0042c750((unsigned int)fb.v_l28, (unsigned int)fb.v_l24, (unsigned int)(int)fb.v_l31);
    }
    *(float*)((char*)(int)this + 88) = *(float*)((char*)a4 + 88);
    *(float*)((char*)(int)this + 92) = *(float*)((char*)a4 + 92);
    *(float*)((char*)(int)this + 96) = *(float*)((char*)a4 + 96);
    return (int)this;
}
