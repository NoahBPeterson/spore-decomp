// 0x0054b630: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0054afe0/s0054afe0.cpp.

struct C_00454cb0 { void FUN_00454cb0(unsigned int, unsigned int); };
#pragma pack(push, 1)
struct Fr0_0054b630 {
    int v_l24;
    int v_l20;
    int v_l16;
    int v_l12;
    char dead0;
    char dead1;
    char dead2;
    unsigned char v_l5;
};
#pragma pack(pop)

// @ 0x0054b630
extern "C" int __cdecl FUN_0054b630(int a4, int a8, int a12)
{
    Fr0_0054b630 fb;
    fb.v_l5 = (unsigned char)0;
    fb.v_l24 = a12;
    fb.v_l20 = a8;
    while (fb.v_l20 != a4) {
        fb.v_l20 = fb.v_l20 - 20;
        fb.v_l24 = fb.v_l24 - 20;
        *(int*)(char*)fb.v_l24 = (int)(int)*(int*)(char*)fb.v_l20;
        fb.v_l16 = fb.v_l20 + 4;
        fb.v_l12 = fb.v_l24 + 4;
        if (fb.v_l16 != fb.v_l12) {
            ((C_00454cb0*)fb.v_l12)->FUN_00454cb0((unsigned int)(int)*(int*)(char*)fb.v_l16, (unsigned int)(int)*(int*)((char*)fb.v_l16 + 4));
        }
    }
    return fb.v_l24;
}
