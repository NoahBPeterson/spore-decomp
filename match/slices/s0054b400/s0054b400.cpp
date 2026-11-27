// 0x0054b400: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0054afe0/s0054afe0.cpp.

struct C_00423820 { void FUN_00423820(unsigned int, unsigned int); };
#pragma pack(push, 1)
struct Fr0_0054b400 {
    int v_l12;
    int v_l8;
};
#pragma pack(pop)

// @ 0x0054b400
extern "C" int __cdecl FUN_0054b400(int a4, int a8, int a12)
{
    Fr0_0054b400 fb;
    for (; a4 != a8; *(int*)&a4 = a4 + 16, *(int*)&a12 = a12 + 16) {
        fb.v_l8 = a12;
        if (fb.v_l8 != 0) {
            *(int*)(char*)fb.v_l8 = 0;
            *(int*)((char*)fb.v_l8 + 4) = 0;
            *(int*)((char*)fb.v_l8 + 8) = 0;
            ((C_00423820*)fb.v_l8)->FUN_00423820((unsigned int)(int)*(int*)(char*)a4, (unsigned int)(int)*(int*)((char*)a4 + 4));
            fb.v_l12 = fb.v_l8;
        } else {
            fb.v_l12 = 0;
        }
    }
    return a12;
}
