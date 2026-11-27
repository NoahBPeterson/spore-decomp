// 0x004b25e0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004b2320/s004b2320.cpp, src/game/SPBake/SPEditorPaintTheme.cpp.

extern "C" unsigned char g_013eb938[];
extern "C" unsigned char g_013ec458[];
extern "C" unsigned char g_013ef6a4[];
extern "C" unsigned char g_013ef6b4[];
struct C_00425990 { void FUN_00425990(); };
struct C_00455290 { void FUN_00455290(); };
struct C_004b5a60 { void FUN_004b5a60(unsigned int); };
#pragma pack(push, 1)
struct Fr0_004b25e0 {
    int v_l48;
    int dead0[3];
    int v_l32;
    int v_l28;
    int v_l24;
    int dead1[3];
    int v_l8;
};
#pragma pack(pop)


struct D_004b25e0 { void FUN_004b25e0(); };
// @ 0x004b25e0
void D_004b25e0::FUN_004b25e0()
{
    Fr0_004b25e0 fb;
    *(int*)(char*)(int)this = (int)g_013ef6b4;
    *(int*)((char*)(int)this + 4) = (int)g_013ef6a4;
    fb.v_l24 = (int)this + 336;
    fb.v_l8 = (int)(int)*(int*)(char*)fb.v_l24;
    for (; (unsigned int)fb.v_l8 < (unsigned int)*(int*)((char*)fb.v_l24 + 4); fb.v_l8 = fb.v_l8 + 4) {
    }
    ((C_00425990*)fb.v_l24)->FUN_00425990();
    fb.v_l28 = (int)this + 296;
    ((C_004b5a60*)fb.v_l28)->FUN_004b5a60((unsigned int)(int)*(int*)((char*)fb.v_l28 + 12));
    fb.v_l48 = (int)this + 12;
    fb.v_l32 = (int)(int)*(int*)(char*)fb.v_l48;
    for (; (unsigned int)fb.v_l32 < (unsigned int)*(int*)((char*)fb.v_l48 + 4); fb.v_l32 = fb.v_l32 + 32) {
    }
    ((C_00455290*)fb.v_l48)->FUN_00455290();
    *(int*)((char*)(int)this + 4) = (int)g_013ec458;
    *(int*)(char*)(int)this = (int)g_013eb938;
    return;
}
