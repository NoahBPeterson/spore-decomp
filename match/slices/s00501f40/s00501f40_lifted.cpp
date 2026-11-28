// 0x00501f40: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00501f40/s00501f40.cpp.

struct C_004098a0 { void FUN_004098a0(unsigned int); };
struct C_0041d140 { void FUN_0041d140(unsigned int); };
extern "C" int __cdecl FUN_0042dee0(...);
struct C_004c0b80 { int FUN_004c0b80(); };
struct C_005030e0 { void FUN_005030e0(unsigned int); };
extern "C" void __cdecl FUN_00503180(...);
extern "C" int __cdecl FUN_005031d0(...);
extern "C" void __cdecl FUN_00503670(...);
extern "C" void __cdecl FUN_005036f0(...);
extern "C" int __cdecl FUN_00503b90(...);
extern "C" void __cdecl FUN_00503be0(...);
extern "C" void __cdecl FUN_00f47380(...);
struct S3 { int m0; int m1; int m2; };


struct D_00501f40 { void FUN_00501f40(int a4, int a8, int a12); };
// @ 0x00501f40
// @ 0x00501f40
void D_00501f40::FUN_00501f40(int a4, int a8, int a12)
{
    int v_l80_c;
    int dead_0_15[2];
    int v_l68_t[14];
    int v_l12_40;
    int v_l8;
    int v_l92_k;
    int v_l88_12;
    int v_l84;
    char dead_3_d;
    int v_l152_a;
    int dead_2_16[3];
    int v_l136;
    int v_l132_21;
    int v_l128_a;
    int v_l124_33;
    int v_l120_c;
    int v_l116_13;
    unsigned char v_l110_a;
    char dead_1_32;
    int v_l108_14;
    int v_l104_a;
    int v_l100_34;
    int v_l96;
    int v_l168_d;
    int v_l164_29;
    int v_l160_38;
    unsigned char v_l154;
    int dead_5_b[8];
    int v_l208_13;
    int v_l204_21;
    int v_l200_26;
    int v_l196_38;
    int v_l192_16;
    int v_l188_b;
    int v_l184_31;
    int v_l180_20;
    int v_l176;
    unsigned char v_l170_35;
    char dead_4;
    unsigned char v_l257_28;
    int v_l256_d;
    int v_l252_21;
    int v_l248_31;
    unsigned char v_l242;
    char dead_6;
    char dead_8_39;
    char dead_7;
    int v_l296;
    int v_l292_14;
    int dead_14_g[5];
    char dead_13_o;
    char dead_12_11;
    char dead_11_k;
    unsigned char v_l265;
    int dead_10_j;
    char dead_9;
    int v_l300;
    int v_l308_35;
    int v_l304;
    if ((unsigned int)a8 <= (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)((char*)(int)this + 4)) / 72)) {
        if ((unsigned int)a8 > (unsigned int)0) {
            ((C_004098a0*)(int)&v_l80_c)->FUN_004098a0((unsigned int)a12);
            ((C_005030e0*)(int)&v_l68_t)->FUN_005030e0((unsigned int)(a12 + 12));
            v_l12_40 = (int)(int)*(int*)((char*)a12 + 68);
            v_l84 = (int)(int)((int)((int)*(int*)((char*)(int)this + 4) - a4) / 72);
            v_l8 = (int)(int)*(int*)((char*)(int)this + 4);
            if ((unsigned int)a8 < (unsigned int)v_l84) {
                v_l136 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l132_21 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l128_a = (int)(int)((int)*(int*)((char*)(int)this + 4) - a8 * 72);
                v_l116_13 = v_l136;
                v_l120_c = v_l132_21;
                v_l124_33 = v_l128_a;
                FUN_00503670((unsigned int)(int)&v_l108_14, (unsigned int)v_l124_33, (unsigned int)v_l120_c, (unsigned int)v_l116_13, (unsigned int)(int)v_l110_a);
                *(int*)((char*)(int)this + 4) = (int)(int)(a8 * 72 + (int)*(int*)((char*)(int)this + 4));
                FUN_00503180((unsigned int)a4, (unsigned int)(v_l8 - a8 * 72), (unsigned int)v_l8);
                v_l152_a = a4;
                for (; v_l152_a != a8 * 72 + a4; v_l152_a = v_l152_a + 72) {
                    *(S3*)v_l152_a = *(S3*)&v_l80_c;
                    ((C_0041d140*)(v_l152_a + 12))->FUN_0041d140((unsigned int)(int)&v_l68_t);
                    *(int*)((char*)v_l152_a + 68) = v_l12_40;
                }
            } else {
                v_l164_29 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l160_38 = v_l164_29;
                FUN_005036f0((unsigned int)v_l160_38, (unsigned int)(a8 - v_l84), (unsigned int)(int)&v_l80_c, (unsigned int)(int)v_l154);
                *(int*)((char*)(int)this + 4) = (int)(int)((a8 - v_l84) * 72 + (int)*(int*)((char*)(int)this + 4));
                v_l196_38 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l192_16 = v_l8;
                v_l188_b = a4;
                v_l176 = v_l196_38;
                v_l180_20 = v_l192_16;
                v_l184_31 = v_l188_b;
                FUN_00503670((unsigned int)(int)&v_l168_d, (unsigned int)v_l184_31, (unsigned int)v_l180_20, (unsigned int)v_l176, (unsigned int)(int)v_l170_35);
                *(int*)((char*)(int)this + 4) = (int)(int)(v_l84 * 72 + (int)*(int*)((char*)(int)this + 4));
                v_l200_26 = a4;
                for (; v_l200_26 != v_l8; v_l200_26 = v_l200_26 + 72) {
                    *(S3*)v_l200_26 = *(S3*)&v_l80_c;
                    ((C_0041d140*)(v_l200_26 + 12))->FUN_0041d140((unsigned int)(int)&v_l68_t);
                    *(int*)((char*)v_l200_26 + 68) = v_l12_40;
                }
            }
            v_l208_13 = (int)&v_l68_t;
            v_l204_21 = (int)(int)*(int*)(char*)v_l208_13;
            for (; (unsigned int)v_l204_21 < (unsigned int)*(int*)((char*)v_l208_13 + 4); v_l204_21 = v_l204_21 + 4) {
            }
            ((C_004c0b80*)v_l208_13)->FUN_004c0b80();
        }
    } else {
        v_l96 = (int)(int)((int)(int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 72);
        v_l104_a = (int)(int)((unsigned int)v_l96 > (unsigned int)0 ? v_l96 << 1 : 1);
        v_l88_12 = (int)(int)((unsigned int)v_l104_a > (unsigned int)(v_l96 + a8) ? v_l104_a : v_l96 + a8);
        v_l100_34 = (int)(int)(v_l88_12 != 0 ? (int)(int)FUN_0042dee0((unsigned int)((int)this + 12), (unsigned int)(v_l88_12 * 72), (unsigned int)4, (unsigned int)0) : 0);
        v_l92_k = (int)(int)FUN_005031d0((unsigned int)(int)*(int*)(char*)(int)this, (unsigned int)a4, (unsigned int)v_l100_34);
        v_l252_21 = v_l92_k;
        v_l248_31 = v_l252_21;
        FUN_005036f0((unsigned int)v_l248_31, (unsigned int)a8, (unsigned int)a12, (unsigned int)(int)v_l242);
        v_l296 = a8 * 72 + v_l92_k;
        v_l292_14 = (int)(int)*(int*)((char*)(int)this + 4);
        v_l257_28 = (unsigned char)0;
        v_l256_d = (int)(int)FUN_00503b90((unsigned int)a4, (unsigned int)v_l292_14, (unsigned int)v_l296);
        v_l265 = (unsigned char)0;
        FUN_00503be0((unsigned int)a4, (unsigned int)v_l292_14, (unsigned int)v_l296);
        v_l92_k = v_l256_d;
        v_l308_35 = (int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) / 72);
        v_l304 = (int)(int)*(int*)(char*)(int)this;
        if (v_l304 != 0) {
            if ((int)*(int*)((char*)v_l304 - 4) != 0) {
                v_l300 = v_l304;
                FUN_00f47380((unsigned int)v_l300);
            }
        }
        *(int*)(char*)(int)this = v_l100_34;
        *(int*)((char*)(int)this + 4) = v_l92_k;
        *(int*)((char*)(int)this + 8) = v_l88_12 * 72 + v_l100_34;
    }
    return;
}
