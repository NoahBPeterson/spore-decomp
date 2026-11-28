// 0x00549940: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00548d90/s00548d90.cpp.

struct C_005477a0 { void FUN_005477a0(); };
struct C_00548e70 { void FUN_00548e70(unsigned int); };
extern "C" void __cdecl FUN_0054a4d0(...);
struct C_0054a570 { int FUN_0054a570(unsigned int, unsigned int, unsigned int); };
extern "C" void __cdecl FUN_00f47380(...);
__forceinline void il2c_d_FUN_00f47380(int p, int fl) { if (fl & 1) FUN_00f47380((unsigned int)(p)); }


struct D_00549940 { int FUN_00549940(int a4); };
// @ 0x00549940
// @ 0x00549940
int D_00549940::FUN_00549940(int a4)
{
    int v_l80_c;
    int v_l76_q;
    int v_l72_k;
    int dead_0_15[13];
    int v_l16_i;
    int v_l12_40;
    int v_l8;
    int v_l88_12;
    int v_l84;
    unsigned char v_l89;
    char dead_1_c;
    unsigned char v_l91_h;
    unsigned char v_l90;
    int v_l116_d;
    int v_l112_79;
    int v_l108_d;
    int v_l104;
    int dead_2[2];
    int v_l120;
    int v_l236;
    int v_l232_11;
    int dead_6_10[7];
    int v_l200;
    int v_l196_62;
    int v_l192_29;
    int v_l188;
    int v_l184_21;
    int dead_5_16[2];
    char dead_4_35;
    unsigned char v_l171_c;
    unsigned char v_l170_14;
    unsigned char v_l169_c;
    int dead_3[12];
    if (a4 != (int)this) {
        v_l8 = (int)(int)((int)((int)*(int*)((char*)a4 + 4) - (int)*(int*)(char*)a4) / 52);
        if ((unsigned int)v_l8 > (unsigned int)(int)((int)(int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) / 52)) {
            v_l12_40 = (int)((C_0054a570*)(int)this)->FUN_0054a570((unsigned int)v_l8, (unsigned int)(int)*(int*)(char*)a4, (unsigned int)(int)*(int*)((char*)a4 + 4));
            v_l76_q = (int)(int)*(int*)((char*)(int)this + 4);
            v_l72_k = (int)(int)*(int*)(char*)(int)this;
            for (; (unsigned int)v_l72_k < (unsigned int)v_l76_q; v_l72_k = v_l72_k + 52) {
                ((C_005477a0*)v_l72_k)->FUN_005477a0();
                il2c_d_FUN_00f47380(v_l72_k, 0);
            }
            v_l88_12 = (int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) / 52);
            v_l84 = (int)(int)*(int*)(char*)(int)this;
            if (v_l84 != 0) {
                if ((int)*(int*)((char*)v_l84 - 4) != 0) {
                    v_l80_c = v_l84;
                    FUN_00f47380((unsigned int)v_l80_c);
                }
            }
            *(int*)(char*)(int)this = v_l12_40;
            *(int*)((char*)(int)this + 8) = (int)(int)(v_l8 * 52 + (int)*(int*)(char*)(int)this);
        } else {
            if ((unsigned int)v_l8 > (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 52)) {
                v_l120 = (int)(int)*(int*)(char*)(int)this;
                v_l116_d = (int)(int)((int)((int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 52) * 52) + (int)*(int*)(char*)a4);
                v_l112_79 = (int)(int)*(int*)(char*)a4;
                v_l90 = (unsigned char)0;
                v_l89 = (unsigned char)0;
                v_l91_h = (unsigned char)0;
                v_l108_d = v_l120;
                v_l104 = v_l112_79;
                for (; v_l104 != v_l116_d; v_l108_d = v_l108_d + 52, v_l104 = v_l104 + 52) {
                    ((C_00548e70*)v_l108_d)->FUN_00548e70((unsigned int)v_l104);
                }
                FUN_0054a4d0((unsigned int)(int)((int)((int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 52) * 52) + (int)*(int*)(char*)a4), (unsigned int)(int)*(int*)((char*)a4 + 4), (unsigned int)(int)*(int*)((char*)(int)this + 4));
            } else {
                v_l200 = (int)(int)*(int*)(char*)(int)this;
                v_l196_62 = (int)(int)*(int*)((char*)a4 + 4);
                v_l192_29 = (int)(int)*(int*)(char*)a4;
                v_l170_14 = (unsigned char)0;
                v_l169_c = (unsigned char)0;
                v_l171_c = (unsigned char)0;
                v_l188 = v_l200;
                v_l184_21 = v_l192_29;
                for (; v_l184_21 != v_l196_62; v_l188 = v_l188 + 52, v_l184_21 = v_l184_21 + 52) {
                    ((C_00548e70*)v_l188)->FUN_00548e70((unsigned int)v_l184_21);
                }
                v_l16_i = v_l188;
                v_l236 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l232_11 = v_l16_i;
                for (; (unsigned int)v_l232_11 < (unsigned int)v_l236; v_l232_11 = v_l232_11 + 52) {
                    ((C_005477a0*)v_l232_11)->FUN_005477a0();
                    il2c_d_FUN_00f47380(v_l232_11, 0);
                }
            }
        }
        *(int*)((char*)(int)this + 4) = (int)(int)(v_l8 * 52 + (int)*(int*)(char*)(int)this);
    }
    return (int)this;
}
