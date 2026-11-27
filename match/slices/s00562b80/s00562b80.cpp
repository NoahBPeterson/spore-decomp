// 0x00562b80: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s005628d0/s005628d0.cpp, src/game/SPEditors/SPObjectTemplateDB.cpp.

struct C_004769b0 { void FUN_004769b0(unsigned int, unsigned int); };
struct C_00562510 { int FUN_00562510(unsigned int, unsigned int); };
struct C_00565500 { void FUN_00565500(unsigned int, unsigned int, unsigned int); };
#pragma pack(push, 1)
struct Fr0_00562b80 {
    int v_l32;
    int v_l28;
    int v_l24;
    int dead0[4];
};
#pragma pack(pop)


struct D_00562b80 { void FUN_00562b80(int a4, int a8); };
// @ 0x00562b80
void D_00562b80::FUN_00562b80(int a4, int a8)
{
    Fr0_00562b80 fb;
    fb.v_l24 = (int)this + 300;
    ((C_004769b0*)fb.v_l24)->FUN_004769b0((unsigned int)(int)*(int*)(char*)fb.v_l24, (unsigned int)(int)*(int*)((char*)fb.v_l24 + 4));
    fb.v_l28 = (int)(int)((int)(int)((int)*(int*)((char*)a8 + 4) - (int)*(int*)(char*)a8) / 36);
    fb.v_l32 = (int)(int)*(int*)(char*)a8;
    ((C_00565500*)(int)this)->FUN_00565500((unsigned int)((int)this + 300), (unsigned int)fb.v_l32, (unsigned int)fb.v_l28);
    ((C_00562510*)(int)this)->FUN_00562510((unsigned int)((int)this + 300), (unsigned int)a4);
    return;
}
