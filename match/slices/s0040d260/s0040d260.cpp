// 0x0040d260: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0040ccb0/s0040ccb0.cpp.

extern "C" unsigned char g_013ef094[];
struct C_0041f760 { void FUN_0041f760(); };
struct C_0041f8e0 { void FUN_0041f8e0(); };
struct C_004b5440 { void FUN_004b5440(); };
struct C_0050ea50 { void FUN_0050ea50(); };
#pragma pack(push, 1)
struct Fr0_0040d260 {
    int dead0[12];
    int v_l44;
    int dead1[3];
    int v_l28;
    int dead2[5];
};
#pragma pack(pop)


struct D_0040d260 { void FUN_0040d260(); };
// @ 0x0040d260
void D_0040d260::FUN_0040d260()
{
    Fr0_0040d260 fb;
    ((C_004b5440*)((int)this + 68))->FUN_004b5440();
    fb.v_l44 = (int)this + 48;
    fb.v_l28 = (int)(int)*(int*)(char*)fb.v_l44;
    for (; (unsigned int)fb.v_l28 < (unsigned int)*(int*)((char*)fb.v_l44 + 4); fb.v_l28 = fb.v_l28 + 20) {
    }
    ((C_0050ea50*)fb.v_l44)->FUN_0050ea50();
    ((C_0041f8e0*)((int)this + 28))->FUN_0041f8e0();
    ((C_0041f760*)((int)this + 8))->FUN_0041f760();
    *(int*)(char*)(int)this = (int)g_013ef094;
    return;
}
