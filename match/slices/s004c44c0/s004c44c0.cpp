// 0x004c44c0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004c38e0/s004c38e0.cpp, src/game/SPBake/_at_004c0000.cpp.

extern "C" unsigned char g_013eb430[];
struct C_00425990 { void FUN_00425990(); };
struct C_00454860 { void FUN_00454860(unsigned int); };
extern "C" void __cdecl FUN_0048ccf0(...);
struct C_004cc190 { int FUN_004cc190(); };
struct C_004cc470 { void FUN_004cc470(unsigned int, unsigned int, unsigned int); };
struct C_004cc540 { void FUN_004cc540(unsigned int, unsigned int); };
struct C_004cc7d0 { void FUN_004cc7d0(unsigned int); };
struct C_004cd020 { void FUN_004cd020(unsigned int); };
struct C_004cd060 { void FUN_004cd060(float, float); };
extern "C" int __cdecl FUN_00f473a0(...);
#pragma pack(push, 1)
struct Fr0_004c44c0 {
    int dead0[3];
    int v_l56;
    int v_l52;
    int dead1[2];
    int v_l40;
    int dead2[1];
    int v_l32;
    int v_l28;
    int v_l24;
    int v_l20;
    int dead3[2];
    int v_l8;
};
#pragma pack(pop)


struct D_004c44c0 { int FUN_004c44c0(int a4, int a8); };
// @ 0x004c44c0
int D_004c44c0::FUN_004c44c0(int a4, int a8)
{
    Fr0_004c44c0 fb;
    fb.v_l32 = (int)(int)FUN_00f473a0((unsigned int)304, (unsigned int)(int)g_013eb430, (unsigned int)0, (unsigned int)0, (unsigned int)0, (unsigned int)0);
    fb.v_l8 = fb.v_l32 != 0 ? ((C_004cc190*)fb.v_l32)->FUN_004cc190() : 0;
    ((C_004cd020*)fb.v_l8)->FUN_004cd020((unsigned int)-895765649);
    ((C_004cc470*)fb.v_l8)->FUN_004cc470((unsigned int)a8, (unsigned int)-269778708, (unsigned int)0);
    ((C_004cd060*)fb.v_l8)->FUN_004cd060(*(float*)((char*)(int)this + 124), *(float*)((char*)(int)this + 128));
    fb.v_l28 = 0;
    fb.v_l24 = 0;
    fb.v_l20 = 0;
    ((C_00454860*)(int)&fb.v_l28)->FUN_00454860((unsigned int)(int)&a4);
    FUN_0048ccf0((unsigned int)a4, (unsigned int)(int)&fb.v_l28);
    ((C_004cc540*)fb.v_l8)->FUN_004cc540((unsigned int)(int)&fb.v_l28, (unsigned int)0);
    fb.v_l52 = (int)(int)*(int*)((char*)a4 + 24);
    ((C_004cc7d0*)fb.v_l8)->FUN_004cc7d0((unsigned int)fb.v_l52);
    fb.v_l40 = fb.v_l8;
    fb.v_l56 = fb.v_l28;
    for (; (unsigned int)fb.v_l56 < (unsigned int)fb.v_l24; fb.v_l56 = fb.v_l56 + 4) {
    }
    ((C_00425990*)(int)&fb.v_l28)->FUN_00425990();
    return fb.v_l40;
}
