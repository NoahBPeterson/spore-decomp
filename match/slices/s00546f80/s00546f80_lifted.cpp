// 0x00546f80: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00546f80/s00546f80.cpp.

struct C_004237d0 { void FUN_004237d0(); };
struct C_00453540 { void FUN_00453540(); };
struct C_005471e0 { void FUN_005471e0(); };
struct C_00547cf0 { void FUN_00547cf0(unsigned int, unsigned int); };
struct C_00547d30 { void FUN_00547d30(); };
struct C_00547e50 { void FUN_00547e50(unsigned int, unsigned int); };
struct C_00548180 { void FUN_00548180(); };
struct C_00548400 { void FUN_00548400(); };
extern "C" int __cdecl FUN_00f47380(...);
#pragma pack(push, 1)
struct il2c_pi_4_int_8919c3cc { char pad[4]; int x; __forceinline int f() { return (int)((int)x++ + 1); } };
#pragma pack(pop)
template<class T> __forceinline T il2c_k(T v) { return v; }


struct D_00546f80 { void FUN_00546f80(); };
// @ 0x00546f80
// @ 0x00546f80
void D_00546f80::FUN_00546f80()
{
    int v_l24;
    int dead_0_15[3];
    int v_l8;
    int v_l28;
    int v_l100_d;
    int v_l96_30;
    int dead_2_d[3];
    int v_l80_d;
    int v_l76;
    int v_l72_c;
    int v_l68_y;
    int v_l64_n;
    int v_l60;
    int v_l56_92;
    int v_l52_h;
    int dead_1_d[3];
    int v_l36_i;
    int v_l32;
    int v_l152_13;
    int v_l148_20;
    int dead_3[11];
    int v_l156;
    v_l24 = (int)this + 164;
    if ((int)*(int*)(char*)v_l24 != 0) {
        v_l8 = (int)(int)*(int*)(char*)v_l24;
        if (il2c_k(0) != 0) {
            ((il2c_pi_4_int_8919c3cc*)(il2c_k((char*)0)))->f();
        }
        *(int*)(char*)v_l24 = 0;
        if (v_l8 != 0) {
            ((C_00453540*)v_l8)->FUN_00453540();
        }
    }
    v_l32 = (int)this + 248;
    v_l28 = (int)(int)*(int*)(char*)v_l32;
    for (; (unsigned int)v_l28 < (unsigned int)*(int*)((char*)v_l32 + 4); v_l28 = v_l28 + 4) {
    }
    ((C_00548400*)v_l32)->FUN_00548400();
    v_l36_i = (int)this + 224;
    ((C_00547e50*)v_l36_i)->FUN_00547e50((unsigned int)(int)*(int*)(char*)v_l36_i, (unsigned int)(int)*(int*)((char*)v_l36_i + 4));
    ((C_00548180*)v_l36_i)->FUN_00548180();
    ((C_004237d0*)((int)this + 208))->FUN_004237d0();
    v_l64_n = (int)this + 184;
    if ((int)((int)*(int*)((char*)v_l64_n + 8) - (int)*(int*)(char*)v_l64_n) > 1) {
        v_l60 = (int)(int)((int)*(int*)((char*)v_l64_n + 8) - (int)*(int*)(char*)v_l64_n);
        v_l56_92 = (int)(int)*(int*)(char*)v_l64_n;
        if (v_l56_92 != 0) {
            v_l52_h = v_l56_92;
            FUN_00f47380((unsigned int)v_l52_h);
        }
    }
    v_l80_d = (int)this + 168;
    if ((int)((int)*(int*)((char*)v_l80_d + 8) - (int)*(int*)(char*)v_l80_d) > 1) {
        v_l76 = (int)(int)((int)*(int*)((char*)v_l80_d + 8) - (int)*(int*)(char*)v_l80_d);
        v_l72_c = (int)(int)*(int*)(char*)v_l80_d;
        if (v_l72_c != 0) {
            v_l68_y = v_l72_c;
            FUN_00f47380((unsigned int)v_l68_y);
        }
    }
    v_l96_30 = (int)this + 164;
    if ((int)*(int*)(char*)v_l96_30 != 0) {
        ((C_00453540*)(int)*(int*)(char*)v_l96_30)->FUN_00453540();
    }
    v_l100_d = (int)this + 140;
    ((C_00547cf0*)v_l100_d)->FUN_00547cf0((unsigned int)(int)*(int*)(char*)v_l100_d, (unsigned int)(int)*(int*)((char*)v_l100_d + 4));
    ((C_00547d30*)v_l100_d)->FUN_00547d30();
    ((C_005471e0*)((int)this + 120))->FUN_005471e0();
    ((C_004237d0*)((int)this + 104))->FUN_004237d0();
    ((C_004237d0*)((int)this + 72))->FUN_004237d0();
    ((C_004237d0*)((int)this + 24))->FUN_004237d0();
    if ((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) > 1) {
        v_l156 = (int)(int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this);
        v_l152_13 = (int)(int)*(int*)(char*)(int)this;
        if (v_l152_13 != 0) {
            v_l148_20 = v_l152_13;
            FUN_00f47380((unsigned int)v_l148_20);
        }
    }
    return;
}
