// 0x004a6d20: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/SPEditorManipulationUtilities.cpp, match/slices/s004a6690/s004a6690.cpp, match/slices/s005ab7a0/s005ab7a0.cpp.

struct C_0043f6b0 { void FUN_0043f6b0(unsigned int, unsigned int); };
struct C_0043fc20 { int FUN_0043fc20(unsigned int); };
struct C_00453540 { int FUN_00453540(); };
struct C_004adc20 { int FUN_004adc20(unsigned int); };
struct C_004adc40 { int FUN_004adc40(); };

// @ 0x004a6d20
// @ 0x004a6d20
extern "C" void __cdecl FUN_004a6d20(int a4, int a8, int a12, int a16, int a20, int a24, int a28, int a32)
{
    int v_l24;
    int v_l20_q;
    int v_l16_i;
    unsigned char v_l10_r;
    unsigned char v_l9_f;
    int v_l8;
    int v_l28;
    int v_l36_i;
    int v_l32;
    char dead_3;
    char dead_2_17;
    char dead_1;
    unsigned char v_l85_13;
    int v_l84_n;
    int dead_0_d[3];
    int v_l68_m;
    int v_l64_o;
    int v_l60_k;
    int v_l56_b;
    int v_l52;
    int v_l48_y;
    int v_l44_e;
    int v_l40;
    v_l36_i = (int)(int)*(int*)((char*)a4 + 40);
    v_l8 = v_l36_i;
    if (v_l8 != 0) {
        v_l40 = v_l8 + 4;
        v_l84_n = (int)(int)((int)*(int*)((char*)v_l40 + 4) + 1);
        *(int*)((char*)v_l40 + 4) = (int)(int)((int)*(int*)((char*)v_l40 + 4) + 1);
    }
    if (v_l8 != 0) {
        v_l44_e = v_l8;
        v_l9_f = (unsigned char)(unsigned char)((C_004adc40*)v_l44_e)->FUN_004adc40();
        ((C_004adc20*)v_l8)->FUN_004adc20((unsigned int)0);
        if ((int)(unsigned char)a24 != 0) {
            v_l85_13 = (unsigned char)0;
        } else {
            v_l85_13 = (unsigned char)(unsigned char)((C_0043fc20*)a4)->FUN_0043fc20((unsigned int)0);
        }
        v_l10_r = (unsigned char)(unsigned char)v_l85_13;
        ((C_0043f6b0*)a4)->FUN_0043f6b0((unsigned int)(int)v_l10_r, (unsigned int)a16);
        if ((int)(unsigned char)a32 != 0) {
            v_l48_y = (int)(int)*(int*)((char*)a4 + 992);
            if (v_l48_y != 0) {
                v_l52 = (int)(int)*(int*)((char*)a4 + 992);
                FUN_004a6d20((unsigned int)v_l52, (unsigned int)0, (unsigned int)(int)(unsigned char)a12, (unsigned int)a16, (unsigned int)0, (unsigned int)(int)(unsigned char)a24, (unsigned int)0, (unsigned int)0);
            }
        }
        if (a8 != 0) {
            v_l16_i = (int)(int)((int)((int)*(int*)((char*)a8 + 4) - (int)*(int*)(char*)a8) >> 2);
            v_l20_q = 0;
            for (; v_l20_q < v_l16_i; v_l20_q = v_l20_q + 1) {
                v_l56_b = (int)(int)((int)*(int*)(char*)a8 + (v_l20_q << 2));
                v_l60_k = (int)(int)*(int*)(char*)v_l56_b;
                FUN_004a6d20((unsigned int)v_l60_k, (unsigned int)0, (unsigned int)(int)(unsigned char)a12, (unsigned int)a16, (unsigned int)0, (unsigned int)(int)(unsigned char)a24, (unsigned int)0, (unsigned int)1);
            }
        } else {
            if ((int)(unsigned char)a28 != 0) {
                v_l24 = a4 + 832;
                v_l32 = 0;
                v_l28 = (int)(int)((int)((int)*(int*)((char*)v_l24 + 4) - (int)*(int*)(char*)v_l24) >> 2);
                for (; v_l32 < v_l28; v_l32 = v_l32 + 1) {
                    v_l64_o = (int)(int)((int)*(int*)(char*)v_l24 + (v_l32 << 2));
                    v_l68_m = (int)(int)*(int*)(char*)v_l64_o;
                    FUN_004a6d20((unsigned int)v_l68_m, (unsigned int)0, (unsigned int)(int)(unsigned char)a12, (unsigned int)a16, (unsigned int)0, (unsigned int)(int)(unsigned char)a24, (unsigned int)1, (unsigned int)1);
                }
            }
        }
        ((C_004adc20*)v_l8)->FUN_004adc20((unsigned int)(int)v_l9_f);
    }
    if (v_l8 != 0) {
        ((C_00453540*)(v_l8 + 4))->FUN_00453540();
    }
    return;
}
