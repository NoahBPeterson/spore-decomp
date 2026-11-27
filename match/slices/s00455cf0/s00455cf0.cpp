// 0x00455cf0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004553b0/s004553b0.cpp, src/game/UTFSpore_Win32/instantiate.cpp.

struct C_0050d750 { void FUN_0050d750(unsigned int); };
#pragma pack(push, 1)
struct Fr0_00455cf0 {
    int dead0[1];
};
#pragma pack(pop)


struct D_00455cf0 { int FUN_00455cf0(int a4); };
// @ 0x00455cf0
int D_00455cf0::FUN_00455cf0(int a4)
{
    Fr0_00455cf0 fb;
    *(int*)(char*)(int)this = 0;
    *(int*)((char*)(int)this + 4) = 0;
    *(int*)((char*)(int)this + 8) = 0;
    *(int*)((char*)(int)this + 20) = 0;
    *(int*)(char*)(int)this = (int)this + 24;
    *(int*)((char*)(int)this + 4) = (int)(int)*(int*)(char*)(int)this;
    *(int*)((char*)(int)this + 8) = (int)(int)((int)*(int*)(char*)(int)this + 64);
    ((C_0050d750*)(int)this)->FUN_0050d750((unsigned int)a4);
    return (int)this;
}
