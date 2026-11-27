// 0x004b9f70: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004b9960/s004b9960.cpp.

extern "C" unsigned char g_013eb938[];
extern "C" unsigned char g_013ebcdc[];
extern "C" unsigned char g_013eeda4[];
struct C_0041e5d0 { void FUN_0041e5d0(); };
struct C_004250b0 { int FUN_004250b0(); };
struct C_00425990 { void FUN_00425990(); };
struct C_00427440 { void FUN_00427440(); };
#pragma pack(push, 1)
struct Fr0_004b9f70 {
    int v_l140;
    int dead0[3];
    int v_l124;
    int v_l120;
    int dead1[3];
    int v_l104;
    int dead2[4];
    int v_l84;
    int dead3[3];
    int v_l68;
    int v_l64;
    int dead4[3];
    int v_l48;
    int v_l44;
    int dead5[3];
    int v_l28;
    int v_l24;
    int dead6[3];
    int v_l8;
};
#pragma pack(pop)


struct D_004b9f70 { void FUN_004b9f70(); };
// @ 0x004b9f70
void D_004b9f70::FUN_004b9f70()
{
    Fr0_004b9f70 fb;
    *(int*)(char*)(int)this = (int)g_013eeda4;
    fb.v_l24 = (int)this + 276;
    fb.v_l8 = (int)(int)*(int*)(char*)fb.v_l24;
    for (; (unsigned int)fb.v_l8 < (unsigned int)*(int*)((char*)fb.v_l24 + 4); fb.v_l8 = fb.v_l8 + 56) {
    }
    ((C_00427440*)fb.v_l24)->FUN_00427440();
    fb.v_l44 = (int)this + 252;
    fb.v_l28 = (int)(int)*(int*)(char*)fb.v_l44;
    for (; (unsigned int)fb.v_l28 < (unsigned int)*(int*)((char*)fb.v_l44 + 4); fb.v_l28 = fb.v_l28 + 4) {
    }
    ((C_00425990*)fb.v_l44)->FUN_00425990();
    fb.v_l64 = (int)this + 232;
    fb.v_l48 = (int)(int)*(int*)(char*)fb.v_l64;
    for (; (unsigned int)fb.v_l48 < (unsigned int)*(int*)((char*)fb.v_l64 + 4); fb.v_l48 = fb.v_l48 + 4) {
    }
    ((C_00425990*)fb.v_l64)->FUN_00425990();
    fb.v_l84 = (int)this + 212;
    fb.v_l68 = (int)(int)*(int*)(char*)fb.v_l84;
    for (; (unsigned int)fb.v_l68 < (unsigned int)*(int*)((char*)fb.v_l84 + 4); fb.v_l68 = fb.v_l68 + 4) {
    }
    ((C_00425990*)fb.v_l84)->FUN_00425990();
    ((C_0041e5d0*)((int)this + 192))->FUN_0041e5d0();
    fb.v_l120 = (int)this + 172;
    fb.v_l104 = (int)(int)*(int*)(char*)fb.v_l120;
    for (; (unsigned int)fb.v_l104 < (unsigned int)*(int*)((char*)fb.v_l120 + 4); fb.v_l104 = fb.v_l104 + 4) {
    }
    ((C_00425990*)fb.v_l120)->FUN_00425990();
    fb.v_l140 = (int)this + 152;
    fb.v_l124 = (int)(int)*(int*)(char*)fb.v_l140;
    for (; (unsigned int)fb.v_l124 < (unsigned int)*(int*)((char*)fb.v_l140 + 4); fb.v_l124 = fb.v_l124 + 140) {
    }
    ((C_004250b0*)fb.v_l140)->FUN_004250b0();
    *(int*)(char*)(int)this = (int)g_013ebcdc;
    *(int*)(char*)(int)this = (int)g_013eb938;
    return;
}
