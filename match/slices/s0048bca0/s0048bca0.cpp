// 0x0048bca0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0048b370/s0048b370.cpp.

extern "C" unsigned char g_01485378[];
template<class T> __forceinline T il2c_k(T v) { return v; }


struct D_0048bca0 { float FUN_0048bca0(); };
// @ 0x0048bca0
float D_0048bca0::FUN_0048bca0()
{
    float v_l24;
    int v_l20_q;
    int v_l16_i;
    float v_l12_40;
    float v_l8;
    int v_l28;
    float v_l36_i;
    int v_l32;
    int v_l52;
    int v_l48_y;
    int v_l44_e;
    int v_l40;
    v_l8 = *(float*)((char*)(int)*(int*)((char*)(int)this + 24) + (il2c_k(2) << 2) + 52);
    v_l12_40 = (float)*(float*)g_01485378;
    v_l20_q = 0;
    v_l40 = (int)this + 64;
    v_l16_i = (int)(int)((int)((int)*(int*)((char*)v_l40 + 4) - (int)*(int*)(char*)v_l40) >> 2);
    for (; v_l20_q < v_l16_i; v_l20_q = v_l20_q + 1) {
        v_l44_e = (int)(int)((int)*(int*)((char*)(int)this + 64) + (v_l20_q << 2));
        v_l24 = (float)((float)v_l8 - (float)*(float*)((char*)(int)*(int*)(char*)v_l44_e + (il2c_k(2) << 2) + 52));
        if ((float)v_l24 > v_l12_40) {
            v_l12_40 = (float)v_l24;
        }
    }
    v_l28 = 0;
    v_l48_y = (int)this + 44;
    v_l32 = (int)(int)((int)((int)*(int*)((char*)v_l48_y + 4) - (int)*(int*)(char*)v_l48_y) >> 2);
    for (; v_l28 < v_l32; v_l28 = v_l28 + 1) {
        v_l52 = (int)(int)((int)*(int*)((char*)(int)this + 44) + (v_l28 << 2));
        v_l36_i = (float)((float)v_l8 - (float)*(float*)((char*)(int)*(int*)(char*)v_l52 + (il2c_k(2) << 2) + 52));
        if ((float)v_l36_i > v_l12_40) {
            v_l12_40 = (float)v_l36_i;
        }
    }
    return (float)v_l12_40;
}
