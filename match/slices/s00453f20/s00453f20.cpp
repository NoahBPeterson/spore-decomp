// 0x00453f20: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00453250/s00453250.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
};

struct C_00455180 { int FUN_00455180(unsigned int, unsigned int, unsigned int); };
extern "C" void __cdecl FUN_004551e0(...);
extern "C" int __cdecl FUN_004571d0(...);
extern "C" void __cdecl FUN_00f47380(...);
__forceinline void il2c_d_FUN_00f47380(int p, int fl) { if (fl & 1) FUN_00f47380((unsigned int)(p)); }


struct D_00453f20 { int FUN_00453f20(int a4); };
// @ 0x00453f20
int D_00453f20::FUN_00453f20(int a4)
{
    int v_l16_i;
    int v_l12_40;
    int v_l8;
    int v_l60_n;
    int v_l56_w;
    int dead_0[9];
    int v_l72_e;
    int v_l68_6;
    int v_l64;
    int dead_2_15[2];
    char dead_1_10;
    unsigned char v_l75_m;
    unsigned char v_l74;
    unsigned char v_l73;
    unsigned char v_l145_15;
    int dead_3_10[12];
    int v_l96_30;
    int v_l92_c;
    int v_l88;
    int v_l176_33;
    int v_l172_43;
    int v_l168_13;
    int v_l164_39;
    int v_l160_12;
    int dead_5_d[2];
    char dead_4_16;
    unsigned char v_l147_17;
    unsigned char v_l146;
    if (a4 != (int)this) {
        v_l8 = (int)(int)((int)((int)*(int*)((char*)a4 + 4) - (int)*(int*)(char*)a4) >> 2);
        if ((unsigned int)v_l8 > (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) >> 2)) {
            v_l12_40 = (int)((C_00455180*)(int)this)->FUN_00455180((unsigned int)v_l8, (unsigned int)(int)*(int*)(char*)a4, (unsigned int)(int)*(int*)((char*)a4 + 4));
            v_l60_n = (int)(int)*(int*)((char*)(int)this + 4);
            v_l56_w = (int)(int)*(int*)(char*)(int)this;
            for (; (unsigned int)v_l56_w < (unsigned int)v_l60_n; v_l56_w = v_l56_w + 4) {
                if ((int)*(int*)(char*)v_l56_w != 0) {
                    ((il2c_vc0*)(int)*(int*)(char*)v_l56_w)->s2();
                }
                il2c_d_FUN_00f47380(v_l56_w, 0);
            }
            v_l72_e = (int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) >> 2);
            v_l68_6 = (int)(int)*(int*)(char*)(int)this;
            if (v_l68_6 != 0) {
                if ((int)*(int*)((char*)v_l68_6 - 4) != 0) {
                    v_l64 = v_l68_6;
                    FUN_00f47380((unsigned int)v_l64);
                }
            }
            *(int*)(char*)(int)this = v_l12_40;
            *(int*)((char*)(int)this + 8) = (int)(int)((int)*(int*)(char*)(int)this + (v_l8 << 2));
        } else {
            if ((unsigned int)v_l8 > (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) >> 2)) {
                v_l96_30 = (int)(int)*(int*)(char*)(int)this;
                v_l92_c = (int)(int)((int)*(int*)(char*)a4 + (int)((int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) >> 2) << 2));
                v_l88 = (int)(int)*(int*)(char*)a4;
                v_l74 = (unsigned char)0;
                v_l73 = (unsigned char)0;
                v_l75_m = (unsigned char)0;
                FUN_004571d0((unsigned int)v_l88, (unsigned int)v_l92_c, (unsigned int)v_l96_30);
                FUN_004551e0((unsigned int)(int)((int)*(int*)(char*)a4 + (int)((int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) >> 2) << 2)), (unsigned int)(int)*(int*)((char*)a4 + 4), (unsigned int)(int)*(int*)((char*)(int)this + 4));
            } else {
                v_l168_13 = (int)(int)*(int*)(char*)(int)this;
                v_l164_39 = (int)(int)*(int*)((char*)a4 + 4);
                v_l160_12 = (int)(int)*(int*)(char*)a4;
                v_l146 = (unsigned char)0;
                v_l145_15 = (unsigned char)0;
                v_l147_17 = (unsigned char)0;
                v_l16_i = (int)(int)FUN_004571d0((unsigned int)v_l160_12, (unsigned int)v_l164_39, (unsigned int)v_l168_13);
                v_l176_33 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l172_43 = v_l16_i;
                for (; (unsigned int)v_l172_43 < (unsigned int)v_l176_33; v_l172_43 = v_l172_43 + 4) {
                    if ((int)*(int*)(char*)v_l172_43 != 0) {
                        ((il2c_vc1*)(int)*(int*)(char*)v_l172_43)->s2();
                    }
                    il2c_d_FUN_00f47380(v_l172_43, 0);
                }
            }
        }
        *(int*)((char*)(int)this + 4) = (int)(int)((int)*(int*)(char*)(int)this + (v_l8 << 2));
    }
    return (int)this;
}
