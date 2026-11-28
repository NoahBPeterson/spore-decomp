// 0x00510350: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPStarManager.cpp, match/slices/s0050f8b0/s0050f8b0.cpp.

extern "C" int __cdecl FUN_0042dee0(...);
extern "C" int __cdecl FUN_00475ef0(...);
extern "C" void __cdecl FUN_004797a0(...);
extern "C" int __cdecl FUN_004b66b0(...);
extern "C" int __cdecl FUN_004b6bf0(...);
extern "C" void __cdecl FUN_00f47380(...);
struct S3 { int m0; int m1; int m2; };


struct D_00510350 { void FUN_00510350(int a4, int a8, int a12, int a16); };
// @ 0x00510350
// @ 0x00510350
void D_00510350::FUN_00510350(int a4, int a8, int a12, int a16)
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
    int v_l328_46;
    int v_l324_29;
    unsigned char v_l317_24;
    int dead_5_16[4];
    int v_l300_b;
    int dead_4_35[5];
    int dead_3[15];
    int v_l344_11;
    int v_l340_24;
    int v_l336_d;
    int v_l332;
    if (a8 != a12) {
        v_l8 = (a12 - a8) / 12;
        if ((unsigned int)v_l8 <= (unsigned int)(int)((int)(int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)((char*)(int)this + 4)) / 12)) {
            v_l16_i = (int)(int)((int)((int)*(int*)((char*)(int)this + 4) - a4) / 12);
            v_l12_40 = (int)(int)*(int*)((char*)(int)this + 4);
            if ((unsigned int)v_l8 < (unsigned int)v_l16_i) {
                v_l76_d = (int)(int)*(int*)((char*)(int)this + 4);
                v_l72_w = (int)(int)*(int*)((char*)(int)this + 4);
                v_l68_a = (int)(int)((int)*(int*)((char*)(int)this + 4) - v_l8 * 12);
                v_l56_k = v_l76_d;
                v_l60_t = v_l72_w;
                v_l64_b = v_l68_a;
                FUN_004797a0((unsigned int)(int)&v_l48_c, (unsigned int)v_l64_b, (unsigned int)v_l60_t, (unsigned int)v_l56_k, (unsigned int)(int)v_l50);
                *(int*)((char*)(int)this + 4) = (int)(int)(v_l8 * 12 + (int)*(int*)((char*)(int)this + 4));
                v_l78_u = (unsigned char)0;
                v_l77_c = (unsigned char)0;
                v_l79_w = (unsigned char)0;
                v_l88_12 = v_l12_40;
                v_l84 = v_l12_40 - v_l8 * 12;
                while (v_l84 != a4) {
                    v_l84 = v_l84 - 12;
                    v_l88_12 = v_l88_12 - 12;
                    *(S3*)v_l88_12 = *(S3*)v_l84;
                }
                v_l90_a = (unsigned char)0;
                v_l89_41 = (unsigned char)0;
                v_l91 = (unsigned char)0;
                v_l100 = a4;
                v_l96 = a8;
                for (; v_l96 != a12; v_l100 = v_l100 + 12, v_l96 = v_l96 + 12) {
                    *(S3*)v_l100 = *(S3*)v_l96;
                }
            } else {
                v_l20_q = a8;
                v_l20_q = v_l16_i * 12 + v_l20_q;
                FUN_00475ef0((unsigned int)v_l20_q, (unsigned int)a12, (unsigned int)(int)*(int*)((char*)(int)this + 4));
                *(int*)((char*)(int)this + 4) = (int)(int)((v_l8 - v_l16_i) * 12 + (int)*(int*)((char*)(int)this + 4));
                FUN_00475ef0((unsigned int)a4, (unsigned int)v_l12_40, (unsigned int)(int)*(int*)((char*)(int)this + 4));
                *(int*)((char*)(int)this + 4) = (int)(int)(v_l16_i * 12 + (int)*(int*)((char*)(int)this + 4));
                v_l216_26 = v_l20_q;
                v_l202_20 = (unsigned char)0;
                v_l201_a = (unsigned char)0;
                v_l203_11 = (unsigned char)0;
                v_l212 = v_l16_i * 12 + a4;
                v_l208 = v_l216_26;
                while (v_l208 != a8) {
                    v_l208 = v_l208 - 12;
                    v_l212 = v_l212 - 12;
                    *(S3*)v_l212 = *(S3*)v_l208;
                }
            }
        } else {
            v_l32_p = (int)(int)((int)(int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 12);
            v_l40_h = (int)(int)((unsigned int)v_l32_p > (unsigned int)0 ? v_l32_p << 1 : 1);
            v_l24 = (int)(int)((unsigned int)v_l40_h > (unsigned int)(v_l32_p + v_l8) ? v_l40_h : v_l32_p + v_l8);
            v_l36_c = (int)(int)(v_l24 != 0 ? (int)(int)FUN_0042dee0((unsigned int)((int)this + 12), (unsigned int)(v_l24 * 12), (unsigned int)4, (unsigned int)0) : 0);
            v_l28_g = (int)(int)FUN_004b66b0((unsigned int)(int)*(int*)(char*)(int)this, (unsigned int)a4, (unsigned int)v_l36_c);
            v_l28_g = (int)(int)FUN_00475ef0((unsigned int)a8, (unsigned int)a12, (unsigned int)v_l28_g);
            v_l332 = (int)(int)*(int*)((char*)(int)this + 4);
            v_l300_b = (int)(int)FUN_004b6bf0((unsigned int)a4, (unsigned int)v_l332, (unsigned int)v_l28_g);
            v_l317_24 = (unsigned char)0;
            v_l328_46 = v_l28_g;
            v_l324_29 = a4;
            for (; v_l324_29 != v_l332; v_l324_29 = v_l324_29 + 12, v_l328_46 = v_l328_46 + 12) {
            }
            v_l28_g = v_l300_b;
            v_l344_11 = (int)(int)((int)(int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) / 12);
            v_l340_24 = (int)(int)*(int*)(char*)(int)this;
            if (v_l340_24 != 0) {
                if ((int)*(int*)((char*)v_l340_24 - 4) != 0) {
                    v_l336_d = v_l340_24;
                    FUN_00f47380((unsigned int)v_l336_d);
                }
            }
            *(int*)(char*)(int)this = v_l36_c;
            *(int*)((char*)(int)this + 4) = v_l28_g;
            *(int*)((char*)(int)this + 8) = v_l24 * 12 + v_l36_c;
        }
    }
    return;
}
