// 0x00475ab0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00474bd0/s00474bd0.cpp, src/game/SPGonzago/InteractionAgent.cpp.

extern "C" unsigned char g_013eb430[];
extern "C" unsigned char g_013ebb38[];
extern "C" unsigned char g_01667bac[];
extern "C" int __cdecl FUN_00f473a0(...);
#pragma pack(push, 1)
struct Fr0_00475ab0 {
    int v_l8;
};
#pragma pack(pop)


struct D_00475ab0 { void FUN_00475ab0(int a4); };
// @ 0x00475ab0
void D_00475ab0::FUN_00475ab0(int a4)
{
    Fr0_00475ab0 fb;
    if ((unsigned int)a4 > (unsigned int)1) {
        fb.v_l8 = (int)(int)FUN_00f473a0((unsigned int)a4, (unsigned int)(int)g_013eb430, (unsigned int)0, (unsigned int)0, (unsigned int)(int)g_013ebb38, (unsigned int)209);
        *(int*)(char*)(int)this = fb.v_l8;
        *(int*)((char*)(int)this + 4) = (int)(int)*(int*)(char*)(int)this;
        *(int*)((char*)(int)this + 8) = (int)(int)((int)*(int*)(char*)(int)this + a4);
    } else {
        *(int*)(char*)(int)this = (int)g_01667bac;
        *(int*)((char*)(int)this + 4) = (int)(int)*(int*)(char*)(int)this;
        *(int*)((char*)(int)this + 8) = (int)(int)((int)*(int*)(char*)(int)this + 1);
    }
    return;
}
