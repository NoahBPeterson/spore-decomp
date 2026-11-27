// 0x0047c140: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0047b480/s0047b480.cpp, src/game/SPGonzago/InteractionAgent.cpp.

struct C_0047bbf0 { int FUN_0047bbf0(unsigned int); };
extern "C" void __cdecl FUN_0047c980(...);
#pragma pack(push, 1)
struct Fr0_0047c140 {
    int v_l60;
    int dead0[6];
    int v_l32;
    int v_l28;
    int dead1[2];
    int v_l16;
    char dead2;
    char dead3;
    char dead4;
    unsigned char v_l9;
    int v_l8;
};
#pragma pack(pop)

// @ 0x0047c140
extern "C" int __cdecl FUN_0047c140(int a4, int a8, int a12)
{
    Fr0_0047c140 fb;
    fb.v_l9 = (unsigned char)0;
    fb.v_l32 = a12;
    fb.v_l28 = a4;
    for (; fb.v_l28 != a8; fb.v_l28 = fb.v_l28 + 668, fb.v_l32 = fb.v_l32 + 668) {
        fb.v_l16 = fb.v_l32;
        if (fb.v_l16 != 0) {
            fb.v_l60 = (int)((C_0047bbf0*)fb.v_l16)->FUN_0047bbf0((unsigned int)fb.v_l28);
        } else {
            fb.v_l60 = 0;
        }
    }
    fb.v_l8 = fb.v_l32;
    FUN_0047c980((unsigned int)a4, (unsigned int)a8, (unsigned int)a12);
    return fb.v_l8;
}
