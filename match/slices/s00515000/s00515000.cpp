// 0x00515000: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00514910/s00514910.cpp.

struct C_00514e10 { int FUN_00514e10(); };
struct C_00515170 { void FUN_00515170(unsigned int); };
struct C_0056a240 { int FUN_0056a240(unsigned int); };
#pragma pack(push, 1)
struct Fr0_00515000 {
    int v_l32;
    int v_l28;
    int v_l24;
    int v_l20;
    int v_l16;
    int v_l12;
    int v_l8;
};
#pragma pack(pop)


struct D_00515000 { void FUN_00515000(int a4); };
// @ 0x00515000
void D_00515000::FUN_00515000(int a4)
{
    Fr0_00515000 fb;
    fb.v_l24 = (int)(int)((int)((unsigned int)a4 >> 2) + 1);
    fb.v_l8 = 8;
    fb.v_l28 = fb.v_l24 + 2;
    fb.v_l32 = (int)(int)((unsigned int)fb.v_l8 < (unsigned int)fb.v_l28 ? (int)&fb.v_l28 : (int)&fb.v_l8);
    *(int*)((char*)(int)this + 4) = (int)(int)*(int*)(char*)fb.v_l32;
    *(int*)(char*)(int)this = (int)((C_0056a240*)(int)this)->FUN_0056a240((unsigned int)(int)*(int*)((char*)(int)this + 4));
    fb.v_l16 = (int)(int)((int)*(int*)(char*)(int)this + (int)((int)((unsigned int)(int)((int)*(int*)((char*)(int)this + 4) - fb.v_l24) >> 1) << 2));
    fb.v_l20 = fb.v_l16 + (fb.v_l24 << 2);
    fb.v_l12 = fb.v_l16;
    while ((unsigned int)fb.v_l12 < (unsigned int)fb.v_l20) {
        *(int*)(char*)fb.v_l12 = ((C_00514e10*)(int)this)->FUN_00514e10();
        fb.v_l12 = fb.v_l12 + 4;
    }
    ((C_00515170*)((int)this + 8))->FUN_00515170((unsigned int)fb.v_l16);
    *(int*)((char*)(int)this + 8) = (int)(int)*(int*)((char*)(int)this + 12);
    ((C_00515170*)((int)this + 24))->FUN_00515170((unsigned int)(fb.v_l20 - 4));
    *(int*)((char*)(int)this + 24) = (int)(int)((int)((int)(unsigned int)((unsigned int)a4 % (unsigned int)4) * 72) + (int)*(int*)((char*)(int)this + 28));
    return;
}
