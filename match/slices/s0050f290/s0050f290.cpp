// 0x0050f290: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPStarManager.cpp, match/slices/s0050e850/s0050e850.cpp.

struct C_004098a0 { void FUN_004098a0(unsigned int); };
extern "C" int __cdecl FUN_00424340(...);
extern "C" int __cdecl FUN_0042dee0(...);
extern "C" void __cdecl FUN_004b2400(...);
extern "C" void __cdecl FUN_0050e7b0(...);
extern "C" void __cdecl FUN_00511990(...);
extern "C" int __cdecl FUN_00512000(...);
extern "C" void __cdecl FUN_00f47380(...);
struct S6 { int m0; int m1; int m2; int m3; int m4; int m5; };


struct D_0050f290 { void FUN_0050f290(int a4, int a8, int a12); };
// @ 0x0050f290
void D_0050f290::FUN_0050f290(int a4, int a8, int a12)
{
    int dead_0_15[2];
    int v_l8;
    int v_l92_k;
    int v_l88_12;
    int v_l84;
    int v_l80_20;
    int v_l76_107;
    int v_l72_l;
    unsigned char v_l66_z;
    char dead_2_66;
    int v_l64_z;
    int v_l60_f;
    int v_l56_a;
    int v_l52_w;
    int v_l48;
    int v_l44_b;
    int v_l40_i;
    int v_l36_42;
    int v_l32_j;
    int dead_1_12[2];
    int v_l20;
    unsigned char v_l110_a;
    char dead_3_d;
    int v_l108_14;
    int v_l104_a;
    int v_l100_34;
    unsigned char v_l95_o;
    unsigned char v_l94;
    unsigned char v_l93;
    int v_l120_21;
    int v_l116;
    int dead_5_b[8];
    int v_l172_14;
    int dead_4[12];
    unsigned char v_l221_31;
    int v_l220_57;
    int v_l216_a;
    int v_l212_c;
    unsigned char v_l206_29;
    char dead_6;
    char dead_8_39;
    char dead_7;
    int v_l248;
    int v_l244_12;
    int v_l240_25;
    int v_l236_c;
    unsigned char v_l229_b;
    int dead_10_j;
    char dead_9;
    int v_l260;
    int v_l256;
    int v_l252;
    if ((unsigned int)a8 <= (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)((char*)(int)this + 4)) / 24)) {
        if ((unsigned int)a8 > (unsigned int)0) {
            ((C_004098a0*)(int)&v_l32_j)->FUN_004098a0((unsigned int)a12);
            v_l60_f = (int)&v_l20;
            ((C_004098a0*)v_l60_f)->FUN_004098a0((unsigned int)(a12 + 12));
            v_l36_42 = (int)(int)((int)((int)*(int*)((char*)(int)this + 4) - a4) / 24);
            v_l8 = (int)(int)*(int*)((char*)(int)this + 4);
            if ((unsigned int)a8 < (unsigned int)v_l36_42) {
                v_l92_k = (int)(int)*(int*)((char*)(int)this + 4);
                v_l88_12 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l84 = (int)(int)((int)*(int*)((char*)(int)this + 4) - a8 * 24);
                v_l72_l = v_l92_k;
                v_l76_107 = v_l88_12;
                v_l80_20 = v_l84;
                FUN_004b2400((unsigned int)(int)&v_l64_z, (unsigned int)v_l80_20, (unsigned int)v_l76_107, (unsigned int)v_l72_l, (unsigned int)(int)v_l66_z);
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
                    *(S6*)v_l108_14 = *(S6*)&v_l32_j;
                }
            } else {
                v_l120_21 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l116 = v_l120_21;
                FUN_00511990((unsigned int)v_l116, (unsigned int)(a8 - v_l36_42), (unsigned int)(int)&v_l32_j, (unsigned int)(int)v_l110_a);
                *(int*)((char*)(int)this + 4) = (int)(int)((a8 - v_l36_42) * 24 + (int)*(int*)((char*)(int)this + 4));
                FUN_0050e7b0((unsigned int)a4, (unsigned int)v_l8, (unsigned int)(int)*(int*)((char*)(int)this + 4));
                *(int*)((char*)(int)this + 4) = (int)(int)(v_l36_42 * 24 + (int)*(int*)((char*)(int)this + 4));
                v_l172_14 = a4;
                for (; v_l172_14 != v_l8; v_l172_14 = v_l172_14 + 24) {
                    *(S6*)v_l172_14 = *(S6*)&v_l32_j;
                }
            }
        }
    } else {
        v_l48 = (int)(int)((int)(int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 24);
        v_l56_a = (int)(int)((unsigned int)v_l48 > (unsigned int)0 ? v_l48 << 1 : 1);
        v_l40_i = (int)(int)((unsigned int)v_l56_a > (unsigned int)(v_l48 + a8) ? v_l56_a : v_l48 + a8);
        v_l52_w = (int)(int)(v_l40_i != 0 ? (int)(int)FUN_0042dee0((unsigned int)((int)this + 12), (unsigned int)(v_l40_i * 24), (unsigned int)4, (unsigned int)0) : 0);
        v_l44_b = (int)(int)FUN_00424340((unsigned int)(int)*(int*)(char*)(int)this, (unsigned int)a4, (unsigned int)v_l52_w);
        v_l216_a = v_l44_b;
        v_l212_c = v_l216_a;
        FUN_00511990((unsigned int)v_l212_c, (unsigned int)a8, (unsigned int)a12, (unsigned int)(int)v_l206_29);
        v_l248 = a8 * 24 + v_l44_b;
        v_l244_12 = (int)(int)*(int*)((char*)(int)this + 4);
        v_l221_31 = (unsigned char)0;
        v_l220_57 = (int)(int)FUN_00512000((unsigned int)a4, (unsigned int)v_l244_12, (unsigned int)v_l248);
        v_l229_b = (unsigned char)0;
        v_l240_25 = v_l248;
        v_l236_c = a4;
        for (; v_l236_c != v_l244_12; v_l236_c = v_l236_c + 24, v_l240_25 = v_l240_25 + 24) {
        }
        v_l44_b = v_l220_57;
        v_l260 = (int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) / 24);
        v_l256 = (int)(int)*(int*)(char*)(int)this;
        if (v_l256 != 0) {
            if ((int)*(int*)((char*)v_l256 - 4) != 0) {
                v_l252 = v_l256;
                FUN_00f47380((unsigned int)v_l252);
            }
        }
        *(int*)(char*)(int)this = v_l52_w;
        *(int*)((char*)(int)this + 4) = v_l44_b;
        *(int*)((char*)(int)this + 8) = v_l40_i * 24 + v_l52_w;
    }
    return;
}
