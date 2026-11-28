// 0x00474bd0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode with local names and order from the /Od frame inverse (odframe.py); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/_at_00470000.cpp, match/slices/s00474bd0/s00474bd0.cpp.

extern "C" void __cdecl FUN_0042e860(...);
struct C_00453540 { void FUN_00453540(); };
struct C_00476dd0 { int FUN_00476dd0(unsigned int, unsigned int, unsigned int); };
struct C_004e4350 { void FUN_004e4350(unsigned int); };
extern "C" void __cdecl FUN_00f47380(...);
__forceinline void il2c_d_FUN_00f47380(int p, int fl) { if (fl & 1) FUN_00f47380((unsigned int)(p)); }


struct D_00474bd0 { int FUN_00474bd0(int a4); };
// @ 0x00474bd0
int D_00474bd0::FUN_00474bd0(int a4)
{
    int v_l80_c;
    int v_l76_q;
    int v_l72_k;
    int v_l68_t;
    int dead_0_15[12];
    int v_l16_i;
    int v_l12_40;
    int v_l8;
    unsigned char v_l85_c;
    int v_l84;
    int v_l112_d;
    int v_l108_14;
    int v_l104_a;
    int v_l100_34;
    int dead_2_16[2];
    char dead_1_32;
    unsigned char v_l87_d;
    unsigned char v_l86;
    unsigned char v_l122_20;
    char dead_3_16;
    int v_l120_21;
    int v_l116;
    int v_l164_19;
    int v_l160_13;
    int dead_4[5];
    int v_l136_41;
    int v_l132_11;
    int v_l128;
    unsigned char v_l169_45;
    int v_l168;
    unsigned char v_l171_17;
    unsigned char v_l170;
    int v_l204_36;
    int v_l200_21;
    int v_l196_22;
    int dead_6_c[5];
    char dead_5;
    int v_l228_30;
    int dead_7_26[3];
    int v_l212;
    int v_l208;
    int v_l232;
    if (a4 != (int)this) {
        v_l8 = (int)(int)((int)((int)*(int*)((char*)a4 + 4) - (int)*(int*)(char*)a4) >> 2);
        if ((unsigned int)v_l8 > (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) >> 2)) {
            v_l12_40 = (int)((C_00476dd0*)(int)this)->FUN_00476dd0((unsigned int)v_l8, (unsigned int)(int)*(int*)(char*)a4, (unsigned int)(int)*(int*)((char*)a4 + 4));
            v_l72_k = (int)(int)*(int*)((char*)(int)this + 4);
            v_l68_t = (int)(int)*(int*)(char*)(int)this;
            for (; (unsigned int)v_l68_t < (unsigned int)v_l72_k; v_l68_t = v_l68_t + 4) {
                if ((int)*(int*)(char*)v_l68_t != 0) {
                    ((C_00453540*)(int)*(int*)(char*)v_l68_t)->FUN_00453540();
                }
                il2c_d_FUN_00f47380(v_l68_t, 0);
            }
            v_l84 = (int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) >> 2);
            v_l80_c = (int)(int)*(int*)(char*)(int)this;
            if (v_l80_c != 0) {
                if ((int)*(int*)((char*)v_l80_c - 4) != 0) {
                    v_l76_q = v_l80_c;
                    FUN_00f47380((unsigned int)v_l76_q);
                }
            }
            *(int*)(char*)(int)this = v_l12_40;
            *(int*)((char*)(int)this + 8) = (int)(int)((int)*(int*)(char*)(int)this + (v_l8 << 2));
        } else {
            if ((unsigned int)v_l8 > (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) >> 2)) {
                v_l116 = (int)(int)*(int*)(char*)(int)this;
                v_l112_d = (int)(int)((int)*(int*)(char*)a4 + (int)((int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) >> 2) << 2));
                v_l108_14 = (int)(int)*(int*)(char*)a4;
                v_l86 = (unsigned char)0;
                v_l85_c = (unsigned char)0;
                v_l87_d = (unsigned char)0;
                v_l104_a = v_l116;
                v_l100_34 = v_l108_14;
                for (; v_l100_34 != v_l112_d; v_l104_a = v_l104_a + 4, v_l100_34 = v_l100_34 + 4) {
                    ((C_004e4350*)v_l104_a)->FUN_004e4350((unsigned int)v_l100_34);
                }
                v_l168 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l164_19 = (int)(int)*(int*)((char*)a4 + 4);
                v_l160_13 = (int)(int)((int)*(int*)(char*)a4 + (int)((int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) >> 2) << 2));
                v_l128 = v_l168;
                v_l132_11 = v_l164_19;
                v_l136_41 = v_l160_13;
                FUN_0042e860((unsigned int)(int)&v_l120_21, (unsigned int)v_l136_41, (unsigned int)v_l132_11, (unsigned int)v_l128, (unsigned int)(int)v_l122_20);
            } else {
                v_l212 = (int)(int)*(int*)(char*)(int)this;
                v_l208 = (int)(int)*(int*)((char*)a4 + 4);
                v_l204_36 = (int)(int)*(int*)(char*)a4;
                v_l170 = (unsigned char)0;
                v_l169_45 = (unsigned char)0;
                v_l171_17 = (unsigned char)0;
                v_l200_21 = v_l212;
                v_l196_22 = v_l204_36;
                for (; v_l196_22 != v_l208; v_l200_21 = v_l200_21 + 4, v_l196_22 = v_l196_22 + 4) {
                    ((C_004e4350*)v_l200_21)->FUN_004e4350((unsigned int)v_l196_22);
                }
                v_l16_i = v_l200_21;
                v_l232 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l228_30 = v_l16_i;
                for (; (unsigned int)v_l228_30 < (unsigned int)v_l232; v_l228_30 = v_l228_30 + 4) {
                    if ((int)*(int*)(char*)v_l228_30 != 0) {
                        ((C_00453540*)(int)*(int*)(char*)v_l228_30)->FUN_00453540();
                    }
                    il2c_d_FUN_00f47380(v_l228_30, 0);
                }
            }
        }
        *(int*)((char*)(int)this + 4) = (int)(int)((int)*(int*)(char*)(int)this + (v_l8 << 2));
    }
    return (int)this;
}
