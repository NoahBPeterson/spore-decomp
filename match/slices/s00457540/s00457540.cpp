// 0x00457540: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00456360/s00456360.cpp.

struct C_00440ff0 { void FUN_00440ff0(unsigned int); };
#pragma pack(push, 1)
struct Fr0_00457540 {
    int v_l40;
    int v_l36;
    int v_l32;
    int dead0[4];
    int v_l12;
    char dead1;
    char dead2;
    char dead3;
    unsigned char v_l5;
};
#pragma pack(pop)

// @ 0x00457540
extern "C" int __cdecl FUN_00457540(int a4, int a8, int a12)
{
    Fr0_00457540 fb;
    fb.v_l5 = (unsigned char)0;
    fb.v_l36 = a12;
    fb.v_l32 = a4;
    for (; fb.v_l32 != a8; fb.v_l32 = fb.v_l32 + 32, fb.v_l36 = fb.v_l36 + 32) {
        fb.v_l12 = fb.v_l36;
        if (fb.v_l12 != 0) {
            *(int*)(char*)fb.v_l12 = (int)(int)*(int*)(char*)fb.v_l32;
            ((C_00440ff0*)(fb.v_l12 + 4))->FUN_00440ff0((unsigned int)(fb.v_l32 + 4));
            fb.v_l40 = fb.v_l12;
        } else {
            fb.v_l40 = 0;
        }
    }
    return fb.v_l36;
}
