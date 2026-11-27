// 0x00423110: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00423110/s00423110.cpp, src/game/SPGonzago/_at_00420000.cpp.

extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
#pragma intrinsic(_InterlockedExchange)
extern "C" unsigned char g_013eb90c[];
extern "C" unsigned char g_013eb918[];
#pragma pack(push, 1)
struct Fr0_00423110 {
    int v_l12;
    int v_l8;
};
#pragma pack(pop)


struct D_00423110 { int FUN_00423110(int a4); };
// @ 0x00423110
int D_00423110::FUN_00423110(int a4)
{
    Fr0_00423110 fb;
    fb.v_l8 = (int)this + 8;
    *(int*)((char*)fb.v_l8 + 40) = a4;
    *(int*)(char*)(int)this = (int)g_013eb918;
    *(int*)(char*)(int)this = (int)g_013eb90c;
    fb.v_l12 = (int)this + 4;
    _InterlockedExchange((long volatile*)(fb.v_l12), (long)(0));
    *(int*)(char*)(int)this = (int)g_013eb90c;
    return (int)this;
}
