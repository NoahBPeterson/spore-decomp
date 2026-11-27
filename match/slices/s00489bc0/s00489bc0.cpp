// 0x00489bc0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00489530/s00489530.cpp, src/game/SPBake/_at_00480000.cpp.

extern "C" double __cdecl FUN_0040ae50(...);
extern "C" int __cdecl FUN_0041db10(...);
struct C_0048c610 { void FUN_0048c610(unsigned int); };
#pragma pack(push, 1)
struct Fr0_00489bc0 {
    int dead0[1];
    int v_l60;
    int v_l56;
    int v_l52[3];
    float v_l40;
    float v_l36;
    float v_l32;
    int v_l28[3];
    float v_l16;
    float v_l12;
    float v_l8;
};
#pragma pack(pop)


struct D_00489bc0 { void FUN_00489bc0(); };
// @ 0x00489bc0
void D_00489bc0::FUN_00489bc0()
{
    Fr0_00489bc0 fb;
    ((C_0048c610*)(int)this)->FUN_0048c610((unsigned int)(int)&fb.v_l28);
    fb.v_l56 = (int)(int)((int)*(int*)((char*)(int)this + 20) + 72);
    fb.v_l16 = *(float*)(char*)fb.v_l56;
    fb.v_l12 = *(float*)((char*)fb.v_l56 + 4);
    fb.v_l8 = *(float*)((char*)fb.v_l56 + 8);
    fb.v_l60 = (int)(int)FUN_0041db10((unsigned int)(int)&fb.v_l52, (unsigned int)(int)&fb.v_l28, (unsigned int)(int)(int)&fb.v_l16);
    fb.v_l40 = *(float*)(char*)fb.v_l60;
    fb.v_l36 = *(float*)((char*)fb.v_l60 + 4);
    fb.v_l32 = *(float*)((char*)fb.v_l60 + 8);
    *(float*)((char*)(int)this + 36) = (float)(double)FUN_0040ae50((unsigned int)(int)(int)&fb.v_l40);
    return;
}
