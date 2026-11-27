// 0x00453e20: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00453250/s00453250.cpp.

struct C_00433960 { int FUN_00433960(); };
struct C_00454dc0 { int FUN_00454dc0(unsigned int, unsigned int); };
struct C_00455fa0 { void FUN_00455fa0(unsigned int, unsigned int, unsigned int); };
struct C_004ae250 { int FUN_004ae250(); };
#pragma pack(push, 1)
struct Fr0_00453e20 {
    int dead0[7];
    int v_l48;
    int v_l44;
    int v_l40;
    int v_l36[8];
};
#pragma pack(pop)


struct D_00453e20 { void FUN_00453e20(int a4); };
// @ 0x00453e20
void D_00453e20::FUN_00453e20(int a4)
{
    Fr0_00453e20 fb;
    if ((unsigned int)a4 > (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) >> 5)) {
        fb.v_l48 = ((C_00433960*)(int)&fb.v_l36)->FUN_00433960();
        fb.v_l44 = (int)(int)(a4 - (int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) >> 5));
        fb.v_l40 = (int)(int)*(int*)((char*)(int)this + 4);
        ((C_00455fa0*)(int)this)->FUN_00455fa0((unsigned int)fb.v_l40, (unsigned int)fb.v_l44, (unsigned int)fb.v_l48);
        ((C_004ae250*)(int)&fb.v_l36)->FUN_004ae250();
    } else {
        ((C_00454dc0*)(int)this)->FUN_00454dc0((unsigned int)(int)((a4 << 5) + (int)*(int*)(char*)(int)this), (unsigned int)(int)*(int*)((char*)(int)this + 4));
    }
    return;
}
