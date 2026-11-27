// 0x007fbf40: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s007fb7b0/s007fb7b0.cpp.

extern "C" unsigned char g_01415714[];
extern "C" unsigned char g_014158f8[];
extern "C" unsigned char g_014159f4[];
extern "C" unsigned char g_01415a08[];
extern "C" unsigned char g_01415a64[];
extern "C" unsigned char g_01415a74[];
extern "C" unsigned char g_01415a84[];
extern "C" unsigned char g_01415a9c[];
struct C_00576770 { void FUN_00576770(unsigned int); };
struct C_0059a180 { void FUN_0059a180(); };
struct C_007f93c0 { int FUN_007f93c0(unsigned int); };
struct C_007f93d0 { int FUN_007f93d0(unsigned int); };
struct C_007fba80 { void FUN_007fba80(); };
struct C_00e5cac0 { int FUN_00e5cac0(unsigned int); };
#pragma pack(push, 1)
struct Fr0_007fbf40 {
    int dead0[5];
};
#pragma pack(pop)


struct D_007fbf40 { int FUN_007fbf40(); };
// @ 0x007fbf40
int D_007fbf40::FUN_007fbf40()
{
    Fr0_007fbf40 fb;
    ((C_007fba80*)(int)this)->FUN_007fba80();
    (*((int*)((char*)&fb + 4))) = (int)this + 24;
    ((C_0059a180*)(*((int*)((char*)&fb + 4))))->FUN_0059a180();
    *(int*)(char*)(*((int*)((char*)&fb + 4))) = (int)g_01415714;
    *(int*)(char*)(*((int*)((char*)&fb + 4))) = (int)g_014158f8;
    *(int*)(char*)(int)this = (int)g_01415a9c;
    *(int*)((char*)(int)this + 4) = (int)g_01415a84;
    *(int*)((char*)(int)this + 8) = (int)g_01415a74;
    *(int*)((char*)(int)this + 16) = (int)g_01415a64;
    *(int*)((char*)(int)this + 24) = (int)g_01415a08;
    *(unsigned char*)((char*)(int)this + 92) = (unsigned char)0;
    *(int*)((char*)(int)this + 96) = -1;
    *(int*)((char*)(int)this + 100) = 0;
    ((C_00576770*)((int)this + 104))->FUN_00576770((unsigned int)((C_00e5cac0*)(int)((int*)((char*)&fb + 11)))->FUN_00e5cac0((unsigned int)(int)g_014159f4));
    (*((int*)((char*)&fb + 0))) = (int)this + 120;
    *(int*)(char*)(*((int*)((char*)&fb + 0))) = 0;
    *(int*)((char*)(int)this + 28) = (int)this + 44;
    *(int*)((char*)(int)this + 32) = (int)this + 48;
    *(int*)((char*)(int)this + 36) = (int)this + 52;
    *(int*)((char*)(int)this + 40) = (int)this + 56;
    (*((int*)((char*)&fb + 16))) = 0;
    for (; (*((int*)((char*)&fb + 16))) < 4; (*((int*)((char*)&fb + 16))) = (*((int*)((char*)&fb + 16))) + 1) {
        *(int*)(char*)((C_007f93c0*)(int)this)->FUN_007f93c0((unsigned int)(*((int*)((char*)&fb + 16)))) = 0;
    }
    *(int*)((char*)(int)this + 60) = (int)this + 76;
    *(int*)((char*)(int)this + 64) = (int)this + 80;
    *(int*)((char*)(int)this + 68) = (int)this + 84;
    *(int*)((char*)(int)this + 72) = (int)this + 88;
    (*((int*)((char*)&fb + 12))) = 0;
    for (; (*((int*)((char*)&fb + 12))) < 4; (*((int*)((char*)&fb + 12))) = (*((int*)((char*)&fb + 12))) + 1) {
        *(int*)(char*)((C_007f93d0*)(int)this)->FUN_007f93d0((unsigned int)(*((int*)((char*)&fb + 12)))) = 0;
    }
    return (int)this;
}
