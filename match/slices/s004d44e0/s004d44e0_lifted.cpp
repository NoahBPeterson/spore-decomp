// 0x004d44e0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/SPEditorSpeciesManager.cpp.

struct C_004237d0 { void FUN_004237d0(); };
struct C_00425990 { void FUN_00425990(); };
struct C_00427440 { void FUN_00427440(); };
struct C_00432d60 { void FUN_00432d60(); };
struct C_004e0a60 { int FUN_004e0a60(); };
struct C_004e3210 { void FUN_004e3210(unsigned int, unsigned int); };
#pragma pack(push, 1)
struct Fr0_004d44e0 {
    int dead0[10];
    int v_l84;
    int dead1[3];
    int v_l68;
    int dead2[2];
    int v_l56;
    int v_l52;
    int v_l48;
    int v_l44;
    int v_l40;
    int v_l36;
    int v_l32;
    int v_l28;
    int v_l24;
    int v_l20;
    int v_l16;
    int v_l12;
    int v_l8;
};
struct Fr1_004d44e0 {
    int dead0[1];
};
#pragma pack(pop)


struct D_004d44e0 { void FUN_004d44e0(); };
// @ 0x004d44e0
void D_004d44e0::FUN_004d44e0()
{
    Fr0_004d44e0 fb;
    Fr1_004d44e0 fa;
    fb.v_l12 = (int)this + 2480;
    fb.v_l8 = (int)(int)*(int*)(char*)fb.v_l12;
    for (; (unsigned int)fb.v_l8 < (unsigned int)*(int*)((char*)fb.v_l12 + 4); fb.v_l8 = fb.v_l8 + 4) {
    }
    ((C_00425990*)fb.v_l12)->FUN_00425990();
    fb.v_l20 = (int)this + 2376;
    fb.v_l16 = (int)(int)*(int*)(char*)fb.v_l20;
    for (; (unsigned int)fb.v_l16 < (unsigned int)*(int*)((char*)fb.v_l20 + 4); fb.v_l16 = fb.v_l16 + 4) {
    }
    ((C_00425990*)fb.v_l20)->FUN_00425990();
    fb.v_l28 = (int)this + 2272;
    fb.v_l24 = (int)(int)*(int*)(char*)fb.v_l28;
    for (; (unsigned int)fb.v_l24 < (unsigned int)*(int*)((char*)fb.v_l28 + 4); fb.v_l24 = fb.v_l24 + 4) {
    }
    ((C_00425990*)fb.v_l28)->FUN_00425990();
    fb.v_l36 = (int)this + 2168;
    fb.v_l32 = (int)(int)*(int*)(char*)fb.v_l36;
    for (; (unsigned int)fb.v_l32 < (unsigned int)*(int*)((char*)fb.v_l36 + 4); fb.v_l32 = fb.v_l32 + 4) {
    }
    ((C_00425990*)fb.v_l36)->FUN_00425990();
    fb.v_l44 = (int)this + 2064;
    fb.v_l40 = (int)(int)*(int*)(char*)fb.v_l44;
    for (; (unsigned int)fb.v_l40 < (unsigned int)*(int*)((char*)fb.v_l44 + 4); fb.v_l40 = fb.v_l40 + 4) {
    }
    ((C_00425990*)fb.v_l44)->FUN_00425990();
    fb.v_l52 = (int)this + 1956;
    fb.v_l48 = (int)(int)*(int*)(char*)fb.v_l52;
    for (; (unsigned int)fb.v_l48 < (unsigned int)*(int*)((char*)fb.v_l52 + 4); fb.v_l48 = fb.v_l48 + 4) {
    }
    ((C_00425990*)fb.v_l52)->FUN_00425990();
    fb.v_l56 = (int)this + 1852;
    ((C_004e3210*)fb.v_l56)->FUN_004e3210((unsigned int)(int)*(int*)(char*)fb.v_l56, (unsigned int)(int)*(int*)((char*)fb.v_l56 + 4));
    ((C_00425990*)fb.v_l56)->FUN_00425990();
    ((C_00432d60*)((int)this + 1748))->FUN_00432d60();
    fb.v_l84 = (int)this + 1720;
    fb.v_l68 = (int)(int)*(int*)(char*)fb.v_l84;
    for (; (unsigned int)fb.v_l68 < (unsigned int)*(int*)((char*)fb.v_l84 + 4); fb.v_l68 = fb.v_l68 + 56) {
    }
    ((C_00427440*)fb.v_l84)->FUN_00427440();
    ((C_004237d0*)((int)this + 1324))->FUN_004237d0();
    ((C_004237d0*)((int)this + 1308))->FUN_004237d0();
    ((C_004e0a60*)(int)this)->FUN_004e0a60();
    return;
}
