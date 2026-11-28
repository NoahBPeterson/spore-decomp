// 0x005704c0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEditors/TraitVector.cpp, match/slices/s0056fb90/s0056fb90.cpp.

extern "C" unsigned char g_01485378[];
extern "C" unsigned char g_015e4a1c[];
extern "C" unsigned char g_015e4a20[];
struct C_00555980 { void FUN_00555980(unsigned int, unsigned int); };
struct C_005715d0 { int FUN_005715d0(unsigned int); };
struct C_00571610 { int FUN_00571610(unsigned int); };
struct C_005716c0 { int FUN_005716c0(); };
struct C_005716e0 { int FUN_005716e0(); };


struct D_005704c0 { float FUN_005704c0(int a4, int a8); };
// @ 0x005704c0
float D_005704c0::FUN_005704c0(int a4, int a8)
{
    int v_l44_f;
    float v_l40_h;
    int v_l36_c;
    int v_l32_p;
    int v_l28_g;
    float v_l24;
    int v_l20_q;
    int v_l16_i;
    int v_l12_40;
    int v_l8;
    int v_l64_z;
    int v_l60_f;
    int v_l56_a;
    int v_l52_w;
    int v_l48;
    int v_l124_c;
    int dead_1_b[3];
    int v_l108_63;
    int v_l104_30;
    int v_l100_b;
    int v_l96_a;
    int v_l92;
    int dead_0_25[3];
    int v_l76_c;
    int v_l72_a;
    int v_l68;
    int v_l128;
    int v_l164_d;
    int v_l160_15;
    int v_l156_55;
    int dead_2_11[3];
    int v_l140_11;
    int v_l136_13;
    int v_l132;
    int v_l172_11;
    int v_l168;
    int v_l196_62;
    int v_l192_29;
    int v_l188;
    int dead_3[3];
    v_l8 = ((C_005716c0*)a4)->FUN_005716c0();
    v_l20_q = ((C_005716c0*)a8)->FUN_005716c0();
    v_l12_40 = ((C_005716e0*)a4)->FUN_005716e0();
    v_l16_i = ((C_005716e0*)a8)->FUN_005716e0();
    v_l24 = (float)*(float*)g_01485378;
    while (v_l8 != v_l12_40 && v_l20_q != v_l16_i) {
        for (; v_l8 != v_l12_40 && (v_l20_q != v_l16_i && (int)(unsigned char)((C_005715d0*)v_l8)->FUN_005715d0((unsigned int)v_l20_q) != 0); v_l8 = v_l8 + 12) {
            v_l28_g = v_l8;
            ((C_00555980*)(int)g_015e4a1c)->FUN_00555980((unsigned int)(int)&v_l56_a, (unsigned int)v_l28_g);
            if (v_l56_a != v_l52_w) {
                v_l64_z = v_l56_a;
            } else {
                v_l60_f = *(int*)g_015e4a20;
                v_l64_z = v_l60_f;
            }
            v_l68 = *(int*)g_015e4a20;
            if (v_l64_z != v_l68) {
                v_l24 = (float)((float)v_l24 + (float)*(float*)((char*)v_l28_g + 8));
            }
        }
        for (; v_l8 != v_l12_40 && (v_l20_q != v_l16_i && (int)(unsigned char)((C_005715d0*)v_l20_q)->FUN_005715d0((unsigned int)v_l8) != 0); v_l20_q = v_l20_q + 12) {
            v_l32_p = v_l20_q;
            ((C_00555980*)(int)g_015e4a1c)->FUN_00555980((unsigned int)(int)&v_l76_c, (unsigned int)v_l32_p);
            if (v_l76_c != v_l72_a) {
                v_l96_a = v_l76_c;
            } else {
                v_l92 = *(int*)g_015e4a20;
                v_l96_a = v_l92;
            }
            v_l100_b = *(int*)g_015e4a20;
            if (v_l96_a != v_l100_b) {
                v_l24 = (float)((float)v_l24 + (float)*(float*)((char*)v_l32_p + 8));
            }
        }
        for (; (int)(unsigned char)((C_00571610*)v_l8)->FUN_00571610((unsigned int)v_l20_q) != 0 && (v_l8 != v_l12_40 && v_l20_q != v_l16_i); v_l8 = v_l8 + 12, v_l20_q = v_l20_q + 12) {
            v_l36_c = v_l8;
            v_l40_h = *(float*)((char*)v_l20_q + 8);
            ((C_00555980*)(int)g_015e4a1c)->FUN_00555980((unsigned int)(int)&v_l108_63, (unsigned int)v_l36_c);
            if (v_l108_63 != v_l104_30) {
                v_l128 = v_l108_63;
            } else {
                v_l124_c = *(int*)g_015e4a20;
                v_l128 = v_l124_c;
            }
            v_l132 = *(int*)g_015e4a20;
            if (v_l128 != v_l132) {
                if ((float)v_l40_h > (float)*(float*)((char*)v_l36_c + 8)) {
                    v_l24 = (float)((float)((float)v_l40_h - (float)*(float*)((char*)v_l36_c + 8)) + v_l24);
                } else {
                    v_l24 = (float)((float)(*(float*)((char*)v_l36_c + 8) - v_l40_h) + v_l24);
                }
            }
        }
    }
    for (; v_l8 != v_l12_40 && v_l20_q == v_l16_i; v_l8 = v_l8 + 12) {
        v_l44_f = v_l8;
        ((C_00555980*)(int)g_015e4a1c)->FUN_00555980((unsigned int)(int)&v_l140_11, (unsigned int)v_l44_f);
        if (v_l140_11 != v_l136_13) {
            v_l160_15 = v_l140_11;
        } else {
            v_l156_55 = *(int*)g_015e4a20;
            v_l160_15 = v_l156_55;
        }
        v_l164_d = *(int*)g_015e4a20;
        if (v_l160_15 != v_l164_d) {
            v_l24 = (float)((float)v_l24 + (float)*(float*)((char*)v_l44_f + 8));
        }
    }
    for (; v_l8 == v_l12_40 && v_l20_q != v_l16_i; v_l20_q = v_l20_q + 12) {
        v_l48 = v_l20_q;
        ((C_00555980*)(int)g_015e4a1c)->FUN_00555980((unsigned int)(int)&v_l172_11, (unsigned int)v_l48);
        if (v_l172_11 != v_l168) {
            v_l192_29 = v_l172_11;
        } else {
            v_l188 = *(int*)g_015e4a20;
            v_l192_29 = v_l188;
        }
        v_l196_62 = *(int*)g_015e4a20;
        if (v_l192_29 != v_l196_62) {
            v_l24 = (float)((float)v_l24 + (float)*(float*)((char*)v_l48 + 8));
        }
    }
    return (float)v_l24;
}
