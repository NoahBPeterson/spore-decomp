// 0x007fc200: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s007fb7b0/s007fb7b0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
};

extern "C" unsigned char g_01415a08[];
extern "C" unsigned char g_01415a64[];
extern "C" unsigned char g_01415a74[];
extern "C" unsigned char g_01415a84[];
extern "C" unsigned char g_01415a9c[];
struct C_004237d0 { void FUN_004237d0(); };
struct C_007f9fe0 { void FUN_007f9fe0(); };
struct C_007fa060 { void FUN_007fa060(); };
struct C_007fb110 { int FUN_007fb110(); };
struct C_00a16a20 { void FUN_00a16a20(); };
#pragma pack(push, 1)
struct Fr0_007fc200 {
    int dead0[3];
    int v_l8;
};
#pragma pack(pop)


struct D_007fc200 { void FUN_007fc200(); };
// @ 0x007fc200
void D_007fc200::FUN_007fc200()
{
    Fr0_007fc200 fb;
    *(int*)(char*)(int)this = (int)g_01415a9c;
    *(int*)((char*)(int)this + 4) = (int)g_01415a84;
    *(int*)((char*)(int)this + 8) = (int)g_01415a74;
    *(int*)((char*)(int)this + 16) = (int)g_01415a64;
    *(int*)((char*)(int)this + 24) = (int)g_01415a08;
    ((C_007f9fe0*)((int)this + 24))->FUN_007f9fe0();
    ((C_007fa060*)((int)this + 24))->FUN_007fa060();
    fb.v_l8 = (int)this + 120;
    if ((int)*(int*)(char*)fb.v_l8 != 0) {
        ((il2c_vc0*)(int)*(int*)(char*)fb.v_l8)->s1();
    }
    ((C_004237d0*)((int)this + 104))->FUN_004237d0();
    ((C_00a16a20*)((int)this + 24))->FUN_00a16a20();
    ((C_007fb110*)(int)this)->FUN_007fb110();
    return;
}
