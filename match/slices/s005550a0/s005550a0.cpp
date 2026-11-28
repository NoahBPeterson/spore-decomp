// 0x005550a0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00554c30/s00554c30.cpp, match/slices/s00555bc0/s00555bc0.cpp.

extern "C" int __cdecl FUN_0042dee0(...);
struct C_00454cb0 { void FUN_00454cb0(unsigned int, unsigned int); };
struct C_0047d390 { void FUN_0047d390(unsigned int, unsigned int); };
struct C_00530670 { int FUN_00530670(); };
extern "C" int __cdecl FUN_005554e0(...);
extern "C" void __cdecl FUN_00555aa0(...);
extern "C" void __cdecl FUN_00555b40(...);
extern "C" void __cdecl FUN_00f47380(...);


struct D_005550a0 { void FUN_005550a0(int a4, int a8, int a12); };
// @ 0x005550a0
void D_005550a0::FUN_005550a0(int a4, int a8, int a12)
{
    int v_l44_f;
    int v_l40_h;
    int v_l36_c;
    int v_l32_p;
    int v_l28_g;
    int v_l24;
    int v_l20_q;
    int v_l16_i;
    int dead_0_15;
    int v_l8;
    int v_l64_z;
    int v_l60_f;
    unsigned char v_l54_s;
    char dead_1_12;
    int v_l52_w;
    int v_l48;
    int v_l124_c;
    int v_l120_21;
    unsigned char v_l114_12;
    char dead_3_16;
    int v_l112_14;
    int v_l108_63;
    int v_l104_30;
    unsigned char v_l98_i;
    char dead_2_b;
    int v_l96_a;
    int v_l92;
    int v_l88_m;
    unsigned char v_l83_o;
    unsigned char v_l82_52;
    unsigned char v_l81_c;
    int v_l80_h;
    int v_l76_c;
    int v_l72_a;
    int v_l68;
    int v_l128;
    int v_l140_11;
    int v_l136_13;
    int v_l132;
    int dead_4_c[14];
    int v_l144;
    unsigned char v_l202_20;
    char dead_5;
    int dead_6_27[9];
    int v_l212;
    int v_l208;
    int v_l260;
    int v_l256;
    int v_l252;
    if ((unsigned int)a8 <= (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)((char*)(int)this + 4)) >> 4)) {
        if ((unsigned int)a8 > (unsigned int)0) {
            v_l24 = 0;
            v_l20_q = 0;
            v_l16_i = 0;
            ((C_0047d390*)(int)&v_l24)->FUN_0047d390((unsigned int)(int)*(int*)(char*)a12, (unsigned int)(int)*(int*)((char*)a12 + 4));
            v_l28_g = (int)(int)((int)((int)*(int*)((char*)(int)this + 4) - a4) >> 4);
            v_l8 = (int)(int)*(int*)((char*)(int)this + 4);
            if ((unsigned int)a8 < (unsigned int)v_l28_g) {
                v_l80_h = (int)(int)*(int*)((char*)(int)this + 4);
                v_l76_c = (int)(int)*(int*)((char*)(int)this + 4);
                v_l72_a = (int)(int)((int)*(int*)((char*)(int)this + 4) - (a8 << 4));
                v_l60_f = v_l80_h;
                v_l64_z = v_l76_c;
                v_l68 = v_l72_a;
                FUN_00555aa0((unsigned int)(int)&v_l52_w, (unsigned int)v_l68, (unsigned int)v_l64_z, (unsigned int)v_l60_f, (unsigned int)(int)v_l54_s);
                *(int*)((char*)(int)this + 4) = (int)(int)((a8 << 4) + (int)*(int*)((char*)(int)this + 4));
                v_l82_52 = (unsigned char)0;
                v_l81_c = (unsigned char)0;
                v_l83_o = (unsigned char)0;
                v_l92 = v_l8;
                v_l88_m = v_l8 - (a8 << 4);
                while (v_l88_m != a4) {
                    v_l88_m = v_l88_m - 16;
                    v_l92 = v_l92 - 16;
                    if (v_l88_m != v_l92) {
                        ((C_00454cb0*)v_l92)->FUN_00454cb0((unsigned int)(int)*(int*)(char*)v_l88_m, (unsigned int)(int)*(int*)((char*)v_l88_m + 4));
                    }
                }
                v_l96_a = a4;
                for (; v_l96_a != (a8 << 4) + a4; v_l96_a = v_l96_a + 16) {
                    if ((int)&v_l24 != v_l96_a) {
                        ((C_00454cb0*)v_l96_a)->FUN_00454cb0((unsigned int)v_l24, (unsigned int)v_l20_q);
                    }
                }
            } else {
                v_l108_63 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l104_30 = v_l108_63;
                FUN_00555b40((unsigned int)v_l104_30, (unsigned int)(a8 - v_l28_g), (unsigned int)(int)&v_l24, (unsigned int)(int)v_l98_i);
                *(int*)((char*)(int)this + 4) = (int)(int)((a8 - v_l28_g << 4) + (int)*(int*)((char*)(int)this + 4));
                v_l140_11 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l136_13 = v_l8;
                v_l132 = a4;
                v_l120_21 = v_l140_11;
                v_l124_c = v_l136_13;
                v_l128 = v_l132;
                FUN_00555aa0((unsigned int)(int)&v_l112_14, (unsigned int)v_l128, (unsigned int)v_l124_c, (unsigned int)v_l120_21, (unsigned int)(int)v_l114_12);
                *(int*)((char*)(int)this + 4) = (int)(int)((v_l28_g << 4) + (int)*(int*)((char*)(int)this + 4));
                v_l144 = a4;
                for (; v_l144 != v_l8; v_l144 = v_l144 + 16) {
                    if ((int)&v_l24 != v_l144) {
                        ((C_00454cb0*)v_l144)->FUN_00454cb0((unsigned int)v_l24, (unsigned int)v_l20_q);
                    }
                }
            }
            ((C_00530670*)(int)&v_l24)->FUN_00530670();
        }
    } else {
        v_l40_h = (int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) >> 4);
        v_l48 = (int)(int)((unsigned int)v_l40_h > (unsigned int)0 ? v_l40_h << 1 : 1);
        v_l32_p = (int)(int)((unsigned int)v_l48 > (unsigned int)(v_l40_h + a8) ? v_l48 : v_l40_h + a8);
        v_l44_f = (int)(int)(v_l32_p != 0 ? (int)(int)FUN_0042dee0((unsigned int)((int)this + 12), (unsigned int)(v_l32_p << 4), (unsigned int)4, (unsigned int)0) : 0);
        v_l36_c = (int)(int)FUN_005554e0((unsigned int)(int)*(int*)(char*)(int)this, (unsigned int)a4, (unsigned int)v_l44_f);
        v_l212 = v_l36_c;
        v_l208 = v_l212;
        FUN_00555b40((unsigned int)v_l208, (unsigned int)a8, (unsigned int)a12, (unsigned int)(int)v_l202_20);
        v_l36_c = (int)(int)FUN_005554e0((unsigned int)a4, (unsigned int)(int)*(int*)((char*)(int)this + 4), (unsigned int)((a8 << 4) + v_l36_c));
        v_l260 = (int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) >> 4);
        v_l256 = (int)(int)*(int*)(char*)(int)this;
        if (v_l256 != 0) {
            if ((int)*(int*)((char*)v_l256 - 4) != 0) {
                v_l252 = v_l256;
                FUN_00f47380((unsigned int)v_l252);
            }
        }
        *(int*)(char*)(int)this = v_l44_f;
        *(int*)((char*)(int)this + 4) = v_l36_c;
        *(int*)((char*)(int)this + 8) = (v_l32_p << 4) + v_l44_f;
    }
    return;
}
