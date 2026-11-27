// 0x0047e600: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0047e4b0/s0047e4b0.cpp, src/game/SPBake/_at_00470000.cpp.

extern "C" unsigned char g_015d4578[];
extern "C" unsigned char g_015d457c[];
extern "C" unsigned char g_015d4580[];
#pragma pack(push, 1)
struct Fr0_0047e600 {
    int v_l8;
};
#pragma pack(pop)


struct D_0047e600 { int FUN_0047e600(int a4); };
// @ 0x0047e600
int D_0047e600::FUN_0047e600(int a4)
{
    Fr0_0047e600 fb;
    if ((int)*(int*)((char*)(int)this + 16) != 0) {
        fb.v_l8 = (int)(int)((int)*(int*)((char*)(int)this + 16) + 72);
        *(float*)(char*)a4 = *(float*)(char*)fb.v_l8;
        *(float*)((char*)a4 + 4) = *(float*)((char*)fb.v_l8 + 4);
        *(float*)((char*)a4 + 8) = *(float*)((char*)fb.v_l8 + 8);
        return a4;
    }
        *(float*)(char*)a4 = (float)*(float*)g_015d4578;
        *(float*)((char*)a4 + 4) = (float)*(float*)g_015d457c;
        *(float*)((char*)a4 + 8) = (float)*(float*)g_015d4580;
        return a4;
}
