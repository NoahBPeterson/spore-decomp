// 0x0047c1c0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0047b480/s0047b480.cpp, src/game/SPGonzago/InteractionAgent.cpp.

#pragma pack(push, 1)
struct Fr0_0047c1c0 {
    int v_l12;
    int v_l8;
};
#pragma pack(pop)

// @ 0x0047c1c0
extern "C" int __cdecl FUN_0047c1c0(int a4, int a8, int a12)
{
    Fr0_0047c1c0 fb;
    for (; a4 != a8; *(int*)&a4 = a4 + 16, *(int*)&a12 = a12 + 16) {
        fb.v_l8 = a12;
        if (fb.v_l8 != 0) {
            *(float*)(char*)fb.v_l8 = *(float*)(char*)a4;
            *(float*)((char*)fb.v_l8 + 4) = *(float*)((char*)a4 + 4);
            *(float*)((char*)fb.v_l8 + 8) = *(float*)((char*)a4 + 8);
            *(float*)((char*)fb.v_l8 + 12) = *(float*)((char*)a4 + 12);
            fb.v_l12 = fb.v_l8;
        } else {
            fb.v_l12 = 0;
        }
    }
    return a12;
}
