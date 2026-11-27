// 0x00455ae0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004553b0/s004553b0.cpp.

#pragma pack(push, 1)
struct Fr0_00455ae0 {
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
struct S5 { int m0; int m1; int m2; int m3; int m4; };


struct D_00455ae0 { int FUN_00455ae0(int a4, int a8); };
// @ 0x00455ae0
int D_00455ae0::FUN_00455ae0(int a4, int a8)
{
    Fr0_00455ae0 fb;
    fb.v_l24 = (int)(int)*(int*)((char*)(int)this + 4);
    fb.v_l10 = (unsigned char)0;
    fb.v_l9 = (unsigned char)0;
    fb.v_l11 = (unsigned char)0;
    fb.v_l20 = a4;
    fb.v_l16 = a8;
    for (; fb.v_l16 != fb.v_l24; fb.v_l20 = fb.v_l20 + 20, fb.v_l16 = fb.v_l16 + 20) {
        *(S5*)fb.v_l20 = *(S5*)fb.v_l16;
    }
    fb.v_l8 = fb.v_l20;
    fb.v_l28 = fb.v_l8;
    for (; (unsigned int)fb.v_l28 < (unsigned int)*(int*)((char*)(int)this + 4); fb.v_l28 = fb.v_l28 + 20) {
    }
    *(int*)((char*)(int)this + 4) = (int)(int)((int)*(int*)((char*)(int)this + 4) - (a8 - a4) / 20 * 20);
    return a4;
}
