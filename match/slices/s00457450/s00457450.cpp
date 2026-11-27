// 0x00457450: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00456360/s00456360.cpp.

#pragma pack(push, 1)
struct Fr0_00457450 {
    int v_l20;
    int v_l16;
    int v_l12;
    int v_l8;
};
#pragma pack(pop)
struct S3 { int m0; int m1; int m2; };

// @ 0x00457450
extern "C" void __cdecl FUN_00457450(int a4, int a8, int a12)
{
    Fr0_00457450 fb;
    fb.v_l8 = a4;
    for (; (unsigned int)a8 > (unsigned int)0; *(int*)&a8 = a8 - 1, fb.v_l8 = fb.v_l8 + 12) {
        fb.v_l16 = fb.v_l8;
        fb.v_l12 = fb.v_l16;
        if (fb.v_l12 != 0) {
            *(S3*)fb.v_l12 = *(S3*)a12;
            fb.v_l20 = fb.v_l12;
        } else {
            fb.v_l20 = 0;
        }
    }
    return;
}
