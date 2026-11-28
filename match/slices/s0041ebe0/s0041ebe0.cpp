// 0x0041ebe0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/SPEditorBaker.cpp, src/game/SPEngine/SPGraphicsChartPacker.cpp, match/slices/s0041e730/s0041e730.cpp, match/slices/s006e0030/s006e0030.cpp, match/slices/s0042f9d0/s0042f9d0.cpp, src/game/SPGonzago/_at_00410000.cpp.

struct C_00404f90 { void FUN_00404f90(); };
struct C_00423ef0 { int FUN_00423ef0(unsigned int, unsigned int, unsigned int); };
extern "C" void __cdecl FUN_00423f50(...);
extern "C" int __cdecl FUN_0042d4a0(...);
extern "C" void __cdecl FUN_00f47380(...);
__forceinline void il2c_d_FUN_00f47380(int p, int fl) { if (fl & 1) FUN_00f47380((unsigned int)(p)); }


struct D_0041ebe0 { int FUN_0041ebe0(int a4); };
// @ 0x0041ebe0
// @ 0x0041ebe0
int D_0041ebe0::FUN_0041ebe0(int a4)
{
    int v_l80_c;
    int v_l76_q;
    int v_l72_k;
    int v_l68_t;
    int dead_0_15[12];
    int v_l16_i;
    int v_l12_40;
    int v_l8;
    unsigned char v_l85_c;
    int v_l84;
    int v_l112_d;
    int v_l108_14;
    int dead_3_d[4];
    char dead_2_16;
    char dead_1_32;
    unsigned char v_l86;
    char dead_5_22;
    unsigned char v_l170_23;
    unsigned char v_l169;
    int dead_4_10[13];
    int v_l116;
    char dead_6;
    int v_l204_19;
    int dead_7[7];
    int v_l228_30;
    int dead_8_40[3];
    int v_l212;
    int v_l208;
    int v_l232;
    if (a4 != (int)this) {
        v_l8 = (int)(int)((int)((int)*(int*)((char*)a4 + 4) - (int)*(int*)(char*)a4) >> 2);
        if ((unsigned int)v_l8 > (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) >> 2)) {
            v_l12_40 = (int)((C_00423ef0*)(int)this)->FUN_00423ef0((unsigned int)v_l8, (unsigned int)(int)*(int*)(char*)a4, (unsigned int)(int)*(int*)((char*)a4 + 4));
            v_l72_k = (int)(int)*(int*)((char*)(int)this + 4);
            v_l68_t = (int)(int)*(int*)(char*)(int)this;
            for (; (unsigned int)v_l68_t < (unsigned int)v_l72_k; v_l68_t = v_l68_t + 4) {
                if ((int)*(int*)(char*)v_l68_t != 0) {
                    ((C_00404f90*)(int)*(int*)(char*)v_l68_t)->FUN_00404f90();
                }
                il2c_d_FUN_00f47380(v_l68_t, 0);
            }
            v_l84 = (int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) >> 2);
            v_l80_c = (int)(int)*(int*)(char*)(int)this;
            if (v_l80_c != 0) {
                if ((int)*(int*)((char*)v_l80_c - 4) != 0) {
                    v_l76_q = v_l80_c;
                    FUN_00f47380((unsigned int)v_l76_q);
                }
            }
            *(int*)(char*)(int)this = v_l12_40;
            *(int*)((char*)(int)this + 8) = (int)(int)((int)*(int*)(char*)(int)this + (v_l8 << 2));
        } else {
            if ((unsigned int)v_l8 > (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) >> 2)) {
                v_l116 = (int)(int)*(int*)(char*)(int)this;
                v_l112_d = (int)(int)((int)*(int*)(char*)a4 + (int)((int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) >> 2) << 2));
                v_l108_14 = (int)(int)*(int*)(char*)a4;
                v_l86 = (unsigned char)0;
                v_l85_c = (unsigned char)0;
                FUN_0042d4a0((unsigned int)v_l108_14, (unsigned int)v_l112_d, (unsigned int)v_l116);
                FUN_00423f50((unsigned int)(int)((int)*(int*)(char*)a4 + (int)((int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) >> 2) << 2)), (unsigned int)(int)*(int*)((char*)a4 + 4), (unsigned int)(int)*(int*)((char*)(int)this + 4));
            } else {
                v_l212 = (int)(int)*(int*)(char*)(int)this;
                v_l208 = (int)(int)*(int*)((char*)a4 + 4);
                v_l204_19 = (int)(int)*(int*)(char*)a4;
                v_l170_23 = (unsigned char)0;
                v_l169 = (unsigned char)0;
                v_l16_i = (int)(int)FUN_0042d4a0((unsigned int)v_l204_19, (unsigned int)v_l208, (unsigned int)v_l212);
                v_l232 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l228_30 = v_l16_i;
                for (; (unsigned int)v_l228_30 < (unsigned int)v_l232; v_l228_30 = v_l228_30 + 4) {
                    if ((int)*(int*)(char*)v_l228_30 != 0) {
                        ((C_00404f90*)(int)*(int*)(char*)v_l228_30)->FUN_00404f90();
                    }
                    il2c_d_FUN_00f47380(v_l228_30, 0);
                }
            }
        }
        *(int*)((char*)(int)this + 4) = (int)(int)((int)*(int*)(char*)(int)this + (v_l8 << 2));
    }
    return (int)this;
}
