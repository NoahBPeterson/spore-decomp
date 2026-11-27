// 0x00559590: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00559050/s00559050.cpp, src/game/SPEditors/SPObjectTemplateDB.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
};

extern "C" unsigned char g_013eb394[];
extern "C" unsigned char g_013eb938[];
extern "C" unsigned char g_013ef094[];
extern "C" unsigned char g_013f446c[];
extern "C" unsigned char g_013f4470[];
extern "C" unsigned char g_013f4480[];
extern "C" unsigned char g_013f44b8[];
extern "C" unsigned char g_015e3f00[];
struct C_00426c70 { void FUN_00426c70(); };
struct C_004e8a30 { void FUN_004e8a30(unsigned int); };
struct C_00548400 { void FUN_00548400(); };
struct C_00553fb0 { void FUN_00553fb0(); };
struct C_00564470 { void FUN_00564470(); };
struct C_00564580 { void FUN_00564580(); };
struct C_005646b0 { void FUN_005646b0(); };
struct C_00566ad0 { void FUN_00566ad0(unsigned int); };
struct C_00566ce0 { void FUN_00566ce0(unsigned int); };
struct C_00566da0 { void FUN_00566da0(unsigned int, unsigned int); };
struct C_00567070 { void FUN_00567070(); };
struct C_00690120 { void FUN_00690120(); };
#pragma pack(push, 1)
struct Fr0_00559590 {
    int dead0[2];
    int v_l84;
    int v_l80;
    int v_l76;
    int v_l72;
    int v_l68;
    int v_l64;
    int v_l60;
    int v_l56;
    int v_l52;
    int v_l48;
    int v_l44;
    int v_l40;
    int v_l36;
    int v_l32;
    int v_l28;
    int v_l24;
    int v_l20;
    int v_l16;
    int v_l12;
    int v_l8;
};
#pragma pack(pop)


struct D_00559590 { void FUN_00559590(); };
// @ 0x00559590
void D_00559590::FUN_00559590()
{
    Fr0_00559590 fb;
    *(int*)(char*)(int)this = (int)g_013f44b8;
    *(int*)((char*)(int)this + 4) = (int)g_013f4480;
    *(int*)((char*)(int)this + 8) = (int)g_013f4470;
    *(int*)((char*)(int)this + 12) = (int)g_013f446c;
    *(int*)g_015e3f00 = 0;
    fb.v_l8 = (int)this + 620;
    if ((int)*(int*)(char*)fb.v_l8 != 0) {
        ((il2c_vc0*)(int)(int)*(int*)(char*)fb.v_l8)->s2();
    }
    fb.v_l12 = (int)this + 600;
    ((C_00566da0*)fb.v_l12)->FUN_00566da0((unsigned int)(int)*(int*)(char*)fb.v_l12, (unsigned int)(int)*(int*)((char*)fb.v_l12 + 4));
    ((C_00567070*)fb.v_l12)->FUN_00567070();
    ((C_00564580*)((int)this + 576))->FUN_00564580();
    ((C_00553fb0*)((int)this + 552))->FUN_00553fb0();
    fb.v_l16 = (int)this + 548;
    if ((int)*(int*)(char*)fb.v_l16 != 0) {
        ((il2c_vc1*)(int)*(int*)(char*)fb.v_l16)->s2();
    }
    fb.v_l20 = (int)this + 520;
    ((C_00566ce0*)fb.v_l20)->FUN_00566ce0((unsigned int)(int)*(int*)((char*)fb.v_l20 + 12));
    fb.v_l24 = (int)this + 492;
    ((C_00566ce0*)fb.v_l24)->FUN_00566ce0((unsigned int)(int)*(int*)((char*)fb.v_l24 + 12));
    ((C_00564580*)((int)this + 468))->FUN_00564580();
    fb.v_l28 = (int)this + 372;
    ((C_00564580*)(fb.v_l28 + 56))->FUN_00564580();
    ((C_00564470*)(fb.v_l28 + 28))->FUN_00564470();
    ((C_00564470*)fb.v_l28)->FUN_00564470();
    ((C_00553fb0*)((int)this + 348))->FUN_00553fb0();
    ((C_00553fb0*)((int)this + 324))->FUN_00553fb0();
    ((C_00553fb0*)((int)this + 300))->FUN_00553fb0();
    fb.v_l32 = (int)this + 272;
    ((C_00566ad0*)fb.v_l32)->FUN_00566ad0((unsigned int)(int)*(int*)((char*)fb.v_l32 + 12));
    fb.v_l36 = (int)this + 244;
    ((C_00566ad0*)fb.v_l36)->FUN_00566ad0((unsigned int)(int)*(int*)((char*)fb.v_l36 + 12));
    ((C_00564580*)((int)this + 220))->FUN_00564580();
    ((C_00564580*)((int)this + 196))->FUN_00564580();
    fb.v_l44 = (int)this + 172;
    fb.v_l40 = (int)(int)*(int*)(char*)fb.v_l44;
    for (; (unsigned int)fb.v_l40 < (unsigned int)*(int*)((char*)fb.v_l44 + 4); fb.v_l40 = fb.v_l40 + 8) {
    }
    ((C_00426c70*)fb.v_l44)->FUN_00426c70();
    fb.v_l52 = (int)this + 148;
    fb.v_l48 = (int)(int)*(int*)(char*)fb.v_l52;
    for (; (unsigned int)fb.v_l48 < (unsigned int)*(int*)((char*)fb.v_l52 + 4); fb.v_l48 = fb.v_l48 + 4) {
    }
    ((C_00548400*)fb.v_l52)->FUN_00548400();
    fb.v_l60 = (int)this + 124;
    fb.v_l56 = (int)(int)*(int*)(char*)fb.v_l60;
    for (; (unsigned int)fb.v_l56 < (unsigned int)*(int*)((char*)fb.v_l60 + 4); fb.v_l56 = fb.v_l56 + 4) {
    }
    ((C_00548400*)fb.v_l60)->FUN_00548400();
    fb.v_l68 = (int)this + 100;
    fb.v_l64 = (int)(int)*(int*)(char*)fb.v_l68;
    for (; (unsigned int)fb.v_l64 < (unsigned int)*(int*)((char*)fb.v_l68 + 4); fb.v_l64 = fb.v_l64 + 4) {
    }
    ((C_00548400*)fb.v_l68)->FUN_00548400();
    fb.v_l72 = (int)this + 72;
    ((C_004e8a30*)fb.v_l72)->FUN_004e8a30((unsigned int)(int)*(int*)((char*)fb.v_l72 + 12));
    fb.v_l76 = (int)this + 68;
    if ((int)*(int*)(char*)fb.v_l76 != 0) {
        ((C_00690120*)(int)*(int*)(char*)fb.v_l76)->FUN_00690120();
    }
    fb.v_l84 = (int)this + 40;
    fb.v_l80 = (int)(int)*(int*)(char*)fb.v_l84;
    for (; (unsigned int)fb.v_l80 < (unsigned int)*(int*)((char*)fb.v_l84 + 4); fb.v_l80 = fb.v_l80 + 4) {
    }
    ((C_00548400*)fb.v_l84)->FUN_00548400();
    ((C_005646b0*)((int)this + 20))->FUN_005646b0();
    *(int*)((char*)(int)this + 12) = (int)g_013ef094;
    *(int*)((char*)(int)this + 8) = (int)g_013eb394;
    *(int*)((char*)(int)this + 4) = (int)g_013eb938;
    *(int*)(char*)(int)this = (int)g_013eb938;
    return;
}
