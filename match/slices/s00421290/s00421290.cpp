// 0x00421290: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/SPEditorBaker.cpp, src/game/SPGonzago/_at_00420000.cpp, match/slices/s00420c70/s00420c70.cpp, match/slices/s0042f9d0/s0042f9d0.cpp.

struct C_00421190 { void FUN_00421190(); };
struct C_00427100 { int FUN_00427100(unsigned int, unsigned int, unsigned int); };
extern "C" void __cdecl FUN_00427160(...);
struct C_0042d990 { int FUN_0042d990(unsigned int); };
extern "C" void __cdecl FUN_00f47380(...);
__forceinline void il2c_d_FUN_00f47380(int p, int fl) { if (fl & 1) FUN_00f47380((unsigned int)(p)); }


struct D_00421290 { int FUN_00421290(int a4); };
// @ 0x00421290
int D_00421290::FUN_00421290(int a4)
{
    int v_l80_c;
    int v_l76_q;
    int dead_0_15[14];
    int v_l16_i;
    int v_l12_40;
    int v_l8;
    int v_l92_k;
    int v_l88_12;
    int v_l84;
    int v_l112_d;
    int v_l108_14;
    int v_l104_a;
    int v_l100_34;
    unsigned char v_l96;
    unsigned char v_l95_o;
    unsigned char v_l94;
    unsigned char v_l93;
    unsigned char v_l165_22;
    int dead_1_b[12];
    int v_l116;
    unsigned char v_l166;
    int v_l188_29;
    int v_l184_a;
    int v_l180_c;
    int v_l176_13;
    int v_l172_11;
    unsigned char v_l168;
    unsigned char v_l167;
    int v_l228_11;
    int dead_2[9];
    int v_l232;
    if (a4 != (int)this) {
        v_l8 = (int)(int)((int)((int)*(int*)((char*)a4 + 4) - (int)*(int*)(char*)a4) / 24);
        if ((unsigned int)v_l8 > (unsigned int)(int)((int)(int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) / 24)) {
            v_l12_40 = (int)((C_00427100*)(int)this)->FUN_00427100((unsigned int)v_l8, (unsigned int)(int)*(int*)(char*)a4, (unsigned int)(int)*(int*)((char*)a4 + 4));
            v_l80_c = (int)(int)*(int*)((char*)(int)this + 4);
            v_l76_q = (int)(int)*(int*)(char*)(int)this;
            for (; (unsigned int)v_l76_q < (unsigned int)v_l80_c; v_l76_q = v_l76_q + 24) {
                ((C_00421190*)v_l76_q)->FUN_00421190();
                il2c_d_FUN_00f47380(v_l76_q, 0);
            }
            v_l92_k = (int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) / 24);
            v_l88_12 = (int)(int)*(int*)(char*)(int)this;
            if (v_l88_12 != 0) {
                if ((int)*(int*)((char*)v_l88_12 - 4) != 0) {
                    v_l84 = v_l88_12;
                    FUN_00f47380((unsigned int)v_l84);
                }
            }
            *(int*)(char*)(int)this = v_l12_40;
            *(int*)((char*)(int)this + 8) = (int)(int)(v_l8 * 24 + (int)*(int*)(char*)(int)this);
        } else {
            if ((unsigned int)v_l8 > (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 24)) {
                v_l116 = (int)(int)*(int*)(char*)(int)this;
                v_l112_d = (int)(int)((int)((int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 24) * 24) + (int)*(int*)(char*)a4);
                v_l108_14 = (int)(int)*(int*)(char*)a4;
                v_l94 = (unsigned char)0;
                v_l93 = (unsigned char)0;
                v_l95_o = (unsigned char)0;
                v_l104_a = v_l116;
                v_l100_34 = v_l108_14;
                for (; v_l100_34 != v_l112_d; v_l104_a = v_l104_a + 24, v_l100_34 = v_l100_34 + 24) {
                    ((C_0042d990*)v_l104_a)->FUN_0042d990((unsigned int)v_l100_34);
                    v_l96 = (unsigned char)(unsigned char)*(unsigned char*)((char*)v_l100_34 + 20);
                    *(unsigned char*)((char*)v_l104_a + 20) = (unsigned char)(unsigned char)v_l96;
                }
                FUN_00427160((unsigned int)(int)((int)((int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 24) * 24) + (int)*(int*)(char*)a4), (unsigned int)(int)*(int*)((char*)a4 + 4), (unsigned int)(int)*(int*)((char*)(int)this + 4));
            } else {
                v_l188_29 = (int)(int)*(int*)(char*)(int)this;
                v_l184_a = (int)(int)*(int*)((char*)a4 + 4);
                v_l180_c = (int)(int)*(int*)(char*)a4;
                v_l166 = (unsigned char)0;
                v_l165_22 = (unsigned char)0;
                v_l167 = (unsigned char)0;
                v_l176_13 = v_l188_29;
                v_l172_11 = v_l180_c;
                for (; v_l172_11 != v_l184_a; v_l176_13 = v_l176_13 + 24, v_l172_11 = v_l172_11 + 24) {
                    ((C_0042d990*)v_l176_13)->FUN_0042d990((unsigned int)v_l172_11);
                    v_l168 = (unsigned char)(unsigned char)*(unsigned char*)((char*)v_l172_11 + 20);
                    *(unsigned char*)((char*)v_l176_13 + 20) = (unsigned char)(unsigned char)v_l168;
                }
                v_l16_i = v_l176_13;
                v_l232 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l228_11 = v_l16_i;
                for (; (unsigned int)v_l228_11 < (unsigned int)v_l232; v_l228_11 = v_l228_11 + 24) {
                    ((C_00421190*)v_l228_11)->FUN_00421190();
                    il2c_d_FUN_00f47380(v_l228_11, 0);
                }
            }
        }
        *(int*)((char*)(int)this + 4) = (int)(int)(v_l8 * 24 + (int)*(int*)(char*)(int)this);
    }
    return (int)this;
}
