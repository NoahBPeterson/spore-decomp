// 0x004c0410: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004c0410/s004c0410.cpp.

struct C_004c10e0 { int FUN_004c10e0(unsigned int, unsigned int, unsigned int); };
struct C_00514750 { int FUN_00514750(unsigned int, unsigned int); };
#pragma pack(push, 1)
struct Fr0_004c0410 {
    int dead0[4];
    int v_l16;
    int v_l12;
    char dead1;
    char dead2;
    char dead3;
    unsigned char v_l5;
};
#pragma pack(pop)


struct D_004c0410 { void FUN_004c0410(int a4); };
// @ 0x004c0410
void D_004c0410::FUN_004c0410(int a4)
{
    Fr0_004c0410 fb;
    if ((unsigned int)a4 > (unsigned int)(int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this)) {
        fb.v_l5 = (unsigned char)0;
        fb.v_l16 = (int)(int)(a4 - (int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this));
        fb.v_l12 = (int)(int)*(int*)((char*)(int)this + 4);
        ((C_004c10e0*)(int)this)->FUN_004c10e0((unsigned int)fb.v_l12, (unsigned int)fb.v_l16, (unsigned int)(int)(int)&fb.v_l5);
    } else {
        ((C_00514750*)(int)this)->FUN_00514750((unsigned int)(int)((int)*(int*)(char*)(int)this + a4), (unsigned int)(int)*(int*)((char*)(int)this + 4));
    }
    return;
}
