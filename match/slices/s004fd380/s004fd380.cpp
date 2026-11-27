// 0x004fd380: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004fcae0/s004fcae0.cpp.

struct C_004f8a40 { void FUN_004f8a40(unsigned int, float, float, unsigned int); };
struct C_004fcd00 { void FUN_004fcd00(unsigned int, float, unsigned int, float, float, unsigned int, float, float, unsigned int); };
#pragma pack(push, 1)
struct Fr0_004fd380 {
    int v_l68;
    float v_l64;
    int v_l60;
    int v_l56;
    int v_l52;
    float v_l48;
    int v_l44;
    float v_l40;
    int v_l36;
    float v_l32;
    int v_l28;
    int v_l24;
    int v_l20;
    int v_l16;
    int v_l12;
    int v_l8;
};
struct Fr1_004fd380 {
    int v_l72;
};
#pragma pack(pop)


struct D_004fd380 { void FUN_004fd380(int a4); };
// @ 0x004fd380
void D_004fd380::FUN_004fd380(int a4)
{
    Fr0_004fd380 fb;
    Fr1_004fd380 fa;
    fb.v_l8 = a4;
    fb.v_l16 = 0;
    fb.v_l68 = (int)this + 8;
    fb.v_l12 = (int)(int)((int)(int)((int)*(int*)((char*)fb.v_l68 + 4) - (int)*(int*)(char*)fb.v_l68) / 24);
    for (; (unsigned int)fb.v_l16 < (unsigned int)fb.v_l12; fb.v_l16 = fb.v_l16 + 1) {
        fb.v_l20 = (int)(int)(fb.v_l16 * 24 + (int)*(int*)((char*)(int)this + 8));
        ((C_004f8a40*)fb.v_l8)->FUN_004f8a40((unsigned int)fb.v_l20, *(float*)((char*)fb.v_l20 + 12), *(float*)((char*)fb.v_l20 + 16), (unsigned int)(int)*(int*)((char*)fb.v_l20 + 20));
    }
    fb.v_l28 = 0;
    fa.v_l72 = (int)this + 28;
    fb.v_l24 = (int)(int)((int)((int)*(int*)((char*)fa.v_l72 + 4) - (int)*(int*)(char*)fa.v_l72) >> 4);
    for (; (unsigned int)fb.v_l28 < (unsigned int)fb.v_l24; fb.v_l28 = fb.v_l28 + 1) {
        fb.v_l60 = (int)(int)((fb.v_l28 << 4) + (int)*(int*)((char*)(int)this + 28));
        fb.v_l44 = (int)(int)*(int*)(char*)fb.v_l60;
        fb.v_l52 = (int)(int)*(int*)((char*)fb.v_l60 + 4);
        fb.v_l48 = *(float*)((char*)(int)*(int*)((char*)(int)this + 8) + fb.v_l44 * 24 + 12);
        fb.v_l64 = *(float*)((char*)(int)*(int*)((char*)(int)this + 8) + fb.v_l52 * 24 + 12);
        fb.v_l32 = *(float*)((char*)(int)*(int*)((char*)(int)this + 8) + fb.v_l44 * 24 + 16);
        fb.v_l40 = *(float*)((char*)(int)*(int*)((char*)(int)this + 8) + fb.v_l52 * 24 + 16);
        fb.v_l36 = (int)(int)(fb.v_l44 * 24 + (int)*(int*)((char*)(int)this + 8));
        fb.v_l56 = (int)(int)(fb.v_l52 * 24 + (int)*(int*)((char*)(int)this + 8));
        ((C_004fcd00*)(int)this)->FUN_004fcd00((unsigned int)fb.v_l8, *(float*)((char*)fb.v_l60 + 8), (unsigned int)fb.v_l36, (float)fb.v_l48, (float)fb.v_l32, (unsigned int)fb.v_l56, (float)fb.v_l64, (float)fb.v_l40, (unsigned int)(int)*(int*)((char*)fb.v_l60 + 12));
    }
    return;
}
