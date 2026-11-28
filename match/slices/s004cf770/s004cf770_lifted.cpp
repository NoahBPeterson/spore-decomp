// 0x004cf770: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/SPEditorSpeciesManager.cpp, match/slices/s004cf770/s004cf770.cpp.

extern "C" int __cdecl FUN_0042dee0(...);
extern "C" void __cdecl FUN_004d0a80(...);
extern "C" int __cdecl FUN_004d0ac0(...);
extern "C" void __cdecl FUN_004d0dd0(...);
extern "C" void __cdecl FUN_004d0e90(...);
extern "C" int __cdecl FUN_004d0f30(...);
struct C_00501290 { void FUN_00501290(unsigned int); };
extern "C" void __cdecl FUN_00f47380(...);
struct S5 { int m0; int m1; int m2; int m3; int m4; };


struct D_004cf770 { void FUN_004cf770(int a4, int a8, int a12); };
// @ 0x004cf770
// @ 0x004cf770
void D_004cf770::FUN_004cf770(int a4, int a8, int a12)
{
    int v_l44_f;
    int v_l40_h;
    int v_l36_c;
    int v_l32_p;
    int v_l28_g;
    int v_l24;
    int dead_0_15[3];
    int v_l8;
    unsigned char v_l91;
    unsigned char v_l90_a;
    unsigned char v_l89_41;
    int v_l88_12;
    int v_l84;
    int v_l80_20;
    int v_l76_107;
    int v_l72_l;
    int v_l68_i;
    unsigned char v_l62_r;
    char dead_1_12;
    int v_l60_f;
    int v_l56_a;
    int v_l52_w;
    int v_l48;
    int v_l112_d;
    unsigned char v_l106;
    char dead_2_16;
    int v_l104_a;
    int v_l100_34;
    int v_l96;
    int v_l168_d;
    int dead_3_16[12];
    int v_l116;
    int dead_4[8];
    unsigned char v_l202_20;
    char dead_5;
    int v_l248_25;
    int v_l244_24;
    unsigned char v_l237_a;
    int dead_6_27[5];
    int v_l216_26;
    int v_l212;
    int v_l208;
    int v_l268_d;
    int v_l264_16;
    int v_l260;
    int v_l256;
    int v_l252;
    if ((unsigned int)a8 <= (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)((char*)(int)this + 4)) / 20)) {
        if ((unsigned int)a8 > (unsigned int)0) {
            v_l28_g = (int)(int)*(int*)(char*)a12;
            v_l56_a = (int)&v_l24;
            ((C_00501290*)v_l56_a)->FUN_00501290((unsigned int)(a12 + 4));
            v_l32_p = (int)(int)((int)((int)*(int*)((char*)(int)this + 4) - a4) / 20);
            v_l8 = (int)(int)*(int*)((char*)(int)this + 4);
            if ((unsigned int)a8 < (unsigned int)v_l32_p) {
                v_l88_12 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l84 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l80_20 = (int)(int)((int)*(int*)((char*)(int)this + 4) - a8 * 20);
                v_l68_i = v_l88_12;
                v_l72_l = v_l84;
                v_l76_107 = v_l80_20;
                FUN_004d0dd0((unsigned int)(int)&v_l60_f, (unsigned int)v_l76_107, (unsigned int)v_l72_l, (unsigned int)v_l68_i, (unsigned int)(int)v_l62_r);
                *(int*)((char*)(int)this + 4) = (int)(int)(a8 * 20 + (int)*(int*)((char*)(int)this + 4));
                v_l90_a = (unsigned char)0;
                v_l89_41 = (unsigned char)0;
                v_l91 = (unsigned char)0;
                v_l100_34 = v_l8;
                v_l96 = v_l8 - a8 * 20;
                while (v_l96 != a4) {
                    v_l96 = v_l96 - 20;
                    v_l100_34 = v_l100_34 - 20;
                    *(S5*)v_l100_34 = *(S5*)v_l96;
                }
                v_l104_a = a4;
                for (; v_l104_a != a8 * 20 + a4; v_l104_a = v_l104_a + 20) {
                    *(S5*)v_l104_a = *(S5*)&v_l28_g;
                }
            } else {
                v_l116 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l112_d = v_l116;
                FUN_004d0e90((unsigned int)v_l112_d, (unsigned int)(a8 - v_l32_p), (unsigned int)(int)&v_l28_g, (unsigned int)(int)v_l106);
                *(int*)((char*)(int)this + 4) = (int)(int)((a8 - v_l32_p) * 20 + (int)*(int*)((char*)(int)this + 4));
                FUN_004d0a80((unsigned int)a4, (unsigned int)v_l8, (unsigned int)(int)*(int*)((char*)(int)this + 4));
                *(int*)((char*)(int)this + 4) = (int)(int)(v_l32_p * 20 + (int)*(int*)((char*)(int)this + 4));
                v_l168_d = a4;
                for (; v_l168_d != v_l8; v_l168_d = v_l168_d + 20) {
                    *(S5*)v_l168_d = *(S5*)&v_l28_g;
                }
            }
        }
    } else {
        v_l44_f = (int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 20);
        v_l52_w = (int)(int)((unsigned int)v_l44_f > (unsigned int)0 ? v_l44_f << 1 : 1);
        v_l36_c = (int)(int)((unsigned int)v_l52_w > (unsigned int)(v_l44_f + a8) ? v_l52_w : v_l44_f + a8);
        v_l48 = (int)(int)(v_l36_c != 0 ? (int)(int)FUN_0042dee0((unsigned int)((int)this + 12), (unsigned int)(v_l36_c * 20), (unsigned int)4, (unsigned int)0) : 0);
        v_l40_h = (int)(int)FUN_004d0ac0((unsigned int)(int)*(int*)(char*)(int)this, (unsigned int)a4, (unsigned int)v_l48);
        v_l212 = v_l40_h;
        v_l208 = v_l212;
        FUN_004d0e90((unsigned int)v_l208, (unsigned int)a8, (unsigned int)a12, (unsigned int)(int)v_l202_20);
        v_l256 = a8 * 20 + v_l40_h;
        v_l252 = (int)(int)*(int*)((char*)(int)this + 4);
        v_l216_26 = (int)(int)FUN_004d0f30((unsigned int)a4, (unsigned int)v_l252, (unsigned int)v_l256);
        v_l237_a = (unsigned char)0;
        v_l248_25 = v_l256;
        v_l244_24 = a4;
        for (; v_l244_24 != v_l252; v_l244_24 = v_l244_24 + 20, v_l248_25 = v_l248_25 + 20) {
        }
        v_l40_h = v_l216_26;
        v_l268_d = (int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) / 20);
        v_l264_16 = (int)(int)*(int*)(char*)(int)this;
        if (v_l264_16 != 0) {
            if ((int)*(int*)((char*)v_l264_16 - 4) != 0) {
                v_l260 = v_l264_16;
                FUN_00f47380((unsigned int)v_l260);
            }
        }
        *(int*)(char*)(int)this = v_l48;
        *(int*)((char*)(int)this + 4) = v_l40_h;
        *(int*)((char*)(int)this + 8) = v_l36_c * 20 + v_l48;
    }
    return;
}
