// 0x0045dc00: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0045d2c0/s0045d2c0.cpp.

struct C_0045dca0 { void FUN_0045dca0(unsigned int); };
#pragma pack(push, 1)
struct Fr0_0045dc00 {
    int v_l132;
    int v_l128;
    int v_l124;
    int v_l120;
    int dead0[19];
    int v_l40;
    int v_l36;
    int v_l32;
    int v_l28;
    int v_l24;
    int v_l20;
    int v_l16;
    int dead1[1];
    int v_l8;
};
#pragma pack(pop)
__forceinline bool il2c_cc_ne(int a, int b) { return a != b; }

// @ 0x0045dc00
extern "C" int __cdecl FUN_0045dc00(int a4, int a8, int a12)
{
    Fr0_0045dc00 fb;
    fb.v_l16 = a12;
    fb.v_l20 = a8;
    fb.v_l24 = a4;
    fb.v_l128 = fb.v_l16;
    fb.v_l124 = fb.v_l20;
    fb.v_l120 = fb.v_l24;
    fb.v_l28 = fb.v_l128;
    for (; (int)(unsigned char)il2c_cc_ne(fb.v_l120, fb.v_l124) != 0; fb.v_l120 = fb.v_l120 + 64, fb.v_l28 = fb.v_l28 + 64) {
        fb.v_l36 = fb.v_l28;
        fb.v_l32 = fb.v_l36;
        if (fb.v_l32 != 0) {
            fb.v_l40 = fb.v_l120;
            ((C_0045dca0*)fb.v_l32)->FUN_0045dca0((unsigned int)fb.v_l40);
            fb.v_l132 = fb.v_l32;
        } else {
            fb.v_l132 = 0;
        }
    }
    fb.v_l8 = fb.v_l28;
    return fb.v_l8;
}
