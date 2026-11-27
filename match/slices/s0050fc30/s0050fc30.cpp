// 0x0050fc30: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0050f8b0/s0050f8b0.cpp, src/game/SPGonzago/SPStarManager.cpp.

struct C_004c0b80 { int FUN_004c0b80(); };
struct C_0050e5f0 { void FUN_0050e5f0(unsigned int); };
extern "C" int __cdecl FUN_00510080(...);
extern "C" void __cdecl FUN_00511790(...);
extern "C" void __cdecl FUN_005117d0(...);
extern "C" int __cdecl FUN_00511810(...);
extern "C" void __cdecl FUN_00511880(...);
extern "C" void __cdecl FUN_00511be0(...);
extern "C" void __cdecl FUN_00511c80(...);
extern "C" void __cdecl FUN_00511d00(...);
extern "C" int __cdecl FUN_00511d50(...);
extern "C" void __cdecl FUN_00f47380(...);
#pragma pack(push, 1)
struct Fr0_0050fc30 {
    int v_l364;
    int v_l360;
    int v_l356;
    int v_l352;
    int dead0[8];
    char dead1;
    char dead2;
    char dead3;
    unsigned char v_l313;
    int v_l312;
    int v_l308;
    int v_l304;
    char dead4;
    char dead5;
    unsigned char v_l298;
    int dead6[12];
    char dead7;
    int v_l248;
    int dead8[13];
    int v_l192;
    int v_l188;
    char dead9;
    char dead10;
    unsigned char v_l182;
    int dead11[3];
    char dead12;
    char dead13;
    char dead14;
    unsigned char v_l166;
    unsigned char v_l165;
    int v_l164;
    int v_l160;
    int v_l156;
    int v_l152;
    int v_l148;
    int v_l144;
    char dead15;
    char dead16;
    unsigned char v_l138;
    char dead17;
    int v_l136;
    int v_l132;
    int v_l128;
    int v_l124;
    int v_l120;
    int v_l116;
    int v_l112;
    int v_l108;
    int v_l104;
    int dead18[20];
    float v_l20;
    float v_l16;
    float v_l12;
    int v_l8;
};
struct Fr1_0050fc30 {
    int v_l368;
};
#pragma pack(pop)


struct D_0050fc30 { void FUN_0050fc30(int a4, int a8, int a12); };
// @ 0x0050fc30
void D_0050fc30::FUN_0050fc30(int a4, int a8, int a12)
{
    Fr0_0050fc30 fb;
    Fr1_0050fc30 fa;
    if ((unsigned int)a8 <= (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)((char*)(int)this + 4)) / 100)) {
        if ((unsigned int)a8 > (unsigned int)0) {
            ((C_0050e5f0*)(int)&fb.v_l108)->FUN_0050e5f0((unsigned int)a12);
            fb.v_l20 = *(float*)((char*)a12 + 88);
            fb.v_l16 = *(float*)((char*)a12 + 92);
            fb.v_l12 = *(float*)((char*)a12 + 96);
            fb.v_l112 = (int)(int)((int)((int)*(int*)((char*)(int)this + 4) - a4) / 100);
            fb.v_l8 = (int)(int)*(int*)((char*)(int)this + 4);
            if ((unsigned int)a8 < (unsigned int)fb.v_l112) {
                fb.v_l164 = (int)(int)*(int*)((char*)(int)this + 4);
                fb.v_l160 = (int)(int)*(int*)((char*)(int)this + 4);
                fb.v_l156 = (int)(int)((int)*(int*)((char*)(int)this + 4) - a8 * 100);
                fb.v_l144 = fb.v_l164;
                fb.v_l148 = fb.v_l160;
                fb.v_l152 = fb.v_l156;
                FUN_00511be0((unsigned int)(int)&fb.v_l136, (unsigned int)fb.v_l152, (unsigned int)fb.v_l148, (unsigned int)fb.v_l144, (unsigned int)(int)fb.v_l138);
                *(int*)((char*)(int)this + 4) = (int)(int)(a8 * 100 + (int)*(int*)((char*)(int)this + 4));
                fb.v_l166 = (unsigned char)0;
                fb.v_l165 = (unsigned char)0;
                FUN_00511d00((unsigned int)a4, (unsigned int)(fb.v_l8 - a8 * 100), (unsigned int)fb.v_l8);
                FUN_005117d0((unsigned int)a4, (unsigned int)(a8 * 100 + a4), (unsigned int)(int)&fb.v_l108);
            } else {
                fb.v_l192 = (int)(int)*(int*)((char*)(int)this + 4);
                fb.v_l188 = fb.v_l192;
                FUN_00511c80((unsigned int)fb.v_l188, (unsigned int)(a8 - fb.v_l112), (unsigned int)(int)&fb.v_l108, (unsigned int)(int)fb.v_l182);
                *(int*)((char*)(int)this + 4) = (int)(int)((a8 - fb.v_l112) * 100 + (int)*(int*)((char*)(int)this + 4));
                FUN_00511790((unsigned int)a4, (unsigned int)fb.v_l8, (unsigned int)(int)*(int*)((char*)(int)this + 4));
                *(int*)((char*)(int)this + 4) = (int)(int)(fb.v_l112 * 100 + (int)*(int*)((char*)(int)this + 4));
                FUN_005117d0((unsigned int)a4, (unsigned int)fb.v_l8, (unsigned int)(int)&fb.v_l108);
            }
            fb.v_l248 = fb.v_l108;
            for (; (unsigned int)fb.v_l248 < (unsigned int)fb.v_l104; fb.v_l248 = fb.v_l248 + 4) {
            }
            ((C_004c0b80*)(int)&fb.v_l108)->FUN_004c0b80();
        }
    } else {
        fb.v_l124 = (int)(int)((int)(int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 100);
        fb.v_l132 = (int)(int)((unsigned int)fb.v_l124 > (unsigned int)0 ? fb.v_l124 << 1 : 1);
        fb.v_l116 = (int)(int)((unsigned int)fb.v_l132 > (unsigned int)(fb.v_l124 + a8) ? fb.v_l132 : fb.v_l124 + a8);
        fb.v_l128 = (int)(int)(fb.v_l116 != 0 ? (int)(int)FUN_00511810((unsigned int)((int)this + 12), (unsigned int)(fb.v_l116 * 100), (unsigned int)4, (unsigned int)0) : 0);
        fb.v_l120 = (int)(int)FUN_00510080((unsigned int)(int)*(int*)(char*)(int)this, (unsigned int)a4, (unsigned int)fb.v_l128);
        fb.v_l308 = fb.v_l120;
        fb.v_l304 = fb.v_l308;
        FUN_00511c80((unsigned int)fb.v_l304, (unsigned int)a8, (unsigned int)a12, (unsigned int)(int)fb.v_l298);
        fb.v_l356 = a8 * 100 + fb.v_l120;
        fb.v_l352 = (int)(int)*(int*)((char*)(int)this + 4);
        fb.v_l313 = (unsigned char)0;
        fb.v_l312 = (int)(int)FUN_00511d50((unsigned int)a4, (unsigned int)fb.v_l352, (unsigned int)fb.v_l356);
        FUN_00511880((unsigned int)a4, (unsigned int)fb.v_l352, (unsigned int)fb.v_l356);
        fb.v_l120 = fb.v_l312;
        fa.v_l368 = (int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) / 100);
        fb.v_l364 = (int)(int)*(int*)(char*)(int)this;
        if (fb.v_l364 != 0) {
            if (fb.v_l364 != (int)*(int*)((char*)(int)this + 16)) {
                fb.v_l360 = fb.v_l364;
                FUN_00f47380((unsigned int)fb.v_l360);
            }
        }
        *(int*)(char*)(int)this = fb.v_l128;
        *(int*)((char*)(int)this + 4) = fb.v_l120;
        *(int*)((char*)(int)this + 8) = fb.v_l116 * 100 + fb.v_l128;
    }
    return;
}
