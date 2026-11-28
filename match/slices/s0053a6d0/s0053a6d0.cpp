// 0x0053a6d0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/SPSkinPaintParticleDescription.cpp, match/slices/s0053acc0/s0053acc0.cpp, match/slices/s00534cf0/s00534cf0.cpp, match/slices/s00539d70/s00539d70.cpp.

struct C_004afc80 { void FUN_004afc80(unsigned int); };
struct C_0053b520 { void FUN_0053b520(unsigned int); };
struct C_0053b8a0 { void FUN_0053b8a0(unsigned int); };
extern "C" void __cdecl FUN_0093a6c0(...);
extern "C" void __cdecl FUN_0093a700(...);
extern "C" void __cdecl FUN_0093a780(...);
template<class T> __forceinline T il2c_k(T v) { return v; }

// @ 0x0053a6d0
extern "C" int __cdecl FUN_0053a6d0(int a4, int a8)
{
    int v_l28_g;
    int v_l24;
    int v_l20_q;
    int v_l16_i;
    int v_l12_40;
    int v_l8;
    int dead_0[15];
    int v_l112;
    int dead_1[5];
    FUN_0093a780((unsigned int)a4, (unsigned int)(int)&v_l8, (unsigned int)1, (unsigned int)0);
    ((C_0053b520*)a8)->FUN_0053b520((unsigned int)v_l8);
    v_l12_40 = 0;
    for (; (unsigned int)v_l12_40 < (unsigned int)v_l8; v_l12_40 = v_l12_40 + 1) {
        v_l16_i = (int)(int)((v_l12_40 << 4) + (int)*(int*)(char*)a8);
        FUN_0093a780((unsigned int)a4, (unsigned int)((il2c_k(0) << 2) + v_l16_i), (unsigned int)1, (unsigned int)0);
        FUN_0093a780((unsigned int)a4, (unsigned int)((il2c_k(1) << 2) + v_l16_i), (unsigned int)1, (unsigned int)0);
        FUN_0093a780((unsigned int)a4, (unsigned int)((il2c_k(2) << 2) + v_l16_i), (unsigned int)1, (unsigned int)0);
        FUN_0093a6c0((unsigned int)a4, (unsigned int)(v_l16_i + 12), (unsigned int)1);
        FUN_0093a6c0((unsigned int)a4, (unsigned int)(v_l16_i + 13), (unsigned int)1);
        FUN_0093a700((unsigned int)a4, (unsigned int)(v_l16_i + 14), (unsigned int)1, (unsigned int)0);
    }
    FUN_0093a780((unsigned int)a4, (unsigned int)(int)&v_l8, (unsigned int)1, (unsigned int)0);
    ((C_0053b8a0*)(a8 + 20))->FUN_0053b8a0((unsigned int)v_l8);
    v_l20_q = 0;
    for (; (unsigned int)v_l20_q < (unsigned int)v_l8; v_l20_q = v_l20_q + 1) {
        v_l24 = (int)(int)(v_l20_q * 20 + (int)*(int*)((char*)a8 + 20));
        FUN_0093a780((unsigned int)a4, (unsigned int)v_l24, (unsigned int)1, (unsigned int)0);
        FUN_0093a780((unsigned int)a4, (unsigned int)(v_l24 + 4), (unsigned int)1, (unsigned int)0);
        FUN_0093a780((unsigned int)a4, (unsigned int)(v_l24 + 8), (unsigned int)1, (unsigned int)0);
        FUN_0093a780((unsigned int)a4, (unsigned int)(v_l24 + 12), (unsigned int)1, (unsigned int)0);
        FUN_0093a6c0((unsigned int)a4, (unsigned int)(v_l24 + 16), (unsigned int)1);
        FUN_0093a6c0((unsigned int)a4, (unsigned int)(v_l24 + 17), (unsigned int)1);
        FUN_0093a6c0((unsigned int)a4, (unsigned int)(v_l24 + 18), (unsigned int)1);
        FUN_0093a6c0((unsigned int)a4, (unsigned int)(v_l24 + 19), (unsigned int)1);
    }
    FUN_0093a780((unsigned int)a4, (unsigned int)(int)&v_l8, (unsigned int)1, (unsigned int)0);
    ((C_004afc80*)(a8 + 40))->FUN_004afc80((unsigned int)v_l8);
    v_l28_g = 0;
    for (; (unsigned int)v_l28_g < (unsigned int)v_l8; v_l28_g = v_l28_g + 1) {
        v_l112 = (int)(int)((int)*(int*)((char*)a8 + 40) + (v_l28_g << 2));
        FUN_0093a780((unsigned int)a4, (unsigned int)v_l112, (unsigned int)1, (unsigned int)0);
    }
    return a4;
}
