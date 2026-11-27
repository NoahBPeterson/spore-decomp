// 0x00548a30: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00547e90/s00547e90.cpp, src/game/SPBake/SPFeedXml.cpp.

struct C_00547840 { void FUN_00547840(); };
struct C_005496a0 { void FUN_005496a0(unsigned int); };
extern "C" void __cdecl FUN_00f47380(...);
#pragma pack(push, 1)
struct Fr0_00548a30 {
    int v_l132;
    int v_l128;
    int dead0[17];
    int v_l56;
    int v_l52;
    int v_l48;
    int dead1[8];
    char dead2;
    unsigned char v_l11;
    unsigned char v_l10;
    unsigned char v_l9;
    int v_l8;
};
#pragma pack(pop)
__forceinline void il2c_d_FUN_00f47380(int p, int fl) { if (fl & 1) FUN_00f47380((unsigned int)(p)); }


struct D_00548a30 { int FUN_00548a30(int a4, int a8); };
// @ 0x00548a30
int D_00548a30::FUN_00548a30(int a4, int a8)
{
    Fr0_00548a30 fb;
    fb.v_l56 = (int)(int)*(int*)((char*)(int)this + 4);
    fb.v_l10 = (unsigned char)0;
    fb.v_l9 = (unsigned char)0;
    fb.v_l11 = (unsigned char)0;
    fb.v_l52 = a4;
    fb.v_l48 = a8;
    for (; fb.v_l48 != fb.v_l56; fb.v_l52 = fb.v_l52 + 112, fb.v_l48 = fb.v_l48 + 112) {
        ((C_005496a0*)fb.v_l52)->FUN_005496a0((unsigned int)fb.v_l48);
    }
    fb.v_l8 = fb.v_l52;
    fb.v_l132 = (int)(int)*(int*)((char*)(int)this + 4);
    fb.v_l128 = fb.v_l8;
    for (; (unsigned int)fb.v_l128 < (unsigned int)fb.v_l132; fb.v_l128 = fb.v_l128 + 112) {
        ((C_00547840*)fb.v_l128)->FUN_00547840();
        il2c_d_FUN_00f47380(fb.v_l128, 0);
    }
    *(int*)((char*)(int)this + 4) = (int)(int)((int)*(int*)((char*)(int)this + 4) - (a8 - a4) / 112 * 112);
    return a4;
}
