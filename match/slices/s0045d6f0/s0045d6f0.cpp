// 0x0045d6f0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0045d2c0/s0045d2c0.cpp.

struct C_00422cf0 { void FUN_00422cf0(unsigned int); };
#pragma pack(push, 1)
struct Fr0_0045d6f0 {
    int dead0[1];
    int v_l12;
    int v_l8;
};
#pragma pack(pop)
struct S16 { int m0; int m1; int m2; int m3; int m4; int m5; int m6; int m7; int m8; int m9; int m10; int m11; int m12; int m13; int m14; int m15; };


struct D_0045d6f0 { int FUN_0045d6f0(); };
// @ 0x0045d6f0
int D_0045d6f0::FUN_0045d6f0()
{
    Fr0_0045d6f0 fb;
    fb.v_l8 = (int)this + 20;
    ((C_00422cf0*)(int)this)->FUN_00422cf0((unsigned int)(int)&fb.v_l12);
    *(int*)((char*)(int)this + 4) = (int)this + 20;
    *(int*)(char*)(int)this = (int)(int)*(int*)((char*)(int)this + 4);
    *(int*)((char*)(int)this + 8) = (int)(int)((int)*(int*)(char*)(int)this + 768);
    *(unsigned char*)(char*)(int)*(int*)(char*)(int)this = (unsigned char)0;
    return (int)this;
}
