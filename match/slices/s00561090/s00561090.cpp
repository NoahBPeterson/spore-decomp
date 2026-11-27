// 0x00561090: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s005609a0/s005609a0.cpp, src/game/SPEditors/SPObjectTemplateDB.cpp.

extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
#pragma intrinsic(_InterlockedExchange)
extern "C" unsigned char g_013eb938[];
extern "C" unsigned char g_013ef094[];
extern "C" unsigned char g_013f1ab0[];
extern "C" unsigned char g_013f4af8[];
extern "C" unsigned char g_013f4afc[];
extern "C" unsigned char g_013f4b00[];
extern "C" unsigned char g_0140b5a0[];
#pragma pack(push, 1)
struct Fr0_00561090 {
    int v_l28;
    int v_l24;
    int v_l20;
    int v_l16;
    int v_l12;
    int dead0[1];
};
#pragma pack(pop)


struct D_00561090 { int FUN_00561090(); };
// @ 0x00561090
int D_00561090::FUN_00561090()
{
    Fr0_00561090 fb;
    *(int*)(char*)(int)this = (int)g_013eb938;
    *(int*)(char*)(int)this = (int)g_013f1ab0;
    fb.v_l12 = (int)this + 4;
    *(int*)(char*)fb.v_l12 = (int)g_0140b5a0;
    fb.v_l20 = (int)this + 8;
    *(int*)(char*)fb.v_l20 = (int)g_013ef094;
    fb.v_l16 = fb.v_l20 + 4;
    _InterlockedExchange((long volatile*)(fb.v_l16), (long)(0));
    *(int*)(char*)(int)this = (int)g_013f4b00;
    *(int*)((char*)(int)this + 4) = (int)g_013f4afc;
    *(int*)((char*)(int)this + 8) = (int)g_013f4af8;
    fb.v_l24 = (int)this + 16;
    *(int*)(char*)fb.v_l24 = 0;
    *(int*)((char*)fb.v_l24 + 4) = 0;
    *(int*)((char*)fb.v_l24 + 8) = 0;
    fb.v_l28 = (int)this + 28;
    *(int*)(char*)fb.v_l28 = 0;
    *(int*)((char*)fb.v_l28 + 4) = 0;
    *(int*)((char*)fb.v_l28 + 8) = 0;
    return (int)this;
}
