// 0x0054def0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0054dd30/s0054dd30.cpp, src/game/SPBake/SPPollinatorAssetDirectory.cpp.

extern "C" unsigned char g_013eb394[];
struct C_004e0f20 { void FUN_004e0f20(); };
struct C_00552860 { void FUN_00552860(); };
struct C_005534b0 { void FUN_005534b0(); };
struct C_00922130 { void FUN_00922130(); };
#pragma pack(push, 1)
struct Fr0_0054def0 {
    int dead0[18];
};
#pragma pack(pop)


struct D_0054def0 { void FUN_0054def0(); };
// @ 0x0054def0
void D_0054def0::FUN_0054def0()
{
    Fr0_0054def0 fb;
    ((C_004e0f20*)((int)this + 256))->FUN_004e0f20();
    ((C_004e0f20*)((int)this + 224))->FUN_004e0f20();
    ((C_005534b0*)((int)this + 156))->FUN_005534b0();
    ((C_005534b0*)((int)this + 124))->FUN_005534b0();
    ((C_00552860*)((int)this + 92))->FUN_00552860();
    ((C_00552860*)((int)this + 60))->FUN_00552860();
    ((C_00922130*)((int)this + 8))->FUN_00922130();
    *(int*)(char*)(int)this = (int)g_013eb394;
    return;
}
