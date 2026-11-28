// 0x004cf2c0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/SPEditorSpeciesManager.cpp, match/slices/s004ce310/s004ce310.cpp.

struct C_004098a0 { void FUN_004098a0(unsigned int); };
struct C_0041d140 { void FUN_0041d140(unsigned int); };
extern "C" int __cdecl FUN_0042dee0(...);
struct C_004c0b80 { int FUN_004c0b80(); };
struct C_004d08c0 { void FUN_004d08c0(unsigned int); };
extern "C" void __cdecl FUN_004d0a00(...);
extern "C" int __cdecl FUN_004d0a40(...);
extern "C" void __cdecl FUN_004d0c90(...);
extern "C" void __cdecl FUN_004d0d40(...);
struct C_004d1030 { void FUN_004d1030(unsigned int); };
extern "C" int __cdecl FUN_004d10b0(...);
extern "C" void __cdecl FUN_004d1130(...);
extern "C" void __cdecl FUN_00f47380(...);
struct S3 { int m0; int m1; int m2; };


struct D_004cf2c0 { void FUN_004cf2c0(int a4, int a8, int a12); };
// @ 0x004cf2c0
// @ 0x004cf2c0
void D_004cf2c0::FUN_004cf2c0(int a4, int a8, int a12)
{
    int v_l8;
    unsigned char v_l90_a;
    char dead_0_a;
    int v_l88_12;
    int v_l84;
    int v_l80_20;
    int v_l76_107;
    int v_l72_l;
    int v_l68_i;
    int v_l64_z;
    int v_l60_f[3];
    int v_l48[10];
    unsigned char v_l117;
    int v_l116_13;
    int v_l112_d;
    int v_l108_14;
    int v_l104_a;
    int v_l100_34;
    int v_l96;
    int v_l292;
    int v_l288;
    unsigned char v_l282_c;
    char dead_7_d;
    int dead_6_15[8];
    int v_l248_35;
    int dead_5_22[3];
    int v_l232_10;
    int v_l228;
    int dead_4_10;
    int dead_3_16[15];
    int v_l160_38;
    int v_l156_31;
    unsigned char v_l150;
    char dead_2_b;
    int v_l148_47;
    int dead_1_b[4];
    int v_l128_22;
    int v_l124_c;
    unsigned char v_l119_c;
    unsigned char v_l118;
    char dead_10_j;
    char dead_9;
    char dead_8_a;
    unsigned char v_l297_24;
    int v_l296;
    char dead_13_b;
    char dead_12_h;
    unsigned char v_l305_15;
    int dead_11;
    int dead_15_i[5];
    char dead_14;
    int v_l348_17;
    int v_l344_11;
    int v_l340_24;
    int v_l336_d;
    int v_l332;
    if ((unsigned int)a8 <= (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)((char*)(int)this + 4)) / 52)) {
        if ((unsigned int)a8 > (unsigned int)0) {
            ((C_004098a0*)(int)&v_l60_f)->FUN_004098a0((unsigned int)a12);
            ((C_004d08c0*)(int)&v_l48)->FUN_004d08c0((unsigned int)(a12 + 12));
            v_l64_z = (int)(int)((int)((int)*(int*)((char*)(int)this + 4) - a4) / 52);
            v_l8 = (int)(int)*(int*)((char*)(int)this + 4);
            if ((unsigned int)a8 < (unsigned int)v_l64_z) {
                v_l116_13 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l112_d = (int)(int)*(int*)((char*)(int)this + 4);
                v_l108_14 = (int)(int)((int)*(int*)((char*)(int)this + 4) - a8 * 52);
                v_l96 = v_l116_13;
                v_l100_34 = v_l112_d;
                v_l104_a = v_l108_14;
                FUN_004d0c90((unsigned int)(int)&v_l88_12, (unsigned int)v_l104_a, (unsigned int)v_l100_34, (unsigned int)v_l96, (unsigned int)(int)v_l90_a);
                *(int*)((char*)(int)this + 4) = (int)(int)(a8 * 52 + (int)*(int*)((char*)(int)this + 4));
                v_l118 = (unsigned char)0;
                v_l117 = (unsigned char)0;
                v_l119_c = (unsigned char)0;
                v_l128_22 = v_l8;
                v_l124_c = v_l8 - a8 * 52;
                while (v_l124_c != a4) {
                    v_l124_c = v_l124_c - 52;
                    v_l128_22 = v_l128_22 - 52;
                    *(S3*)v_l128_22 = *(S3*)v_l124_c;
                    ((C_0041d140*)(v_l128_22 + 12))->FUN_0041d140((unsigned int)(v_l124_c + 12));
                }
                v_l148_47 = a4;
                for (; v_l148_47 != a8 * 52 + a4; v_l148_47 = v_l148_47 + 52) {
                    ((C_004d1030*)v_l148_47)->FUN_004d1030((unsigned int)(int)&v_l60_f);
                }
            } else {
                v_l160_38 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l156_31 = v_l160_38;
                FUN_004d0d40((unsigned int)v_l156_31, (unsigned int)(a8 - v_l64_z), (unsigned int)(int)&v_l60_f, (unsigned int)(int)v_l150);
                *(int*)((char*)(int)this + 4) = (int)(int)((a8 - v_l64_z) * 52 + (int)*(int*)((char*)(int)this + 4));
                FUN_004d0a00((unsigned int)a4, (unsigned int)v_l8, (unsigned int)(int)*(int*)((char*)(int)this + 4));
                *(int*)((char*)(int)this + 4) = (int)(int)(v_l64_z * 52 + (int)*(int*)((char*)(int)this + 4));
                v_l228 = a4;
                for (; v_l228 != v_l8; v_l228 = v_l228 + 52) {
                    ((C_004d1030*)v_l228)->FUN_004d1030((unsigned int)(int)&v_l60_f);
                }
            }
            v_l248_35 = (int)&v_l48;
            v_l232_10 = (int)(int)*(int*)(char*)v_l248_35;
            for (; (unsigned int)v_l232_10 < (unsigned int)*(int*)((char*)v_l248_35 + 4); v_l232_10 = v_l232_10 + 4) {
            }
            ((C_004c0b80*)v_l248_35)->FUN_004c0b80();
        }
    } else {
        v_l76_107 = (int)(int)((int)(int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 52);
        v_l84 = (int)(int)((unsigned int)v_l76_107 > (unsigned int)0 ? v_l76_107 << 1 : 1);
        v_l68_i = (int)(int)((unsigned int)v_l84 > (unsigned int)(v_l76_107 + a8) ? v_l84 : v_l76_107 + a8);
        v_l80_20 = (int)(int)(v_l68_i != 0 ? (int)(int)FUN_0042dee0((unsigned int)((int)this + 12), (unsigned int)(v_l68_i * 52), (unsigned int)4, (unsigned int)0) : 0);
        v_l72_l = (int)(int)FUN_004d0a40((unsigned int)(int)*(int*)(char*)(int)this, (unsigned int)a4, (unsigned int)v_l80_20);
        v_l292 = v_l72_l;
        v_l288 = v_l292;
        FUN_004d0d40((unsigned int)v_l288, (unsigned int)a8, (unsigned int)a12, (unsigned int)(int)v_l282_c);
        v_l336_d = a8 * 52 + v_l72_l;
        v_l332 = (int)(int)*(int*)((char*)(int)this + 4);
        v_l297_24 = (unsigned char)0;
        v_l296 = (int)(int)FUN_004d10b0((unsigned int)a4, (unsigned int)v_l332, (unsigned int)v_l336_d);
        v_l305_15 = (unsigned char)0;
        FUN_004d1130((unsigned int)a4, (unsigned int)v_l332, (unsigned int)v_l336_d);
        v_l72_l = v_l296;
        v_l348_17 = (int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) / 52);
        v_l344_11 = (int)(int)*(int*)(char*)(int)this;
        if (v_l344_11 != 0) {
            if ((int)*(int*)((char*)v_l344_11 - 4) != 0) {
                v_l340_24 = v_l344_11;
                FUN_00f47380((unsigned int)v_l340_24);
            }
        }
        *(int*)(char*)(int)this = v_l80_20;
        *(int*)((char*)(int)this + 4) = v_l72_l;
        *(int*)((char*)(int)this + 8) = v_l68_i * 52 + v_l80_20;
    }
    return;
}
