// 0x00529bf0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s005296b0/s005296b0.cpp, src/game/SPBake/SPSkinnerRTT_SporeApp.cpp.

extern "C" unsigned char g_015dea58[];
extern "C" unsigned char g_015dea5c[];
extern "C" unsigned char g_015dea60[];
extern "C" unsigned char g_015dea64[];
extern "C" unsigned char g_015dea68[];
extern "C" unsigned char g_016f8b00[];
extern "C" unsigned char g_016f9218[];
extern "C" unsigned char g_016f921c[];
extern "C" unsigned char g_016f9238[];
extern "C" unsigned char g_016f923c[];
extern "C" unsigned char g_016f9244[];
extern "C" unsigned char g_016fa38c[];
extern "C" void __cdecl FUN_00529350(...);
extern "C" void __cdecl FUN_011f1280(...);
struct C_011f38e0 { void FUN_011f38e0(); };
#pragma pack(push, 1)
struct Fr0_00529bf0 {
    int v_l8;
};
#pragma pack(pop)


struct D_00529bf0 { void FUN_00529bf0(); };
// @ 0x00529bf0
void D_00529bf0::FUN_00529bf0()
{
    Fr0_00529bf0 fb;
    *(int*)g_016fa38c = *(int*)g_016fa38c | 32768;
    *(int*)g_016f9238 = *(int*)g_015dea64;
    *(int*)g_016fa38c = *(int*)g_016fa38c | 65536;
    if (*(int*)g_015dea5c != 0) {
        *(int*)g_016f923c = 4;
    } else {
        *(int*)g_016f923c = 8;
    }
    *(int*)g_016fa38c = *(int*)g_016fa38c | 128;
    *(int*)g_016f9218 = *(int*)g_015dea58;
    FUN_00529350((unsigned int)168, (unsigned int)*(int*)g_015dea68);
    if (*(int*)g_015dea60 != 8) {
        *(int*)g_016fa38c = *(int*)g_016fa38c | 256;
        *(int*)g_016f921c = 1;
    } else {
        *(int*)g_016fa38c = *(int*)g_016fa38c | 256;
        *(int*)g_016f921c = 0;
    }
    *(int*)g_016fa38c = *(int*)g_016fa38c | 262144;
    *(int*)g_016f9244 = *(int*)g_015dea60;
    FUN_011f1280((unsigned int)0, (unsigned int)0);
    FUN_011f1280((unsigned int)1, (unsigned int)0);
    *(int*)g_016f8b00 = *(int*)g_016f8b00 | 1;
    *(int*)g_016f8b00 = *(int*)g_016f8b00 | 2;
    ((C_011f38e0*)(int)*(int*)(char*)(int)this)->FUN_011f38e0();
    fb.v_l8 = (int)(int)*(int*)(char*)(int)this;
    *(int*)((char*)fb.v_l8 + 64) = 0;
    return;
}
