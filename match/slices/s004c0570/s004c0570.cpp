// 0x004c0570: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004c0410/s004c0410.cpp.

struct C_0042bfa0 { void FUN_0042bfa0(unsigned int, unsigned int); };
#pragma pack(push, 1)
struct Fr0_004c0570 {
    int v_l24;
    int v_l20;
    int dead0[2];
    int v_l8;
};
#pragma pack(pop)


struct D_004c0570 { int FUN_004c0570(int a4, int a8); };
// @ 0x004c0570
int D_004c0570::FUN_004c0570(int a4, int a8)
{
    Fr0_004c0570 fb;
    fb.v_l8 = (int)this + 24;
    *(int*)(char*)(int)this = 0;
    *(int*)((char*)(int)this + 4) = 0;
    *(int*)((char*)(int)this + 8) = 0;
    fb.v_l20 = (int)this + 12;
    *(int*)((char*)fb.v_l20 + 4) = fb.v_l8;
    *(int*)((char*)(int)this + 4) = (int)this + 24;
    *(int*)(char*)(int)this = (int)(int)*(int*)((char*)(int)this + 4);
    *(int*)((char*)(int)this + 8) = (int)(int)((int)*(int*)(char*)(int)this + 1024);
    fb.v_l24 = a8;
    ((C_0042bfa0*)(int)this)->FUN_0042bfa0((unsigned int)a4, (unsigned int)(int)&fb.v_l24);
    return (int)this;
}
