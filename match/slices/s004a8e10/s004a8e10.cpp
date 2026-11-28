// 0x004a8e10: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/SPEditorManipulationUtilities.cpp, match/slices/s0049cfd0/s0049cfd0.cpp, match/slices/s004a89e0/s004a89e0.cpp.

extern "C" unsigned char g_015d6324[];
extern "C" unsigned char g_015d63f4[];
extern "C" int __cdecl FUN_0041daf0(...);
extern "C" void __cdecl FUN_0069b440(...);
template<class T> __forceinline T il2c_k(T v) { return v; }

// @ 0x004a8e10
// @ 0x004a8e10
extern "C" int __cdecl FUN_004a8e10(int a4, int a8, int a12)
{
    int v_l16_i[3];
    float v_l20;
    int v_l28[2];
    int v_l60_k;
    int v_l56_b;
    int v_l52[3];
    int v_l40[3];
    v_l56_b = (int)(int)FUN_0041daf0((unsigned int)(int)&v_l40, (unsigned int)(int)g_015d63f4, (unsigned int)a8);
    *(float*)&v_l28[0] = *(float*)(char*)v_l56_b;
    *(float*)&v_l28[1] = *(float*)((char*)v_l56_b + 4);
    v_l20 = *(float*)((char*)v_l56_b + 8);
    v_l60_k = (int)(int)FUN_0041daf0((unsigned int)(int)&v_l52, (unsigned int)(int)g_015d6324, (unsigned int)a8);
    *(float*)&v_l16_i[0] = *(float*)(char*)v_l60_k;
    *(float*)&v_l16_i[1] = *(float*)((char*)v_l60_k + 4);
    *(float*)&v_l16_i[2] = *(float*)((char*)v_l60_k + 8);
    if ((int)(unsigned char)a12 != 0) {
        *(float*)((char*)(int)&v_l28 + (il2c_k(2) << 2)) = (float)-*(float*)((char*)(int)&v_l28 + (il2c_k(2) << 2));
        *(float*)((char*)(int)&v_l16_i + (il2c_k(2) << 2)) = (float)-*(float*)((char*)(int)&v_l16_i + (il2c_k(2) << 2));
    } else {
        *(float*)((char*)(int)&v_l28 + (il2c_k(0) << 2)) = (float)-*(float*)((char*)(int)&v_l28 + (il2c_k(0) << 2));
        *(float*)((char*)(int)&v_l16_i + (il2c_k(0) << 2)) = (float)-*(float*)((char*)(int)&v_l16_i + (il2c_k(0) << 2));
    }
    FUN_0069b440((unsigned int)a4, (unsigned int)(int)&v_l28, (unsigned int)(int)&v_l16_i);
    return a4;
}
