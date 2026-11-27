// 0x005031d0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00502ee0/s00502ee0.cpp.

struct C_00503250 { int FUN_00503250(unsigned int); };
extern "C" void __cdecl FUN_00503be0(...);
#pragma pack(push, 1)
struct Fr0_005031d0 {
    int dead0[5];
    char dead1;
    char dead2;
    char dead3;
    unsigned char v_l45;
    int v_l44;
    int v_l40;
    int dead4[5];
    int v_l16;
    char dead5;
    char dead6;
    char dead7;
    unsigned char v_l9;
    int v_l8;
};
struct Fr1_005031d0 {
    int v_l72;
};
#pragma pack(pop)

// @ 0x005031d0
extern "C" int __cdecl FUN_005031d0(int a4, int a8, int a12)
{
    Fr0_005031d0 fb;
    Fr1_005031d0 fa;
    fb.v_l9 = (unsigned char)0;
    fb.v_l44 = a12;
    fb.v_l40 = a4;
    for (; fb.v_l40 != a8; fb.v_l40 = fb.v_l40 + 72, fb.v_l44 = fb.v_l44 + 72) {
        fb.v_l16 = fb.v_l44;
        if (fb.v_l16 != 0) {
            fa.v_l72 = (int)((C_00503250*)fb.v_l16)->FUN_00503250((unsigned int)fb.v_l40);
        } else {
            fa.v_l72 = 0;
        }
    }
    fb.v_l8 = fb.v_l44;
    fb.v_l45 = (unsigned char)0;
    FUN_00503be0((unsigned int)a4, (unsigned int)a8, (unsigned int)a12);
    return fb.v_l8;
}
