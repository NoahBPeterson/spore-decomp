// 0x004e8ee0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004e88a0/s004e88a0.cpp, src/game/SPBake/_at_004e0000.cpp.

struct il2c_vc0 {
    virtual void s0();
};

#pragma pack(push, 1)
struct Fr0_004e8ee0 {
    int v_l24;
    int v_l20;
    int v_l16;
    int v_l12;
    int v_l8;
};
#pragma pack(pop)
__forceinline bool il2c_cc_ne(int a, int b) { return a != b; }

// @ 0x004e8ee0
extern "C" int __cdecl FUN_004e8ee0(int a4, int a8, int a12, int a16)
{
    Fr0_004e8ee0 fb;
    fb.v_l8 = a16;
    for (; (int)(unsigned char)il2c_cc_ne(a8, a12) != 0; *(int*)&a8 = a8 + 4, fb.v_l8 = fb.v_l8 + 4) {
        fb.v_l16 = fb.v_l8;
        fb.v_l12 = fb.v_l16;
        if (fb.v_l12 != 0) {
            fb.v_l20 = a8;
            *(int*)(char*)fb.v_l12 = (int)(int)*(int*)(char*)fb.v_l20;
            if ((int)*(int*)(char*)fb.v_l12 != 0) {
                ((il2c_vc0*)(int)*(int*)(char*)fb.v_l12)->s0();
            }
            fb.v_l24 = fb.v_l12;
        } else {
            fb.v_l24 = 0;
        }
    }
    *(int*)(char*)a4 = fb.v_l8;
    return a4;
}
