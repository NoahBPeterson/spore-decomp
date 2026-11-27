// 0x0047b3d0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0047a5a0/s0047a5a0.cpp, src/game/SPGonzago/InteractionAgent.cpp.

#pragma pack(push, 1)
struct Fr0_0047b3d0 {
    int v_l40;
    int v_l36;
    int v_l32;
    char dead0;
    char dead1;
    char dead2;
    unsigned char v_l25;
    int v_l24;
    int v_l20;
    int v_l16;
    char dead3;
    char dead4;
    char dead5;
    unsigned char v_l9;
    int v_l8;
};
#pragma pack(pop)
struct S5 { int m0; int m1; int m2; int m3; int m4; };

// @ 0x0047b3d0
extern "C" int __cdecl FUN_0047b3d0(int a4, int a8, int a12)
{
    Fr0_0047b3d0 fb;
    fb.v_l9 = (unsigned char)0;
    fb.v_l24 = a12;
    fb.v_l20 = a4;
    for (; fb.v_l20 != a8; fb.v_l20 = fb.v_l20 + 20, fb.v_l24 = fb.v_l24 + 20) {
        fb.v_l16 = fb.v_l24;
        if (fb.v_l16 != 0) {
            *(S5*)fb.v_l16 = *(S5*)fb.v_l20;
            fb.v_l40 = fb.v_l16;
        } else {
            fb.v_l40 = 0;
        }
    }
    fb.v_l8 = fb.v_l24;
    fb.v_l25 = (unsigned char)0;
    fb.v_l36 = a12;
    fb.v_l32 = a4;
    for (; fb.v_l32 != a8; fb.v_l32 = fb.v_l32 + 20, fb.v_l36 = fb.v_l36 + 20) {
    }
    return fb.v_l8;
}
