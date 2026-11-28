// 0x0044eea0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/SPEditorBlock.cpp, match/slices/s0044e460/s0044e460.cpp.

struct C_0044ea80 { void FUN_0044ea80(); };
struct C_0044eea0 { void FUN_0044eea0(); };
template<class T> __forceinline bool il2c_nz(T v) { return v != 0; }
template<class T> __forceinline T il2c_k(T v) { return v; }


struct D_0044eea0 { void FUN_0044eea0(); };
// @ 0x0044eea0
// @ 0x0044eea0
void D_0044eea0::FUN_0044eea0()
{
    int v_l24;
    unsigned char v_l17;
    int v_l16_i;
    int v_l12_40;
    int v_l8;
    int v_l28;
    int v_l36_i;
    int v_l32;
    int v_l52;
    int v_l48_y;
    int v_l44_e;
    int v_l40;
    if (il2c_k((unsigned int)57) < (unsigned int)60) {
        v_l16_i = (int)(int)*(int*)((char*)(int)this + (int)(il2c_k((unsigned int)57) >> 5) * 4 + 3528);
        v_l17 = (unsigned char)(unsigned char)(unsigned char)il2c_nz((int)(int)((int)(1 << (int)(unsigned int)(il2c_k((unsigned int)57) % (unsigned int)32)) & v_l16_i));
    } else {
        v_l17 = (unsigned char)0;
    }
    if ((int)v_l17 != 0) {
        v_l12_40 = 0;
        v_l24 = (int)this + 832;
        v_l8 = (int)(int)((int)((int)*(int*)((char*)v_l24 + 4) - (int)*(int*)(char*)v_l24) >> 2);
        for (; v_l12_40 < v_l8; v_l12_40 = v_l12_40 + 1) {
            v_l28 = (int)(int)((int)*(int*)((char*)(int)this + 832) + (v_l12_40 << 2));
            v_l32 = (int)(int)*(int*)(char*)v_l28;
            v_l36_i = (int)(int)*(int*)((char*)v_l32 + 992);
            if (v_l36_i != 0) {
                v_l40 = (int)(int)((int)*(int*)((char*)(int)this + 832) + (v_l12_40 << 2));
                v_l44_e = (int)(int)*(int*)(char*)v_l40;
                ((C_0044ea80*)v_l44_e)->FUN_0044ea80();
            } else {
                v_l48_y = (int)(int)((int)*(int*)((char*)(int)this + 832) + (v_l12_40 << 2));
                v_l52 = (int)(int)*(int*)(char*)v_l48_y;
                ((C_0044eea0*)v_l52)->FUN_0044eea0();
            }
        }
    }
    return;
}
