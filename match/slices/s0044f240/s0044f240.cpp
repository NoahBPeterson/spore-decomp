// 0x0044f240: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/SPEditorManipulationUtilities.cpp, src/game/SPBake/_at_00480000.cpp, src/game/SPBake/SPEditorBlock.cpp, match/slices/s0044e460/s0044e460.cpp, src/game/SPEditors/SPEditorManipulationTranslateCreature.cpp, src/game/SPEditors/SPEditorManipulationStackingSimple.cpp, match/slices/s0048a4e0/s0048a4e0.cpp, match/slices/s005ab7a0/s005ab7a0.cpp, match/slices/s00488600/s00488600.cpp, match/slices/s005bccc0/s005bccc0.cpp, match/slices/s00489530/s00489530.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual int s9(int, int);
};

struct C_0041e920 { int FUN_0041e920(); };
struct C_0044c050 { int FUN_0044c050(); };
struct C_0044c450 { int FUN_0044c450(); };
extern "C" int __cdecl FUN_004a7e60(...);
template<class T> __forceinline bool il2c_nz(T v) { return v != 0; }
template<class T> __forceinline T il2c_k(T v) { return v; }


struct D_0044f240 { int FUN_0044f240(); };
// @ 0x0044f240
// @ 0x0044f240
int D_0044f240::FUN_0044f240()
{
    int v_l24;
    unsigned char v_l19_p;
    unsigned char v_l18_k;
    unsigned char v_l17;
    int v_l16_i;
    int v_l12_40;
    int v_l8;
    unsigned char v_l25;
    int v_l36_i;
    int v_l32;
    int dead_0_d;
    int v_l64_o;
    int v_l60_k;
    unsigned char v_l53_63;
    int v_l52;
    int v_l48_y;
    unsigned char v_l41_d;
    int v_l40;
    int v_l72;
    v_l17 = (unsigned char)(unsigned char)(int)FUN_004a7e60((unsigned int)(int)this);
    if (il2c_k((unsigned int)7) < (unsigned int)60) {
        v_l24 = (int)(int)*(int*)((char*)(int)this + (int)(il2c_k((unsigned int)7) >> 5) * 4 + 3528);
        v_l25 = (unsigned char)(unsigned char)(unsigned char)il2c_nz((int)(int)((int)(1 << (int)(unsigned int)(il2c_k((unsigned int)7) % (unsigned int)32)) & v_l24));
    } else {
        v_l25 = (unsigned char)0;
    }
    if ((int)v_l25 != 0) {
        return 0;
    }
        v_l18_k = (unsigned char)0;
        v_l32 = (int)(int)*(int*)((char*)(int)this + 828);
        if (v_l32 != 0) {
            v_l36_i = (int)(int)*(int*)((char*)(int)this + 828);
            if (il2c_k((unsigned int)7) < (unsigned int)60) {
                v_l40 = (int)(int)*(int*)((char*)v_l36_i + (int)(il2c_k((unsigned int)7) >> 5) * 4 + 3528);
                v_l41_d = (unsigned char)(unsigned char)(unsigned char)il2c_nz((int)(int)((int)(1 << (int)(unsigned int)(il2c_k((unsigned int)7) % (unsigned int)32)) & v_l40));
            } else {
                v_l41_d = (unsigned char)0;
            }
            if ((int)v_l41_d != 0) {
                v_l18_k = (unsigned char)1;
            } else {
                v_l48_y = (int)(int)*(int*)((char*)(int)this + 828);
                if (il2c_k((unsigned int)0) < (unsigned int)60) {
                    v_l52 = (int)(int)*(int*)((char*)v_l48_y + (int)(il2c_k((unsigned int)0) >> 5) * 4 + 3528);
                    v_l53_63 = (unsigned char)(unsigned char)(unsigned char)il2c_nz((int)(int)((int)(1 << (int)(unsigned int)(il2c_k((unsigned int)0) % (unsigned int)32)) & v_l52));
                } else {
                    v_l53_63 = (unsigned char)0;
                }
                if ((int)v_l53_63 == 0) {
                    v_l18_k = (unsigned char)1;
                }
            }
        }
        v_l12_40 = ((C_0044c050*)(int)this)->FUN_0044c050();
        v_l16_i = ((C_0044c450*)(int)this)->FUN_0044c450();
        v_l8 = v_l12_40;
        if (v_l8 == 0) {
            v_l8 = v_l16_i;
            if (v_l8 == 0) {
                v_l19_p = (unsigned char)0;
                v_l60_k = (int)(int)*(int*)((char*)(int)this + 12);
                if (v_l60_k != 0) {
                    if ((int)(unsigned char)((il2c_vc0*)v_l60_k)->s9(2077280830, (int)&v_l64_o) != 0) {
                        if ((int)*(unsigned short*)((char*)v_l64_o + 18) == 1) {
                            v_l19_p = (unsigned char)(unsigned char)*(unsigned char*)(char*)((C_0041e920*)v_l64_o)->FUN_0041e920();
                        }
                    }
                }
                if ((int)v_l19_p != 0) {
                    v_l8 = -1;
                }
            }
        }
        v_l72 = (int)(int)*(int*)((char*)(int)this + 828);
        return v_l8;
}
