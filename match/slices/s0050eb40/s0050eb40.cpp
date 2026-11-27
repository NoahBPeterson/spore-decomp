// 0x0050eb40: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0050e850/s0050e850.cpp.

#pragma pack(push, 1)
struct Fr0_0050eb40 {
    int v_l52;
    int v_l48;
    int v_l44;
    int v_l40;
    int v_l36;
    int v_l32;
    int v_l28;
    int v_l24;
    int v_l20;
    int v_l16;
    int dead0[1];
    int v_l8;
};
#pragma pack(pop)
struct S3 { int m0; int m1; int m2; };
__forceinline bool il2c_cc_ne(int a, int b) { return a != b; }

// @ 0x0050eb40
extern "C" int __cdecl FUN_0050eb40(int a4, int a8, int a12)
{
    Fr0_0050eb40 fb;
    fb.v_l16 = a12;
    fb.v_l20 = a8;
    fb.v_l24 = a4;
    fb.v_l48 = fb.v_l16;
    fb.v_l44 = fb.v_l20;
    fb.v_l40 = fb.v_l24;
    fb.v_l28 = fb.v_l48;
    for (; (int)(unsigned char)il2c_cc_ne(fb.v_l40, fb.v_l44) != 0; fb.v_l40 = fb.v_l40 + 12, fb.v_l28 = fb.v_l28 + 12) {
        fb.v_l36 = fb.v_l28;
        fb.v_l32 = fb.v_l36;
        if (fb.v_l32 != 0) {
            *(S3*)fb.v_l32 = *(S3*)fb.v_l40;
            fb.v_l52 = fb.v_l32;
        } else {
            fb.v_l52 = 0;
        }
    }
    fb.v_l8 = fb.v_l28;
    return fb.v_l8;
}
