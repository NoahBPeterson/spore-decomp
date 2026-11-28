// 0x00521ba0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/SPSkinnerPaintSystem.cpp, match/slices/s005218e0/s005218e0.cpp.

extern "C" unsigned char g_01485720[];
extern "C" unsigned char g_015fd918[];
extern "C" unsigned char g_016778dc[];
extern "C" void __cdecl FUN_0040cf10(...);
struct C_00453540 { void FUN_00453540(); };
struct C_00506590 { void FUN_00506590(unsigned int); };
struct C_00521d70 { void FUN_00521d70(unsigned int); };
struct C_00522720 { int FUN_00522720(); };
struct C_00522b40 { void FUN_00522b40(unsigned int, unsigned int); };
struct C_00936090 { int FUN_00936090(unsigned int); };
#pragma pack(push, 1)
struct il2c_pi_4_int_8919c3cc { char pad[4]; int x; __forceinline int f() { return (int)((int)x++ + 1); } };
#pragma pack(pop)
template<class T> __forceinline T il2c_k(T v) { return v; }


struct D_00521ba0 { void FUN_00521ba0(int a4); };
// @ 0x00521ba0
void D_00521ba0::FUN_00521ba0(int a4)
{
    int v_l36_c;
    int v_l32_p;
    int v_l28_g;
    int v_l24;
    int v_l20_q;
    int v_l16_i;
    float v_l12_40;
    float v_l8;
    int dead_0[6];
    int v_l72_e;
    int v_l68_6;
    int v_l64;
    int v_l92_c;
    int v_l88;
    int v_l84_i;
    int v_l80_d;
    int v_l76;
    int v_l112;
    int v_l108_38;
    int dead_1[3];
    v_l24 = (int)(int)*(int*)((char*)(int)this + 28);
    if (v_l24 != 0) {
        v_l16_i = (int)g_016778dc;
        v_l20_q = (int)(int)*(int*)(char*)v_l16_i;
        ((C_00936090*)v_l16_i)->FUN_00936090((unsigned int)(int)*(int*)((char*)(int)this + 88));
        v_l28_g = (int)(int)*(int*)((char*)(int)this + 12);
        if ((int)*(int*)((char*)v_l28_g + 16) == 0) {
            v_l32_p = (int)(int)*(int*)((char*)(int)this + 28);
            v_l36_c = (int)(int)*(int*)((char*)(int)this + 12);
            ((C_00506590*)v_l36_c)->FUN_00506590((unsigned int)(int)*(int*)((char*)v_l32_p + 92));
        }
        ((C_00521d70*)(int)this)->FUN_00521d70((unsigned int)a4);
        v_l12_40 = (float)*(float*)g_01485720;
        v_l8 = (float)*(float*)g_01485720;
        FUN_0040cf10((unsigned int)*(int*)g_015fd918, (unsigned int)1976403177, (unsigned int)(int)(int)&v_l12_40);
        FUN_0040cf10((unsigned int)*(int*)g_015fd918, (unsigned int)-353190763, (unsigned int)(int)(int)&v_l8);
        v_l64 = (int)(int)*(int*)((char*)(int)this + 12);
        v_l68_6 = (int)(int)*(int*)((char*)(int)this + 28);
        *(float*)((char*)v_l68_6 + 112) = *(float*)((char*)v_l64 + 40);
        v_l72_e = (int)(int)*(int*)((char*)(int)this + 12);
        v_l76 = (int)(int)*(int*)((char*)(int)this + 28);
        *(float*)((char*)v_l76 + 116) = (float)(*(float*)((char*)v_l72_e + 36) * v_l12_40);
        v_l80_d = (int)(int)*(int*)((char*)(int)this + 12);
        v_l84_i = (int)(int)*(int*)((char*)(int)this + 28);
        *(float*)((char*)v_l84_i + 120) = (float)(*(float*)((char*)v_l80_d + 32) * v_l8);
        if ((int)(unsigned char)((C_00522720*)(int)this)->FUN_00522720() == 0) {
            v_l88 = (int)(int)*(int*)((char*)(int)this + 28);
            *(unsigned char*)((char*)v_l88 + 108) = (unsigned char)1;
            ((C_00522b40*)(int)this)->FUN_00522b40((unsigned int)0, (unsigned int)0);
            v_l108_38 = (int)this + 28;
            if ((int)*(int*)(char*)v_l108_38 != 0) {
                v_l92_c = (int)(int)*(int*)(char*)v_l108_38;
                if (il2c_k(0) != 0) {
                    ((il2c_pi_4_int_8919c3cc*)(il2c_k((char*)0)))->f();
                }
                *(int*)(char*)v_l108_38 = 0;
                if (v_l92_c != 0) {
                    ((C_00453540*)v_l92_c)->FUN_00453540();
                }
            }
        }
        v_l112 = (int)(int)*(int*)(char*)v_l16_i;
        *(int*)((char*)(int)this + 88) = v_l112;
        ((C_00936090*)v_l16_i)->FUN_00936090((unsigned int)v_l20_q);
    }
    return;
}
