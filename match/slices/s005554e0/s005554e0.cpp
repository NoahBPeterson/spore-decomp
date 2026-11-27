// 0x005554e0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00554c30/s00554c30.cpp, match/slices/s00555bc0/s00555bc0.cpp.

struct C_00429410 { void FUN_00429410(unsigned int); };
extern "C" int __cdecl FUN_00555bc0(...);
#pragma pack(push, 1)
struct Fr0_005554e0 {
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

// @ 0x005554e0
extern "C" int __cdecl FUN_005554e0(int a4, int a8, int a12)
{
    Fr0_005554e0 fb;
    fb.v_l9 = (unsigned char)0;
    fb.v_l8 = (int)(int)FUN_00555bc0((unsigned int)a4, (unsigned int)a8, (unsigned int)a12);
    fb.v_l17 = (unsigned char)0;
    fb.v_l40 = a12;
    fb.v_l36 = a4;
    for (; fb.v_l36 != a8; fb.v_l36 = fb.v_l36 + 16, fb.v_l40 = fb.v_l40 + 16) {
        ((C_00429410*)fb.v_l36)->FUN_00429410((unsigned int)0);
    }
    return fb.v_l8;
}
