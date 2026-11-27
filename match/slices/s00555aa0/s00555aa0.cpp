// 0x00555aa0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00554c30/s00554c30.cpp, match/slices/s00555bc0/s00555bc0.cpp.

struct C_0047d390 { void FUN_0047d390(unsigned int, unsigned int); };
#pragma pack(push, 1)
struct Fr0_00555aa0 {
    int v_l24;
    int v_l20;
    int v_l16;
    int v_l12;
    int v_l8;
};
#pragma pack(pop)
__forceinline bool il2c_cc_ne(int a, int b) { return a != b; }

// @ 0x00555aa0
extern "C" int __cdecl FUN_00555aa0(int a4, int a8, int a12, int a16)
{
    Fr0_00555aa0 fb;
    fb.v_l8 = a16;
    for (; (int)(unsigned char)il2c_cc_ne(a8, a12) != 0; *(int*)&a8 = a8 + 16, fb.v_l8 = fb.v_l8 + 16) {
        fb.v_l16 = fb.v_l8;
        fb.v_l12 = fb.v_l16;
        if (fb.v_l12 != 0) {
            fb.v_l20 = a8;
            *(int*)(char*)fb.v_l12 = 0;
            *(int*)((char*)fb.v_l12 + 4) = 0;
            *(int*)((char*)fb.v_l12 + 8) = 0;
            ((C_0047d390*)fb.v_l12)->FUN_0047d390((unsigned int)(int)*(int*)(char*)fb.v_l20, (unsigned int)(int)*(int*)((char*)fb.v_l20 + 4));
            fb.v_l24 = fb.v_l12;
        } else {
            fb.v_l24 = 0;
        }
    }
    *(int*)(char*)a4 = fb.v_l8;
    return a4;
}
