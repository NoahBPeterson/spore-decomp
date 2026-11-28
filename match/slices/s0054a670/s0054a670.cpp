// 0x0054a670: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00549e40/s00549e40.cpp.

struct C_005477e0 { void FUN_005477e0(); };
extern "C" void __cdecl FUN_0054b250(...);
struct C_0054b2f0 { int FUN_0054b2f0(unsigned int, unsigned int, unsigned int); };
extern "C" int __cdecl FUN_0054b5b0(...);
extern "C" void __cdecl FUN_00f47380(...);
__forceinline void il2c_d_FUN_00f47380(int p, int fl) { if (fl & 1) FUN_00f47380((unsigned int)(p)); }


struct D_0054a670 { int FUN_0054a670(int a4); };
// @ 0x0054a670
// @ 0x0054a670
int D_0054a670::FUN_0054a670(int a4)
{
    int v_l80_c;
    int v_l76_q;
    int v_l72_k;
    int dead_0_15[13];
    int v_l16_i;
    int v_l12_40;
    int v_l8;
    int v_l88_12;
    int v_l84;
    unsigned char v_l89;
    char dead_1_c;
    unsigned char v_l90;
    char dead_2;
    int v_l224_19;
    int v_l220_32;
    int dead_8_28[4];
    int v_l200;
    int v_l196_62;
    int v_l192_29;
    int dead_7_19[4];
    char dead_6_10;
    char dead_5_16;
    unsigned char v_l170_14;
    unsigned char v_l169_c;
    int dead_4_35[12];
    int v_l120_13;
    int v_l116_24;
    int v_l112;
    int dead_3[4];
    if (a4 != (int)this) {
        v_l8 = (int)(int)((int)((int)*(int*)((char*)a4 + 4) - (int)*(int*)(char*)a4) / 20);
        if ((unsigned int)v_l8 > (unsigned int)(int)((int)(int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) / 20)) {
            v_l12_40 = (int)((C_0054b2f0*)(int)this)->FUN_0054b2f0((unsigned int)v_l8, (unsigned int)(int)*(int*)(char*)a4, (unsigned int)(int)*(int*)((char*)a4 + 4));
            v_l76_q = (int)(int)*(int*)((char*)(int)this + 4);
            v_l72_k = (int)(int)*(int*)(char*)(int)this;
            for (; (unsigned int)v_l72_k < (unsigned int)v_l76_q; v_l72_k = v_l72_k + 20) {
                ((C_005477e0*)v_l72_k)->FUN_005477e0();
                il2c_d_FUN_00f47380(v_l72_k, 0);
            }
            v_l88_12 = (int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) / 20);
            v_l84 = (int)(int)*(int*)(char*)(int)this;
            if (v_l84 != 0) {
                v_l80_c = v_l84;
                FUN_00f47380((unsigned int)v_l80_c);
            }
            *(int*)(char*)(int)this = v_l12_40;
            *(int*)((char*)(int)this + 8) = (int)(int)(v_l8 * 20 + (int)*(int*)(char*)(int)this);
        } else {
            if ((unsigned int)v_l8 > (unsigned int)(int)((int)(int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 20)) {
                v_l120_13 = (int)(int)*(int*)(char*)(int)this;
                v_l116_24 = (int)(int)((int)((int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 20) * 20) + (int)*(int*)(char*)a4);
                v_l112 = (int)(int)*(int*)(char*)a4;
                v_l90 = (unsigned char)0;
                v_l89 = (unsigned char)0;
                FUN_0054b5b0((unsigned int)v_l112, (unsigned int)v_l116_24, (unsigned int)v_l120_13);
                FUN_0054b250((unsigned int)(int)((int)((int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 20) * 20) + (int)*(int*)(char*)a4), (unsigned int)(int)*(int*)((char*)a4 + 4), (unsigned int)(int)*(int*)((char*)(int)this + 4));
            } else {
                v_l200 = (int)(int)*(int*)(char*)(int)this;
                v_l196_62 = (int)(int)*(int*)((char*)a4 + 4);
                v_l192_29 = (int)(int)*(int*)(char*)a4;
                v_l170_14 = (unsigned char)0;
                v_l169_c = (unsigned char)0;
                v_l16_i = (int)(int)FUN_0054b5b0((unsigned int)v_l192_29, (unsigned int)v_l196_62, (unsigned int)v_l200);
                v_l224_19 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l220_32 = v_l16_i;
                for (; (unsigned int)v_l220_32 < (unsigned int)v_l224_19; v_l220_32 = v_l220_32 + 20) {
                    ((C_005477e0*)v_l220_32)->FUN_005477e0();
                    il2c_d_FUN_00f47380(v_l220_32, 0);
                }
            }
        }
        *(int*)((char*)(int)this + 4) = (int)(int)(v_l8 * 20 + (int)*(int*)(char*)(int)this);
    }
    return (int)this;
}
