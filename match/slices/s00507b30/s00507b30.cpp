// 0x00507b30: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00507670/s00507670.cpp, src/game/UTFSpore_Win32/instantiate.cpp.

struct C_00425990 { int FUN_00425990(); };
struct C_0050ea50 { void FUN_0050ea50(); };
struct C_005156b0 { void FUN_005156b0(); };
#pragma pack(push, 1)
struct Fr0_00507b30 {
    int v_l124;
    int dead0[3];
    int v_l108;
    int v_l104;
    int dead1[3];
    int v_l88;
    int v_l84;
    int dead2[3];
    int v_l68;
    int v_l64;
    int dead3[3];
    int v_l48;
    int v_l44;
    int dead4[3];
    int v_l28;
    int v_l24;
    int dead5[3];
    int v_l8;
};
#pragma pack(pop)


struct D_00507b30 { void FUN_00507b30(); };
// @ 0x00507b30
void D_00507b30::FUN_00507b30()
{
    Fr0_00507b30 fb;
    fb.v_l24 = (int)this + 128;
    fb.v_l8 = (int)(int)*(int*)(char*)fb.v_l24;
    for (; (unsigned int)fb.v_l8 < (unsigned int)*(int*)((char*)fb.v_l24 + 4); fb.v_l8 = fb.v_l8 + 12) {
    }
    ((C_005156b0*)fb.v_l24)->FUN_005156b0();
    fb.v_l44 = (int)this + 108;
    fb.v_l28 = (int)(int)*(int*)(char*)fb.v_l44;
    for (; (unsigned int)fb.v_l28 < (unsigned int)*(int*)((char*)fb.v_l44 + 4); fb.v_l28 = fb.v_l28 + 4) {
    }
    ((C_00425990*)fb.v_l44)->FUN_00425990();
    fb.v_l64 = (int)this + 68;
    fb.v_l48 = (int)(int)*(int*)(char*)fb.v_l64;
    for (; (unsigned int)fb.v_l48 < (unsigned int)*(int*)((char*)fb.v_l64 + 4); fb.v_l48 = fb.v_l48 + 20) {
    }
    ((C_0050ea50*)fb.v_l64)->FUN_0050ea50();
    fb.v_l84 = (int)this + 48;
    fb.v_l68 = (int)(int)*(int*)(char*)fb.v_l84;
    for (; (unsigned int)fb.v_l68 < (unsigned int)*(int*)((char*)fb.v_l84 + 4); fb.v_l68 = fb.v_l68 + 4) {
    }
    ((C_00425990*)fb.v_l84)->FUN_00425990();
    fb.v_l104 = (int)this + 28;
    fb.v_l88 = (int)(int)*(int*)(char*)fb.v_l104;
    for (; (unsigned int)fb.v_l88 < (unsigned int)*(int*)((char*)fb.v_l104 + 4); fb.v_l88 = fb.v_l88 + 4) {
    }
    ((C_00425990*)fb.v_l104)->FUN_00425990();
    fb.v_l124 = (int)this + 8;
    fb.v_l108 = (int)(int)*(int*)(char*)fb.v_l124;
    for (; (unsigned int)fb.v_l108 < (unsigned int)*(int*)((char*)fb.v_l124 + 4); fb.v_l108 = fb.v_l108 + 4) {
    }
    ((C_00425990*)fb.v_l124)->FUN_00425990();
    return;
}
