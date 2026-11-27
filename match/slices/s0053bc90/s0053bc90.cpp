// 0x0053bc90: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0053b930/s0053b930.cpp, src/game/SPBake/SPSkinPaintParticleDescription.cpp.

struct C_004cd3c0 { void FUN_004cd3c0(unsigned int); };
extern "C" void __cdecl FUN_0093a780(...);
#pragma pack(push, 1)
struct Fr0_0053bc90 {
    int v_l44;
    int dead0[7];
    int v_l12;
    int v_l8;
};
#pragma pack(pop)

// @ 0x0053bc90
extern "C" int __cdecl FUN_0053bc90(int a4, int a8)
{
    Fr0_0053bc90 fb;
    FUN_0093a780((unsigned int)a4, (unsigned int)(int)&fb.v_l8, (unsigned int)1, (unsigned int)0);
    ((C_004cd3c0*)a8)->FUN_004cd3c0((unsigned int)fb.v_l8);
    fb.v_l12 = 0;
    for (; (unsigned int)fb.v_l12 < (unsigned int)fb.v_l8; fb.v_l12 = fb.v_l12 + 1) {
        fb.v_l44 = (int)(int)((int)*(int*)(char*)a8 + (fb.v_l12 << 2));
        FUN_0093a780((unsigned int)a4, (unsigned int)fb.v_l44, (unsigned int)1, (unsigned int)0);
    }
    return a4;
}
