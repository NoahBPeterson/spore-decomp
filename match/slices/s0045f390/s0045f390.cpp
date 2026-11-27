// 0x0045f390: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0045edf0/s0045edf0.cpp.

struct C_0045f080 { void FUN_0045f080(unsigned int, unsigned int); };
struct C_0045f430 { void FUN_0045f430(unsigned int, unsigned int); };
extern "C" void __cdecl FUN_011e0744(...);
#pragma pack(push, 1)
struct Fr0_0045f390 {
    int v_l8;
};
#pragma pack(pop)


struct D_0045f390 { int FUN_0045f390(int a4, int a8); };
// @ 0x0045f390
int D_0045f390::FUN_0045f390(int a4, int a8)
{
    Fr0_0045f390 fb;
    fb.v_l8 = a8 - a4;
    if ((unsigned int)fb.v_l8 <= (unsigned int)(int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this)) {
        FUN_011e0744((unsigned int)(int)*(int*)(char*)(int)this, (unsigned int)a4, (unsigned int)fb.v_l8);
        ((C_0045f080*)(int)this)->FUN_0045f080((unsigned int)(int)((int)*(int*)(char*)(int)this + fb.v_l8), (unsigned int)(int)*(int*)((char*)(int)this + 4));
    } else {
        FUN_011e0744((unsigned int)(int)*(int*)(char*)(int)this, (unsigned int)a4, (unsigned int)(int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this));
        ((C_0045f430*)(int)this)->FUN_0045f430((unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) + a4), (unsigned int)a8);
    }
    return (int)this;
}
