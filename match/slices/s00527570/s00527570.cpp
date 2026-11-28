// 0x00527570: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/_at_00520000.cpp, match/slices/s005266f0/s005266f0.cpp.

extern "C" int __cdecl FUN_0042dee0(...);
struct C_005218e0 { void FUN_005218e0(unsigned int); };
struct C_00526660 { int FUN_00526660(); };
struct C_00527440 { void FUN_00527440(unsigned int); };
extern "C" int __cdecl FUN_005279c0(...);
extern "C" void __cdecl FUN_005287a0(...);
extern "C" void __cdecl FUN_00528820(...);
extern "C" void __cdecl FUN_00f47380(...);


struct D_00527570 { void FUN_00527570(int a4, int a8, int a12); };
// @ 0x00527570
// @ 0x00527570
void D_00527570::FUN_00527570(int a4, int a8, int a12)
{
    int v_l80_c;
    int v_l76_q;
    int v_l72_k;
    int v_l68_t;
    int v_l64_r[14];
    int v_l8;
    int v_l88_12;
    int v_l84;
    int v_l172;
    int v_l168_17;
    int v_l164_21;
    unsigned char v_l158_24;
    char dead_2_16;
    int v_l156_a;
    int v_l152_a;
    int v_l148_13;
    unsigned char v_l142_21;
    char dead_1_32;
    int v_l140_d;
    int v_l136;
    int v_l132_21;
    unsigned char v_l127_d;
    unsigned char v_l126_29;
    unsigned char v_l125_c;
    int v_l124_33;
    int v_l120_c;
    int v_l116_13;
    int v_l112_d;
    int v_l108_14;
    int v_l104_a;
    unsigned char v_l98_107;
    char dead_0_11;
    int v_l96[2];
    char dead_4;
    int dead_3_46[13];
    int v_l188_b;
    int v_l184_31;
    int v_l180_20;
    int v_l176;
    unsigned char v_l242;
    int v_l252_b;
    int v_l248;
    int dead_5[11];
    int v_l300;
    int v_l308_35;
    int v_l304;
    if ((unsigned int)a8 <= (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)((char*)(int)this + 4)) / 56)) {
        if ((unsigned int)a8 > (unsigned int)0) {
            ((C_00527440*)(int)&v_l64_r)->FUN_00527440((unsigned int)a12);
            v_l68_t = (int)(int)((int)((int)*(int*)((char*)(int)this + 4) - a4) / 56);
            v_l8 = (int)(int)*(int*)((char*)(int)this + 4);
            if ((unsigned int)a8 < (unsigned int)v_l68_t) {
                v_l124_33 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l120_c = (int)(int)*(int*)((char*)(int)this + 4);
                v_l116_13 = (int)(int)((int)*(int*)((char*)(int)this + 4) - a8 * 56);
                v_l104_a = v_l124_33;
                v_l108_14 = v_l120_c;
                v_l112_d = v_l116_13;
                FUN_005287a0((unsigned int)(int)&v_l96, (unsigned int)v_l112_d, (unsigned int)v_l108_14, (unsigned int)v_l104_a, (unsigned int)(int)v_l98_107);
                *(int*)((char*)(int)this + 4) = (int)(int)(a8 * 56 + (int)*(int*)((char*)(int)this + 4));
                v_l126_29 = (unsigned char)0;
                v_l125_c = (unsigned char)0;
                v_l127_d = (unsigned char)0;
                v_l136 = v_l8;
                v_l132_21 = v_l8 - a8 * 56;
                while (v_l132_21 != a4) {
                    v_l132_21 = v_l132_21 - 56;
                    v_l136 = v_l136 - 56;
                    ((C_005218e0*)v_l136)->FUN_005218e0((unsigned int)v_l132_21);
                }
                v_l140_d = a4;
                for (; v_l140_d != a8 * 56 + a4; v_l140_d = v_l140_d + 56) {
                    ((C_005218e0*)v_l140_d)->FUN_005218e0((unsigned int)(int)&v_l64_r);
                }
            } else {
                v_l152_a = (int)(int)*(int*)((char*)(int)this + 4);
                v_l148_13 = v_l152_a;
                FUN_00528820((unsigned int)v_l148_13, (unsigned int)(a8 - v_l68_t), (unsigned int)(int)&v_l64_r, (unsigned int)(int)v_l142_21);
                *(int*)((char*)(int)this + 4) = (int)(int)((a8 - v_l68_t) * 56 + (int)*(int*)((char*)(int)this + 4));
                v_l184_31 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l180_20 = v_l8;
                v_l176 = a4;
                v_l164_21 = v_l184_31;
                v_l168_17 = v_l180_20;
                v_l172 = v_l176;
                FUN_005287a0((unsigned int)(int)&v_l156_a, (unsigned int)v_l172, (unsigned int)v_l168_17, (unsigned int)v_l164_21, (unsigned int)(int)v_l158_24);
                *(int*)((char*)(int)this + 4) = (int)(int)(v_l68_t * 56 + (int)*(int*)((char*)(int)this + 4));
                v_l188_b = a4;
                for (; v_l188_b != v_l8; v_l188_b = v_l188_b + 56) {
                    ((C_005218e0*)v_l188_b)->FUN_005218e0((unsigned int)(int)&v_l64_r);
                }
            }
            ((C_00526660*)(int)&v_l64_r)->FUN_00526660();
        }
    } else {
        v_l80_c = (int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 56);
        v_l88_12 = (int)(int)((unsigned int)v_l80_c > (unsigned int)0 ? v_l80_c << 1 : 1);
        v_l72_k = (int)(int)((unsigned int)v_l88_12 > (unsigned int)(v_l80_c + a8) ? v_l88_12 : v_l80_c + a8);
        v_l84 = (int)(int)(v_l72_k != 0 ? (int)(int)FUN_0042dee0((unsigned int)((int)this + 12), (unsigned int)(v_l72_k * 56), (unsigned int)0, (unsigned int)0) : 0);
        v_l76_q = (int)(int)FUN_005279c0((unsigned int)(int)*(int*)(char*)(int)this, (unsigned int)a4, (unsigned int)v_l84);
        v_l252_b = v_l76_q;
        v_l248 = v_l252_b;
        FUN_00528820((unsigned int)v_l248, (unsigned int)a8, (unsigned int)a12, (unsigned int)(int)v_l242);
        v_l76_q = (int)(int)FUN_005279c0((unsigned int)a4, (unsigned int)(int)*(int*)((char*)(int)this + 4), (unsigned int)(a8 * 56 + v_l76_q));
        v_l308_35 = (int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) / 56);
        v_l304 = (int)(int)*(int*)(char*)(int)this;
        if (v_l304 != 0) {
            if ((int)*(int*)((char*)v_l304 - 4) != 0) {
                v_l300 = v_l304;
                FUN_00f47380((unsigned int)v_l300);
            }
        }
        *(int*)(char*)(int)this = v_l84;
        *(int*)((char*)(int)this + 4) = v_l76_q;
        *(int*)((char*)(int)this + 8) = v_l72_k * 56 + v_l84;
    }
    return;
}
