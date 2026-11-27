// 0x00464680: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00464300/s00464300.cpp, src/game/SPBake/SPEditorExportUtilities.cpp.

struct C_00425990 { int FUN_00425990(); };
struct C_0045daf0 { void FUN_0045daf0(); };
struct C_005156b0 { void FUN_005156b0(); };
struct C_00554b10 { void FUN_00554b10(); };
#pragma pack(push, 1)
struct Fr0_00464680 {
    int dead0[2];
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
struct Fr1_00464680 {
    int dead0[1];
};
#pragma pack(pop)


struct D_00464680 { void FUN_00464680(); };
// @ 0x00464680
void D_00464680::FUN_00464680()
{
    Fr0_00464680 fb;
    Fr1_00464680 fa;
    fb.v_l24 = (int)this + 100;
    fb.v_l8 = (int)(int)*(int*)(char*)fb.v_l24;
    for (; (unsigned int)fb.v_l8 < (unsigned int)*(int*)((char*)fb.v_l24 + 4); fb.v_l8 = fb.v_l8 + 4) {
    }
    ((C_00425990*)fb.v_l24)->FUN_00425990();
    fb.v_l44 = (int)this + 80;
    fb.v_l28 = (int)(int)*(int*)(char*)fb.v_l44;
    for (; (unsigned int)fb.v_l28 < (unsigned int)*(int*)((char*)fb.v_l44 + 4); fb.v_l28 = fb.v_l28 + 16) {
    }
    ((C_00554b10*)fb.v_l44)->FUN_00554b10();
    fb.v_l64 = (int)this + 60;
    fb.v_l48 = (int)(int)*(int*)(char*)fb.v_l64;
    for (; (unsigned int)fb.v_l48 < (unsigned int)*(int*)((char*)fb.v_l64 + 4); fb.v_l48 = fb.v_l48 + 8) {
    }
    ((C_0045daf0*)fb.v_l64)->FUN_0045daf0();
    fb.v_l84 = (int)this + 40;
    fb.v_l68 = (int)(int)*(int*)(char*)fb.v_l84;
    for (; (unsigned int)fb.v_l68 < (unsigned int)*(int*)((char*)fb.v_l84 + 4); fb.v_l68 = fb.v_l68 + 12) {
    }
    ((C_005156b0*)fb.v_l84)->FUN_005156b0();
    fb.v_l104 = (int)this + 20;
    fb.v_l88 = (int)(int)*(int*)(char*)fb.v_l104;
    for (; (unsigned int)fb.v_l88 < (unsigned int)*(int*)((char*)fb.v_l104 + 4); fb.v_l88 = fb.v_l88 + 12) {
    }
    ((C_005156b0*)fb.v_l104)->FUN_005156b0();
    fb.v_l108 = (int)(int)*(int*)(char*)(int)this;
    for (; (unsigned int)fb.v_l108 < (unsigned int)*(int*)((char*)(int)this + 4); fb.v_l108 = fb.v_l108 + 4) {
    }
    ((C_00425990*)(int)this)->FUN_00425990();
    return;
}
