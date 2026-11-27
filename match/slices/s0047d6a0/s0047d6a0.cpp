// 0x0047d6a0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0047d450/s0047d450.cpp.

struct il2c_vc0 {
    virtual void s0();
};

extern "C" unsigned char g_013eb938[];
extern "C" unsigned char g_013ec458[];
extern "C" unsigned char g_013ef0fc[];
extern "C" unsigned char g_013ef110[];
extern "C" unsigned char g_013f1ab0[];
extern "C" unsigned char g_01485378[];
extern "C" unsigned char g_01485720[];
#pragma pack(push, 1)
struct Fr0_0047d6a0 {
    int v_l36;
    int v_l32;
    int v_l28;
    int v_l24;
    int v_l20;
    int v_l16;
    int v_l12;
    int v_l8;
};
#pragma pack(pop)


struct D_0047d6a0 { int FUN_0047d6a0(); };
// @ 0x0047d6a0
int D_0047d6a0::FUN_0047d6a0()
{
    Fr0_0047d6a0 fb;
    *(int*)(char*)(int)this = (int)g_013eb938;
    *(int*)(char*)(int)this = (int)g_013f1ab0;
    fb.v_l8 = (int)this + 4;
    *(int*)(char*)fb.v_l8 = (int)g_013ec458;
    *(int*)((char*)fb.v_l8 + 4) = 0;
    *(int*)(char*)(int)this = (int)g_013ef110;
    *(int*)((char*)(int)this + 4) = (int)g_013ef0fc;
    fb.v_l12 = (int)this + 12;
    *(int*)(char*)fb.v_l12 = 0;
    if ((int)*(int*)(char*)fb.v_l12 != 0) {
        ((il2c_vc0*)(int)*(int*)(char*)fb.v_l12)->s0();
    }
    *(int*)((char*)(int)this + 16) = 0;
    fb.v_l20 = (int)this + 20;
    *(int*)(char*)fb.v_l20 = 0;
    if ((int)*(int*)(char*)fb.v_l20 != 0) {
        fb.v_l16 = (int)(int)*(int*)(char*)fb.v_l20;
        *(int*)((char*)fb.v_l16 + 64) = (int)(int)((int)*(int*)((char*)fb.v_l16 + 64) + 1);
    }
    fb.v_l28 = (int)this + 24;
    *(int*)(char*)fb.v_l28 = 0;
    if ((int)*(int*)(char*)fb.v_l28 != 0) {
        fb.v_l24 = (int)(int)*(int*)(char*)fb.v_l28;
        *(int*)((char*)fb.v_l24 + 64) = (int)(int)((int)*(int*)((char*)fb.v_l24 + 64) + 1);
    }
    *(float*)((char*)(int)this + 32) = (float)*(float*)g_01485378;
    *(float*)((char*)(int)this + 36) = (float)*(float*)g_01485378;
    *(float*)((char*)(int)this + 40) = (float)*(float*)g_01485378;
    *(float*)((char*)(int)this + 44) = (float)*(float*)g_01485378;
    fb.v_l32 = (int)this + 48;
    *(int*)(char*)fb.v_l32 = 0;
    *(int*)((char*)fb.v_l32 + 4) = 0;
    *(int*)((char*)fb.v_l32 + 8) = 0;
    fb.v_l36 = (int)this + 60;
    *(int*)(char*)fb.v_l36 = 0;
    *(int*)((char*)fb.v_l36 + 4) = 0;
    *(int*)((char*)fb.v_l36 + 8) = 0;
    *(unsigned char*)((char*)(int)this + 72) = (unsigned char)0;
    *(float*)((char*)(int)this + 76) = (float)*(float*)g_01485720;
    return (int)this;
}
