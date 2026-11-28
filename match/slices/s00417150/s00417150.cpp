// 0x00417150: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/SPEditorBaker.cpp, match/slices/s00416990/s00416990.cpp.

struct C_00421950 { void FUN_00421950(unsigned int, unsigned int); };
__forceinline bool il2c_cc_ne(int a, int b) { return a != b; }


struct D_00417150 { float FUN_00417150(int a4); };
// @ 0x00417150
// @ 0x00417150
float D_00417150::FUN_00417150(int a4)
{
    int v_l24;
    int v_l20_q;
    int dead_0_15;
    int v_l12_40;
    int v_l8;
    int v_l28;
    int v_l36_i;
    int v_l32;
    int v_l108_38;
    int v_l104_26;
    int v_l100_25;
    int dead_1[15];
    v_l12_40 = a4 + 8;
    v_l36_i = (int)(int)*(int*)((char*)v_l12_40 + 8);
    v_l24 = v_l36_i;
    v_l8 = (int)(int)((int)((unsigned int)v_l24 >> 16) & 255);
    if (v_l8 >= 97) {
        if (v_l8 <= 102) {
            ((C_00421950*)((int)this + (v_l8 - 97 << 5) + 4484))->FUN_00421950((unsigned int)(int)&v_l20_q, (unsigned int)v_l12_40);
            v_l108_38 = (int)this + (v_l8 - 97 << 5) + 4484;
            v_l104_26 = (int)(int)((int)*(int*)((char*)v_l108_38 + 4) + (int)((int)*(int*)((char*)v_l108_38 + 8) << 2));
            v_l100_25 = (int)(int)*(int*)(char*)v_l104_26;
            v_l32 = v_l100_25;
            v_l28 = v_l104_26;
            if ((int)(unsigned char)il2c_cc_ne(v_l20_q, v_l32) != 0) {
                return *(float*)((char*)v_l20_q + 4);
            }
        }
    }
    return (float)(float)0;
}
