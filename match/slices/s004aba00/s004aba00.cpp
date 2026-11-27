// 0x004aba00: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004ab690/s004ab690.cpp, src/game/SPBake/_at_004a0000.cpp.

extern "C" unsigned char g_013ef094[];
extern "C" unsigned char g_013ef620[];
extern "C" unsigned char g_013ef624[];
struct C_004237d0 { void FUN_004237d0(); };
struct C_00453540 { void FUN_00453540(); };
struct C_00453eb0 { int FUN_00453eb0(); };
struct C_004ad330 { void FUN_004ad330(); };
struct C_004fd940 { void FUN_004fd940(); };
#pragma pack(push, 1)
struct Fr0_004aba00 {
    int dead0[4];
    int v_l76;
    int dead1[12];
    int v_l24;
    int dead2[3];
    int v_l8;
};
struct Fr1_004aba00 {
    int dead0[1];
};
#pragma pack(pop)


struct D_004aba00 { void FUN_004aba00(); };
// @ 0x004aba00
void D_004aba00::FUN_004aba00()
{
    Fr0_004aba00 fb;
    Fr1_004aba00 fa;
    *(int*)(char*)(int)this = (int)g_013ef624;
    *(int*)((char*)(int)this + 4) = (int)g_013ef620;
    ((C_004ad330*)(int)this)->FUN_004ad330();
    fb.v_l24 = (int)this + 200;
    fb.v_l8 = (int)(int)*(int*)(char*)fb.v_l24;
    for (; (unsigned int)fb.v_l8 < (unsigned int)*(int*)((char*)fb.v_l24 + 4); fb.v_l8 = fb.v_l8 + 24) {
    }
    ((C_004fd940*)fb.v_l24)->FUN_004fd940();
    ((C_004237d0*)((int)this + 124))->FUN_004237d0();
    ((C_004237d0*)((int)this + 108))->FUN_004237d0();
    ((C_004237d0*)((int)this + 92))->FUN_004237d0();
    fb.v_l76 = (int)this + 48;
    if ((int)*(int*)(char*)fb.v_l76 != 0) {
        ((C_00453540*)(int)*(int*)(char*)fb.v_l76)->FUN_00453540();
    }
    ((C_00453eb0*)((int)this + 24))->FUN_00453eb0();
    *(int*)((char*)(int)this + 4) = (int)g_013ef094;
    return;
}
