// 0x005506c0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0054fb00/s0054fb00.cpp, src/game/SPBake/SPPollinatorAssetDirectory.cpp.

extern "C" unsigned char g_013eb938[];
extern "C" unsigned char g_013ebcdc[];
extern "C" unsigned char g_013f3d8c[];
struct C_004237d0 { int FUN_004237d0(); };
struct C_00553b90 { void FUN_00553b90(); };
struct C_00553e00 { void FUN_00553e00(); };
struct C_00553fb0 { void FUN_00553fb0(); };
#pragma pack(push, 1)
struct Fr0_005506c0 {
    int dead0[26];
};
#pragma pack(pop)


struct D_005506c0 { void FUN_005506c0(); };
// @ 0x005506c0
void D_005506c0::FUN_005506c0()
{
    Fr0_005506c0 fb;
    *(int*)(char*)(int)this = (int)g_013f3d8c;
    ((C_00553fb0*)((int)this + 192))->FUN_00553fb0();
    ((C_00553e00*)((int)this + 172))->FUN_00553e00();
    ((C_00553b90*)((int)this + 152))->FUN_00553b90();
    ((C_004237d0*)((int)this + 136))->FUN_004237d0();
    ((C_004237d0*)((int)this + 120))->FUN_004237d0();
    ((C_004237d0*)((int)this + 88))->FUN_004237d0();
    *(int*)(char*)(int)this = (int)g_013ebcdc;
    *(int*)(char*)(int)this = (int)g_013eb938;
    return;
}
