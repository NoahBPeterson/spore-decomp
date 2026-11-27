// 0x00550cf0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00550bd0/s00550bd0.cpp, src/game/SPBake/SPPollinatorAssetDirectory.cpp.

extern "C" unsigned char g_013f027c[];
struct C_00429580 { int FUN_00429580(unsigned int, unsigned int); };
#pragma pack(push, 1)
struct Fr0_00550cf0 {
    int v_l24;
    int v_l20;
    char dead0;
    char dead1;
    char dead2;
    unsigned char v_l13;
    int v_l12;
    int v_l8;
};
#pragma pack(pop)


struct D_00550cf0 { void FUN_00550cf0(int a4); };
// @ 0x00550cf0
void D_00550cf0::FUN_00550cf0(int a4)
{
    Fr0_00550cf0 fb;
    fb.v_l8 = (int)(int)*(int*)((char*)(int)this + 172);
    fb.v_l12 = (int)(int)*(int*)((char*)(int)this + 176);
    fb.v_l13 = (unsigned char)1;
    while (fb.v_l8 != fb.v_l12) {
        fb.v_l20 = fb.v_l8;
        if ((int)fb.v_l13 == 0) {
            fb.v_l24 = (int)g_013f027c;
            while ((int)*(unsigned short*)(char*)fb.v_l24 != 0) {
                fb.v_l24 = fb.v_l24 + 2;
            }
            ((C_00429580*)a4)->FUN_00429580((unsigned int)(int)g_013f027c, (unsigned int)((fb.v_l24 - (int)g_013f027c >> 1 << 1) + (int)g_013f027c));
        }
        ((C_00429580*)a4)->FUN_00429580((unsigned int)(int)*(int*)(char*)fb.v_l20, (unsigned int)(int)*(int*)((char*)fb.v_l20 + 4));
        fb.v_l13 = (unsigned char)0;
        fb.v_l8 = fb.v_l8 + 16;
    }
    return;
}
