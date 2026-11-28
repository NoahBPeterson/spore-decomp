// 0x004c0bd0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004c0410/s004c0410.cpp.

#include <string.h>
extern "C" int __cdecl FUN_0042dee0(...);
struct C_0047b950 { void FUN_0047b950(unsigned int); };
extern "C" int __cdecl FUN_004c1ce0(...);
extern "C" void __cdecl FUN_004c22a0(...);
extern "C" void __cdecl FUN_004c2320(...);
extern "C" void __cdecl FUN_00f47380(...);
struct S35 { int m0; int m1; int m2; int m3; int m4; int m5; int m6; int m7; int m8; int m9; int m10; int m11; int m12; int m13; int m14; int m15; int m16; int m17; int m18; int m19; int m20; int m21; int m22; int m23; int m24; int m25; int m26; int m27; int m28; int m29; int m30; int m31; int m32; int m33; int m34; };


struct D_004c0bd0 { void FUN_004c0bd0(int a4, int a8, int a12); };
// @ 0x004c0bd0
// @ 0x004c0bd0
void D_004c0bd0::FUN_004c0bd0(int a4, int a8, int a12)
{
    int v_l156_32[35];
    int v_l8;
    unsigned char v_l219_54;
    unsigned char v_l218;
    unsigned char v_l217_19;
    int v_l216_10;
    int v_l212_20;
    int v_l208_12;
    int v_l204_58;
    int v_l200_32;
    int v_l196_16;
    unsigned char v_l190_33;
    char dead_0_10;
    int v_l188_c[2];
    int v_l180;
    int v_l176_11;
    int v_l172_15;
    int v_l168_14;
    int v_l164_27;
    int v_l160;
    int v_l224;
    char dead_1_b;
    int v_l232_10;
    int v_l228;
    int v_l244_21;
    int v_l240_a;
    unsigned char v_l234;
    int v_l248;
    int v_l368;
    int v_l364_10;
    int v_l360_17;
    int dead_5[8];
    int v_l324_16;
    int v_l320_10;
    unsigned char v_l314;
    char dead_4_36;
    int dead_3_35[8];
    int v_l280_13;
    int v_l276_21;
    int v_l272_23;
    int v_l268_a;
    int v_l264_19;
    int v_l260_14;
    int v_l256_14;
    unsigned char v_l250_82;
    char dead_2;
    if ((unsigned int)a8 <= (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)((char*)(int)this + 4)) / 140)) {
        if ((unsigned int)a8 > (unsigned int)0) {
            ((C_0047b950*)(int)&v_l156_32)->FUN_0047b950((unsigned int)a12);
            v_l160 = (int)(int)((int)((int)*(int*)((char*)(int)this + 4) - a4) / 140);
            v_l8 = (int)(int)*(int*)((char*)(int)this + 4);
            if ((unsigned int)a8 < (unsigned int)v_l160) {
                v_l216_10 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l212_20 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l208_12 = (int)(int)((int)*(int*)((char*)(int)this + 4) - a8 * 140);
                v_l196_16 = v_l216_10;
                v_l200_32 = v_l212_20;
                v_l204_58 = v_l208_12;
                FUN_004c22a0((unsigned int)(int)&v_l188_c, (unsigned int)v_l204_58, (unsigned int)v_l200_32, (unsigned int)v_l196_16, (unsigned int)(int)v_l190_33);
                *(int*)((char*)(int)this + 4) = (int)(int)(a8 * 140 + (int)*(int*)((char*)(int)this + 4));
                v_l218 = (unsigned char)0;
                v_l217_19 = (unsigned char)0;
                v_l219_54 = (unsigned char)0;
                v_l228 = v_l8;
                v_l224 = v_l8 - a8 * 140;
                while (v_l224 != a4) {
                    v_l224 = v_l224 - 140;
                    v_l228 = v_l228 - 140;
                    *(S35*)v_l228 = *(S35*)v_l224;
                }
                v_l232_10 = a4;
                for (; v_l232_10 != a8 * 140 + a4; v_l232_10 = v_l232_10 + 140) {
                    *(S35*)v_l232_10 = *(S35*)(int)&v_l156_32;
                }
            } else {
                v_l244_21 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l240_a = v_l244_21;
                FUN_004c2320((unsigned int)v_l240_a, (unsigned int)(a8 - v_l160), (unsigned int)(int)&v_l156_32, (unsigned int)(int)v_l234);
                *(int*)((char*)(int)this + 4) = (int)(int)((a8 - v_l160) * 140 + (int)*(int*)((char*)(int)this + 4));
                v_l276_21 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l272_23 = v_l8;
                v_l268_a = a4;
                v_l256_14 = v_l276_21;
                v_l260_14 = v_l272_23;
                v_l264_19 = v_l268_a;
                FUN_004c22a0((unsigned int)(int)&v_l248, (unsigned int)v_l264_19, (unsigned int)v_l260_14, (unsigned int)v_l256_14, (unsigned int)(int)v_l250_82);
                *(int*)((char*)(int)this + 4) = (int)(int)(v_l160 * 140 + (int)*(int*)((char*)(int)this + 4));
                v_l280_13 = a4;
                for (; v_l280_13 != v_l8; v_l280_13 = v_l280_13 + 140) {
                    *(S35*)v_l280_13 = *(S35*)(int)&v_l156_32;
                }
            }
        }
    } else {
        v_l172_15 = (int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 140);
        v_l180 = (int)(int)((unsigned int)v_l172_15 > (unsigned int)0 ? v_l172_15 << 1 : 1);
        v_l164_27 = (int)(int)((unsigned int)v_l180 > (unsigned int)(v_l172_15 + a8) ? v_l180 : v_l172_15 + a8);
        v_l176_11 = (int)(int)(v_l164_27 != 0 ? (int)(int)FUN_0042dee0((unsigned int)((int)this + 12), (unsigned int)(v_l164_27 * 140), (unsigned int)4, (unsigned int)0) : 0);
        v_l168_14 = (int)(int)FUN_004c1ce0((unsigned int)(int)*(int*)(char*)(int)this, (unsigned int)a4, (unsigned int)v_l176_11);
        v_l324_16 = v_l168_14;
        v_l320_10 = v_l324_16;
        FUN_004c2320((unsigned int)v_l320_10, (unsigned int)a8, (unsigned int)a12, (unsigned int)(int)v_l314);
        v_l168_14 = (int)(int)FUN_004c1ce0((unsigned int)a4, (unsigned int)(int)*(int*)((char*)(int)this + 4), (unsigned int)(a8 * 140 + v_l168_14));
        v_l368 = (int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) / 140);
        v_l364_10 = (int)(int)*(int*)(char*)(int)this;
        if (v_l364_10 != 0) {
            if ((int)*(int*)((char*)v_l364_10 - 4) != 0) {
                v_l360_17 = v_l364_10;
                FUN_00f47380((unsigned int)v_l360_17);
            }
        }
        *(int*)(char*)(int)this = v_l176_11;
        *(int*)((char*)(int)this + 4) = v_l168_14;
        *(int*)((char*)(int)this + 8) = v_l164_27 * 140 + v_l176_11;
    }
    return;
}
