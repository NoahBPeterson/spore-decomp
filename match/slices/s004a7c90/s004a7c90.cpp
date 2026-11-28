// 0x004a7c90: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/SPEditorManipulationUtilities.cpp, match/slices/s004a7c30/s004a7c30.cpp.

struct C_00454860 { void FUN_00454860(unsigned int); };
extern "C" int __cdecl FUN_004a7c30(...);
struct C_004accb0 { int FUN_004accb0(unsigned int); };
struct C_004accf0 { int FUN_004accf0(); };
struct C_004adc40 { int FUN_004adc40(); };

// @ 0x004a7c90
extern "C" void __cdecl FUN_004a7c90(int a4, int a8)
{
    int v_l28_g;
    int v_l24;
    int v_l20_q;
    int v_l16_i;
    int v_l12_40;
    int v_l8;
    int v_l40_a;
    int dead_0[2];
    int v_l60_b;
    int v_l56_d;
    int v_l52_i;
    int v_l48_i;
    int v_l44;
    int v_l64;
    int dead_1[2];
    if (a4 == 0) {
    } else {
        v_l8 = (int)(int)*(int*)((char*)a4 + 40);
        if (v_l8 == 0) {
        } else {
            v_l16_i = 0;
            v_l12_40 = ((C_004accf0*)v_l8)->FUN_004accf0();
            for (; v_l16_i < v_l12_40; v_l16_i = v_l16_i + 1) {
                v_l20_q = (int)((C_004accb0*)v_l8)->FUN_004accb0((unsigned int)v_l16_i);
                if (v_l20_q != 0) {
                    if (v_l20_q != a4) {
                        if ((int)(unsigned char)(int)FUN_004a7c30((unsigned int)v_l20_q, (unsigned int)a4) != 0) {
                            ((C_00454860*)a8)->FUN_00454860((unsigned int)(int)&v_l20_q);
                            if ((int)(unsigned char)((C_004adc40*)v_l8)->FUN_004adc40() != 0) {
                                v_l40_a = (int)(int)*(int*)((char*)v_l20_q + 992);
                                if (v_l40_a != 0) {
                                    v_l44 = (int)(int)*(int*)((char*)v_l20_q + 992);
                                    v_l24 = v_l44;
                                    v_l48_i = (int)(int)*(int*)((char*)a8 + 4);
                                    v_l52_i = (int)(int)*(int*)(char*)a8;
                                    v_l56_d = v_l52_i;
                                    while (v_l56_d != v_l48_i && (int)*(int*)(char*)v_l56_d != v_l24) {
                                        v_l56_d = v_l56_d + 4;
                                    }
                                    v_l60_b = (int)(int)*(int*)((char*)a8 + 4);
                                    if (v_l56_d == v_l60_b) {
                                        v_l64 = (int)(int)*(int*)((char*)v_l20_q + 992);
                                        v_l28_g = v_l64;
                                        ((C_00454860*)a8)->FUN_00454860((unsigned int)(int)&v_l28_g);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return;
}
