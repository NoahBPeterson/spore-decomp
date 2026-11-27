// 0x004f89a0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004f85b0/s004f85b0.cpp.

extern "C" unsigned char g_016c8b44[];
struct C_004769b0 { void FUN_004769b0(unsigned int, unsigned int); };
struct C_009276c0 { void FUN_009276c0(unsigned int); };
#pragma pack(push, 1)
struct Fr0_004f89a0 {
    int v_l36;
    int dead0[4];
    int v_l16;
    int v_l12;
    int v_l8;
};
#pragma pack(pop)


struct D_004f89a0 { void FUN_004f89a0(); };
// @ 0x004f89a0
void D_004f89a0::FUN_004f89a0()
{
    Fr0_004f89a0 fb;
    fb.v_l12 = 0;
    fb.v_l16 = (int)this + 88;
    fb.v_l8 = (int)(int)((int)((int)*(int*)((char*)fb.v_l16 + 4) - (int)*(int*)(char*)fb.v_l16) >> 2);
    for (; fb.v_l12 < fb.v_l8; fb.v_l12 = fb.v_l12 + 1) {
        ((C_009276c0*)*(int*)g_016c8b44)->FUN_009276c0((unsigned int)(int)*(int*)((char*)(int)*(int*)((char*)(int)this + 88) + fb.v_l12 * 4));
    }
    fb.v_l36 = (int)this + 88;
    ((C_004769b0*)fb.v_l36)->FUN_004769b0((unsigned int)(int)*(int*)(char*)fb.v_l36, (unsigned int)(int)*(int*)((char*)fb.v_l36 + 4));
    *(int*)((char*)(int)this + 240) = 0;
    *(int*)((char*)(int)this + 244) = 0;
    return;
}
