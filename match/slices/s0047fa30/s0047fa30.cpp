// 0x0047fa30: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0047f520/s0047f520.cpp, src/game/SPBake/SPEditorHandleDeform.cpp.

extern "C" unsigned char g_013ef25c[];
extern "C" unsigned char g_013ef270[];
extern "C" unsigned char g_01471064[];
extern "C" unsigned char g_015d4fd8[];
extern "C" unsigned char g_015d4fdc[];
extern "C" unsigned char g_015d4fe0[];
extern "C" unsigned char g_01667bac[];
struct C_00409930 { void FUN_00409930(); };
struct C_0047d6a0 { void FUN_0047d6a0(); };
struct C_004e8f70 { void FUN_004e8f70(); };
#pragma pack(push, 1)
struct Fr0_0047fa30 {
    int v_l28;
    int v_l24;
    int v_l20;
    int v_l16;
    int v_l12;
    int dead0[1];
};
#pragma pack(pop)


struct D_0047fa30 { int FUN_0047fa30(); };
// @ 0x0047fa30
int D_0047fa30::FUN_0047fa30()
{
    Fr0_0047fa30 fb;
    ((C_0047d6a0*)(int)this)->FUN_0047d6a0();
    *(int*)(char*)(int)this = (int)g_013ef270;
    *(int*)((char*)(int)this + 4) = (int)g_013ef25c;
    fb.v_l12 = (int)this + 80;
    ((C_00409930*)(fb.v_l12 + 4))->FUN_00409930();
    *(int*)((char*)(int)this + 172) = -1779400899;
    *(int*)((char*)(int)this + 176) = 0;
    *(int*)((char*)(int)this + 180) = 0;
    *(unsigned char*)((char*)(int)this + 280) = (unsigned char)0;
    fb.v_l16 = (int)this + 284;
    *(int*)(char*)fb.v_l16 = 0;
    *(int*)((char*)fb.v_l16 + 4) = 0;
    *(int*)((char*)fb.v_l16 + 8) = 0;
    *(int*)(char*)fb.v_l16 = (int)g_01667bac;
    *(int*)((char*)fb.v_l16 + 4) = (int)(int)*(int*)(char*)fb.v_l16;
    *(int*)((char*)fb.v_l16 + 8) = (int)(int)((int)*(int*)(char*)fb.v_l16 + 1);
    fb.v_l20 = (int)this + 300;
    *(float*)(char*)fb.v_l20 = (float)*(float*)g_015d4fd8;
    *(float*)((char*)fb.v_l20 + 4) = (float)*(float*)g_015d4fdc;
    *(float*)((char*)fb.v_l20 + 8) = (float)*(float*)g_015d4fe0;
    fb.v_l24 = (int)this + 312;
    *(float*)(char*)fb.v_l24 = (float)*(float*)g_015d4fd8;
    *(float*)((char*)fb.v_l24 + 4) = (float)*(float*)g_015d4fdc;
    *(float*)((char*)fb.v_l24 + 8) = (float)*(float*)g_015d4fe0;
    fb.v_l28 = (int)this + 324;
    *(float*)(char*)fb.v_l28 = (float)*(float*)g_015d4fd8;
    *(float*)((char*)fb.v_l28 + 4) = (float)*(float*)g_015d4fdc;
    *(float*)((char*)fb.v_l28 + 8) = (float)*(float*)g_015d4fe0;
    *(float*)((char*)(int)this + 388) = (float)*(float*)g_01471064;
    ((C_004e8f70*)((int)this + 392))->FUN_004e8f70();
    *(unsigned char*)((char*)(int)this + 469) = (unsigned char)0;
    return (int)this;
}
