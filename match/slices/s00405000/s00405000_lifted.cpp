// 0x00405000: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00405000/s00405000.cpp, src/game/SPBake/SPEditorBaker.cpp.

extern "C" unsigned char g_013eb80c[];
struct C_00405050 { void FUN_00405050(); };
struct C_0083c750 { void FUN_0083c750(); };
extern "C" void __cdecl FUN_00f47380(...);
#pragma pack(push, 1)
struct Fr0_00405000 {
    int dead0[20];
};
struct Fr1_00405000 {
    int dead0[1];
};
#pragma pack(pop)


struct D_00405000 { int FUN_00405000(int a4); };
// @ 0x00405000
int D_00405000::FUN_00405000(int a4)
{
    Fr0_00405000 fb;
    Fr1_00405000 fa;
    *(int*)(char*)(int)this = (int)g_013eb80c;
    ((C_00405050*)((int)this + 20))->FUN_00405050();
    ((C_0083c750*)(int)this)->FUN_0083c750();
    if ((a4 & 1) != 0) {
        FUN_00f47380((unsigned int)(int)this);
    }
    return (int)this;
}
