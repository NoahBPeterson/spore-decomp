// 0x004600f0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0045f5e0/s0045f5e0.cpp.

extern "C" unsigned char g_01485378[];
extern "C" unsigned char g_01485720[];
extern "C" void __cdecl FUN_00460470(...);
struct C_004740f0 { void FUN_004740f0(unsigned int, unsigned int); };
struct C_00474450 { void FUN_00474450(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_0071ddc0(...);
extern "C" int __cdecl FUN_0071de40(...);
#pragma pack(push, 1)
struct Fr0_004600f0 {
    int v_l156;
    int v_l152;
    int v_l148;
    int v_l144;
    int v_l140;
    int v_l136;
    int dead0[1];
    int v_l128;
    int v_l124;
    int v_l120;
    int dead1[4];
    float v_l100;
    float v_l96;
    float v_l92;
    float v_l88;
    int v_l84;
    int v_l80;
    int v_l76;
    int v_l72;
    int v_l68;
    int v_l64;
    int v_l60;
    char dead2;
    char dead3;
    char dead4;
    unsigned char v_l53;
    int v_l52;
    int v_l48;
    int v_l44;
    char dead5;
    char dead6;
    char dead7;
    unsigned char v_l37;
    unsigned short v_l36;
    char dead8;
    char dead9;
    int v_l32;
    int v_l28;
    int v_l24;
    int v_l20;
    char dead10;
    char dead11;
    char dead12;
    unsigned char v_l13;
    unsigned short v_l12;
    unsigned short v_l10;
    unsigned short v_l8;
    unsigned short v_l6;
};
struct Fr1_004600f0 {
    int v_l160;
};
#pragma pack(pop)
__forceinline bool il2c_cc_e(int a, int b) { return a == b; }

// @ 0x004600f0
extern "C" bool __cdecl FUN_004600f0(int a4, int a8, int a12, int a16)
{
    Fr0_004600f0 fb;
    Fr1_004600f0 fa;
    fb.v_l28 = (int)(int)FUN_0071de40((unsigned int)a4, (unsigned int)1, (unsigned int)-1, (unsigned int)0, (unsigned int)14);
    fb.v_l52 = (int)(int)FUN_0071ddc0((unsigned int)a4, (unsigned int)9, (unsigned int)-1, (unsigned int)0, (unsigned int)14);
    if (fb.v_l52 < 0) {
        return (unsigned char)0;
    }
        fb.v_l32 = (int)(int)((fb.v_l52 << 5) + (int)*(int*)((char*)a4 + 8));
        fb.v_l20 = (int)(int)FUN_0071ddc0((unsigned int)a4, (unsigned int)10, (unsigned int)-1, (unsigned int)0, (unsigned int)14);
        fb.v_l24 = (int)(int)((fb.v_l20 << 5) + (int)*(int*)((char*)a4 + 8));
        fb.v_l13 = (unsigned char)(unsigned char)il2c_cc_e((int)*(int*)((char*)fb.v_l32 + 8), 7);
        if (fb.v_l20 >= 0 && (int)*(int*)((char*)fb.v_l24 + 8) == 10) {
            fb.v_l152 = 1;
        } else {
            fb.v_l152 = 0;
        }
        fb.v_l37 = (unsigned char)(unsigned char)(unsigned char)fb.v_l152;
        if (fb.v_l20 >= 0 && ((int)*(int*)((char*)fb.v_l24 + 8) >= 1 && (int)*(int*)((char*)fb.v_l24 + 8) <= 4)) {
            fb.v_l156 = 1;
        } else {
            fb.v_l156 = 0;
        }
        fb.v_l53 = (unsigned char)(unsigned char)(unsigned char)fb.v_l156;
        fb.v_l44 = (int)(int)((int)((int)*(int*)((char*)a8 + 4) - (int)*(int*)(char*)a8) >> 3);
        fb.v_l48 = (int)(int)*(int*)(char*)fb.v_l28;
        fb.v_l12 = (unsigned short)(unsigned short)0;
        fb.v_l10 = (unsigned short)(unsigned short)0;
        fb.v_l8 = (unsigned short)(unsigned short)0;
        fb.v_l6 = (unsigned short)(unsigned short)0;
        ((C_004740f0*)a8)->FUN_004740f0((unsigned int)(fb.v_l44 + fb.v_l48), (unsigned int)(int)(int)&fb.v_l12);
        fb.v_l100 = (float)*(float*)g_01485720;
        fb.v_l96 = (float)*(float*)g_01485378;
        fb.v_l92 = (float)*(float*)g_01485378;
        fb.v_l88 = (float)*(float*)g_01485378;
        ((C_00474450*)a12)->FUN_00474450((unsigned int)(fb.v_l44 + fb.v_l48), (unsigned int)(int)(int)&fb.v_l100);
        fb.v_l36 = (unsigned short)(unsigned short)(a16 * 3);
        if ((int)fb.v_l13 != 0) {
            fb.v_l60 = 0;
            for (; fb.v_l60 < fb.v_l48; fb.v_l60 = fb.v_l60 + 1) {
                fb.v_l64 = (int)(int)((int)*(int*)(char*)a8 + (fb.v_l44 + fb.v_l60 << 3));
                fb.v_l120 = fb.v_l32 + 16;
                fb.v_l68 = (int)(int)((int)((int)*(unsigned short*)((char*)fb.v_l120 + 10) * fb.v_l60) + (int)*(int*)((char*)fb.v_l120 + 4));
                fb.v_l72 = 0;
                for (; (unsigned int)fb.v_l72 < (unsigned int)4; fb.v_l72 = fb.v_l72 + 1) {
                    *(unsigned short*)((char*)fb.v_l64 + fb.v_l72 * 2) = (unsigned short)(unsigned short)(int)((int)*(unsigned char*)(char*)(fb.v_l68 + fb.v_l72) + (int)fb.v_l36);
                }
                if ((int)fb.v_l37 != 0) {
                    fb.v_l124 = (int)(int)((fb.v_l44 + fb.v_l60 << 4) + (int)*(int*)(char*)a12);
                    fb.v_l128 = fb.v_l24 + 16;
                    FUN_00460470((unsigned int)(int)*(int*)((char*)(int)*(int*)((char*)fb.v_l128 + 4) + (int)((int)*(unsigned short*)((char*)fb.v_l128 + 10) * fb.v_l60)), (unsigned int)fb.v_l124);
                }
            }
        } else {
            if ((int)fb.v_l53 != 0) {
                fa.v_l160 = (int)(int)*(int*)((char*)fb.v_l24 + 8);
            } else {
                fa.v_l160 = 1;
            }
            fb.v_l76 = fa.v_l160;
            fb.v_l80 = 0;
            for (; fb.v_l80 < fb.v_l48; fb.v_l80 = fb.v_l80 + 1) {
                fb.v_l84 = 0;
                for (; fb.v_l84 < fb.v_l76; fb.v_l84 = fb.v_l84 + 1) {
                    fb.v_l136 = fb.v_l32 + 16;
                    fb.v_l140 = (int)(int)((int)((int)*(unsigned short*)((char*)fb.v_l136 + 10) * fb.v_l80) + (int)*(int*)((char*)fb.v_l136 + 4));
                    *(unsigned short*)((char*)(int)((int)*(int*)(char*)a8 + (fb.v_l44 + fb.v_l80 << 3)) + fb.v_l84 * 2) = (unsigned short)(unsigned short)(int)((int)*(unsigned short*)((char*)fb.v_l140 + fb.v_l84 * 2) + (int)fb.v_l36);
                    if ((int)fb.v_l53 != 0) {
                        fb.v_l144 = fb.v_l24 + 16;
                        fb.v_l148 = (int)(int)((int)((int)*(unsigned short*)((char*)fb.v_l144 + 10) * fb.v_l80) + (int)*(int*)((char*)fb.v_l144 + 4));
                        *(float*)((char*)(int)((fb.v_l44 + fb.v_l80 << 4) + (int)*(int*)(char*)a12) + fb.v_l84 * 4) = *(float*)((char*)fb.v_l148 + fb.v_l84 * 4);
                    }
                }
            }
        }
        return (unsigned char)1;
}
