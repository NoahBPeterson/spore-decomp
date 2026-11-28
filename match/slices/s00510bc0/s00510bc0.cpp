// 0x00510bc0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s005107d0/s005107d0.cpp, src/game/SPGonzago/SPStarManager.cpp.

extern "C" int __cdecl FUN_0042dee0(...);
extern "C" void __cdecl FUN_004b2400(...);
extern "C" void __cdecl FUN_0050e7b0(...);
extern "C" int __cdecl FUN_00512000(...);
extern "C" void __cdecl FUN_00f47380(...);
struct S6 { int m0; int m1; int m2; int m3; int m4; int m5; };


struct D_00510bc0 { void FUN_00510bc0(int a4, int a8, int a12, int a16); };
// @ 0x00510bc0
void D_00510bc0::FUN_00510bc0(int a4, int a8, int a12, int a16)
{
    char dead_0_15;
    int v_l48_c[2];
    int v_l40_h;
    int v_l36_c;
    int v_l32_p;
    int v_l28_g;
    int v_l24;
    int v_l20_q;
    int v_l16_i;
    int v_l12_40;
    int v_l8;
    unsigned char v_l79_w;
    unsigned char v_l78_u;
    unsigned char v_l77_c;
    int v_l76_d;
    int v_l72_w;
    int v_l68_a;
    int v_l64_b;
    int v_l60_t;
    int v_l56_k;
    unsigned char v_l50;
    unsigned char v_l91;
    unsigned char v_l90_a;
    unsigned char v_l89_41;
    int v_l88_12;
    int v_l84;
    int v_l96;
    int dead_1_36[15];
    int v_l100;
    unsigned char v_l203_11;
    unsigned char v_l202_20;
    unsigned char v_l201_a;
    int dead_2[10];
    int v_l216_26;
    int v_l212;
    int v_l208;
    unsigned char v_l250_d;
    char dead_7_b;
    int v_l248_19;
    int v_l244_66;
    int v_l240_30;
    int v_l236_d;
    unsigned char v_l229_c;
    int dead_6_14;
    char dead_5_20;
    char dead_4_11;
    char dead_3_10;
    unsigned char v_l221_a;
    int v_l220;
    char dead_9_13;
    unsigned char v_l297_b;
    int v_l296_19;
    int v_l292_19;
    int v_l288_32;
    int v_l284_43;
    int dead_8_14[4];
    int v_l264_16;
    int v_l260;
    int v_l256;
    int v_l328_46;
    int v_l324_29;
    int v_l320_b;
    int v_l316_31;
    int v_l312_31;
    unsigned char v_l305_d;
    int dead_12_u;
    char dead_11_x;
    char dead_10;
    int v_l332;
    if (a8 != a12) {
        v_l8 = (a12 - a8) / 24;
        if ((unsigned int)v_l8 <= (unsigned int)(int)((int)(int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)((char*)(int)this + 4)) / 24)) {
            v_l16_i = (int)(int)((int)((int)*(int*)((char*)(int)this + 4) - a4) / 24);
            v_l12_40 = (int)(int)*(int*)((char*)(int)this + 4);
            if ((unsigned int)v_l8 < (unsigned int)v_l16_i) {
                v_l76_d = (int)(int)*(int*)((char*)(int)this + 4);
                v_l72_w = (int)(int)*(int*)((char*)(int)this + 4);
                v_l68_a = (int)(int)((int)*(int*)((char*)(int)this + 4) - v_l8 * 24);
                v_l56_k = v_l76_d;
                v_l60_t = v_l72_w;
                v_l64_b = v_l68_a;
                FUN_004b2400((unsigned int)(int)&v_l48_c, (unsigned int)v_l64_b, (unsigned int)v_l60_t, (unsigned int)v_l56_k, (unsigned int)(int)v_l50);
                *(int*)((char*)(int)this + 4) = (int)(int)(v_l8 * 24 + (int)*(int*)((char*)(int)this + 4));
                v_l78_u = (unsigned char)0;
                v_l77_c = (unsigned char)0;
                v_l79_w = (unsigned char)0;
                v_l88_12 = v_l12_40;
                v_l84 = v_l12_40 - v_l8 * 24;
                while (v_l84 != a4) {
                    v_l84 = v_l84 - 24;
                    v_l88_12 = v_l88_12 - 24;
                    *(S6*)v_l88_12 = *(S6*)v_l84;
                }
                v_l90_a = (unsigned char)0;
                v_l89_41 = (unsigned char)0;
                v_l91 = (unsigned char)0;
                v_l100 = a4;
                v_l96 = a8;
                for (; v_l96 != a12; v_l100 = v_l100 + 24, v_l96 = v_l96 + 24) {
                    *(S6*)v_l100 = *(S6*)v_l96;
                }
            } else {
                v_l20_q = a8;
                v_l20_q = v_l16_i * 24 + v_l20_q;
                FUN_0050e7b0((unsigned int)v_l20_q, (unsigned int)a12, (unsigned int)(int)*(int*)((char*)(int)this + 4));
                *(int*)((char*)(int)this + 4) = (int)(int)((v_l8 - v_l16_i) * 24 + (int)*(int*)((char*)(int)this + 4));
                FUN_0050e7b0((unsigned int)a4, (unsigned int)v_l12_40, (unsigned int)(int)*(int*)((char*)(int)this + 4));
                *(int*)((char*)(int)this + 4) = (int)(int)(v_l16_i * 24 + (int)*(int*)((char*)(int)this + 4));
                v_l216_26 = v_l20_q;
                v_l202_20 = (unsigned char)0;
                v_l201_a = (unsigned char)0;
                v_l203_11 = (unsigned char)0;
                v_l212 = v_l16_i * 24 + a4;
                v_l208 = v_l216_26;
                while (v_l208 != a8) {
                    v_l208 = v_l208 - 24;
                    v_l212 = v_l212 - 24;
                    *(S6*)v_l212 = *(S6*)v_l208;
                }
            }
        } else {
            v_l32_p = (int)(int)((int)(int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 24);
            v_l40_h = (int)(int)((unsigned int)v_l32_p > (unsigned int)0 ? v_l32_p << 1 : 1);
            v_l24 = (int)(int)((unsigned int)v_l40_h > (unsigned int)(v_l32_p + v_l8) ? v_l40_h : v_l32_p + v_l8);
            v_l36_c = (int)(int)(v_l24 != 0 ? (int)(int)FUN_0042dee0((unsigned int)((int)this + 12), (unsigned int)(v_l24 * 24), (unsigned int)4, (unsigned int)0) : 0);
            v_l244_66 = (int)(int)*(int*)(char*)(int)this;
            v_l221_a = (unsigned char)0;
            v_l220 = (int)(int)FUN_00512000((unsigned int)v_l244_66, (unsigned int)a4, (unsigned int)v_l36_c);
            v_l229_c = (unsigned char)0;
            v_l240_30 = v_l36_c;
            v_l236_d = v_l244_66;
            for (; v_l236_d != a4; v_l236_d = v_l236_d + 24, v_l240_30 = v_l240_30 + 24) {
            }
            v_l28_g = v_l220;
            v_l292_19 = v_l28_g;
            v_l288_32 = a12;
            v_l284_43 = a8;
            v_l256 = v_l292_19;
            v_l260 = v_l288_32;
            v_l264_16 = v_l284_43;
            FUN_004b2400((unsigned int)(int)&v_l248_19, (unsigned int)v_l264_16, (unsigned int)v_l260, (unsigned int)v_l256, (unsigned int)(int)v_l250_d);
            v_l28_g = v_l248_19;
            v_l320_b = (int)(int)*(int*)((char*)(int)this + 4);
            v_l297_b = (unsigned char)0;
            v_l296_19 = (int)(int)FUN_00512000((unsigned int)a4, (unsigned int)v_l320_b, (unsigned int)v_l28_g);
            v_l305_d = (unsigned char)0;
            v_l316_31 = v_l28_g;
            v_l312_31 = a4;
            for (; v_l312_31 != v_l320_b; v_l312_31 = v_l312_31 + 24, v_l316_31 = v_l316_31 + 24) {
            }
            v_l28_g = v_l296_19;
            v_l332 = (int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) / 24);
            v_l328_46 = (int)(int)*(int*)(char*)(int)this;
            if (v_l328_46 != 0) {
                if ((int)*(int*)((char*)v_l328_46 - 4) != 0) {
                    v_l324_29 = v_l328_46;
                    FUN_00f47380((unsigned int)v_l324_29);
                }
            }
            *(int*)(char*)(int)this = v_l36_c;
            *(int*)((char*)(int)this + 4) = v_l28_g;
            *(int*)((char*)(int)this + 8) = v_l24 * 24 + v_l36_c;
        }
    }
    return;
}
