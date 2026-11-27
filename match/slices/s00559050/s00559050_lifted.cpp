// 0x00559050: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00559050/s00559050.cpp, src/game/SPEditors/SPObjectTemplateDB.cpp.

extern "C" unsigned char g_013eb938[];
extern "C" unsigned char g_013ebcdc[];
struct C_005156b0 { void FUN_005156b0(); };
extern "C" void __cdecl FUN_00f47380(...);
#pragma pack(push, 1)
struct Fr0_00559050 {
    int v_l24;
    int dead0[3];
    int v_l8;
};
#pragma pack(pop)


struct D_00559050 { int FUN_00559050(int a4); };
// @ 0x00559050
int D_00559050::FUN_00559050(int a4)
{
    Fr0_00559050 fb;
    fb.v_l24 = (int)this + 24;
    fb.v_l8 = (int)(int)*(int*)(char*)fb.v_l24;
    for (; (unsigned int)fb.v_l8 < (unsigned int)*(int*)((char*)fb.v_l24 + 4); fb.v_l8 = fb.v_l8 + 12) {
    }
    ((C_005156b0*)fb.v_l24)->FUN_005156b0();
    *(int*)(char*)(int)this = (int)g_013ebcdc;
    *(int*)(char*)(int)this = (int)g_013eb938;
    if ((a4 & 1) != 0) {
        FUN_00f47380((unsigned int)(int)this);
    }
    return (int)this;
}
