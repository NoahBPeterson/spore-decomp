// 0x004b9d40: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004b9960/s004b9960.cpp.

extern "C" unsigned char g_013eb938[];
extern "C" unsigned char g_013ebcdc[];
extern "C" unsigned char g_013ef8d4[];
struct C_004b1700 { int FUN_004b1700(); };
#pragma pack(push, 1)
struct Fr0_004b9d40 {
    int v_l24;
    int dead0[3];
    int v_l8;
};
#pragma pack(pop)


struct D_004b9d40 { void FUN_004b9d40(); };
// @ 0x004b9d40
void D_004b9d40::FUN_004b9d40()
{
    Fr0_004b9d40 fb;
    *(int*)(char*)(int)this = (int)g_013ef8d4;
    fb.v_l24 = (int)this + 152;
    fb.v_l8 = (int)(int)*(int*)(char*)fb.v_l24;
    for (; (unsigned int)fb.v_l8 < (unsigned int)*(int*)((char*)fb.v_l24 + 4); fb.v_l8 = fb.v_l8 + 472) {
    }
    ((C_004b1700*)fb.v_l24)->FUN_004b1700();
    *(int*)(char*)(int)this = (int)g_013ebcdc;
    *(int*)(char*)(int)this = (int)g_013eb938;
    return;
}
