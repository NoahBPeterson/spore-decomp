// 0x0053a530: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00539d70/s00539d70.cpp, src/game/SPBake/SPSkinPaintParticleDescription.cpp.

extern "C" unsigned char g_01485378[];
extern "C" unsigned char g_01485720[];
#pragma pack(push, 1)
struct Fr0_0053a530 {
    int v_l20;
    int v_l16;
    int v_l12;
    int v_l8;
};
#pragma pack(pop)


struct D_0053a530 { void FUN_0053a530(); };
// @ 0x0053a530
void D_0053a530::FUN_0053a530()
{
    Fr0_0053a530 fb;
    *(int*)((char*)(int)this + 28) = 0;
    *(int*)((char*)(int)this + 24) = -1;
    *(int*)((char*)(int)this + 104) = 0;
    *(unsigned char*)((char*)(int)this + 45) = (unsigned char)0;
    fb.v_l8 = (int)this + 48;
    *(float*)(char*)fb.v_l8 = (float)*(float*)g_01485378;
    *(float*)((char*)fb.v_l8 + 4) = (float)*(float*)g_01485720;
    *(float*)((char*)fb.v_l8 + 8) = (float)*(float*)g_01485378;
    *(unsigned char*)((char*)(int)this + 46) = (unsigned char)0;
    fb.v_l12 = (int)this + 60;
    *(float*)(char*)fb.v_l12 = (float)*(float*)g_01485378;
    *(float*)((char*)fb.v_l12 + 4) = (float)*(float*)g_01485720;
    *(float*)((char*)fb.v_l12 + 8) = (float)*(float*)g_01485378;
    *(unsigned char*)((char*)(int)this + 47) = (unsigned char)0;
    fb.v_l16 = (int)this + 72;
    *(float*)(char*)fb.v_l16 = (float)*(float*)g_01485378;
    *(float*)((char*)fb.v_l16 + 4) = (float)*(float*)g_01485720;
    *(float*)((char*)fb.v_l16 + 8) = (float)*(float*)g_01485378;
    *(float*)((char*)(int)this + 84) = (float)*(float*)g_01485378;
    *(float*)((char*)(int)this + 92) = (float)*(float*)g_01485378;
    *(float*)((char*)(int)this + 88) = (float)*(float*)g_01485378;
    *(float*)((char*)(int)this + 100) = (float)*(float*)g_01485378;
    *(float*)((char*)(int)this + 96) = (float)*(float*)g_01485378;
    fb.v_l20 = (int)this + 32;
    *(float*)(char*)fb.v_l20 = (float)*(float*)g_01485378;
    *(float*)((char*)fb.v_l20 + 4) = (float)*(float*)g_01485378;
    *(float*)((char*)fb.v_l20 + 8) = (float)*(float*)g_01485720;
    *(unsigned char*)((char*)(int)this + 44) = (unsigned char)255;
    *(unsigned char*)((char*)(int)this + 168) = (unsigned char)0;
    *(unsigned char*)((char*)(int)this + 169) = (unsigned char)0;
    *(unsigned char*)((char*)(int)this + 170) = (unsigned char)0;
    return;
}
