// 0x0053a930: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/SPSkinPaintParticleDescription.cpp, match/slices/s0053acc0/s0053acc0.cpp, match/slices/s00534cf0/s00534cf0.cpp, match/slices/s00539d70/s00539d70.cpp.

extern "C" int __cdecl FUN_0093a9a0(...);
extern "C" void __cdecl FUN_0093a9d0(...);
extern "C" int __cdecl FUN_0093aa70(...);
#pragma pack(push, 1)
struct Fr0_0053a930 {
    float v_l124;
    int v_l120;
    int v_l116;
    unsigned char v_l112;
    unsigned char v_l111;
    unsigned char v_l110;
    unsigned char v_l109;
    unsigned char v_l108;
    unsigned char v_l107;
    unsigned char v_l106;
    unsigned char v_l105;
    float v_l104;
    float v_l100;
    float v_l96;
    float v_l92;
    float v_l88;
    float v_l84;
    float v_l80;
    float v_l76;
    int v_l72;
    int v_l68;
    unsigned short v_l64;
    unsigned short v_l62;
    unsigned char v_l60;
    unsigned char v_l59;
    unsigned char v_l58;
    unsigned char v_l57;
    float v_l56;
    float v_l52;
    float v_l48;
    float v_l44;
    float v_l40;
    float v_l36;
    int v_l32;
    int v_l28;
    int v_l24;
    int v_l20;
    int v_l16;
    int v_l12;
    int v_l8;
};
struct Fr1_0053a930 {
    float v_l128;
};
#pragma pack(pop)
template<class T> __forceinline T il2c_k(T v) { return v; }

// @ 0x0053a930
extern "C" int __cdecl FUN_0053a930(int a4, int a8)
{
    Fr0_0053a930 fb;
    Fr1_0053a930 fa;
    fb.v_l8 = (int)(int)((int)((int)*(int*)((char*)a8 + 4) - (int)*(int*)(char*)a8) >> 4);
    fb.v_l32 = fb.v_l8;
    FUN_0093aa70((unsigned int)a4, (unsigned int)(int)&fb.v_l32, (unsigned int)1, (unsigned int)0);
    fb.v_l12 = 0;
    for (; (unsigned int)fb.v_l12 < (unsigned int)fb.v_l8; fb.v_l12 = fb.v_l12 + 1) {
        fb.v_l16 = (int)(int)((fb.v_l12 << 4) + (int)*(int*)(char*)a8);
        fb.v_l40 = *(float*)((char*)fb.v_l16 + (il2c_k(0) << 2));
        fb.v_l36 = (float)fb.v_l40;
        FUN_0093aa70((unsigned int)a4, (unsigned int)(int)(int)&fb.v_l36, (unsigned int)1, (unsigned int)0);
        fb.v_l48 = *(float*)((char*)fb.v_l16 + (il2c_k(1) << 2));
        fb.v_l44 = (float)fb.v_l48;
        FUN_0093aa70((unsigned int)a4, (unsigned int)(int)(int)&fb.v_l44, (unsigned int)1, (unsigned int)0);
        fb.v_l56 = *(float*)((char*)fb.v_l16 + (il2c_k(2) << 2));
        fb.v_l52 = (float)fb.v_l56;
        FUN_0093aa70((unsigned int)a4, (unsigned int)(int)(int)&fb.v_l52, (unsigned int)1, (unsigned int)0);
        fb.v_l58 = (unsigned char)(unsigned char)*(unsigned char*)((char*)fb.v_l16 + 12);
        fb.v_l57 = (unsigned char)(unsigned char)fb.v_l58;
        FUN_0093a9a0((unsigned int)a4, (unsigned int)(int)(int)&fb.v_l57, (unsigned int)1);
        fb.v_l60 = (unsigned char)(unsigned char)*(unsigned char*)((char*)fb.v_l16 + 13);
        fb.v_l59 = (unsigned char)(unsigned char)fb.v_l60;
        FUN_0093a9a0((unsigned int)a4, (unsigned int)(int)(int)&fb.v_l59, (unsigned int)1);
        fb.v_l64 = (unsigned short)(unsigned short)*(unsigned short*)((char*)fb.v_l16 + 14);
        fb.v_l62 = (unsigned short)(unsigned short)fb.v_l64;
        FUN_0093a9d0((unsigned int)a4, (unsigned int)(int)(int)&fb.v_l62, (unsigned int)1, (unsigned int)0);
    }
    fb.v_l68 = a8 + 20;
    fb.v_l8 = (int)(int)((int)(int)((int)*(int*)((char*)fb.v_l68 + 4) - (int)*(int*)(char*)fb.v_l68) / 20);
    fb.v_l72 = fb.v_l8;
    FUN_0093aa70((unsigned int)a4, (unsigned int)(int)&fb.v_l72, (unsigned int)1, (unsigned int)0);
    fb.v_l20 = 0;
    for (; (unsigned int)fb.v_l20 < (unsigned int)fb.v_l8; fb.v_l20 = fb.v_l20 + 1) {
        fb.v_l24 = (int)(int)(fb.v_l20 * 20 + (int)*(int*)((char*)a8 + 20));
        fb.v_l80 = *(float*)(char*)fb.v_l24;
        fb.v_l76 = (float)fb.v_l80;
        FUN_0093aa70((unsigned int)a4, (unsigned int)(int)(int)&fb.v_l76, (unsigned int)1, (unsigned int)0);
        fb.v_l88 = *(float*)((char*)fb.v_l24 + 4);
        fb.v_l84 = (float)fb.v_l88;
        FUN_0093aa70((unsigned int)a4, (unsigned int)(int)(int)&fb.v_l84, (unsigned int)1, (unsigned int)0);
        fb.v_l96 = *(float*)((char*)fb.v_l24 + 8);
        fb.v_l92 = (float)fb.v_l96;
        FUN_0093aa70((unsigned int)a4, (unsigned int)(int)(int)&fb.v_l92, (unsigned int)1, (unsigned int)0);
        fb.v_l104 = *(float*)((char*)fb.v_l24 + 12);
        fb.v_l100 = (float)fb.v_l104;
        FUN_0093aa70((unsigned int)a4, (unsigned int)(int)(int)&fb.v_l100, (unsigned int)1, (unsigned int)0);
        fb.v_l106 = (unsigned char)(unsigned char)*(unsigned char*)((char*)fb.v_l24 + 16);
        fb.v_l105 = (unsigned char)(unsigned char)fb.v_l106;
        FUN_0093a9a0((unsigned int)a4, (unsigned int)(int)(int)&fb.v_l105, (unsigned int)1);
        fb.v_l108 = (unsigned char)(unsigned char)*(unsigned char*)((char*)fb.v_l24 + 17);
        fb.v_l107 = (unsigned char)(unsigned char)fb.v_l108;
        FUN_0093a9a0((unsigned int)a4, (unsigned int)(int)(int)&fb.v_l107, (unsigned int)1);
        fb.v_l110 = (unsigned char)(unsigned char)*(unsigned char*)((char*)fb.v_l24 + 18);
        fb.v_l109 = (unsigned char)(unsigned char)fb.v_l110;
        FUN_0093a9a0((unsigned int)a4, (unsigned int)(int)(int)&fb.v_l109, (unsigned int)1);
        fb.v_l112 = (unsigned char)(unsigned char)*(unsigned char*)((char*)fb.v_l24 + 19);
        fb.v_l111 = (unsigned char)(unsigned char)fb.v_l112;
        FUN_0093a9a0((unsigned int)a4, (unsigned int)(int)(int)&fb.v_l111, (unsigned int)1);
    }
    fb.v_l116 = a8 + 40;
    fb.v_l8 = (int)(int)((int)((int)*(int*)((char*)fb.v_l116 + 4) - (int)*(int*)(char*)fb.v_l116) >> 2);
    fb.v_l120 = fb.v_l8;
    FUN_0093aa70((unsigned int)a4, (unsigned int)(int)&fb.v_l120, (unsigned int)1, (unsigned int)0);
    fb.v_l28 = 0;
    for (; (unsigned int)fb.v_l28 < (unsigned int)fb.v_l8; fb.v_l28 = fb.v_l28 + 1) {
        fa.v_l128 = *(float*)((char*)(int)*(int*)((char*)a8 + 40) + fb.v_l28 * 4);
        fb.v_l124 = (float)fa.v_l128;
        FUN_0093aa70((unsigned int)a4, (unsigned int)(int)(int)&fb.v_l124, (unsigned int)1, (unsigned int)0);
    }
    return a4;
}
