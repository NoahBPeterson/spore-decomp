// 0x00455fa0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004553b0/s004553b0.cpp.

#include <string.h>
extern "C" int __cdecl FUN_0042dee0(...);
struct C_0044d960 { void FUN_0044d960(unsigned int); };
extern "C" void __cdecl FUN_00456c10(...);
extern "C" int __cdecl FUN_00456cb0(...);
extern "C" void __cdecl FUN_004570f0(...);
extern "C" void __cdecl FUN_00457170(...);
struct C_004ae250 { int FUN_004ae250(); };
extern "C" void __cdecl FUN_00f47380(...);
struct S8 { int m0; int m1; int m2; int m3; int m4; int m5; int m6; int m7; };


struct D_00455fa0 { void FUN_00455fa0(int a4, int a8, int a12); };
// @ 0x00455fa0
// @ 0x00455fa0
void D_00455fa0::FUN_00455fa0(int a4, int a8, int a12)
{
    int v_l44_f;
    int v_l40_h[8];
    int v_l8;
    int v_l92_k;
    int v_l88_12;
    int v_l84;
    int v_l80_20;
    unsigned char v_l74_f;
    char dead_0_a;
    int v_l72_l[2];
    int v_l64_z;
    int v_l60_f;
    int v_l56_a;
    int v_l52_w;
    int v_l48;
    int v_l100_34;
    int v_l96;
    unsigned char v_l101;
    unsigned char v_l102;
    int v_l108_c;
    unsigned char v_l103;
    int v_l272_36;
    int v_l268_14;
    int v_l264_13;
    int dead_5_16[9];
    int v_l224_19;
    int v_l220_32;
    unsigned char v_l214;
    char dead_4_35;
    int dead_3[8];
    int v_l180_17;
    int dead_2_17[12];
    int v_l128_24;
    int v_l124_19;
    unsigned char v_l118_30;
    char dead_1;
    int v_l116_24;
    int v_l112;
    if ((unsigned int)a8 <= (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)((char*)(int)this + 4)) >> 5)) {
        if ((unsigned int)a8 > (unsigned int)0) {
            ((C_0044d960*)(int)&v_l40_h)->FUN_0044d960((unsigned int)a12);
            v_l44_f = (int)(int)((int)((int)*(int*)((char*)(int)this + 4) - a4) >> 5);
            v_l8 = (int)(int)*(int*)((char*)(int)this + 4);
            if ((unsigned int)a8 < (unsigned int)v_l44_f) {
                v_l100_34 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l96 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l92_k = (int)(int)((int)*(int*)((char*)(int)this + 4) - (a8 << 5));
                v_l80_20 = v_l100_34;
                v_l84 = v_l96;
                v_l88_12 = v_l92_k;
                FUN_004570f0((unsigned int)(int)&v_l72_l, (unsigned int)v_l88_12, (unsigned int)v_l84, (unsigned int)v_l80_20, (unsigned int)(int)v_l74_f);
                *(int*)((char*)(int)this + 4) = (int)(int)((a8 << 5) + (int)*(int*)((char*)(int)this + 4));
                v_l102 = (unsigned char)0;
                v_l101 = (unsigned char)0;
                v_l103 = (unsigned char)0;
                v_l112 = v_l8;
                v_l108_c = v_l8 - (a8 << 5);
                while (v_l108_c != a4) {
                    v_l108_c = v_l108_c - 32;
                    v_l112 = v_l112 - 32;
                    *(S8*)v_l112 = *(S8*)v_l108_c;
                }
                v_l116_24 = a4;
                for (; v_l116_24 != (a8 << 5) + a4; v_l116_24 = v_l116_24 + 32) {
                    *(S8*)v_l116_24 = *(S8*)(int)&v_l40_h;
                }
            } else {
                v_l128_24 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l124_19 = v_l128_24;
                FUN_00457170((unsigned int)v_l124_19, (unsigned int)(a8 - v_l44_f), (unsigned int)(int)&v_l40_h, (unsigned int)(int)v_l118_30);
                *(int*)((char*)(int)this + 4) = (int)(int)((a8 - v_l44_f << 5) + (int)*(int*)((char*)(int)this + 4));
                FUN_00456c10((unsigned int)a4, (unsigned int)v_l8, (unsigned int)(int)*(int*)((char*)(int)this + 4));
                *(int*)((char*)(int)this + 4) = (int)(int)((v_l44_f << 5) + (int)*(int*)((char*)(int)this + 4));
                v_l180_17 = a4;
                for (; v_l180_17 != v_l8; v_l180_17 = v_l180_17 + 32) {
                    *(S8*)v_l180_17 = *(S8*)(int)&v_l40_h;
                }
            }
            ((C_004ae250*)(int)&v_l40_h)->FUN_004ae250();
        }
    } else {
        v_l56_a = (int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) >> 5);
        v_l64_z = (int)(int)((unsigned int)v_l56_a > (unsigned int)0 ? v_l56_a << 1 : 1);
        v_l48 = (int)(int)((unsigned int)v_l64_z > (unsigned int)(v_l56_a + a8) ? v_l64_z : v_l56_a + a8);
        v_l60_f = (int)(int)(v_l48 != 0 ? (int)(int)FUN_0042dee0((unsigned int)((int)this + 12), (unsigned int)(v_l48 << 5), (unsigned int)4, (unsigned int)0) : 0);
        v_l52_w = (int)(int)FUN_00456cb0((unsigned int)(int)*(int*)(char*)(int)this, (unsigned int)a4, (unsigned int)v_l60_f);
        v_l224_19 = v_l52_w;
        v_l220_32 = v_l224_19;
        FUN_00457170((unsigned int)v_l220_32, (unsigned int)a8, (unsigned int)a12, (unsigned int)(int)v_l214);
        v_l52_w = (int)(int)FUN_00456cb0((unsigned int)a4, (unsigned int)(int)*(int*)((char*)(int)this + 4), (unsigned int)((a8 << 5) + v_l52_w));
        v_l272_36 = (int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) >> 5);
        v_l268_14 = (int)(int)*(int*)(char*)(int)this;
        if (v_l268_14 != 0) {
            if ((int)*(int*)((char*)v_l268_14 - 4) != 0) {
                v_l264_13 = v_l268_14;
                FUN_00f47380((unsigned int)v_l264_13);
            }
        }
        *(int*)(char*)(int)this = v_l60_f;
        *(int*)((char*)(int)this + 4) = v_l52_w;
        *(int*)((char*)(int)this + 8) = (v_l48 << 5) + v_l60_f;
    }
    return;
}
