// 0x004f8d80: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004f85b0/s004f85b0.cpp.

struct C_004f8e20 { double FUN_004f8e20(unsigned int); };
struct C_004f8f70 { int FUN_004f8f70(unsigned int); };
#pragma pack(push, 1)
struct Fr0_004f8d80 {
    int dead0[7];
    int v_l112;
    int dead1[22];
    int v_l20;
    int v_l16;
    float v_l12;
    int v_l8;
};
struct Fr1_004f8d80 {
    int dead0[1];
};
#pragma pack(pop)


struct D_004f8d80 { void FUN_004f8d80(int a4, int a8); };
// @ 0x004f8d80
void D_004f8d80::FUN_004f8d80(int a4, int a8)
{
    Fr0_004f8d80 fb;
    Fr1_004f8d80 fa;
    fb.v_l12 = (float)-*(float*)((char*)(int)this + 12);
    fb.v_l8 = (int)((C_004f8f70*)(int)this)->FUN_004f8f70((unsigned int)a4);
    if (fb.v_l8 != 0) {
        fb.v_l112 = fb.v_l8;
        fb.v_l16 = (int)(int)*(int*)((char*)fb.v_l112 - 8);
        fb.v_l20 = 0;
        for (; (unsigned int)fb.v_l20 < (unsigned int)fb.v_l16; fb.v_l20 = fb.v_l20 + 1) {
            fb.v_l12 = (float)(double)((double)((C_004f8e20*)((fb.v_l20 << 7) + fb.v_l8))->FUN_004f8e20((unsigned int)a4) + (double)fb.v_l12);
        }
    }
    *(float*)(char*)a8 = (float)fb.v_l12;
    return;
}
