// 0x005611b0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s005609a0/s005609a0.cpp, src/game/SPEditors/_at_00560000.cpp.

extern "C" unsigned char g_013eb938[];
extern "C" unsigned char g_013ef094[];
extern "C" unsigned char g_013f4af8[];
extern "C" unsigned char g_013f4afc[];
extern "C" unsigned char g_013f4b00[];
struct C_005156b0 { void FUN_005156b0(); };
#pragma pack(push, 1)
struct Fr0_005611b0 {
    int v_l24;
    int dead0[3];
    int v_l8;
};
#pragma pack(pop)


struct D_005611b0 { void FUN_005611b0(); };
// @ 0x005611b0
void D_005611b0::FUN_005611b0()
{
    Fr0_005611b0 fb;
    *(int*)(char*)(int)this = (int)g_013f4b00;
    *(int*)((char*)(int)this + 4) = (int)g_013f4afc;
    *(int*)((char*)(int)this + 8) = (int)g_013f4af8;
    fb.v_l24 = (int)this + 28;
    fb.v_l8 = (int)(int)*(int*)(char*)fb.v_l24;
    for (; (unsigned int)fb.v_l8 < (unsigned int)*(int*)((char*)fb.v_l24 + 4); fb.v_l8 = fb.v_l8 + 12) {
    }
    ((C_005156b0*)fb.v_l24)->FUN_005156b0();
    *(int*)((char*)(int)this + 8) = (int)g_013ef094;
    *(int*)(char*)(int)this = (int)g_013eb938;
    return;
}
