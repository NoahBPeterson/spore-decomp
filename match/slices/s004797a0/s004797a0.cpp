// 0x004797a0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00478930/s00478930.cpp, src/game/SPGonzago/InteractionAgent.cpp.

#pragma pack(push, 1)
struct Fr0_004797a0 {
    int v_l24;
    int v_l20;
    int v_l16;
    int v_l12;
    int v_l8;
};
#pragma pack(pop)
__forceinline bool il2c_cc_ne(int a, int b) { return a != b; }

// @ 0x004797a0
extern "C" int __cdecl FUN_004797a0(int a4, int a8, int a12, int a16)
{
    Fr0_004797a0 fb;
    fb.v_l8 = a16;
    for (; (int)(unsigned char)il2c_cc_ne(a8, a12) != 0; *(int*)&a8 = a8 + 12, fb.v_l8 = fb.v_l8 + 12) {
        fb.v_l16 = fb.v_l8;
        fb.v_l12 = fb.v_l16;
        if (fb.v_l12 != 0) {
            fb.v_l20 = a8;
            *(float*)(char*)fb.v_l12 = *(float*)(char*)fb.v_l20;
            *(float*)((char*)fb.v_l12 + 4) = *(float*)((char*)fb.v_l20 + 4);
            *(float*)((char*)fb.v_l12 + 8) = *(float*)((char*)fb.v_l20 + 8);
            fb.v_l24 = fb.v_l12;
        } else {
            fb.v_l24 = 0;
        }
    }
    *(int*)(char*)a4 = fb.v_l8;
    return a4;
}
