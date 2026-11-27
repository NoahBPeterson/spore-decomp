// 0x00476950: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00475d00/s00475d00.cpp.

extern "C" int __cdecl FUN_0047c1c0(...);
#pragma pack(push, 1)
struct Fr0_00476950 {
    int v_l28;
    int v_l24;
    char dead0;
    char dead1;
    char dead2;
    unsigned char v_l17;
    int dead3[1];
    char dead4;
    char dead5;
    char dead6;
    unsigned char v_l9;
    int v_l8;
};
#pragma pack(pop)

// @ 0x00476950
extern "C" int __cdecl FUN_00476950(int a4, int a8, int a12)
{
    Fr0_00476950 fb;
    fb.v_l9 = (unsigned char)0;
    fb.v_l8 = (int)(int)FUN_0047c1c0((unsigned int)a4, (unsigned int)a8, (unsigned int)a12);
    fb.v_l17 = (unsigned char)0;
    fb.v_l28 = a12;
    fb.v_l24 = a4;
    for (; fb.v_l24 != a8; fb.v_l24 = fb.v_l24 + 16, fb.v_l28 = fb.v_l28 + 16) {
    }
    return fb.v_l8;
}
