// 0x004ea190: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/SPEditorValidity.cpp, match/slices/s004e95e0/s004e95e0.cpp.

extern "C" unsigned char g_015dabcc[];
extern "C" unsigned char g_015dacc8[];
struct C_004e19a0 { int FUN_004e19a0(unsigned int); };
extern "C" int __cdecl FUN_004e9ca0(...);
struct il2c_bfs_8_8 { unsigned int pad : 8; unsigned int f : 8; };
__forceinline void il2c_bf_8_8(void* p, unsigned int x) { ((il2c_bfs_8_8*)p)->f = x; }
struct il2c_bfs_16_8 { unsigned int pad : 16; unsigned int f : 8; };
__forceinline void il2c_bf_16_8(void* p, unsigned int x) { ((il2c_bfs_16_8*)p)->f = x; }
template<class T> __forceinline T il2c_k(T v) { return v; }

// @ 0x004ea190
// @ 0x004ea190
extern "C" void __cdecl FUN_004ea190(int a4, int a8, int a12)
{
    int v_l32_p;
    int v_l28_g;
    int v_l24;
    int v_l20_q;
    int v_l16_i;
    int v_l12_40;
    int v_l8;
    int dead_0[2];
    int v_l44;
    int dead_1[6];
    switch ((a4)) {
    case -542269615:
        L4ea1f5:;
        v_l32_p = 0;
        v_l32_p = v_l32_p & 1073741823 | 1073741824;
        il2c_bf_16_8(&(v_l32_p), 97);
        il2c_bf_8_8(&(v_l32_p), 96);
        v_l16_i = -1050871164;
        v_l12_40 = 0;
        v_l8 = v_l32_p;
        ((C_004e19a0*)a8)->FUN_004e19a0((unsigned int)(int)&v_l16_i);
        break;
    case -1633484006:
    case -859612090:
    case 925772804:
    case 1098430696:
    case 1701259998:
        L4ea26a:;
        v_l44 = 0;
        v_l44 = v_l44 & 1073741823 | 1073741824;
        il2c_bf_16_8(&(v_l44), 98);
        il2c_bf_8_8(&(v_l44), 96);
        v_l28_g = -799255645;
        v_l24 = 0;
        v_l20_q = v_l44;
        ((C_004e19a0*)a8)->FUN_004e19a0((unsigned int)(int)&v_l28_g);
        ((C_004e19a0*)a8)->FUN_004e19a0((unsigned int)(int)g_015dacc8);
        ((C_004e19a0*)a8)->FUN_004e19a0((unsigned int)(int)g_015dabcc);
        if (a12 != 1543042932) {
            FUN_004e9ca0((unsigned int)a8);
        }
    }
    return;
}
