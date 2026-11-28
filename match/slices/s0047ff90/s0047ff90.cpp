// 0x0047ff90: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/SPEditorHandleDeform.cpp, match/slices/s0047f520/s0047f520.cpp.

extern "C" double __cdecl FUN_00455cc0(...);
template<class T> __forceinline T il2c_k(T v) { return v; }

// @ 0x0047ff90
// @ 0x0047ff90
extern "C" int __cdecl FUN_0047ff90(int a4, int a8, int a12)
{
    float v_l24;
    float v_l20_q;
    float v_l16_i;
    float v_l12_40;
    float v_l8;
    float v_l28;
    v_l28 = (float)(double)FUN_00455cc0((unsigned int)a12, (unsigned int)(il2c_k(0) * 12 + a8));
    v_l24 = (float)(double)FUN_00455cc0((unsigned int)a12, (unsigned int)(il2c_k(1) * 12 + a8));
    v_l20_q = (float)(double)FUN_00455cc0((unsigned int)a12, (unsigned int)(il2c_k(2) * 12 + a8));
    v_l16_i = (float)v_l28;
    v_l12_40 = (float)v_l24;
    v_l8 = (float)v_l20_q;
    *(float*)(char*)a4 = (float)v_l16_i;
    *(float*)((char*)a4 + 4) = (float)v_l12_40;
    *(float*)((char*)a4 + 8) = (float)v_l8;
    return a4;
}
