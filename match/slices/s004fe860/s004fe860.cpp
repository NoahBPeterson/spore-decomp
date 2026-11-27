// 0x004fe860: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004fd9a0/s004fd9a0.cpp.

struct C_00423650 { int FUN_00423650(unsigned int, unsigned int); };
struct C_004feb50 { void FUN_004feb50(); };
#pragma pack(push, 1)
struct Fr0_004fe860 {
    int v_l8;
};
#pragma pack(pop)


struct D_004fe860 { void FUN_004fe860(int a4); };
// @ 0x004fe860
void D_004fe860::FUN_004fe860(int a4)
{
    Fr0_004fe860 fb;
    ((C_004feb50*)(int)this)->FUN_004feb50();
    *(unsigned char*)((char*)(int)this + 60) = (unsigned char)0;
    fb.v_l8 = a4;
    while ((int)*(unsigned short*)(char*)fb.v_l8 != 0) {
        fb.v_l8 = fb.v_l8 + 2;
    }
    ((C_00423650*)(int)this)->FUN_00423650((unsigned int)a4, (unsigned int)(a4 + (fb.v_l8 - a4 >> 1 << 1)));
    return;
}
