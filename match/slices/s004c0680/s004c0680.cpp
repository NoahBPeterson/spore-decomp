// 0x004c0680: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004c0410/s004c0410.cpp.

#include <string.h>
#pragma pack(push, 1)
struct Fr0_004c0680 {
    int v_l28;
    int v_l24;
    int v_l20;
    int v_l16;
    char dead0;
    unsigned char v_l11;
    unsigned char v_l10;
    unsigned char v_l9;
    int v_l8;
};
#pragma pack(pop)
struct S35 { int m0; int m1; int m2; int m3; int m4; int m5; int m6; int m7; int m8; int m9; int m10; int m11; int m12; int m13; int m14; int m15; int m16; int m17; int m18; int m19; int m20; int m21; int m22; int m23; int m24; int m25; int m26; int m27; int m28; int m29; int m30; int m31; int m32; int m33; int m34; };


struct D_004c0680 { int FUN_004c0680(int a4, int a8); };
// @ 0x004c0680
int D_004c0680::FUN_004c0680(int a4, int a8)
{
    Fr0_004c0680 fb;
    fb.v_l24 = (int)(int)*(int*)((char*)(int)this + 4);
    fb.v_l10 = (unsigned char)0;
    fb.v_l9 = (unsigned char)0;
    fb.v_l11 = (unsigned char)0;
    fb.v_l20 = a4;
    fb.v_l16 = a8;
    for (; fb.v_l16 != fb.v_l24; fb.v_l20 = fb.v_l20 + 140, fb.v_l16 = fb.v_l16 + 140) {
        *(S35*)fb.v_l20 = *(S35*)fb.v_l16;
    }
    fb.v_l8 = fb.v_l20;
    fb.v_l28 = fb.v_l8;
    for (; (unsigned int)fb.v_l28 < (unsigned int)*(int*)((char*)(int)this + 4); fb.v_l28 = fb.v_l28 + 140) {
    }
    *(int*)((char*)(int)this + 4) = (int)(int)((int)*(int*)((char*)(int)this + 4) - (a8 - a4) / 140 * 140);
    return a4;
}
