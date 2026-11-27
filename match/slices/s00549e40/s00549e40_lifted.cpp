// 0x00549e40: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00549e40/s00549e40.cpp.

struct C_004237d0 { void FUN_004237d0(); };
extern "C" int __cdecl FUN_0054b400(...);
extern "C" void __cdecl FUN_00f47380(...);
#pragma pack(push, 1)
struct Fr0_00549e40 {
    int v_l40;
    int v_l36;
    int dead0[3];
    char dead1;
    char dead2;
    char dead3;
    unsigned char v_l17;
    int dead4[1];
    char dead5;
    char dead6;
    char dead7;
    unsigned char v_l9;
    int v_l8;
};
#pragma pack(pop)
__forceinline void il2c_d_FUN_00f47380(int p, int fl) { if (fl & 1) FUN_00f47380((unsigned int)(p)); }

// @ 0x00549e40
extern "C" int __cdecl FUN_00549e40(int a4, int a8, int a12)
{
    Fr0_00549e40 fb;
    fb.v_l9 = (unsigned char)0;
    fb.v_l8 = (int)(int)FUN_0054b400((unsigned int)a4, (unsigned int)a8, (unsigned int)a12);
    fb.v_l17 = (unsigned char)0;
    fb.v_l40 = a12;
    fb.v_l36 = a4;
    for (; fb.v_l36 != a8; fb.v_l36 = fb.v_l36 + 16, fb.v_l40 = fb.v_l40 + 16) {
        ((C_004237d0*)fb.v_l36)->FUN_004237d0();
        il2c_d_FUN_00f47380(fb.v_l36, 0);
    }
    return fb.v_l8;
}
