// 0x004a3c70: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/SPEditorManipulationUtilities.cpp, match/slices/s005ab7a0/s005ab7a0.cpp, match/slices/s004a3760/s004a3760.cpp.

extern "C" unsigned char g_013ef4c0[];
extern "C" double __cdecl FUN_0040ae50(...);
extern "C" int __cdecl FUN_0041db10(...);
struct C_0044a9a0 { int FUN_0044a9a0(unsigned int); };
extern "C" int __cdecl FUN_004a18b0(unsigned int, unsigned int, float);
struct C_004accb0 { int FUN_004accb0(unsigned int); };
struct C_004accf0 { int FUN_004accf0(); };

// @ 0x004a3c70
extern "C" int __cdecl FUN_004a3c70(int a4, int a8)
{
    float v_l32_p;
    int v_l28_g;
    int v_l24;
    int v_l20_q;
    float v_l16_i;
    int v_l12_40;
    int v_l8;
    int v_l60_b;
    int v_l56_d[3];
    float v_l44;
    float v_l40_w;
    float v_l36;
    int dead_0_c;
    int v_l68_6;
    int v_l64;
    v_l60_b = (int)(int)*(int*)((char*)a4 + 828);
    if (v_l60_b == 0) {
        return 0;
    }
        v_l8 = (int)(int)*(int*)((char*)a4 + 40);
        v_l16_i = (float)*(float*)g_013ef4c0;
        v_l12_40 = 0;
        v_l20_q = 0;
        v_l24 = ((C_004accf0*)v_l8)->FUN_004accf0();
        for (; v_l20_q < v_l24; v_l20_q = v_l20_q + 1) {
            v_l28_g = (int)((C_004accb0*)v_l8)->FUN_004accb0((unsigned int)v_l20_q);
            if (v_l28_g != a4) {
                v_l64 = (int)(int)*(int*)((char*)a4 + 992);
                if (v_l28_g != v_l64) {
                    if ((int)(unsigned char)((C_0044a9a0*)v_l28_g)->FUN_0044a9a0((unsigned int)a4) == 0) {
                        v_l68_6 = (int)(int)FUN_0041db10((unsigned int)(int)&v_l56_d, (unsigned int)(v_l28_g + 72), (unsigned int)(int)&a8);
                        v_l44 = *(float*)(char*)v_l68_6;
                        v_l40_w = *(float*)((char*)v_l68_6 + 4);
                        v_l36 = *(float*)((char*)v_l68_6 + 8);
                        v_l32_p = (float)(double)FUN_0040ae50((unsigned int)(int)(int)&v_l44);
                        if ((int)(unsigned char)(int)FUN_004a18b0((unsigned int)a4, (unsigned int)v_l28_g, (float)v_l32_p) != 0) {
                            if ((float)v_l16_i > v_l32_p) {
                                v_l16_i = (float)v_l32_p;
                                v_l12_40 = v_l28_g;
                            }
                        }
                    }
                }
            }
        }
        return v_l12_40;
}
