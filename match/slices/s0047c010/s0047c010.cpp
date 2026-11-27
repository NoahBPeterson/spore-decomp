// 0x0047c010: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0047b480/s0047b480.cpp, src/game/SPGonzago/InteractionAgent.cpp.

#pragma pack(push, 1)
struct Fr0_0047c010 {
    int v_l60;
    int v_l56;
    int v_l52;
    int v_l48;
    int v_l44;
    int v_l40;
    int v_l36;
    int v_l32;
    int v_l28;
    int v_l24;
    int v_l20;
    int v_l16;
    int dead0[1];
    int v_l8;
};
#pragma pack(pop)
__forceinline bool il2c_cc_ne(int a, int b) { return a != b; }

// @ 0x0047c010
extern "C" int __cdecl FUN_0047c010(int a4, int a8, int a12)
{
    Fr0_0047c010 fb;
    fb.v_l16 = a12;
    fb.v_l20 = a8;
    fb.v_l24 = a4;
    fb.v_l56 = fb.v_l16;
    fb.v_l52 = fb.v_l20;
    fb.v_l48 = fb.v_l24;
    fb.v_l28 = fb.v_l56;
    for (; (int)(unsigned char)il2c_cc_ne(fb.v_l48, fb.v_l52) != 0; fb.v_l48 = fb.v_l48 + 4, fb.v_l28 = fb.v_l28 + 4) {
        fb.v_l36 = fb.v_l28;
        fb.v_l32 = fb.v_l36;
        if (fb.v_l32 != 0) {
            fb.v_l40 = fb.v_l48;
            *(int*)(char*)fb.v_l32 = (int)(int)*(int*)(char*)fb.v_l40;
            if ((int)*(int*)(char*)fb.v_l32 != 0) {
                fb.v_l44 = (int)(int)*(int*)(char*)fb.v_l32;
                *(int*)((char*)fb.v_l44 + 64) = (int)(int)((int)*(int*)((char*)fb.v_l44 + 64) + 1);
            }
            fb.v_l60 = fb.v_l32;
        } else {
            fb.v_l60 = 0;
        }
    }
    fb.v_l8 = fb.v_l28;
    return fb.v_l8;
}
