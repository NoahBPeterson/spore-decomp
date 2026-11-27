// 0x00506590: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00505850/s00505850.cpp.

extern "C" unsigned char g_013eecd8[];
extern "C" unsigned char g_013f116c[];
extern "C" unsigned char g_01471064[];
extern "C" unsigned char g_01485720[];
struct C_005288f0 { int FUN_005288f0(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00f473a0(...);
#pragma pack(push, 1)
struct Fr0_00506590 {
    int v_l16;
    int v_l12;
    int v_l8;
};
#pragma pack(pop)


struct D_00506590 { void FUN_00506590(int a4); };
// @ 0x00506590
void D_00506590::FUN_00506590(int a4)
{
    Fr0_00506590 fb;
    fb.v_l8 = (int)(int)FUN_00f473a0((unsigned int)100, (unsigned int)(int)g_013f116c, (unsigned int)0, (unsigned int)0, (unsigned int)0, (unsigned int)0);
    *(int*)((char*)(int)this + 16) = (int)(int)(fb.v_l8 != 0 ? (int)((C_005288f0*)fb.v_l8)->FUN_005288f0((unsigned int)a4, (unsigned int)a4) : 0);
    fb.v_l12 = (int)(int)FUN_00f473a0((unsigned int)100, (unsigned int)(int)g_013f116c, (unsigned int)0, (unsigned int)0, (unsigned int)0, (unsigned int)0);
    *(int*)((char*)(int)this + 20) = (int)(int)(fb.v_l12 != 0 ? (int)((C_005288f0*)fb.v_l12)->FUN_005288f0((unsigned int)a4, (unsigned int)a4) : 0);
    fb.v_l16 = (int)(int)FUN_00f473a0((unsigned int)100, (unsigned int)(int)g_013f116c, (unsigned int)0, (unsigned int)0, (unsigned int)0, (unsigned int)0);
    *(int*)((char*)(int)this + 24) = (int)(int)(fb.v_l16 != 0 ? (int)((C_005288f0*)fb.v_l16)->FUN_005288f0((unsigned int)a4, (unsigned int)a4) : 0);
    *(int*)((char*)(int)this + 28) = a4;
    *(float*)((char*)(int)this + 32) = (float)*(float*)g_01471064;
    *(float*)((char*)(int)this + 36) = (float)*(float*)g_01485720;
    *(float*)((char*)(int)this + 40) = (float)*(float*)g_013eecd8;
    *(float*)((char*)(int)this + 44) = (float)*(float*)g_01485720;
    *(float*)((char*)(int)this + 48) = (float)*(float*)g_01485720;
    return;
}
