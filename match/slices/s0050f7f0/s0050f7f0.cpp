// 0x0050f7f0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0050e850/s0050e850.cpp, src/game/SPGonzago/SPStarManager.cpp.

#pragma pack(push, 1)
struct Fr0_0050f7f0 {
    int v_l32;
    int v_l28;
    int v_l24;
    int v_l20;
    int v_l16;
    int v_l12;
    int v_l8;
};
#pragma pack(pop)
__forceinline bool il2c_cc_ne(int a, int b) { return a != b; }

// @ 0x0050f7f0
extern "C" int __cdecl FUN_0050f7f0(int a4, int a8, int a12, int a16)
{
    Fr0_0050f7f0 fb;
    fb.v_l8 = a16;
    for (; (int)(unsigned char)il2c_cc_ne(a8, a12) != 0; *(int*)&a8 = a8 + 20, fb.v_l8 = fb.v_l8 + 20) {
        fb.v_l16 = fb.v_l8;
        fb.v_l12 = fb.v_l16;
        if (fb.v_l12 != 0) {
            fb.v_l20 = a8;
            *(float*)(char*)fb.v_l12 = *(float*)(char*)fb.v_l20;
            *(float*)((char*)fb.v_l12 + 4) = *(float*)((char*)fb.v_l20 + 4);
            *(float*)((char*)fb.v_l12 + 8) = *(float*)((char*)fb.v_l20 + 8);
            fb.v_l28 = fb.v_l20 + 12;
            fb.v_l24 = fb.v_l12 + 12;
            *(float*)(char*)fb.v_l24 = *(float*)(char*)fb.v_l28;
            *(float*)((char*)fb.v_l24 + 4) = *(float*)((char*)fb.v_l28 + 4);
            fb.v_l32 = fb.v_l12;
        } else {
            fb.v_l32 = 0;
        }
    }
    *(int*)(char*)a4 = fb.v_l8;
    return a4;
}
