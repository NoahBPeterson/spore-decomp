// 0x004b0ef0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/_at_004b0000.cpp, match/slices/s004b0490/s004b0490.cpp.

#include <string.h>
extern "C" void __cdecl FUN_004b1760(...);
struct C_004b1f50 { int FUN_004b1f50(unsigned int, unsigned int, unsigned int); };
extern "C" void __cdecl FUN_00f47380(...);
struct S118 { int m0; int m1; int m2; int m3; int m4; int m5; int m6; int m7; int m8; int m9; int m10; int m11; int m12; int m13; int m14; int m15; int m16; int m17; int m18; int m19; int m20; int m21; int m22; int m23; int m24; int m25; int m26; int m27; int m28; int m29; int m30; int m31; int m32; int m33; int m34; int m35; int m36; int m37; int m38; int m39; int m40; int m41; int m42; int m43; int m44; int m45; int m46; int m47; int m48; int m49; int m50; int m51; int m52; int m53; int m54; int m55; int m56; int m57; int m58; int m59; int m60; int m61; int m62; int m63; int m64; int m65; int m66; int m67; int m68; int m69; int m70; int m71; int m72; int m73; int m74; int m75; int m76; int m77; int m78; int m79; int m80; int m81; int m82; int m83; int m84; int m85; int m86; int m87; int m88; int m89; int m90; int m91; int m92; int m93; int m94; int m95; int m96; int m97; int m98; int m99; int m100; int m101; int m102; int m103; int m104; int m105; int m106; int m107; int m108; int m109; int m110; int m111; int m112; int m113; int m114; int m115; int m116; int m117; };


struct D_004b0ef0 { int FUN_004b0ef0(int a4); };
// @ 0x004b0ef0
// @ 0x004b0ef0
int D_004b0ef0::FUN_004b0ef0(int a4)
{
    int v_l64_r;
    int v_l60_g;
    int v_l56_j;
    int dead_0_15[9];
    int v_l16_i;
    int v_l12_40;
    int v_l8;
    unsigned char v_l70_i;
    unsigned char v_l69_k;
    int v_l68;
    int v_l76_r;
    unsigned char v_l71;
    int v_l84_m;
    int v_l80;
    int v_l92_c;
    int v_l88;
    int v_l152_13;
    int v_l148_20;
    unsigned char v_l143_10;
    unsigned char v_l142;
    unsigned char v_l141_33;
    int dead_1[12];
    int v_l168_20;
    int v_l164_60;
    int v_l160_c;
    int v_l156;
    if (a4 != (int)this) {
        v_l8 = (int)(int)((int)((int)*(int*)((char*)a4 + 4) - (int)*(int*)(char*)a4) / 472);
        if ((unsigned int)v_l8 > (unsigned int)(int)((int)(int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) / 472)) {
            v_l12_40 = (int)((C_004b1f50*)(int)this)->FUN_004b1f50((unsigned int)v_l8, (unsigned int)(int)*(int*)(char*)a4, (unsigned int)(int)*(int*)((char*)a4 + 4));
            v_l56_j = (int)(int)*(int*)(char*)(int)this;
            for (; (unsigned int)v_l56_j < (unsigned int)*(int*)((char*)(int)this + 4); v_l56_j = v_l56_j + 472) {
            }
            v_l68 = (int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) / 472);
            v_l64_r = (int)(int)*(int*)(char*)(int)this;
            if (v_l64_r != 0) {
                if ((int)*(int*)((char*)v_l64_r - 4) != 0) {
                    v_l60_g = v_l64_r;
                    FUN_00f47380((unsigned int)v_l60_g);
                }
            }
            *(int*)(char*)(int)this = v_l12_40;
            *(int*)((char*)(int)this + 8) = (int)(int)(v_l8 * 472 + (int)*(int*)(char*)(int)this);
        } else {
            if ((unsigned int)v_l8 > (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 472)) {
                v_l92_c = (int)(int)*(int*)(char*)(int)this;
                v_l88 = (int)(int)((int)((int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 472) * 472) + (int)*(int*)(char*)a4);
                v_l84_m = (int)(int)*(int*)(char*)a4;
                v_l70_i = (unsigned char)0;
                v_l69_k = (unsigned char)0;
                v_l71 = (unsigned char)0;
                v_l80 = v_l92_c;
                v_l76_r = v_l84_m;
                for (; v_l76_r != v_l88; v_l80 = v_l80 + 472, v_l76_r = v_l76_r + 472) {
                    *(S118*)v_l80 = *(S118*)v_l76_r;
                }
                FUN_004b1760((unsigned int)(int)((int)((int)((int)(int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 472) * 472) + (int)*(int*)(char*)a4), (unsigned int)(int)*(int*)((char*)a4 + 4), (unsigned int)(int)*(int*)((char*)(int)this + 4));
            } else {
                v_l164_60 = (int)(int)*(int*)(char*)(int)this;
                v_l160_c = (int)(int)*(int*)((char*)a4 + 4);
                v_l156 = (int)(int)*(int*)(char*)a4;
                v_l142 = (unsigned char)0;
                v_l141_33 = (unsigned char)0;
                v_l143_10 = (unsigned char)0;
                v_l152_13 = v_l164_60;
                v_l148_20 = v_l156;
                for (; v_l148_20 != v_l160_c; v_l152_13 = v_l152_13 + 472, v_l148_20 = v_l148_20 + 472) {
                    *(S118*)v_l152_13 = *(S118*)v_l148_20;
                }
                v_l16_i = v_l152_13;
                v_l168_20 = v_l16_i;
                for (; (unsigned int)v_l168_20 < (unsigned int)*(int*)((char*)(int)this + 4); v_l168_20 = v_l168_20 + 472) {
                }
            }
        }
        *(int*)((char*)(int)this + 4) = (int)(int)(v_l8 * 472 + (int)*(int*)(char*)(int)this);
    }
    return (int)this;
}
