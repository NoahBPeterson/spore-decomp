// 0x0047ae60: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0047a5a0/s0047a5a0.cpp, src/game/SPGonzago/InteractionAgent.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual int s1();
};

struct C_00423080 { void FUN_00423080(unsigned int); };
struct C_00424f10 { int FUN_00424f10(unsigned int); };
extern "C" int __cdecl FUN_0042a730(...);
extern "C" int __cdecl FUN_0042dee0(...);
extern "C" void __cdecl FUN_0047b290(...);
extern "C" void __cdecl FUN_0047cd20(...);
extern "C" void __cdecl FUN_00f47380(...);


struct D_0047ae60 { void FUN_0047ae60(int a4, int a8, int a12); };
// @ 0x0047ae60
// @ 0x0047ae60
void D_0047ae60::FUN_0047ae60(int a4, int a8, int a12)
{
    int v_l44_f;
    int v_l40_h[7];
    int v_l12_40;
    int v_l8;
    int v_l92_k;
    int v_l88_12;
    int v_l84;
    int v_l80_20;
    int v_l76_107;
    unsigned char v_l70_63;
    char dead_0_a;
    int v_l68_i;
    int v_l64_z;
    int v_l60_f;
    int v_l56_a;
    int v_l52_w;
    int v_l48;
    int v_l96;
    int v_l104_d;
    unsigned char v_l99;
    unsigned char v_l98_n;
    unsigned char v_l97;
    int v_l108;
    int v_l120_13;
    unsigned char v_l114_11;
    char dead_1;
    int v_l112;
    int v_l244;
    int v_l240_c;
    int v_l236_40;
    int dead_5_26[7];
    int v_l204;
    int v_l200_36;
    unsigned char v_l194_14;
    char dead_4_a;
    int dead_3_c[7];
    int v_l164_60;
    int v_l160_c;
    int v_l156;
    int v_l152_d;
    int v_l148_31;
    int v_l144_a;
    int v_l140_c;
    int v_l136_b;
    unsigned char v_l130;
    char dead_2_13;
    int v_l128_b;
    int v_l124;
    if ((unsigned int)a8 <= (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)((char*)(int)this + 4)) >> 5)) {
        if ((unsigned int)a8 > (unsigned int)0) {
            ((C_00423080*)(int)&v_l40_h)->FUN_00423080((unsigned int)a12);
            v_l44_f = (int)(int)((int)((int)*(int*)((char*)(int)this + 4) - a4) >> 5);
            v_l8 = (int)(int)*(int*)((char*)(int)this + 4);
            if ((unsigned int)a8 < (unsigned int)v_l44_f) {
                v_l96 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l92_k = (int)(int)*(int*)((char*)(int)this + 4);
                v_l88_12 = (int)(int)((int)*(int*)((char*)(int)this + 4) - (a8 << 5));
                v_l76_107 = v_l96;
                v_l80_20 = v_l92_k;
                v_l84 = v_l88_12;
                FUN_0047b290((unsigned int)(int)&v_l68_i, (unsigned int)v_l84, (unsigned int)v_l80_20, (unsigned int)v_l76_107, (unsigned int)(int)v_l70_63);
                *(int*)((char*)(int)this + 4) = (int)(int)((a8 << 5) + (int)*(int*)((char*)(int)this + 4));
                v_l98_n = (unsigned char)0;
                v_l97 = (unsigned char)0;
                v_l99 = (unsigned char)0;
                v_l108 = v_l8;
                v_l104_d = v_l8 - (a8 << 5);
                while (v_l104_d != a4) {
                    v_l104_d = v_l104_d - 32;
                    v_l108 = v_l108 - 32;
                    ((C_00424f10*)v_l108)->FUN_00424f10((unsigned int)v_l104_d);
                }
                v_l112 = a4;
                for (; v_l112 != (a8 << 5) + a4; v_l112 = v_l112 + 32) {
                    ((C_00424f10*)v_l112)->FUN_00424f10((unsigned int)(int)&v_l40_h);
                }
            } else {
                v_l124 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l120_13 = v_l124;
                FUN_0047cd20((unsigned int)v_l120_13, (unsigned int)(a8 - v_l44_f), (unsigned int)(int)&v_l40_h, (unsigned int)(int)v_l114_11);
                *(int*)((char*)(int)this + 4) = (int)(int)((a8 - v_l44_f << 5) + (int)*(int*)((char*)(int)this + 4));
                v_l156 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l152_d = v_l8;
                v_l148_31 = a4;
                v_l136_b = v_l156;
                v_l140_c = v_l152_d;
                v_l144_a = v_l148_31;
                FUN_0047b290((unsigned int)(int)&v_l128_b, (unsigned int)v_l144_a, (unsigned int)v_l140_c, (unsigned int)v_l136_b, (unsigned int)(int)v_l130);
                *(int*)((char*)(int)this + 4) = (int)(int)((v_l44_f << 5) + (int)*(int*)((char*)(int)this + 4));
                v_l160_c = a4;
                for (; v_l160_c != v_l8; v_l160_c = v_l160_c + 32) {
                    ((C_00424f10*)v_l160_c)->FUN_00424f10((unsigned int)(int)&v_l40_h);
                }
            }
            v_l164_60 = (int)&v_l12_40;
            if ((int)*(int*)(char*)v_l164_60 != 0) {
                ((il2c_vc0*)(int)(int)*(int*)(char*)v_l164_60)->s1();
            }
        }
    } else {
        v_l56_a = (int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) >> 5);
        v_l64_z = (int)(int)((unsigned int)v_l56_a > (unsigned int)0 ? v_l56_a << 1 : 1);
        v_l48 = (int)(int)((unsigned int)v_l64_z > (unsigned int)(v_l56_a + a8) ? v_l64_z : v_l56_a + a8);
        v_l60_f = (int)(int)(v_l48 != 0 ? (int)(int)FUN_0042dee0((unsigned int)((int)this + 12), (unsigned int)(v_l48 << 5), (unsigned int)4, (unsigned int)0) : 0);
        v_l52_w = (int)(int)FUN_0042a730((unsigned int)(int)*(int*)(char*)(int)this, (unsigned int)a4, (unsigned int)v_l60_f);
        v_l204 = v_l52_w;
        v_l200_36 = v_l204;
        FUN_0047cd20((unsigned int)v_l200_36, (unsigned int)a8, (unsigned int)a12, (unsigned int)(int)v_l194_14);
        v_l52_w = (int)(int)FUN_0042a730((unsigned int)a4, (unsigned int)(int)*(int*)((char*)(int)this + 4), (unsigned int)((a8 << 5) + v_l52_w));
        v_l244 = (int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) >> 5);
        v_l240_c = (int)(int)*(int*)(char*)(int)this;
        if (v_l240_c != 0) {
            if ((int)*(int*)((char*)v_l240_c - 4) != 0) {
                v_l236_40 = v_l240_c;
                FUN_00f47380((unsigned int)v_l236_40);
            }
        }
        *(int*)(char*)(int)this = v_l60_f;
        *(int*)((char*)(int)this + 4) = v_l52_w;
        *(int*)((char*)(int)this + 8) = (v_l48 << 5) + v_l60_f;
    }
    return;
}
