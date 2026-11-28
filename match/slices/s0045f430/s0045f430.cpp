// 0x0045f430: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0045edf0/s0045edf0.cpp.

extern "C" unsigned char g_013eb430[];
extern "C" unsigned char g_013ebb38[];
struct C_00429300 { void FUN_00429300(); };
extern "C" int __cdecl FUN_00f473a0(...);
extern "C" void __cdecl FUN_011e0744(...);


struct D_0045f430 { int FUN_0045f430(int a4, int a8); };
// @ 0x0045f430
int D_0045f430::FUN_0045f430(int a4, int a8)
{
    int v_l24;
    int v_l20_q;
    int v_l16_i;
    int v_l12_40;
    int v_l8;
    int v_l28;
    int v_l36_i;
    int v_l32;
    int dead_0_d[3];
    int v_l56_b;
    int v_l52;
    int v_l48_y;
    int v_l44_e;
    int v_l40;
    int v_l72;
    if (a4 != a8) {
        v_l8 = (int)(int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this);
        v_l12_40 = a8 - a4;
        v_l16_i = (int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) - 1);
        if ((unsigned int)(v_l8 + v_l12_40) > (unsigned int)v_l16_i) {
            v_l36_i = v_l8 + v_l12_40;
            v_l40 = (int)(int)((unsigned int)v_l16_i > (unsigned int)8 ? v_l16_i << 1 : 8);
            v_l44_e = (int)(int)((unsigned int)v_l40 < (unsigned int)v_l36_i ? (int)&v_l36_i : (int)&v_l40);
            v_l24 = (int)(int)((int)*(int*)(char*)v_l44_e + 1);
            v_l48_y = (int)(int)FUN_00f473a0((unsigned int)v_l24, (unsigned int)(int)g_013eb430, (unsigned int)0, (unsigned int)0, (unsigned int)(int)g_013ebb38, (unsigned int)209);
            v_l28 = v_l48_y;
            v_l20_q = v_l28;
            v_l56_b = (int)(int)*(int*)((char*)(int)this + 4);
            v_l52 = (int)(int)*(int*)(char*)(int)this;
            FUN_011e0744((unsigned int)v_l28, (unsigned int)v_l52, (unsigned int)(v_l56_b - v_l52));
            v_l20_q = v_l56_b - v_l52 + v_l28;
            FUN_011e0744((unsigned int)v_l20_q, (unsigned int)a4, (unsigned int)(a8 - a4));
            v_l20_q = a8 - a4 + v_l20_q;
            *(unsigned char*)(char*)v_l20_q = (unsigned char)0;
            ((C_00429300*)(int)this)->FUN_00429300();
            *(int*)(char*)(int)this = v_l28;
            *(int*)((char*)(int)this + 4) = v_l20_q;
            *(int*)((char*)(int)this + 8) = v_l28 + v_l24;
        } else {
            v_l32 = a4;
            v_l32 = v_l32 + 1;
            v_l72 = (int)(int)((int)*(int*)((char*)(int)this + 4) + 1);
            FUN_011e0744((unsigned int)v_l72, (unsigned int)v_l32, (unsigned int)(a8 - v_l32));
            *(unsigned char*)((char*)(int)*(int*)((char*)(int)this + 4) + v_l12_40) = (unsigned char)0;
            *(unsigned char*)(char*)(int)*(int*)((char*)(int)this + 4) = (unsigned char)(unsigned char)*(unsigned char*)(char*)a4;
            *(int*)((char*)(int)this + 4) = (int)(int)((int)*(int*)((char*)(int)this + 4) + v_l12_40);
        }
    }
    return (int)this;
}
