// 0x0048cf00: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0048c0f0/s0048c0f0.cpp.

extern "C" unsigned char g_013ef4c0[];
extern "C" unsigned char g_01485378[];
struct C_0044ae00 { void FUN_0044ae00(unsigned int, unsigned int, unsigned int, unsigned int); };
struct C_004accb0 { int FUN_004accb0(unsigned int); };
struct C_004accf0 { int FUN_004accf0(); };
template<class T> __forceinline bool il2c_nz(T v) { return v != 0; }
template<class T> __forceinline T il2c_k(T v) { return v; }

// @ 0x0048cf00
// @ 0x0048cf00
extern "C" float __cdecl FUN_0048cf00(int a4)
{
    int v_l52_w;
    int v_l48[11];
    char dead_1_33;
    char dead_0;
    unsigned char v_l53;
    char dead_2;
    *(float*)&v_l48[10] = (float)*(float*)g_01485378;
    if (a4 != 0) {
        *(float*)&v_l48[9] = (float)*(float*)g_013ef4c0;
        *(int*)&v_l48[8] = ((C_004accf0*)a4)->FUN_004accf0();
        *(int*)&v_l48[7] = 0;
        for (; *(int*)&v_l48[7] < *(int*)&v_l48[8]; *(int*)&v_l48[7] = *(int*)&v_l48[7] + 1) {
            *(int*)&v_l48[6] = (int)((C_004accb0*)a4)->FUN_004accb0((unsigned int)*(int*)&v_l48[7]);
            if (il2c_k((unsigned int)7) < (unsigned int)60) {
                v_l52_w = (int)(int)*(int*)((char*)*(int*)&v_l48[6] + (int)(il2c_k((unsigned int)7) >> 5) * 4 + 3528);
                v_l53 = (unsigned char)(unsigned char)(unsigned char)il2c_nz((int)(int)((int)(1 << (int)(unsigned int)(il2c_k((unsigned int)7) % (unsigned int)32)) & v_l52_w));
            } else {
                v_l53 = (unsigned char)0;
            }
            if ((int)v_l53 != 0) {
                ((C_0044ae00*)*(int*)&v_l48[6])->FUN_0044ae00((unsigned int)(int)&v_l48, (unsigned int)0, (unsigned int)1, (unsigned int)0);
                if ((float)*(float*)&v_l48[9] > (float)*(float*)((char*)(int)&v_l48 + (il2c_k(2) << 2))) {
                    *(float*)&v_l48[9] = *(float*)((char*)(int)&v_l48 + (il2c_k(2) << 2));
                }
            }
        }
        *(float*)&v_l48[10] = (float)*(float*)&v_l48[9];
    }
    return (float)*(float*)&v_l48[10];
}
