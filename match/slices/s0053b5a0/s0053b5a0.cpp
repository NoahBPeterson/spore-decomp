// 0x0053b5a0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/SPSkinPaintParticleDescription.cpp, match/slices/s0053acc0/s0053acc0.cpp.

extern "C" void __cdecl FUN_00537240(...);
struct C_0053cd20 { int FUN_0053cd20(unsigned int, unsigned int, unsigned int); };
extern "C" void __cdecl FUN_00f47380(...);
struct S5 { int m0; int m1; int m2; int m3; int m4; };


struct D_0053b5a0 { int FUN_0053b5a0(int a4); };
// @ 0x0053b5a0
// @ 0x0053b5a0
int D_0053b5a0::FUN_0053b5a0(int a4)
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
    int v_l164;
    int v_l160_10;
    int v_l156_10;
    int v_l152_14;
    int v_l148_28;
    int v_l144_19;
    unsigned char v_l139_18;
    unsigned char v_l138;
    unsigned char v_l137;
    int dead_1_c[11];
    int v_l92_h;
    int v_l88_j;
    int v_l84_m;
    int v_l80;
    if (a4 != (int)this) {
        v_l8 = (int)(int)((int)((int)*(int*)((char*)a4 + 4) - (int)*(int*)(char*)a4) / 20);
        if ((unsigned int)v_l8 > (unsigned int)(int)((int)(int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) / 20)) {
            v_l12_40 = (int)((C_0053cd20*)(int)this)->FUN_0053cd20((unsigned int)v_l8, (unsigned int)(int)*(int*)(char*)a4, (unsigned int)(int)*(int*)((char*)a4 + 4));
            v_l56_j = (int)(int)*(int*)(char*)(int)this;
            for (; (unsigned int)v_l56_j < (unsigned int)*(int*)((char*)(int)this + 4); v_l56_j = v_l56_j + 20) {
            }
            v_l68 = (int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) / 20);
            v_l64_r = (int)(int)*(int*)(char*)(int)this;
            if (v_l64_r != 0) {
                if ((int)*(int*)((char*)v_l64_r - 4) != 0) {
                    v_l60_g = v_l64_r;
                    FUN_00f47380((unsigned int)v_l60_g);
                }
            }
            *(int*)(char*)(int)this = v_l12_40;
            *(int*)((char*)(int)this + 8) = (int)(int)(v_l8 * 20 + (int)*(int*)(char*)(int)this);
        } else {
            if ((unsigned int)v_l8 > (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 20)) {
                v_l92_h = (int)(int)*(int*)(char*)(int)this;
                v_l88_j = (int)(int)((int)((int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 20) * 20) + (int)*(int*)(char*)a4);
                v_l84_m = (int)(int)*(int*)(char*)a4;
                v_l70_i = (unsigned char)0;
                v_l69_k = (unsigned char)0;
                v_l71 = (unsigned char)0;
                v_l80 = v_l92_h;
                v_l76_r = v_l84_m;
                for (; v_l76_r != v_l88_j; v_l80 = v_l80 + 20, v_l76_r = v_l76_r + 20) {
                    *(S5*)v_l80 = *(S5*)v_l76_r;
                }
                FUN_00537240((unsigned int)(int)((int)((int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 20) * 20) + (int)*(int*)(char*)a4), (unsigned int)(int)*(int*)((char*)a4 + 4), (unsigned int)(int)*(int*)((char*)(int)this + 4));
            } else {
                v_l160_10 = (int)(int)*(int*)(char*)(int)this;
                v_l156_10 = (int)(int)*(int*)((char*)a4 + 4);
                v_l152_14 = (int)(int)*(int*)(char*)a4;
                v_l138 = (unsigned char)0;
                v_l137 = (unsigned char)0;
                v_l139_18 = (unsigned char)0;
                v_l148_28 = v_l160_10;
                v_l144_19 = v_l152_14;
                for (; v_l144_19 != v_l156_10; v_l148_28 = v_l148_28 + 20, v_l144_19 = v_l144_19 + 20) {
                    *(S5*)v_l148_28 = *(S5*)v_l144_19;
                }
                v_l16_i = v_l148_28;
                v_l164 = v_l16_i;
                for (; (unsigned int)v_l164 < (unsigned int)*(int*)((char*)(int)this + 4); v_l164 = v_l164 + 20) {
                }
            }
        }
        *(int*)((char*)(int)this + 4) = (int)(int)(v_l8 * 20 + (int)*(int*)(char*)(int)this);
    }
    return (int)this;
}
