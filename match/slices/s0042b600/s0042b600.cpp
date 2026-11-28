// 0x0042b600: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0042b4e0/s0042b4e0.cpp.

#include <string.h>
struct C_0042cbf0 { void FUN_0042cbf0(unsigned int); };
extern "C" int __cdecl FUN_0042dee0(...);
extern "C" void __cdecl FUN_0042df50(...);
extern "C" int __cdecl FUN_0042dff0(...);
extern "C" void __cdecl FUN_0042f020(...);
extern "C" void __cdecl FUN_0042f0a0(...);
extern "C" void __cdecl FUN_00f47380(...);
struct S12 { int m0; int m1; int m2; int m3; int m4; int m5; int m6; int m7; int m8; int m9; int m10; int m11; };


struct D_0042b600 { void FUN_0042b600(int a4, int a8, int a12); };
// @ 0x0042b600
void D_0042b600::FUN_0042b600(int a4, int a8, int a12)
{
    int v_l80_c;
    int v_l76_q;
    int v_l72_k;
    int v_l68_t;
    int v_l64_r;
    int v_l60_g;
    int v_l56_j[12];
    int v_l8;
    char dead_0_a;
    int v_l84;
    int v_l96;
    int v_l92_n;
    unsigned char v_l86;
    int v_l104_d;
    int v_l100;
    unsigned char v_l114_16;
    unsigned char v_l113_14;
    int v_l112_10;
    int v_l108;
    unsigned char v_l115;
    int v_l128_14;
    int v_l124_49;
    int v_l120;
    int dead_5_16[9];
    int v_l236;
    int v_l232_11;
    unsigned char v_l226_19;
    char dead_4_35;
    int dead_3[8];
    int v_l192_29;
    int dead_2_17[12];
    int v_l140_62;
    int v_l136_61;
    unsigned char v_l130_a;
    char dead_1;
    int v_l284_c;
    int v_l280_19;
    int v_l276;
    if ((unsigned int)a8 <= (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)((char*)(int)this + 4)) / 48)) {
        if ((unsigned int)a8 > (unsigned int)0) {
            ((C_0042cbf0*)(int)&v_l56_j)->FUN_0042cbf0((unsigned int)a12);
            v_l60_g = (int)(int)((int)((int)*(int*)((char*)(int)this + 4) - a4) / 48);
            v_l8 = (int)(int)*(int*)((char*)(int)this + 4);
            if ((unsigned int)a8 < (unsigned int)v_l60_g) {
                v_l112_10 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l108 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l104_d = (int)(int)((int)*(int*)((char*)(int)this + 4) - a8 * 48);
                v_l92_n = v_l112_10;
                v_l96 = v_l108;
                v_l100 = v_l104_d;
                FUN_0042f020((unsigned int)(int)&v_l84, (unsigned int)v_l100, (unsigned int)v_l96, (unsigned int)v_l92_n, (unsigned int)(int)v_l86);
                *(int*)((char*)(int)this + 4) = (int)(int)(a8 * 48 + (int)*(int*)((char*)(int)this + 4));
                v_l114_16 = (unsigned char)0;
                v_l113_14 = (unsigned char)0;
                v_l115 = (unsigned char)0;
                v_l124_49 = v_l8;
                v_l120 = v_l8 - a8 * 48;
                while (v_l120 != a4) {
                    v_l120 = v_l120 - 48;
                    v_l124_49 = v_l124_49 - 48;
                    *(S12*)v_l124_49 = *(S12*)v_l120;
                }
                v_l128_14 = a4;
                for (; v_l128_14 != a8 * 48 + a4; v_l128_14 = v_l128_14 + 48) {
                    *(S12*)v_l128_14 = *(S12*)(int)&v_l56_j;
                }
            } else {
                v_l140_62 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l136_61 = v_l140_62;
                FUN_0042f0a0((unsigned int)v_l136_61, (unsigned int)(a8 - v_l60_g), (unsigned int)(int)&v_l56_j, (unsigned int)(int)v_l130_a);
                *(int*)((char*)(int)this + 4) = (int)(int)((a8 - v_l60_g) * 48 + (int)*(int*)((char*)(int)this + 4));
                FUN_0042df50((unsigned int)a4, (unsigned int)v_l8, (unsigned int)(int)*(int*)((char*)(int)this + 4));
                *(int*)((char*)(int)this + 4) = (int)(int)(v_l60_g * 48 + (int)*(int*)((char*)(int)this + 4));
                v_l192_29 = a4;
                for (; v_l192_29 != v_l8; v_l192_29 = v_l192_29 + 48) {
                    *(S12*)v_l192_29 = *(S12*)(int)&v_l56_j;
                }
            }
        }
    } else {
        v_l72_k = (int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 48);
        v_l80_c = (int)(int)((unsigned int)v_l72_k > (unsigned int)0 ? v_l72_k << 1 : 1);
        v_l64_r = (int)(int)((unsigned int)v_l80_c > (unsigned int)(v_l72_k + a8) ? v_l80_c : v_l72_k + a8);
        v_l76_q = (int)(int)(v_l64_r != 0 ? (int)(int)FUN_0042dee0((unsigned int)((int)this + 12), (unsigned int)(v_l64_r * 48), (unsigned int)4, (unsigned int)0) : 0);
        v_l68_t = (int)(int)FUN_0042dff0((unsigned int)(int)*(int*)(char*)(int)this, (unsigned int)a4, (unsigned int)v_l76_q);
        v_l236 = v_l68_t;
        v_l232_11 = v_l236;
        FUN_0042f0a0((unsigned int)v_l232_11, (unsigned int)a8, (unsigned int)a12, (unsigned int)(int)v_l226_19);
        v_l68_t = (int)(int)FUN_0042dff0((unsigned int)a4, (unsigned int)(int)*(int*)((char*)(int)this + 4), (unsigned int)(a8 * 48 + v_l68_t));
        v_l284_c = (int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) / 48);
        v_l280_19 = (int)(int)*(int*)(char*)(int)this;
        if (v_l280_19 != 0) {
            if (v_l280_19 != (int)*(int*)((char*)(int)this + 16)) {
                v_l276 = v_l280_19;
                FUN_00f47380((unsigned int)v_l276);
            }
        }
        *(int*)(char*)(int)this = v_l76_q;
        *(int*)((char*)(int)this + 4) = v_l68_t;
        *(int*)((char*)(int)this + 8) = v_l64_r * 48 + v_l76_q;
    }
    return;
}
