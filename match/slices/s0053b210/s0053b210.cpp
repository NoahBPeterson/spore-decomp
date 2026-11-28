// 0x0053b210: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/SPSkinPaintParticleDescription.cpp, match/slices/s0053acc0/s0053acc0.cpp.

extern "C" void __cdecl FUN_00537a40(...);
struct C_0053ccc0 { int FUN_0053ccc0(unsigned int, unsigned int, unsigned int); };
extern "C" void __cdecl FUN_00f47380(...);
struct S4 { int m0; int m1; int m2; int m3; };


struct D_0053b210 { int FUN_0053b210(int a4); };
// @ 0x0053b210
// @ 0x0053b210
int D_0053b210::FUN_0053b210(int a4)
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
    int v_l112_10;
    int v_l108;
    int v_l104_70;
    unsigned char v_l98_c;
    char dead_1_c;
    int v_l96_e;
    int v_l92_h;
    int v_l88_j;
    int v_l84_m;
    int v_l80;
    int v_l136_22;
    int v_l132_19;
    int dead_2[4];
    unsigned char v_l141_20;
    int v_l140;
    int v_l152_13;
    int v_l148_20;
    unsigned char v_l143_10;
    unsigned char v_l142;
    int v_l168_20;
    int v_l164_60;
    int v_l160_c;
    int v_l156;
    if (a4 != (int)this) {
        v_l8 = (int)(int)((int)((int)*(int*)((char*)a4 + 4) - (int)*(int*)(char*)a4) >> 4);
        if ((unsigned int)v_l8 > (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) >> 4)) {
            v_l12_40 = (int)((C_0053ccc0*)(int)this)->FUN_0053ccc0((unsigned int)v_l8, (unsigned int)(int)*(int*)(char*)a4, (unsigned int)(int)*(int*)((char*)a4 + 4));
            v_l56_j = (int)(int)*(int*)(char*)(int)this;
            for (; (unsigned int)v_l56_j < (unsigned int)*(int*)((char*)(int)this + 4); v_l56_j = v_l56_j + 16) {
            }
            v_l68 = (int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) >> 4);
            v_l64_r = (int)(int)*(int*)(char*)(int)this;
            if (v_l64_r != 0) {
                if ((int)*(int*)((char*)v_l64_r - 4) != 0) {
                    v_l60_g = v_l64_r;
                    FUN_00f47380((unsigned int)v_l60_g);
                }
            }
            *(int*)(char*)(int)this = v_l12_40;
            *(int*)((char*)(int)this + 8) = (int)(int)((v_l8 << 4) + (int)*(int*)(char*)(int)this);
        } else {
            if ((unsigned int)v_l8 > (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) >> 4)) {
                v_l92_h = (int)(int)*(int*)(char*)(int)this;
                v_l88_j = (int)(int)((int)((int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) >> 4) << 4) + (int)*(int*)(char*)a4);
                v_l84_m = (int)(int)*(int*)(char*)a4;
                v_l70_i = (unsigned char)0;
                v_l69_k = (unsigned char)0;
                v_l71 = (unsigned char)0;
                v_l80 = v_l92_h;
                v_l76_r = v_l84_m;
                for (; v_l76_r != v_l88_j; v_l80 = v_l80 + 16, v_l76_r = v_l76_r + 16) {
                    *(S4*)v_l80 = *(S4*)v_l76_r;
                }
                v_l140 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l136_22 = (int)(int)*(int*)((char*)a4 + 4);
                v_l132_19 = (int)(int)((int)((int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) >> 4) << 4) + (int)*(int*)(char*)a4);
                v_l104_70 = v_l140;
                v_l108 = v_l136_22;
                v_l112_10 = v_l132_19;
                FUN_00537a40((unsigned int)(int)&v_l96_e, (unsigned int)v_l112_10, (unsigned int)v_l108, (unsigned int)v_l104_70, (unsigned int)(int)v_l98_c);
            } else {
                v_l164_60 = (int)(int)*(int*)(char*)(int)this;
                v_l160_c = (int)(int)*(int*)((char*)a4 + 4);
                v_l156 = (int)(int)*(int*)(char*)a4;
                v_l142 = (unsigned char)0;
                v_l141_20 = (unsigned char)0;
                v_l143_10 = (unsigned char)0;
                v_l152_13 = v_l164_60;
                v_l148_20 = v_l156;
                for (; v_l148_20 != v_l160_c; v_l152_13 = v_l152_13 + 16, v_l148_20 = v_l148_20 + 16) {
                    *(S4*)v_l152_13 = *(S4*)v_l148_20;
                }
                v_l16_i = v_l152_13;
                v_l168_20 = v_l16_i;
                for (; (unsigned int)v_l168_20 < (unsigned int)*(int*)((char*)(int)this + 4); v_l168_20 = v_l168_20 + 16) {
                }
            }
        }
        *(int*)((char*)(int)this + 4) = (int)(int)((v_l8 << 4) + (int)*(int*)(char*)(int)this);
    }
    return (int)this;
}
