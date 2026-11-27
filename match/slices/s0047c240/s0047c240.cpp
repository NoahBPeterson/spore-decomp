// 0x0047c240: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0047b480/s0047b480.cpp, src/game/SPGonzago/InteractionAgent.cpp.

struct C_00401b80 { void FUN_00401b80(unsigned int); };
extern "C" void __cdecl FUN_0047d3f0(...);
#pragma pack(push, 1)
struct Fr0_0047c240 {
    int v_l40;
    int dead0[1];
    char dead1;
    char dead2;
    char dead3;
    unsigned char v_l29;
    int v_l28;
    int v_l24;
    int dead4[1];
    int v_l16;
    char dead5;
    char dead6;
    char dead7;
    unsigned char v_l9;
    int v_l8;
};
#pragma pack(pop)

// @ 0x0047c240
extern "C" int __cdecl FUN_0047c240(int a4, int a8, int a12)
{
    Fr0_0047c240 fb;
    fb.v_l9 = (unsigned char)0;
    fb.v_l28 = a12;
    fb.v_l24 = a4;
    for (; fb.v_l24 != a8; fb.v_l24 = fb.v_l24 + 16, fb.v_l28 = fb.v_l28 + 16) {
        fb.v_l16 = fb.v_l28;
        if (fb.v_l16 != 0) {
            ((C_00401b80*)fb.v_l16)->FUN_00401b80((unsigned int)fb.v_l24);
            fb.v_l40 = fb.v_l16;
        } else {
            fb.v_l40 = 0;
        }
    }
    fb.v_l8 = fb.v_l28;
    fb.v_l29 = (unsigned char)0;
    FUN_0047d3f0((unsigned int)a4, (unsigned int)a8, (unsigned int)a12);
    return fb.v_l8;
}
