// 0x0054ac70: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode with local names and order from the /Od frame inverse (odframe.py); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00549e40/s00549e40.cpp.

struct C_00423650 { void FUN_00423650(unsigned int, unsigned int); };
struct C_004237d0 { void FUN_004237d0(); };
struct C_0054b480 { int FUN_0054b480(unsigned int, unsigned int, unsigned int); };
extern "C" void __cdecl FUN_0054b510(...);
extern "C" void __cdecl FUN_00f47380(...);
__forceinline void il2c_d_FUN_00f47380(int p, int fl) { if (fl & 1) FUN_00f47380((unsigned int)(p)); }


struct D_0054ac70 { int FUN_0054ac70(int a4); };
// @ 0x0054ac70
int D_0054ac70::FUN_0054ac70(int a4)
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
    int v_l96;
    int v_l92_n;
    unsigned char v_l87_d;
    unsigned char v_l86;
    int v_l104_d;
    int v_l100;
    int v_l108;
    int v_l200;
    int v_l196_62;
    int dead_3[3];
    int v_l180_17;
    int v_l176_20;
    int v_l172_16;
    int v_l168_10;
    int v_l164_b;
    unsigned char v_l159_10;
    unsigned char v_l158;
    unsigned char v_l157_a;
    int v_l156_37;
    int v_l152_13;
    int v_l148_20;
    int dead_2_17[4];
    int v_l128_24;
    int v_l124_19;
    int v_l120_13;
    unsigned char v_l114_11;
    char dead_1;
    int v_l112;
    if (a4 != (int)this) {
        v_l8 = (int)(int)((int)((int)*(int*)((char*)a4 + 4) - (int)*(int*)(char*)a4) >> 4);
        if ((unsigned int)v_l8 > (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) >> 4)) {
            v_l12_40 = (int)((C_0054b480*)(int)this)->FUN_0054b480((unsigned int)v_l8, (unsigned int)(int)*(int*)(char*)a4, (unsigned int)(int)*(int*)((char*)a4 + 4));
            v_l72_k = (int)(int)*(int*)((char*)(int)this + 4);
            v_l68_t = (int)(int)*(int*)(char*)(int)this;
            for (; (unsigned int)v_l68_t < (unsigned int)v_l72_k; v_l68_t = v_l68_t + 16) {
                ((C_004237d0*)v_l68_t)->FUN_004237d0();
                il2c_d_FUN_00f47380(v_l68_t, 0);
            }
            v_l84 = (int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) >> 4);
            v_l80_c = (int)(int)*(int*)(char*)(int)this;
            if (v_l80_c != 0) {
                v_l76_q = v_l80_c;
                FUN_00f47380((unsigned int)v_l76_q);
            }
            *(int*)(char*)(int)this = v_l12_40;
            *(int*)((char*)(int)this + 8) = (int)(int)((v_l8 << 4) + (int)*(int*)(char*)(int)this);
        } else {
            if ((unsigned int)v_l8 > (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) >> 4)) {
                v_l108 = (int)(int)*(int*)(char*)(int)this;
                v_l104_d = (int)(int)((int)((int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) >> 4) << 4) + (int)*(int*)(char*)a4);
                v_l100 = (int)(int)*(int*)(char*)a4;
                v_l86 = (unsigned char)0;
                v_l85_c = (unsigned char)0;
                v_l87_d = (unsigned char)0;
                v_l96 = v_l108;
                v_l92_n = v_l100;
                for (; v_l92_n != v_l104_d; v_l96 = v_l96 + 16, v_l92_n = v_l92_n + 16) {
                    if (v_l92_n != v_l96) {
                        ((C_00423650*)v_l96)->FUN_00423650((unsigned int)(int)*(int*)(char*)v_l92_n, (unsigned int)(int)*(int*)((char*)v_l92_n + 4));
                    }
                }
                v_l156_37 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l152_13 = (int)(int)*(int*)((char*)a4 + 4);
                v_l148_20 = (int)(int)((int)((int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) >> 4) << 4) + (int)*(int*)(char*)a4);
                v_l120_13 = v_l156_37;
                v_l124_19 = v_l152_13;
                v_l128_24 = v_l148_20;
                FUN_0054b510((unsigned int)(int)&v_l112, (unsigned int)v_l128_24, (unsigned int)v_l124_19, (unsigned int)v_l120_13, (unsigned int)(int)v_l114_11);
            } else {
                v_l180_17 = (int)(int)*(int*)(char*)(int)this;
                v_l176_20 = (int)(int)*(int*)((char*)a4 + 4);
                v_l172_16 = (int)(int)*(int*)(char*)a4;
                v_l158 = (unsigned char)0;
                v_l157_a = (unsigned char)0;
                v_l159_10 = (unsigned char)0;
                v_l168_10 = v_l180_17;
                v_l164_b = v_l172_16;
                for (; v_l164_b != v_l176_20; v_l168_10 = v_l168_10 + 16, v_l164_b = v_l164_b + 16) {
                    if (v_l164_b != v_l168_10) {
                        ((C_00423650*)v_l168_10)->FUN_00423650((unsigned int)(int)*(int*)(char*)v_l164_b, (unsigned int)(int)*(int*)((char*)v_l164_b + 4));
                    }
                }
                v_l16_i = v_l168_10;
                v_l200 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l196_62 = v_l16_i;
                for (; (unsigned int)v_l196_62 < (unsigned int)v_l200; v_l196_62 = v_l196_62 + 16) {
                    ((C_004237d0*)v_l196_62)->FUN_004237d0();
                    il2c_d_FUN_00f47380(v_l196_62, 0);
                }
            }
        }
        *(int*)((char*)(int)this + 4) = (int)(int)((v_l8 << 4) + (int)*(int*)(char*)(int)this);
    }
    return (int)this;
}
