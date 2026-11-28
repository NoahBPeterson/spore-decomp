// 0x004ac480: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/SPEditorManipulationUtilities.cpp, src/game/SPBake/_at_00480000.cpp, match/slices/s004ab690/s004ab690.cpp, match/slices/s00486910/s00486910.cpp.

extern "C" unsigned char g_013ef5c8[];
extern "C" double __cdecl FUN_0040ae50(...);
extern "C" int __cdecl FUN_0041db10(...);
extern "C" double __cdecl FUN_004a5bd0(...);
template<class T> __forceinline bool il2c_nz(T v) { return v != 0; }
template<class T> __forceinline T il2c_k(T v) { return v; }


struct D_004ac480 { int FUN_004ac480(int a4, int a8, int a12); };
// @ 0x004ac480
int D_004ac480::FUN_004ac480(int a4, int a8, int a12)
{
    float v_l24;
    int v_l20_q;
    int v_l16_i;
    int v_l12_40;
    float v_l8;
    float v_l28;
    int v_l100_d;
    int dead_0_12;
    int v_l92_c;
    int v_l88;
    int v_l84_i;
    int v_l80_d;
    int v_l76;
    unsigned char v_l69_b;
    int v_l68_y;
    int v_l64_n;
    int v_l60;
    int v_l56_92;
    int v_l52_h[3];
    float v_l40_e;
    float v_l36_i;
    float v_l32;
    v_l8 = (float)*(float*)g_013ef5c8;
    v_l12_40 = 0;
    v_l16_i = 0;
    v_l56_92 = (int)this + 24;
    v_l20_q = (int)(int)((int)((int)*(int*)((char*)v_l56_92 + 4) - (int)*(int*)(char*)v_l56_92) >> 2);
    for (; v_l16_i < v_l20_q; v_l16_i = v_l16_i + 1) {
        v_l60 = (int)(int)((int)*(int*)((char*)(int)this + 24) + (v_l16_i << 2));
        v_l64_n = (int)(int)*(int*)(char*)v_l60;
        if (il2c_k((unsigned int)7) < (unsigned int)60) {
            v_l68_y = (int)(int)*(int*)((char*)v_l64_n + (int)(il2c_k((unsigned int)7) >> 5) * 4 + 3528);
            v_l69_b = (unsigned char)(unsigned char)(unsigned char)il2c_nz((int)(int)((int)(1 << (int)(unsigned int)(il2c_k((unsigned int)7) % (unsigned int)32)) & v_l68_y));
        } else {
            v_l69_b = (unsigned char)0;
        }
        if ((int)v_l69_b != 0) {
            v_l76 = (int)(int)((int)*(int*)((char*)(int)this + 24) + (v_l16_i << 2));
            v_l80_d = (int)(int)*(int*)(char*)v_l76;
            v_l28 = (float)(double)FUN_004a5bd0((unsigned int)v_l80_d);
            v_l84_i = (int)(int)((int)*(int*)((char*)(int)this + 24) + (v_l16_i << 2));
            v_l88 = (int)(int)*(int*)(char*)v_l84_i;
            v_l92_c = (int)(int)FUN_0041db10((unsigned int)(int)&v_l52_h, (unsigned int)(v_l88 + 72), (unsigned int)(int)&a4);
            v_l40_e = *(float*)(char*)v_l92_c;
            v_l36_i = *(float*)((char*)v_l92_c + 4);
            v_l32 = *(float*)((char*)v_l92_c + 8);
            v_l24 = (float)(double)((double)FUN_0040ae50((unsigned int)(int)(int)&v_l40_e) - (double)v_l28);
            if ((float)v_l8 > v_l24) {
                v_l8 = (float)v_l24;
                v_l100_d = (int)(int)((int)*(int*)((char*)(int)this + 24) + (v_l16_i << 2));
                v_l12_40 = (int)(int)*(int*)(char*)v_l100_d;
            }
        }
    }
    return v_l12_40;
}
