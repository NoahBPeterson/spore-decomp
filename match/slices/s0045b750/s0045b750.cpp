// 0x0045b750: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0045aa70/s0045aa70.cpp.

struct C_0045b6f0 { void FUN_0045b6f0(unsigned int); };
#pragma pack(push, 1)
struct Fr0_0045b750 {
    int dead0[2];
    int v_l16;
    int v_l12;
    int v_l8;
};
#pragma pack(pop)


struct D_0045b750 { void FUN_0045b750(int a4, int a8); };
// @ 0x0045b750
void D_0045b750::FUN_0045b750(int a4, int a8)
{
    Fr0_0045b750 fb;
    fb.v_l8 = 0;
    for (; (unsigned int)fb.v_l8 < (unsigned int)a8; fb.v_l8 = fb.v_l8 + 1) {
        fb.v_l12 = (int)(int)*(int*)((char*)a4 + fb.v_l8 * 4);
        while (fb.v_l12 != 0) {
            fb.v_l16 = fb.v_l12;
            fb.v_l12 = (int)(int)*(int*)((char*)fb.v_l12 + 8);
            ((C_0045b6f0*)(int)this)->FUN_0045b6f0((unsigned int)fb.v_l16);
        }
        *(int*)((char*)a4 + fb.v_l8 * 4) = 0;
    }
    return;
}
