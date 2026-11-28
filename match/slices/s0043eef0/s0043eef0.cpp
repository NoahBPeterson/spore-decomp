// 0x0043eef0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/SPEditorBlock.cpp, match/slices/s0043e3f0/s0043e3f0.cpp.

extern "C" unsigned char g_01485378[];
struct C_00409c00 { void FUN_00409c00(); };
struct C_0041bd50 { void FUN_0041bd50(unsigned int); };
struct C_0043f050 { void FUN_0043f050(unsigned int); };
struct C_0043f3a0 { double FUN_0043f3a0(); };
struct C_0044ae00 { int FUN_0044ae00(unsigned int, unsigned int, unsigned int, unsigned int); };
struct C_00511140 { void FUN_00511140(unsigned int); };
template<class T> __forceinline bool il2c_nz(T v) { return v != 0; }
template<class T> __forceinline T il2c_k(T v) { return v; }


struct D_0043eef0 { int FUN_0043eef0(int a4); };
// @ 0x0043eef0
// @ 0x0043eef0
int D_0043eef0::FUN_0043eef0(int a4)
{
    int v_l32_p[6];
    float v_l8;
    char dead_1_c;
    unsigned char v_l117_14;
    int v_l116_47;
    unsigned char v_l109_19;
    int v_l108;
    int dead_0_13[6];
    int v_l80[6];
    float v_l56_d;
    float v_l52_i;
    float v_l48_i;
    float v_l44;
    float v_l40_w;
    float v_l36;
    char dead_2;
    int dead_4_35[2];
    char dead_3;
    ((C_00409c00*)(int)&v_l32_p)->FUN_00409c00();
    v_l8 = (float)(double)((C_0043f3a0*)(int)this)->FUN_0043f3a0();
    v_l44 = (float)v_l8;
    v_l40_w = (float)*(float*)g_01485378;
    v_l36 = (float)*(float*)g_01485378;
    ((C_0041bd50*)(int)&v_l32_p)->FUN_0041bd50((unsigned int)(int)(int)&v_l44);
    v_l56_d = (float)-(float)v_l8;
    v_l52_i = (float)*(float*)g_01485378;
    v_l48_i = (float)*(float*)g_01485378;
    ((C_0041bd50*)(int)&v_l32_p)->FUN_0041bd50((unsigned int)(int)(int)&v_l56_d);
    if (il2c_k((unsigned int)11) < (unsigned int)60) {
        v_l108 = (int)(int)*(int*)((char*)(int)this + (int)(il2c_k((unsigned int)11) >> 5) * 4 + 3528);
        v_l109_19 = (unsigned char)(unsigned char)(unsigned char)il2c_nz((int)(int)((int)(1 << (int)(unsigned int)(il2c_k((unsigned int)11) % (unsigned int)32)) & v_l108));
    } else {
        v_l109_19 = (unsigned char)0;
    }
    if ((int)v_l109_19 == 0) {
        if (il2c_k((unsigned int)20) < (unsigned int)60) {
            v_l116_47 = (int)(int)*(int*)((char*)(int)this + (int)(il2c_k((unsigned int)20) >> 5) * 4 + 3528);
            v_l117_14 = (unsigned char)(unsigned char)(unsigned char)il2c_nz((int)(int)((int)(1 << (int)(unsigned int)(il2c_k((unsigned int)20) % (unsigned int)32)) & v_l116_47));
        } else {
            v_l117_14 = (unsigned char)0;
        }
        if ((int)v_l117_14 == 0) {
            ((C_0043f050*)(int)&v_l32_p)->FUN_0043f050((unsigned int)((C_0044ae00*)(int)this)->FUN_0044ae00((unsigned int)(int)&v_l80, (unsigned int)1, (unsigned int)0, (unsigned int)0));
        }
    }
    ((C_00511140*)a4)->FUN_00511140((unsigned int)(int)&v_l32_p);
    return a4;
}
