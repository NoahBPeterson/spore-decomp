// 0x00464480: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00464300/s00464300.cpp, src/game/SPBake/SPEditorExportUtilities.cpp.

struct C_004237d0 { int FUN_004237d0(); };
struct C_00425990 { void FUN_00425990(); };
struct C_0045daf0 { void FUN_0045daf0(); };
struct C_00474f30 { void FUN_00474f30(); };
struct C_00474fb0 { void FUN_00474fb0(); };
struct C_00476ec0 { void FUN_00476ec0(); };
struct C_00476f80 { void FUN_00476f80(); };
#pragma pack(push, 1)
struct Fr0_00464480 {
    int dead0[6];
    int v_l92;
    int dead1[3];
    int v_l76;
    int v_l72;
    int dead2[3];
    int v_l56;
    int dead3[2];
    int v_l44;
    int dead4[3];
    int v_l28;
    int v_l24;
    int dead5[3];
    int v_l8;
};
struct Fr1_00464480 {
    int dead0[1];
};
#pragma pack(pop)


struct D_00464480 { void FUN_00464480(); };
// @ 0x00464480
void D_00464480::FUN_00464480()
{
    Fr0_00464480 fb;
    Fr1_00464480 fa;
    fb.v_l24 = (int)this + 144;
    fb.v_l8 = (int)(int)*(int*)(char*)fb.v_l24;
    for (; (unsigned int)fb.v_l8 < (unsigned int)*(int*)((char*)fb.v_l24 + 4); fb.v_l8 = fb.v_l8 + 48) {
    }
    ((C_00476f80*)fb.v_l24)->FUN_00476f80();
    fb.v_l44 = (int)this + 124;
    fb.v_l28 = (int)(int)*(int*)(char*)fb.v_l44;
    for (; (unsigned int)fb.v_l28 < (unsigned int)*(int*)((char*)fb.v_l44 + 4); fb.v_l28 = fb.v_l28 + 8) {
    }
    ((C_0045daf0*)fb.v_l44)->FUN_0045daf0();
    ((C_00474fb0*)((int)this + 84))->FUN_00474fb0();
    fb.v_l72 = (int)this + 64;
    fb.v_l56 = (int)(int)*(int*)(char*)fb.v_l72;
    for (; (unsigned int)fb.v_l56 < (unsigned int)*(int*)((char*)fb.v_l72 + 4); fb.v_l56 = fb.v_l56 + 4) {
    }
    ((C_00425990*)fb.v_l72)->FUN_00425990();
    fb.v_l92 = (int)this + 36;
    fb.v_l76 = (int)(int)*(int*)(char*)fb.v_l92;
    for (; (unsigned int)fb.v_l76 < (unsigned int)*(int*)((char*)fb.v_l92 + 4); fb.v_l76 = fb.v_l76 + 84) {
    }
    ((C_00476ec0*)fb.v_l92)->FUN_00476ec0();
    ((C_00474f30*)((int)this + 16))->FUN_00474f30();
    ((C_004237d0*)(int)this)->FUN_004237d0();
    return;
}
