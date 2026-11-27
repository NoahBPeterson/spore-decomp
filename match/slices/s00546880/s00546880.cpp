// 0x00546880: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00546160/s00546160.cpp.

struct C_005477a0 { void FUN_005477a0(); };
struct C_00548e70 { void FUN_00548e70(unsigned int); };
extern "C" void __cdecl FUN_00f47380(...);
#pragma pack(push, 1)
struct Fr0_00546880 {
    int v_l60;
    int dead0[7];
    int v_l28;
    int v_l24;
    int v_l20;
    int dead1[2];
    char dead2;
    unsigned char v_l7;
    unsigned char v_l6;
    unsigned char v_l5;
};
#pragma pack(pop)
__forceinline void il2c_d_FUN_00f47380(int p, int fl) { if (fl & 1) FUN_00f47380((unsigned int)(p)); }


struct D_00546880 { int FUN_00546880(int a4); };
// @ 0x00546880
int D_00546880::FUN_00546880(int a4)
{
    Fr0_00546880 fb;
    if ((unsigned int)(a4 + 52) < (unsigned int)*(int*)((char*)(int)this + 4)) {
        fb.v_l28 = (int)(int)*(int*)((char*)(int)this + 4);
        fb.v_l6 = (unsigned char)0;
        fb.v_l5 = (unsigned char)0;
        fb.v_l7 = (unsigned char)0;
        fb.v_l24 = a4;
        fb.v_l20 = a4 + 52;
        for (; fb.v_l20 != fb.v_l28; fb.v_l24 = fb.v_l24 + 52, fb.v_l20 = fb.v_l20 + 52) {
            ((C_00548e70*)fb.v_l24)->FUN_00548e70((unsigned int)fb.v_l20);
        }
    }
    *(int*)((char*)(int)this + 4) = (int)(int)((int)*(int*)((char*)(int)this + 4) - 52);
    fb.v_l60 = (int)(int)*(int*)((char*)(int)this + 4);
    ((C_005477a0*)fb.v_l60)->FUN_005477a0();
    il2c_d_FUN_00f47380(fb.v_l60, 0);
    return a4;
}
