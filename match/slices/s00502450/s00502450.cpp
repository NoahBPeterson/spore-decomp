// 0x00502450: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00501f40/s00501f40.cpp.

extern "C" int __cdecl FUN_0042dee0(...);
struct C_00502ee0 { void FUN_00502ee0(unsigned int); };
extern "C" void __cdecl FUN_005032b0(...);
extern "C" int __cdecl FUN_00503350(...);
extern "C" void __cdecl FUN_00503750(...);
extern "C" void __cdecl FUN_005037d0(...);
struct C_005039c0 { int FUN_005039c0(unsigned int); };
extern "C" void __cdecl FUN_00f47380(...);


struct D_00502450 { void FUN_00502450(int a4, int a8, int a12); };
// @ 0x00502450
void D_00502450::FUN_00502450(int a4, int a8, int a12)
{
    int v_l112_16;
    int v_l108_33;
    int v_l104_19;
    int v_l100_c[15];
    int dead_0_15[8];
    int v_l8;
    int v_l124_c;
    int v_l120_21;
    int v_l116;
    int v_l144_37;
    int v_l140_19;
    int v_l136_41;
    unsigned char v_l130_16;
    char dead_1_33;
    int v_l128;
    int v_l156_55;
    int v_l152_21;
    int v_l148;
    int v_l168_a;
    int v_l164;
    unsigned char v_l159_c;
    unsigned char v_l158_32;
    unsigned char v_l157;
    char dead_3_35;
    int v_l176_17;
    int dead_2;
    int v_l184_19;
    unsigned char v_l178;
    int dead_4_35[13];
    int v_l188;
    int v_l332;
    int v_l328_39;
    int v_l324_d;
    int dead_7_66[8];
    int v_l288_20;
    int v_l284_c;
    unsigned char v_l278_12;
    char dead_6_56;
    int dead_5_26[8];
    int v_l244;
    if ((unsigned int)a8 <= (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)((char*)(int)this + 4)) / 84)) {
        if ((unsigned int)a8 > (unsigned int)0) {
            ((C_00502ee0*)(int)&v_l100_c)->FUN_00502ee0((unsigned int)a12);
            v_l104_19 = (int)(int)((int)((int)*(int*)((char*)(int)this + 4) - a4) / 84);
            v_l8 = (int)(int)*(int*)((char*)(int)this + 4);
            if ((unsigned int)a8 < (unsigned int)v_l104_19) {
                v_l156_55 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l152_21 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l148 = (int)(int)((int)*(int*)((char*)(int)this + 4) - a8 * 84);
                v_l136_41 = v_l156_55;
                v_l140_19 = v_l152_21;
                v_l144_37 = v_l148;
                FUN_00503750((unsigned int)(int)&v_l128, (unsigned int)v_l144_37, (unsigned int)v_l140_19, (unsigned int)v_l136_41, (unsigned int)(int)v_l130_16);
                *(int*)((char*)(int)this + 4) = (int)(int)(a8 * 84 + (int)*(int*)((char*)(int)this + 4));
                v_l158_32 = (unsigned char)0;
                v_l157 = (unsigned char)0;
                v_l159_c = (unsigned char)0;
                v_l168_a = v_l8;
                v_l164 = v_l8 - a8 * 84;
                while (v_l164 != a4) {
                    v_l164 = v_l164 - 84;
                    v_l168_a = v_l168_a - 84;
                    ((C_005039c0*)v_l168_a)->FUN_005039c0((unsigned int)v_l164);
                }
                v_l176_17 = a4;
                for (; v_l176_17 != a8 * 84 + a4; v_l176_17 = v_l176_17 + 84) {
                    ((C_005039c0*)v_l176_17)->FUN_005039c0((unsigned int)(int)&v_l100_c);
                }
            } else {
                v_l188 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l184_19 = v_l188;
                FUN_005037d0((unsigned int)v_l184_19, (unsigned int)(a8 - v_l104_19), (unsigned int)(int)&v_l100_c, (unsigned int)(int)v_l178);
                *(int*)((char*)(int)this + 4) = (int)(int)((a8 - v_l104_19) * 84 + (int)*(int*)((char*)(int)this + 4));
                FUN_005032b0((unsigned int)a4, (unsigned int)v_l8, (unsigned int)(int)*(int*)((char*)(int)this + 4));
                *(int*)((char*)(int)this + 4) = (int)(int)(v_l104_19 * 84 + (int)*(int*)((char*)(int)this + 4));
                v_l244 = a4;
                for (; v_l244 != v_l8; v_l244 = v_l244 + 84) {
                    ((C_005039c0*)v_l244)->FUN_005039c0((unsigned int)(int)&v_l100_c);
                }
            }
        }
    } else {
        v_l116 = (int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 84);
        v_l124_c = (int)(int)((unsigned int)v_l116 > (unsigned int)0 ? v_l116 << 1 : 1);
        v_l108_33 = (int)(int)((unsigned int)v_l124_c > (unsigned int)(v_l116 + a8) ? v_l124_c : v_l116 + a8);
        v_l120_21 = (int)(int)(v_l108_33 != 0 ? (int)(int)FUN_0042dee0((unsigned int)((int)this + 12), (unsigned int)(v_l108_33 * 84), (unsigned int)4, (unsigned int)0) : 0);
        v_l112_16 = (int)(int)FUN_00503350((unsigned int)(int)*(int*)(char*)(int)this, (unsigned int)a4, (unsigned int)v_l120_21);
        v_l288_20 = v_l112_16;
        v_l284_c = v_l288_20;
        FUN_005037d0((unsigned int)v_l284_c, (unsigned int)a8, (unsigned int)a12, (unsigned int)(int)v_l278_12);
        v_l112_16 = (int)(int)FUN_00503350((unsigned int)a4, (unsigned int)(int)*(int*)((char*)(int)this + 4), (unsigned int)(a8 * 84 + v_l112_16));
        v_l332 = (int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) / 84);
        v_l328_39 = (int)(int)*(int*)(char*)(int)this;
        if (v_l328_39 != 0) {
            if ((int)*(int*)((char*)v_l328_39 - 4) != 0) {
                v_l324_d = v_l328_39;
                FUN_00f47380((unsigned int)v_l324_d);
            }
        }
        *(int*)(char*)(int)this = v_l120_21;
        *(int*)((char*)(int)this + 4) = v_l112_16;
        *(int*)((char*)(int)this + 8) = v_l108_33 * 84 + v_l120_21;
    }
    return;
}
