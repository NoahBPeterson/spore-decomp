// 0x00570400: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0056fb90/s0056fb90.cpp, src/game/SPEditors/_at_00570000.cpp.

struct C_0050d440 { void FUN_0050d440(unsigned int); };
#pragma pack(push, 1)
struct Fr0_00570400 {
    int v_l100;
    int v_l96;
    int v_l92;
    int v_l88;
    int dead0[18];
    int v_l12;
    char dead1;
    char dead2;
    char dead3;
    unsigned char v_l5;
};
#pragma pack(pop)

// @ 0x00570400
extern "C" int __cdecl FUN_00570400(int a4, int a8, int a12)
{
    Fr0_00570400 fb;
    fb.v_l5 = (unsigned char)0;
    fb.v_l96 = a12;
    fb.v_l92 = a4;
    for (; fb.v_l92 != a8; fb.v_l92 = fb.v_l92 + 28, fb.v_l96 = fb.v_l96 + 28) {
        fb.v_l12 = fb.v_l96;
        if (fb.v_l12 != 0) {
            *(int*)(char*)fb.v_l12 = (int)(int)*(int*)(char*)fb.v_l92;
            fb.v_l88 = fb.v_l12 + 4;
            ((C_0050d440*)fb.v_l88)->FUN_0050d440((unsigned int)(fb.v_l92 + 4));
            fb.v_l100 = fb.v_l12;
        } else {
            fb.v_l100 = 0;
        }
    }
    return fb.v_l96;
}
