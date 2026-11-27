// 0x004c5100: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004c4650/s004c4650.cpp, src/game/SPBake/_at_004c0000.cpp.

struct C_004cd060 { void FUN_004cd060(float, float); };
#pragma pack(push, 1)
struct Fr0_004c5100 {
    int v_l40;
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


struct D_004c5100 { void FUN_004c5100(float a4, float a8); };
// @ 0x004c5100
void D_004c5100::FUN_004c5100(float a4, float a8)
{
    Fr0_004c5100 fb;
    *(float*)((char*)(int)this + 120) = (float)a8;
    *(float*)((char*)(int)this + 124) = (float)a4;
    *(float*)((char*)(int)this + 128) = (float)a8;
    fb.v_l16 = (int)(int)*(int*)((char*)(int)this + 24);
    if (fb.v_l16 != 0) {
        fb.v_l20 = (int)(int)*(int*)((char*)(int)this + 24);
        ((C_004cd060*)fb.v_l20)->FUN_004cd060((float)a8, (float)a8);
    }
    fb.v_l24 = (int)(int)*(int*)((char*)(int)this + 28);
    if (fb.v_l24 != 0) {
        fb.v_l28 = (int)(int)*(int*)((char*)(int)this + 28);
        ((C_004cd060*)fb.v_l28)->FUN_004cd060((float)a4, (float)a8);
    }
    fb.v_l12 = 0;
    fb.v_l32 = (int)this + 72;
    fb.v_l8 = (int)(int)((int)((int)*(int*)((char*)fb.v_l32 + 4) - (int)*(int*)(char*)fb.v_l32) >> 3);
    for (; fb.v_l12 < fb.v_l8; fb.v_l12 = fb.v_l12 + 1) {
        fb.v_l36 = (int)(int)((int)*(int*)((char*)(int)this + 72) + (fb.v_l12 << 3));
        fb.v_l40 = (int)(int)*(int*)((char*)fb.v_l36 + 4);
        ((C_004cd060*)fb.v_l40)->FUN_004cd060((float)a4, (float)a8);
    }
    return;
}
