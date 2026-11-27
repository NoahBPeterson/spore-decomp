// 0x004ab4d0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004aa760/s004aa760.cpp, src/game/SPBake/SPEditorManipulationUtilities.cpp.

struct C_004aa2f0 { int FUN_004aa2f0(unsigned int); };
#pragma pack(push, 1)
struct Fr0_004ab4d0 {
    int v_l76;
    int v_l72;
    int v_l68;
    int dead0[13];
    int v_l12;
    char dead1;
    char dead2;
    char dead3;
    unsigned char v_l5;
};
#pragma pack(pop)

// @ 0x004ab4d0
extern "C" int __cdecl FUN_004ab4d0(int a4, int a8, int a12)
{
    Fr0_004ab4d0 fb;
    fb.v_l5 = (unsigned char)0;
    fb.v_l72 = a12;
    fb.v_l68 = a4;
    for (; fb.v_l68 != a8; fb.v_l68 = fb.v_l68 + 52, fb.v_l72 = fb.v_l72 + 52) {
        fb.v_l12 = fb.v_l72;
        if (fb.v_l12 != 0) {
            fb.v_l76 = (int)((C_004aa2f0*)fb.v_l12)->FUN_004aa2f0((unsigned int)fb.v_l68);
        } else {
            fb.v_l76 = 0;
        }
    }
    return fb.v_l72;
}
