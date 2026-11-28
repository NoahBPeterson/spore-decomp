// 0x0041e0d0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/SPEditorBaker.cpp, match/slices/s0041dd90/s0041dd90.cpp, match/slices/s0042f9d0/s0042f9d0.cpp.

struct C_0042e4b0 { int FUN_0042e4b0(unsigned int, unsigned int, unsigned int); };
extern "C" void __cdecl FUN_0042e510(...);
struct C_00537dc0 { void FUN_00537dc0(unsigned int); };
extern "C" void __cdecl FUN_00f47380(...);


struct D_0041e0d0 { int FUN_0041e0d0(int a4); };
// @ 0x0041e0d0
// @ 0x0041e0d0
int D_0041e0d0::FUN_0041e0d0(int a4)
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
        v_l8 = (int)(int)((int)((int)*(int*)((char*)a4 + 4) - (int)*(int*)(char*)a4) / 56);
        if ((unsigned int)v_l8 > (unsigned int)(int)((int)(int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) / 56)) {
            v_l12_40 = (int)((C_0042e4b0*)(int)this)->FUN_0042e4b0((unsigned int)v_l8, (unsigned int)(int)*(int*)(char*)a4, (unsigned int)(int)*(int*)((char*)a4 + 4));
            v_l56_j = (int)(int)*(int*)(char*)(int)this;
            for (; (unsigned int)v_l56_j < (unsigned int)*(int*)((char*)(int)this + 4); v_l56_j = v_l56_j + 56) {
            }
            v_l68 = (int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) / 56);
            v_l64_r = (int)(int)*(int*)(char*)(int)this;
            if (v_l64_r != 0) {
                if ((int)*(int*)((char*)v_l64_r - 4) != 0) {
                    v_l60_g = v_l64_r;
                    FUN_00f47380((unsigned int)v_l60_g);
                }
            }
            *(int*)(char*)(int)this = v_l12_40;
            *(int*)((char*)(int)this + 8) = (int)(int)(v_l8 * 56 + (int)*(int*)(char*)(int)this);
        } else {
            if ((unsigned int)v_l8 > (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 56)) {
                v_l92_c = (int)(int)*(int*)(char*)(int)this;
                v_l88 = (int)(int)((int)((int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 56) * 56) + (int)*(int*)(char*)a4);
                v_l84_m = (int)(int)*(int*)(char*)a4;
                v_l70_i = (unsigned char)0;
                v_l69_k = (unsigned char)0;
                v_l71 = (unsigned char)0;
                v_l80 = v_l92_c;
                v_l76_r = v_l84_m;
                for (; v_l76_r != v_l88; v_l80 = v_l80 + 56, v_l76_r = v_l76_r + 56) {
                    ((C_00537dc0*)v_l80)->FUN_00537dc0((unsigned int)v_l76_r);
                }
                FUN_0042e510((unsigned int)(int)((int)((int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 56) * 56) + (int)*(int*)(char*)a4), (unsigned int)(int)*(int*)((char*)a4 + 4), (unsigned int)(int)*(int*)((char*)(int)this + 4));
            } else {
                v_l164_60 = (int)(int)*(int*)(char*)(int)this;
                v_l160_c = (int)(int)*(int*)((char*)a4 + 4);
                v_l156 = (int)(int)*(int*)(char*)a4;
                v_l142 = (unsigned char)0;
                v_l141_33 = (unsigned char)0;
                v_l143_10 = (unsigned char)0;
                v_l152_13 = v_l164_60;
                v_l148_20 = v_l156;
                for (; v_l148_20 != v_l160_c; v_l152_13 = v_l152_13 + 56, v_l148_20 = v_l148_20 + 56) {
                    ((C_00537dc0*)v_l152_13)->FUN_00537dc0((unsigned int)v_l148_20);
                }
                v_l16_i = v_l152_13;
                v_l168_20 = v_l16_i;
                for (; (unsigned int)v_l168_20 < (unsigned int)*(int*)((char*)(int)this + 4); v_l168_20 = v_l168_20 + 56) {
                }
            }
        }
        *(int*)((char*)(int)this + 4) = (int)(int)(v_l8 * 56 + (int)*(int*)(char*)(int)this);
    }
    return (int)this;
}
