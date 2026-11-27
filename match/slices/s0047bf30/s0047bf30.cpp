// 0x0047bf30: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0047b480/s0047b480.cpp, src/game/SPGonzago/InteractionAgent.cpp.

struct C_0047c600 { void FUN_0047c600(unsigned int); };
extern "C" int __cdecl FUN_011e073e(...);
#pragma pack(push, 1)
struct Fr0_0047bf30 {
    int v_l32;
    int v_l28;
    int v_l24;
    int v_l20;
    int v_l16;
    int v_l12;
    int v_l8;
};
#pragma pack(pop)


struct D_0047bf30 { int FUN_0047bf30(int a4, int a8); };
// @ 0x0047bf30
int D_0047bf30::FUN_0047bf30(int a4, int a8)
{
    Fr0_0047bf30 fb;
    fb.v_l8 = (int)(int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this);
    fb.v_l12 = (int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) - 1);
    if ((unsigned int)(fb.v_l8 + a4) > (unsigned int)fb.v_l12) {
        fb.v_l16 = fb.v_l8 + a4;
        fb.v_l20 = (int)(int)((unsigned int)fb.v_l12 > (unsigned int)8 ? fb.v_l12 << 1 : 8);
        fb.v_l24 = (int)(int)((unsigned int)fb.v_l20 < (unsigned int)fb.v_l16 ? (int)&fb.v_l16 : (int)&fb.v_l20);
        ((C_0047c600*)(int)this)->FUN_0047c600((unsigned int)(int)*(int*)(char*)fb.v_l24);
    }
    if ((unsigned int)a4 > (unsigned int)0) {
        fb.v_l32 = a4 - 1;
        fb.v_l28 = (int)(int)((int)*(int*)((char*)(int)this + 4) + 1);
        FUN_011e073e((unsigned int)fb.v_l28, (unsigned int)(int)(unsigned char)a8, (unsigned int)fb.v_l32);
        *(unsigned char*)(char*)(int)*(int*)((char*)(int)this + 4) = (unsigned char)(unsigned char)(unsigned char)a8;
        *(int*)((char*)(int)this + 4) = (int)(int)((int)*(int*)((char*)(int)this + 4) + a4);
        *(unsigned char*)(char*)(int)*(int*)((char*)(int)this + 4) = (unsigned char)0;
    }
    return (int)this;
}
