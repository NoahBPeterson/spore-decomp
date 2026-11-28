// 0x0049fee0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/SPEditorManipulationUtilities.cpp, match/slices/s0049fbd0/s0049fbd0.cpp.

struct C_00425990 { int FUN_00425990(); };
struct C_00488850 { void FUN_00488850(); };
struct C_00488900 { void FUN_00488900(); };
struct C_00488980 { void FUN_00488980(); };
struct C_004891a0 { void FUN_004891a0(unsigned int, unsigned int, unsigned int); };
struct C_00489ae0 { void FUN_00489ae0(); };
extern "C" void __cdecl FUN_004a0020(...);
template<class T> __forceinline bool il2c_nz(T v) { return v != 0; }
template<class T> __forceinline T il2c_k(T v) { return v; }

// @ 0x0049fee0
// @ 0x0049fee0
extern "C" void __cdecl FUN_0049fee0(int a4, int a8)
{
    int v_l24;
    int v_l20_q;
    int v_l16_i;
    int dead_0_15[2];
    int v_l28;
    int v_l32;
    int dead_3[3];
    int v_l144_42;
    unsigned char v_l137_10;
    int v_l136_61;
    int v_l132_d;
    int dead_2_17;
    int v_l124_19[15];
    int dead_1[8];
    v_l24 = 0;
    v_l20_q = 0;
    v_l16_i = 0;
    FUN_004a0020((unsigned int)a4, (unsigned int)(int)&v_l24, (unsigned int)(int)(unsigned char)a8);
    v_l32 = 0;
    v_l28 = v_l20_q - v_l24 >> 2;
    for (; v_l32 < v_l28; v_l32 = v_l32 + 1) {
        v_l132_d = v_l24 + (v_l32 << 2);
        if (il2c_k((unsigned int)11) < (unsigned int)60) {
            v_l136_61 = (int)(int)*(int*)((char*)(int)*(int*)(char*)v_l132_d + (int)(il2c_k((unsigned int)11) >> 5) * 4 + 3528);
            v_l137_10 = (unsigned char)(unsigned char)(unsigned char)il2c_nz((int)(int)((int)(1 << (int)(unsigned int)(il2c_k((unsigned int)11) % (unsigned int)32)) & v_l136_61));
        } else {
            v_l137_10 = (unsigned char)0;
        }
        if ((int)v_l137_10 != 0) {
            ((C_00488850*)(int)&v_l124_19)->FUN_00488850();
            ((C_004891a0*)(int)&v_l124_19)->FUN_004891a0((unsigned int)(int)*(int*)((char*)v_l24 + v_l32 * 4), (unsigned int)0, (unsigned int)0);
            ((C_00489ae0*)(int)&v_l124_19)->FUN_00489ae0();
            ((C_00488980*)(int)&v_l124_19)->FUN_00488980();
            ((C_00488900*)(int)&v_l124_19)->FUN_00488900();
        }
    }
    v_l144_42 = v_l24;
    for (; (unsigned int)v_l144_42 < (unsigned int)v_l20_q; v_l144_42 = v_l144_42 + 4) {
    }
    ((C_00425990*)(int)&v_l24)->FUN_00425990();
    return;
}
