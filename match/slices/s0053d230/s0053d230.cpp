// 0x0053d230: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0053c6f0/s0053c6f0.cpp, src/game/SPBake/SPSkinPaintParticleDescription.cpp.

#pragma pack(push, 1)
struct Fr0_0053d230 {
    int v_l20;
    int v_l16;
    int v_l12;
    int v_l8;
};
#pragma pack(pop)
struct S5 { int m0; int m1; int m2; int m3; int m4; };

// @ 0x0053d230
extern "C" void __cdecl FUN_0053d230(int a4, int a8, int a12)
{
    Fr0_0053d230 fb;
    fb.v_l8 = a4;
    for (; (unsigned int)a8 > (unsigned int)0; *(int*)&a8 = a8 - 1, fb.v_l8 = fb.v_l8 + 20) {
        fb.v_l16 = fb.v_l8;
        fb.v_l12 = fb.v_l16;
        if (fb.v_l12 != 0) {
            *(S5*)fb.v_l12 = *(S5*)a12;
            fb.v_l20 = fb.v_l12;
        } else {
            fb.v_l20 = 0;
        }
    }
    return;
}
