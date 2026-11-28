// 0x004c4290: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/SPEditorSkinManager.cpp, src/game/SPEditors/SPAppModeEditorBase.cpp, match/slices/s004c38e0/s004c38e0.cpp, match/slices/s0058be50/s0058be50.cpp.

extern "C" int __cdecl FUN_004bb860(...);
struct C_00526430 { int FUN_00526430(); };
template<class T> __forceinline T il2c_k(T v) { return v; }


struct D_004c4290 { void FUN_004c4290(); };
// @ 0x004c4290
void D_004c4290::FUN_004c4290()
{
    int v_l32_p;
    int v_l28_g;
    int v_l24;
    int v_l20_q;
    int v_l16_i;
    unsigned char v_l9_f;
    int v_l8;
    int v_l60_b;
    int v_l56_d;
    int v_l52_i;
    int v_l48_i;
    int v_l44;
    int v_l40_w;
    int v_l36;
    int v_l72_e;
    int v_l68_6;
    int v_l64;
    int v_l92_c;
    int v_l88;
    int v_l84_i;
    int v_l80_d;
    int v_l76;
    if ((int)*(unsigned char*)((char*)(int)this + 132) != 0) {
        v_l36 = (int)(int)*(int*)((char*)(int)this + 92);
        if (v_l36 != 0) {
            v_l40_w = (int)(int)*(int*)((char*)(int)this + 28);
            if (v_l40_w != 0) {
                v_l44 = (int)(int)*(int*)((char*)(int)this + 28);
                v_l48_i = (int)(int)*(int*)((char*)v_l44 + 8);
                v_l16_i = (int)(int)FUN_004bb860((unsigned int)(int)*(int*)((char*)v_l48_i + 24));
                if (v_l16_i == 1133470535) {
                    v_l9_f = (unsigned char)5;
                } else {
                    if (v_l16_i == 1033349348) {
                        v_l9_f = (unsigned char)4;
                    } else {
                        v_l9_f = (unsigned char)7;
                    }
                }
                v_l52_i = (int)(int)*(int*)((char*)(int)this + 28);
                v_l8 = (int)(int)*(int*)((char*)v_l52_i + 184);
                if (v_l8 != 0) {
                    if ((int)(unsigned char)((C_00526430*)(v_l8 + 8))->FUN_00526430() == 0) {
                        if ((int)*(unsigned short*)((char*)(int)*(int*)((char*)(int)*(int*)((char*)v_l8 + 8) + (il2c_k(0) << 2)) + 4) == 528) {
                            v_l20_q = (int)(int)*(int*)((char*)(int)*(int*)((char*)(int)*(int*)((char*)v_l8 + 8) + (il2c_k(0) << 2)) + 8);
                            *(unsigned char*)(char*)v_l20_q = (unsigned char)(unsigned char)v_l9_f;
                            v_l56_d = (int)(int)*(int*)((char*)(int)this + 92);
                            *(float*)((char*)v_l20_q + 4) = *(float*)((char*)v_l56_d + 112);
                            v_l60_b = (int)(int)*(int*)((char*)(int)this + 92);
                            *(float*)((char*)v_l20_q + 8) = *(float*)((char*)v_l60_b + 116);
                            v_l64 = (int)(int)*(int*)((char*)(int)this + 92);
                            *(float*)((char*)v_l20_q + 16) = *(float*)((char*)v_l64 + 120);
                        }
                    }
                }
                v_l28_g = 0;
                v_l68_6 = (int)(int)*(int*)((char*)(int)this + 28);
                v_l72_e = v_l68_6 + 228;
                v_l24 = (int)(int)((int)((int)*(int*)((char*)v_l72_e + 4) - (int)*(int*)(char*)v_l72_e) >> 2);
                for (; v_l28_g < v_l24; v_l28_g = v_l28_g + 1) {
                    v_l76 = (int)(int)*(int*)((char*)(int)this + 28);
                    v_l80_d = (int)(int)((int)*(int*)((char*)v_l76 + 228) + (v_l28_g << 2));
                    v_l8 = (int)(int)*(int*)(char*)v_l80_d;
                    if (v_l8 != 0) {
                        if ((int)(unsigned char)((C_00526430*)(v_l8 + 8))->FUN_00526430() == 0) {
                            if ((int)*(unsigned short*)((char*)(int)*(int*)((char*)(int)*(int*)((char*)v_l8 + 8) + (il2c_k(0) << 2)) + 4) == 528) {
                                v_l32_p = (int)(int)*(int*)((char*)(int)*(int*)((char*)(int)*(int*)((char*)v_l8 + 8) + (il2c_k(0) << 2)) + 8);
                                *(unsigned char*)(char*)v_l32_p = (unsigned char)(unsigned char)v_l9_f;
                                v_l84_i = (int)(int)*(int*)((char*)(int)this + 92);
                                *(float*)((char*)v_l32_p + 4) = *(float*)((char*)v_l84_i + 112);
                                v_l88 = (int)(int)*(int*)((char*)(int)this + 92);
                                *(float*)((char*)v_l32_p + 8) = *(float*)((char*)v_l88 + 116);
                                v_l92_c = (int)(int)*(int*)((char*)(int)this + 92);
                                *(float*)((char*)v_l32_p + 16) = *(float*)((char*)v_l92_c + 120);
                            }
                        }
                    }
                }
            }
        }
    }
    return;
}
