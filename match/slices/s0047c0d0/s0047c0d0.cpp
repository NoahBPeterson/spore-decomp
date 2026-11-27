// 0x0047c0d0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0047b480/s0047b480.cpp, src/game/SPGonzago/InteractionAgent.cpp.

struct C_0040f360 { int FUN_0040f360(); };
#pragma pack(push, 1)
struct Fr0_0047c0d0 {
    int v_l24;
    int v_l20;
    int dead0[2];
    int v_l8;
};
#pragma pack(pop)

// @ 0x0047c0d0
extern "C" void __cdecl FUN_0047c0d0(int a4, int a8, int a12)
{
    Fr0_0047c0d0 fb;
    fb.v_l24 = a4;
    for (; fb.v_l24 != a8; fb.v_l24 = fb.v_l24 + 4) {
        fb.v_l20 = (int)(int)*(int*)(char*)a12;
        if (fb.v_l20 != (int)*(int*)(char*)fb.v_l24) {
            fb.v_l8 = (int)(int)*(int*)(char*)fb.v_l24;
            if (fb.v_l20 != 0) {
                *(int*)((char*)fb.v_l20 + 64) = (int)(int)((int)*(int*)((char*)fb.v_l20 + 64) + 1);
            }
            *(int*)(char*)fb.v_l24 = fb.v_l20;
            if (fb.v_l8 != 0) {
                ((C_0040f360*)fb.v_l8)->FUN_0040f360();
            }
        }
    }
    return;
}
