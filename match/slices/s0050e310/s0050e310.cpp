// 0x0050e310: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0050d750/s0050d750.cpp.

extern "C" unsigned char g_01485378[];
struct C_0041cfe0 { void FUN_0041cfe0(); };
struct C_004c0b80 { int FUN_004c0b80(); };
struct C_0050eca0 { int FUN_0050eca0(unsigned int, unsigned int); };
struct C_0050fc30 { void FUN_0050fc30(unsigned int, unsigned int, unsigned int); };
#pragma pack(push, 1)
struct Fr0_0050e310 {
    int dead0[17];
    int v_l128;
    int v_l124;
    int v_l120;
    int dead1[3];
    int v_l104;
    int v_l100;
    int dead2[20];
    float v_l16;
    float v_l12;
    float v_l8;
};
#pragma pack(pop)


struct D_0050e310 { void FUN_0050e310(int a4); };
// @ 0x0050e310
void D_0050e310::FUN_0050e310(int a4)
{
    Fr0_0050e310 fb;
    if ((unsigned int)a4 > (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 100)) {
        ((C_0041cfe0*)(int)&fb.v_l104)->FUN_0041cfe0();
        fb.v_l16 = (float)*(float*)g_01485378;
        fb.v_l12 = (float)*(float*)g_01485378;
        fb.v_l8 = (float)*(float*)g_01485378;
        fb.v_l124 = (int)(int)(a4 - (int)((int)(int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 100));
        fb.v_l120 = (int)(int)*(int*)((char*)(int)this + 4);
        ((C_0050fc30*)(int)this)->FUN_0050fc30((unsigned int)fb.v_l120, (unsigned int)fb.v_l124, (unsigned int)(int)&fb.v_l104);
        fb.v_l128 = fb.v_l104;
        for (; (unsigned int)fb.v_l128 < (unsigned int)fb.v_l100; fb.v_l128 = fb.v_l128 + 4) {
        }
        ((C_004c0b80*)(int)&fb.v_l104)->FUN_004c0b80();
    } else {
        ((C_0050eca0*)(int)this)->FUN_0050eca0((unsigned int)(int)(a4 * 100 + (int)*(int*)(char*)(int)this), (unsigned int)(int)*(int*)((char*)(int)this + 4));
    }
    return;
}
