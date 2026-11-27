// 0x00440f60: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00440110/s00440110.cpp, src/game/SPBake/SPEditorBlock.cpp.

extern "C" unsigned char g_015d241c[];
extern "C" unsigned char g_015d2420[];
extern "C" unsigned char g_015d2424[];
#pragma pack(push, 1)
struct Fr0_00440f60 {
    int v_l12;
    int v_l8;
};
#pragma pack(pop)


struct D_00440f60 { int FUN_00440f60(); };
// @ 0x00440f60
int D_00440f60::FUN_00440f60()
{
    Fr0_00440f60 fb;
    *(int*)(char*)(int)this = 0;
    fb.v_l8 = (int)this + 4;
    *(float*)(char*)fb.v_l8 = (float)*(float*)g_015d241c;
    *(float*)((char*)fb.v_l8 + 4) = (float)*(float*)g_015d2420;
    *(float*)((char*)fb.v_l8 + 8) = (float)*(float*)g_015d2424;
    fb.v_l12 = (int)this + 16;
    *(float*)(char*)fb.v_l12 = (float)*(float*)g_015d241c;
    *(float*)((char*)fb.v_l12 + 4) = (float)*(float*)g_015d2420;
    *(float*)((char*)fb.v_l12 + 8) = (float)*(float*)g_015d2424;
    return (int)this;
}
