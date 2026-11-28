// 0x0043f3f0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/SPEditorBlock.cpp, match/slices/s0043f3a0/s0043f3a0.cpp.

struct C_0043eed0 { float FUN_0043eed0(); };
template<class T> __forceinline bool il2c_nz(T v) { return v != 0; }
template<class T> __forceinline T il2c_k(T v) { return v; }


struct D_0043f3f0 { float FUN_0043f3f0(); };
// @ 0x0043f3f0
float D_0043f3f0::FUN_0043f3f0()
{
    int v_l28_g;
    int v_l24;
    int v_l20_q;
    int v_l16_i;
    int v_l12_40;
    int v_l8;
    unsigned char v_l29;
    int v_l36;
    int v_l40;
    v_l12_40 = 0;
    v_l16_i = (int)this + 832;
    v_l8 = (int)(int)((int)((int)*(int*)((char*)v_l16_i + 4) - (int)*(int*)(char*)v_l16_i) >> 2);
    for (; v_l12_40 < v_l8; v_l12_40 = v_l12_40 + 1) {
        v_l20_q = (int)(int)((int)*(int*)((char*)(int)this + 832) + (v_l12_40 << 2));
        v_l24 = (int)(int)*(int*)(char*)v_l20_q;
        if (il2c_k((unsigned int)31) < (unsigned int)60) {
            v_l28_g = (int)(int)*(int*)((char*)v_l24 + (int)(il2c_k((unsigned int)31) >> 5) * 4 + 3528);
            v_l29 = (unsigned char)(unsigned char)(unsigned char)il2c_nz((int)(int)((int)(1 << (int)(unsigned int)(il2c_k((unsigned int)31) % (unsigned int)32)) & v_l28_g));
        } else {
            v_l29 = (unsigned char)0;
        }
        if ((int)v_l29 != 0) {
            v_l36 = (int)(int)((int)*(int*)((char*)(int)this + 832) + (v_l12_40 << 2));
            v_l40 = (int)(int)*(int*)(char*)v_l36;
            return (float)(float)((C_0043eed0*)v_l40)->FUN_0043eed0();
        }
    }
    return (float)(float)1;
}
