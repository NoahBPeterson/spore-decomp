// 0x00545220: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00545220/s00545220.cpp.

struct il2c_gm0 { int m(unsigned int); };
typedef int (il2c_gm0::*il2c_gp0)(unsigned int);

extern "C" unsigned char g_015e2e48[];
extern "C" unsigned char g_015e2e4c[];
struct C_00429520 { void FUN_00429520(unsigned int); };
struct C_00548740 { void FUN_00548740(unsigned int, unsigned int); };

// @ 0x00545220
// @ 0x00545220
extern "C" void __cdecl FUN_00545220(int a4, int a8, int a12)
{
    int v_l24;
    int v_l20_q;
    int v_l16_i;
    int v_l12_40;
    int v_l8;
    int v_l60_n;
    int dead_0[8];
    int v_l68_6;
    int v_l64;
    v_l8 = a4;
    v_l16_i = (int)(int)*(int*)((char*)v_l8 + 32);
    if (v_l16_i != 0) {
        ((C_00429520*)(v_l8 + 16))->FUN_00429520((unsigned int)0);
        ((C_00548740*)(int)g_015e2e48)->FUN_00548740((unsigned int)(int)&v_l24, (unsigned int)(int)&a8);
        if (v_l24 != v_l20_q) {
            v_l12_40 = v_l24;
        } else {
            v_l60_n = *(int*)g_015e2e4c;
            v_l12_40 = v_l60_n;
        }
        v_l64 = *(int*)g_015e2e4c;
        if (v_l12_40 != v_l64) {
            v_l68_6 = v_l12_40 + 8;
            (((il2c_gm0*)((int)((int)((v_l8) + (int)*(int*)((char*)(v_l68_6) + 4)))))->*(*(il2c_gp0*)&(*(int*)((char*)(v_l68_6)))))((unsigned int)(a12));
        }
    }
    return;
}
