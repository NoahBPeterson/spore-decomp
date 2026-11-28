// 0x004298f0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004298f0/s004298f0.cpp, src/game/SPEngine/SPGraphicsModelUtilities.cpp.

struct C_0040ce80 { void FUN_0040ce80(unsigned int); };
extern "C" int __cdecl FUN_00429ce0(...);
extern "C" void __cdecl FUN_00429d80(...);
extern "C" int __cdecl FUN_0042dee0(...);
extern "C" void __cdecl FUN_0042e510(...);
extern "C" void __cdecl FUN_0042e680(...);
struct C_00537dc0 { int FUN_00537dc0(unsigned int); };
extern "C" void __cdecl FUN_00f47380(...);


struct D_004298f0 { void FUN_004298f0(int a4, int a8, int a12); };
// @ 0x004298f0
// @ 0x004298f0
void D_004298f0::FUN_004298f0(int a4, int a8, int a12)
{
    int v_l80_c;
    int v_l76_q;
    int v_l72_k;
    int v_l68_t;
    int v_l64_r[14];
    int v_l8;
    int v_l88_12;
    int v_l84;
    int v_l112_d;
    int v_l108_14;
    int v_l104_a;
    unsigned char v_l98_107;
    char dead_0_11;
    int v_l96[2];
    unsigned char v_l125_11;
    int v_l124_c;
    int v_l120_21;
    int v_l116;
    unsigned char v_l127_19;
    unsigned char v_l126;
    int v_l136_13;
    int v_l132;
    int v_l140;
    unsigned char v_l238_11;
    char dead_4_35;
    int dead_3[8];
    int v_l204_12;
    int dead_2_17[12];
    int v_l152_13;
    int v_l148_20;
    unsigned char v_l142;
    char dead_1;
    int v_l296_32;
    int v_l292_a;
    int v_l288_20;
    int dead_5_26[9];
    int v_l248_36;
    int v_l244;
    if ((unsigned int)a8 <= (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)((char*)(int)this + 4)) / 56)) {
        if ((unsigned int)a8 > (unsigned int)0) {
            ((C_0040ce80*)(int)&v_l64_r)->FUN_0040ce80((unsigned int)a12);
            v_l68_t = (int)(int)((int)((int)*(int*)((char*)(int)this + 4) - a4) / 56);
            v_l8 = (int)(int)*(int*)((char*)(int)this + 4);
            if ((unsigned int)a8 < (unsigned int)v_l68_t) {
                v_l124_c = (int)(int)*(int*)((char*)(int)this + 4);
                v_l120_21 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l116 = (int)(int)((int)*(int*)((char*)(int)this + 4) - a8 * 56);
                v_l104_a = v_l124_c;
                v_l108_14 = v_l120_21;
                v_l112_d = v_l116;
                FUN_00429d80((unsigned int)(int)&v_l96, (unsigned int)v_l112_d, (unsigned int)v_l108_14, (unsigned int)v_l104_a, (unsigned int)(int)v_l98_107);
                *(int*)((char*)(int)this + 4) = (int)(int)(a8 * 56 + (int)*(int*)((char*)(int)this + 4));
                v_l126 = (unsigned char)0;
                v_l125_11 = (unsigned char)0;
                v_l127_19 = (unsigned char)0;
                v_l136_13 = v_l8;
                v_l132 = v_l8 - a8 * 56;
                while (v_l132 != a4) {
                    v_l132 = v_l132 - 56;
                    v_l136_13 = v_l136_13 - 56;
                    ((C_00537dc0*)v_l136_13)->FUN_00537dc0((unsigned int)v_l132);
                }
                v_l140 = a4;
                for (; v_l140 != a8 * 56 + a4; v_l140 = v_l140 + 56) {
                    ((C_00537dc0*)v_l140)->FUN_00537dc0((unsigned int)(int)&v_l64_r);
                }
            } else {
                v_l152_13 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l148_20 = v_l152_13;
                FUN_0042e680((unsigned int)v_l148_20, (unsigned int)(a8 - v_l68_t), (unsigned int)(int)&v_l64_r, (unsigned int)(int)v_l142);
                *(int*)((char*)(int)this + 4) = (int)(int)((a8 - v_l68_t) * 56 + (int)*(int*)((char*)(int)this + 4));
                FUN_0042e510((unsigned int)a4, (unsigned int)v_l8, (unsigned int)(int)*(int*)((char*)(int)this + 4));
                *(int*)((char*)(int)this + 4) = (int)(int)(v_l68_t * 56 + (int)*(int*)((char*)(int)this + 4));
                v_l204_12 = a4;
                for (; v_l204_12 != v_l8; v_l204_12 = v_l204_12 + 56) {
                    ((C_00537dc0*)v_l204_12)->FUN_00537dc0((unsigned int)(int)&v_l64_r);
                }
            }
        }
    } else {
        v_l80_c = (int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 56);
        v_l88_12 = (int)(int)((unsigned int)v_l80_c > (unsigned int)0 ? v_l80_c << 1 : 1);
        v_l72_k = (int)(int)((unsigned int)v_l88_12 > (unsigned int)(v_l80_c + a8) ? v_l88_12 : v_l80_c + a8);
        v_l84 = (int)(int)(v_l72_k != 0 ? (int)(int)FUN_0042dee0((unsigned int)((int)this + 12), (unsigned int)(v_l72_k * 56), (unsigned int)4, (unsigned int)0) : 0);
        v_l76_q = (int)(int)FUN_00429ce0((unsigned int)(int)*(int*)(char*)(int)this, (unsigned int)a4, (unsigned int)v_l84);
        v_l248_36 = v_l76_q;
        v_l244 = v_l248_36;
        FUN_0042e680((unsigned int)v_l244, (unsigned int)a8, (unsigned int)a12, (unsigned int)(int)v_l238_11);
        v_l76_q = (int)(int)FUN_00429ce0((unsigned int)a4, (unsigned int)(int)*(int*)((char*)(int)this + 4), (unsigned int)(a8 * 56 + v_l76_q));
        v_l296_32 = (int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) / 56);
        v_l292_a = (int)(int)*(int*)(char*)(int)this;
        if (v_l292_a != 0) {
            if ((int)*(int*)((char*)v_l292_a - 4) != 0) {
                v_l288_20 = v_l292_a;
                FUN_00f47380((unsigned int)v_l288_20);
            }
        }
        *(int*)(char*)(int)this = v_l84;
        *(int*)((char*)(int)this + 4) = v_l76_q;
        *(int*)((char*)(int)this + 8) = v_l72_k * 56 + v_l84;
    }
    return;
}
