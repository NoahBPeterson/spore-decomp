// 0x00555b40: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00554c30/s00554c30.cpp, match/slices/s00555bc0/s00555bc0.cpp.

struct C_0047d390 { void FUN_0047d390(unsigned int, unsigned int); };
#pragma pack(push, 1)
struct Fr0_00555b40 {
    int v_l20;
    int v_l16;
    int v_l12;
    int v_l8;
};
#pragma pack(pop)

// @ 0x00555b40
extern "C" void __cdecl FUN_00555b40(int a4, int a8, int a12)
{
    Fr0_00555b40 fb;
    fb.v_l8 = a4;
    for (; (unsigned int)a8 > (unsigned int)0; *(int*)&a8 = a8 - 1, fb.v_l8 = fb.v_l8 + 16) {
        fb.v_l16 = fb.v_l8;
        fb.v_l12 = fb.v_l16;
        if (fb.v_l12 != 0) {
            *(int*)(char*)fb.v_l12 = 0;
            *(int*)((char*)fb.v_l12 + 4) = 0;
            *(int*)((char*)fb.v_l12 + 8) = 0;
            ((C_0047d390*)fb.v_l12)->FUN_0047d390((unsigned int)(int)*(int*)(char*)a12, (unsigned int)(int)*(int*)((char*)a12 + 4));
            fb.v_l20 = fb.v_l12;
        } else {
            fb.v_l20 = 0;
        }
    }
    return;
}
