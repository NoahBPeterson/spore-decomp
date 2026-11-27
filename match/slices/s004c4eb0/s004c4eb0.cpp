// 0x004c4eb0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004c4650/s004c4650.cpp, src/game/SPBake/_at_004c0000.cpp.

struct C_004c4650 { void FUN_004c4650(unsigned int); };
struct C_004c6070 { void FUN_004c6070(); };
struct C_004cced0 { void FUN_004cced0(); };
struct C_00526430 { int FUN_00526430(); };
#pragma pack(push, 1)
struct Fr0_004c4eb0 {
    int dead0[2];
    int v_l28;
    int v_l24;
    int v_l20;
    int v_l16;
    int v_l12;
    int v_l8;
};
#pragma pack(pop)


struct D_004c4eb0 { void FUN_004c4eb0(); };
// @ 0x004c4eb0
void D_004c4eb0::FUN_004c4eb0()
{
    Fr0_004c4eb0 fb;
    ((C_004c4650*)(int)this)->FUN_004c4650((unsigned int)0);
    *(int*)((char*)(int)this + 16) = 0;
    *(int*)((char*)(int)this + 20) = 0;
    fb.v_l8 = (int)(int)*(int*)((char*)(int)this + 24);
    if (fb.v_l8 != 0) {
        fb.v_l12 = (int)(int)*(int*)((char*)(int)this + 24);
        ((C_004cced0*)fb.v_l12)->FUN_004cced0();
    }
    fb.v_l16 = (int)(int)*(int*)((char*)(int)this + 28);
    if (fb.v_l16 != 0) {
        fb.v_l20 = (int)(int)*(int*)((char*)(int)this + 28);
        ((C_004cced0*)fb.v_l20)->FUN_004cced0();
    }
    while ((int)(unsigned char)((C_00526430*)((int)this + 72))->FUN_00526430() == 0) {
        fb.v_l24 = (int)(int)((int)*(int*)((char*)(int)this + 76) - 8);
        fb.v_l28 = (int)(int)*(int*)((char*)fb.v_l24 + 4);
        ((C_004cced0*)fb.v_l28)->FUN_004cced0();
        ((C_004c6070*)((int)this + 72))->FUN_004c6070();
    }
    return;
}
