// 0x004fe2a0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004fd9a0/s004fd9a0.cpp.

extern "C" unsigned char g_013eb8a0[];
extern "C" unsigned char g_013ec480[];
extern "C" unsigned char g_013ec4d4[];
extern "C" unsigned char g_013f1290[];
extern "C" unsigned char g_01485378[];
extern "C" unsigned char g_01485720[];
#pragma pack(push, 1)
struct Fr0_004fe2a0 {
    int v_l16;
    int v_l12;
    int v_l8;
};
#pragma pack(pop)


struct D_004fe2a0 { int FUN_004fe2a0(int a4); };
// @ 0x004fe2a0
int D_004fe2a0::FUN_004fe2a0(int a4)
{
    Fr0_004fe2a0 fb;
    *(int*)(char*)(int)this = 0;
    *(unsigned char*)((char*)(int)this + 4) = (unsigned char)0;
    *(int*)((char*)(int)this + 8) = 0;
    *(int*)((char*)(int)this + 12) = a4;
    *(float*)((char*)(int)this + 16) = (float)*(float*)g_01485720;
    fb.v_l8 = (int)this + 20;
    *(float*)(char*)fb.v_l8 = (float)*(float*)g_01485378;
    *(float*)((char*)fb.v_l8 + 4) = (float)*(float*)g_01485378;
    *(int*)((char*)(int)this + 28) = 0;
    *(float*)((char*)(int)this + 32) = (float)*(float*)g_013ec480;
    *(float*)((char*)(int)this + 36) = (float)*(float*)g_01485378;
    *(float*)((char*)(int)this + 40) = (float)*(float*)g_013eb8a0;
    *(double*)((char*)(int)this + 48) = (double)(float)0;
    *(int*)((char*)(int)this + 56) = 0;
    *(float*)((char*)(int)this + 60) = (float)*(float*)g_01485378;
    *(float*)((char*)(int)this + 64) = (float)*(float*)g_01485720;
    *(int*)((char*)(int)this + 68) = 0;
    *(float*)((char*)(int)this + 72) = (float)*(float*)g_013ec4d4;
    *(float*)((char*)(int)this + 76) = (float)*(float*)g_01485378;
    *(float*)((char*)(int)this + 80) = (float)*(float*)g_013f1290;
    *(unsigned char*)((char*)(int)this + 84) = (unsigned char)0;
    *(float*)((char*)(int)this + 88) = (float)*(float*)g_01485378;
    *(float*)((char*)(int)this + 92) = (float)*(float*)g_01485720;
    fb.v_l12 = (int)this + 96;
    *(float*)(char*)fb.v_l12 = (float)*(float*)g_01485720;
    *(float*)((char*)fb.v_l12 + 4) = (float)*(float*)g_01485720;
    *(float*)((char*)fb.v_l12 + 8) = (float)*(float*)g_01485720;
    *(float*)((char*)(int)this + 108) = (float)*(float*)g_01485720;
    *(float*)((char*)(int)this + 112) = (float)*(float*)g_01485720;
    *(float*)((char*)(int)this + 116) = (float)*(float*)g_01485720;
    *(float*)((char*)(int)this + 120) = (float)*(float*)g_01485720;
    *(float*)((char*)(int)this + 124) = (float)*(float*)g_01485720;
    *(float*)((char*)(int)this + 128) = (float)*(float*)g_01485720;
    *(float*)((char*)(int)this + 132) = (float)*(float*)g_01485720;
    *(unsigned char*)((char*)(int)this + 137) = (unsigned char)0;
    fb.v_l16 = (int)this + 140;
    *(float*)(char*)fb.v_l16 = (float)*(float*)g_01485378;
    *(float*)((char*)fb.v_l16 + 4) = (float)*(float*)g_01485378;
    *(float*)((char*)fb.v_l16 + 8) = (float)*(float*)g_01485378;
    *(float*)((char*)(int)this + 152) = (float)*(float*)g_01485720;
    *(int*)((char*)(int)this + 156) = 0;
    *(int*)((char*)(int)this + 160) = 0;
    *(int*)((char*)(int)this + 164) = 0;
    return (int)this;
}
