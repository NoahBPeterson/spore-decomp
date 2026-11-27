// 0x00548690: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00547e90/s00547e90.cpp.

#pragma pack(push, 1)
struct Fr0_00548690 {
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
struct S4 { int m0; int m1; int m2; int m3; };


struct D_00548690 { int FUN_00548690(int a4, int a8); };
// @ 0x00548690
int D_00548690::FUN_00548690(int a4, int a8)
{
    Fr0_00548690 fb;
    fb.v_l24 = (int)(int)*(int*)((char*)(int)this + 4);
    fb.v_l10 = (unsigned char)0;
    fb.v_l9 = (unsigned char)0;
    fb.v_l11 = (unsigned char)0;
    fb.v_l20 = a4;
    fb.v_l16 = a8;
    for (; fb.v_l16 != fb.v_l24; fb.v_l20 = fb.v_l20 + 16, fb.v_l16 = fb.v_l16 + 16) {
        *(S4*)fb.v_l20 = *(S4*)fb.v_l16;
    }
    fb.v_l8 = fb.v_l20;
    fb.v_l28 = fb.v_l8;
    for (; (unsigned int)fb.v_l28 < (unsigned int)*(int*)((char*)(int)this + 4); fb.v_l28 = fb.v_l28 + 16) {
    }
    *(int*)((char*)(int)this + 4) = (int)(int)((int)*(int*)((char*)(int)this + 4) - (a8 - a4 >> 4 << 4));
    return a4;
}
