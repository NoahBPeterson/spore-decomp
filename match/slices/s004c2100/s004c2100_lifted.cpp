// 0x004c2100: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPCastingManager.cpp, match/slices/s004c2100/s004c2100.cpp.

struct C_0042f280 { void FUN_0042f280(unsigned int); };
struct C_004c0b80 { int FUN_004c0b80(); };
struct C_004c2740 { void FUN_004c2740(unsigned int); };
__forceinline bool il2c_cc_e(int a, int b) { return a == b; }
template<class T> __forceinline T il2c_k(T v) { return v; }


struct D_004c2100 { void FUN_004c2100(int a4); };
// @ 0x004c2100
void D_004c2100::FUN_004c2100(int a4)
{
    int v_l32_p;
    int v_l28_g;
    int v_l24;
    int dead_0_15[4];
    int v_l60_b;
    int v_l56_d;
    int v_l52_i;
    int v_l48_i;
    int v_l44;
    int v_l40_w;
    int v_l36;
    int v_l72_e;
    int v_l68_6;
    int v_l64;
    int v_l84_i;
    int v_l80_d;
    int v_l76;
    int dead_3[3];
    int v_l160_37;
    int dead_2_17[3];
    int dead_1[15];
    if (il2c_k(0) != 0) {
        v_l32_p = (int)(int)*(int*)(char*)(int)this;
        *(int*)(char*)(int)this = (int)(int)*(int*)(char*)a4;
        *(int*)(char*)a4 = v_l32_p;
        v_l44 = a4 + 4;
        v_l40_w = (int)this + 4;
        v_l36 = (int)(int)*(int*)(char*)v_l40_w;
        *(int*)(char*)v_l40_w = (int)(int)*(int*)(char*)v_l44;
        *(int*)(char*)v_l44 = v_l36;
        v_l56_d = a4 + 8;
        v_l52_i = (int)this + 8;
        v_l48_i = (int)(int)*(int*)(char*)v_l52_i;
        *(int*)(char*)v_l52_i = (int)(int)*(int*)(char*)v_l56_d;
        *(int*)(char*)v_l56_d = v_l48_i;
    } else {
        if ((int)(unsigned char)il2c_cc_e((int)this + 12, a4 + 12) != 0) {
            v_l60_b = (int)(int)*(int*)(char*)(int)this;
            *(int*)(char*)(int)this = (int)(int)*(int*)(char*)a4;
            *(int*)(char*)a4 = v_l60_b;
            v_l72_e = a4 + 4;
            v_l68_6 = (int)this + 4;
            v_l64 = (int)(int)*(int*)(char*)v_l68_6;
            *(int*)(char*)v_l68_6 = (int)(int)*(int*)(char*)v_l72_e;
            *(int*)(char*)v_l72_e = v_l64;
            v_l84_i = a4 + 8;
            v_l80_d = (int)this + 8;
            v_l76 = (int)(int)*(int*)(char*)v_l80_d;
            *(int*)(char*)v_l80_d = (int)(int)*(int*)(char*)v_l84_i;
            *(int*)(char*)v_l84_i = v_l76;
        } else {
            ((C_0042f280*)(int)&v_l28_g)->FUN_0042f280((unsigned int)(int)this);
            ((C_004c2740*)(int)this)->FUN_004c2740((unsigned int)a4);
            ((C_004c2740*)a4)->FUN_004c2740((unsigned int)(int)&v_l28_g);
            v_l160_37 = v_l28_g;
            for (; (unsigned int)v_l160_37 < (unsigned int)v_l24; v_l160_37 = v_l160_37 + 4) {
            }
            ((C_004c0b80*)(int)&v_l28_g)->FUN_004c0b80();
        }
    }
    return;
}
