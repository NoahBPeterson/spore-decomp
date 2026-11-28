// 0x005409d0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s005409d0/s005409d0.cpp.

struct C_004098a0 { void FUN_004098a0(unsigned int); };
extern "C" int __cdecl FUN_0042dee0(...);
extern "C" void __cdecl FUN_00540e80(...);
extern "C" int __cdecl FUN_00540f90(...);
extern "C" void __cdecl FUN_005414d0(...);
extern "C" void __cdecl FUN_00541550(...);
extern "C" int __cdecl FUN_005415b0(...);
extern "C" void __cdecl FUN_00f47380(...);
struct S6 { int m0; int m1; int m2; int m3; int m4; int m5; };


struct D_005409d0 { void FUN_005409d0(int a4, int a8, int a12); };
// @ 0x005409d0
// @ 0x005409d0
void D_005409d0::FUN_005409d0(int a4, int a8, int a12)
{
    int v_l44_f;
    int v_l40_h;
    int v_l36_c;
    int v_l32_p;
    int v_l28_g;
    int v_l24;
    int v_l20_q;
    int dead_0_15[2];
    int v_l8;
    int v_l92_k;
    int v_l88_12;
    int v_l84;
    int v_l80_20;
    int v_l76_107;
    int v_l72_l;
    unsigned char v_l66_z;
    char dead_1_12;
    int v_l64_z;
    int v_l60_f;
    int v_l56_a;
    int v_l52_w;
    int v_l48;
    int v_l172;
    int dead_3_d[12];
    int v_l120_c;
    int v_l116_13;
    unsigned char v_l110_a;
    char dead_2_16;
    int v_l108_14;
    int v_l104_a;
    int v_l100_34;
    unsigned char v_l95_o;
    unsigned char v_l94;
    unsigned char v_l93;
    unsigned char v_l221_20;
    int v_l220_10;
    int v_l216_40;
    int v_l212_46;
    unsigned char v_l206_10;
    char dead_5_b;
    int dead_4[8];
    char dead_6;
    char dead_8_39;
    char dead_7;
    int v_l248;
    int v_l244_12;
    int v_l240_25;
    unsigned char v_l233_12;
    int dead_9[2];
    int v_l264_16;
    int v_l260;
    int v_l256;
    int v_l252;
    if ((unsigned int)a8 <= (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)((char*)(int)this + 4)) / 24)) {
        if ((unsigned int)a8 > (unsigned int)0) {
            v_l32_p = (int)(int)*(int*)(char*)a12;
            v_l28_g = (int)(int)*(int*)((char*)a12 + 4);
            v_l24 = (int)(int)*(int*)((char*)a12 + 8);
            v_l60_f = (int)&v_l20_q;
            ((C_004098a0*)v_l60_f)->FUN_004098a0((unsigned int)(a12 + 12));
            v_l36_c = (int)(int)((int)((int)*(int*)((char*)(int)this + 4) - a4) / 24);
            v_l8 = (int)(int)*(int*)((char*)(int)this + 4);
            if ((unsigned int)a8 < (unsigned int)v_l36_c) {
                v_l92_k = (int)(int)*(int*)((char*)(int)this + 4);
                v_l88_12 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l84 = (int)(int)((int)*(int*)((char*)(int)this + 4) - a8 * 24);
                v_l72_l = v_l92_k;
                v_l76_107 = v_l88_12;
                v_l80_20 = v_l84;
                FUN_005414d0((unsigned int)(int)&v_l64_z, (unsigned int)v_l80_20, (unsigned int)v_l76_107, (unsigned int)v_l72_l, (unsigned int)(int)v_l66_z);
                *(int*)((char*)(int)this + 4) = (int)(int)(a8 * 24 + (int)*(int*)((char*)(int)this + 4));
                v_l94 = (unsigned char)0;
                v_l93 = (unsigned char)0;
                v_l95_o = (unsigned char)0;
                v_l104_a = v_l8;
                v_l100_34 = v_l8 - a8 * 24;
                while (v_l100_34 != a4) {
                    v_l100_34 = v_l100_34 - 24;
                    v_l104_a = v_l104_a - 24;
                    *(S6*)v_l104_a = *(S6*)v_l100_34;
                }
                v_l108_14 = a4;
                for (; v_l108_14 != a8 * 24 + a4; v_l108_14 = v_l108_14 + 24) {
                    *(S6*)v_l108_14 = *(S6*)&v_l32_p;
                }
            } else {
                v_l120_c = (int)(int)*(int*)((char*)(int)this + 4);
                v_l116_13 = v_l120_c;
                FUN_00541550((unsigned int)v_l116_13, (unsigned int)(a8 - v_l36_c), (unsigned int)(int)&v_l32_p, (unsigned int)(int)v_l110_a);
                *(int*)((char*)(int)this + 4) = (int)(int)((a8 - v_l36_c) * 24 + (int)*(int*)((char*)(int)this + 4));
                FUN_00540e80((unsigned int)a4, (unsigned int)v_l8, (unsigned int)(int)*(int*)((char*)(int)this + 4));
                *(int*)((char*)(int)this + 4) = (int)(int)(v_l36_c * 24 + (int)*(int*)((char*)(int)this + 4));
                v_l172 = a4;
                for (; v_l172 != v_l8; v_l172 = v_l172 + 24) {
                    *(S6*)v_l172 = *(S6*)&v_l32_p;
                }
            }
        }
    } else {
        v_l48 = (int)(int)((int)(int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 24);
        v_l56_a = (int)(int)((unsigned int)v_l48 > (unsigned int)0 ? v_l48 << 1 : 1);
        v_l40_h = (int)(int)((unsigned int)v_l56_a > (unsigned int)(v_l48 + a8) ? v_l56_a : v_l48 + a8);
        v_l52_w = (int)(int)(v_l40_h != 0 ? (int)(int)FUN_0042dee0((unsigned int)((int)this + 12), (unsigned int)(v_l40_h * 24), (unsigned int)4, (unsigned int)0) : 0);
        v_l44_f = (int)(int)FUN_00540f90((unsigned int)(int)*(int*)(char*)(int)this, (unsigned int)a4, (unsigned int)v_l52_w);
        v_l216_40 = v_l44_f;
        v_l212_46 = v_l216_40;
        FUN_00541550((unsigned int)v_l212_46, (unsigned int)a8, (unsigned int)a12, (unsigned int)(int)v_l206_10);
        v_l252 = a8 * 24 + v_l44_f;
        v_l248 = (int)(int)*(int*)((char*)(int)this + 4);
        v_l221_20 = (unsigned char)0;
        v_l220_10 = (int)(int)FUN_005415b0((unsigned int)a4, (unsigned int)v_l248, (unsigned int)v_l252);
        v_l233_12 = (unsigned char)0;
        v_l244_12 = v_l252;
        v_l240_25 = a4;
        for (; v_l240_25 != v_l248; v_l240_25 = v_l240_25 + 24, v_l244_12 = v_l244_12 + 24) {
        }
        v_l44_f = v_l220_10;
        v_l264_16 = (int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) / 24);
        v_l260 = (int)(int)*(int*)(char*)(int)this;
        if (v_l260 != 0) {
            if ((int)*(int*)((char*)v_l260 - 4) != 0) {
                v_l256 = v_l260;
                FUN_00f47380((unsigned int)v_l256);
            }
        }
        *(int*)(char*)(int)this = v_l52_w;
        *(int*)((char*)(int)this + 4) = v_l44_f;
        *(int*)((char*)(int)this + 8) = v_l40_h * 24 + v_l52_w;
    }
    return;
}
