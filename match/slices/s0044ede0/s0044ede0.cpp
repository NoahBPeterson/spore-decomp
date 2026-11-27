// 0x0044ede0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0044e460/s0044e460.cpp, src/game/SPBake/SPEditorBlock.cpp.

struct C_00435a10 { void FUN_00435a10(unsigned int, unsigned int); };
struct C_00435c80 { int FUN_00435c80(); };
struct C_0044ede0 { void FUN_0044ede0(); };
#pragma pack(push, 1)
struct Fr0_0044ede0 {
    int v_l40;
    int v_l36;
    int v_l32;
    int v_l28;
    int v_l24;
    int v_l20;
    int v_l16;
    int v_l12;
    char dead0;
    char dead1;
    char dead2;
    unsigned char v_l5;
};
#pragma pack(pop)


struct D_0044ede0 { void FUN_0044ede0(); };
// @ 0x0044ede0
void D_0044ede0::FUN_0044ede0()
{
    Fr0_0044ede0 fb;
    fb.v_l5 = (unsigned char)0;
    fb.v_l20 = (int)(int)*(int*)((char*)(int)this + 828);
    if (fb.v_l20 != 0) {
        fb.v_l24 = (int)(int)*(int*)((char*)(int)this + 992);
        if (fb.v_l24 != 0) {
            fb.v_l28 = (int)(int)*(int*)((char*)(int)this + 828);
            if ((int)(unsigned char)((C_00435c80*)fb.v_l28)->FUN_00435c80() != 0) {
                fb.v_l5 = (unsigned char)1;
            }
        }
    }
    ((C_00435a10*)(int)this)->FUN_00435a10((unsigned int)58, (unsigned int)(int)fb.v_l5);
    fb.v_l16 = 0;
    fb.v_l32 = (int)this + 832;
    fb.v_l12 = (int)(int)((int)((int)*(int*)((char*)fb.v_l32 + 4) - (int)*(int*)(char*)fb.v_l32) >> 2);
    for (; fb.v_l16 < fb.v_l12; fb.v_l16 = fb.v_l16 + 1) {
        fb.v_l36 = (int)(int)((int)*(int*)((char*)(int)this + 832) + (fb.v_l16 << 2));
        fb.v_l40 = (int)(int)*(int*)(char*)fb.v_l36;
        ((C_0044ede0*)fb.v_l40)->FUN_0044ede0();
    }
    return;
}
