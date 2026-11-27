// 0x004e8f70: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004e88a0/s004e88a0.cpp, src/game/SPBake/_at_004e0000.cpp.

struct il2c_vc0 {
    virtual void s0();
};

extern "C" unsigned char g_015da458[];
extern "C" unsigned char g_015da588[];
extern "C" unsigned char g_015da58c[];
extern "C" unsigned char g_015da590[];
struct C_0041cb40 { void FUN_0041cb40(unsigned int); };
#pragma pack(push, 1)
struct Fr0_004e8f70 {
    int v_l64;
    int dead0[11];
    int v_l16;
    int v_l12;
    int v_l8;
};
#pragma pack(pop)


struct D_004e8f70 { int FUN_004e8f70(); };
// @ 0x004e8f70
int D_004e8f70::FUN_004e8f70()
{
    Fr0_004e8f70 fb;
    *(int*)(char*)(int)this = 0;
    fb.v_l8 = (int)this + 4;
    *(int*)(char*)fb.v_l8 = 0;
    if ((int)*(int*)(char*)fb.v_l8 != 0) {
        ((il2c_vc0*)(int)*(int*)(char*)fb.v_l8)->s0();
    }
    fb.v_l12 = (int)this + 8;
    *(float*)(char*)fb.v_l12 = (float)*(float*)g_015da588;
    *(float*)((char*)fb.v_l12 + 4) = (float)*(float*)g_015da58c;
    *(float*)((char*)fb.v_l12 + 8) = (float)*(float*)g_015da590;
    fb.v_l16 = (int)this + 20;
    *(float*)(char*)fb.v_l16 = (float)*(float*)g_015da588;
    *(float*)((char*)fb.v_l16 + 4) = (float)*(float*)g_015da58c;
    *(float*)((char*)fb.v_l16 + 8) = (float)*(float*)g_015da590;
    fb.v_l64 = (int)this + 32;
    ((C_0041cb40*)fb.v_l64)->FUN_0041cb40((unsigned int)(int)g_015da458);
    *(int*)((char*)(int)this + 68) = -1;
    *(unsigned char*)((char*)(int)this + 72) = (unsigned char)0;
    return (int)this;
}
