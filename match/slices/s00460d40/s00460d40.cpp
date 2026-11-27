// 0x00460d40: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004604f0/s004604f0.cpp, src/game/SPBake/SPEditorExportUtilities.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13(int, int, int);
};

extern "C" unsigned char g_013eb8a4[];
extern "C" unsigned char g_01486114[];
extern "C" unsigned char g_015d3e8c[];
extern "C" unsigned char g_015d3e90[];
extern "C" unsigned char g_015d3e94[];
extern "C" void __cdecl FUN_0040cf10(...);
struct C_0041eb80 { void FUN_0041eb80(); };
struct C_0041ef20 { void FUN_0041ef20(unsigned int); };
struct C_00429360 { void FUN_00429360(unsigned int); };
struct C_00432de0 { int FUN_00432de0(); };
struct C_00453540 { int FUN_00453540(); };
struct C_00526430 { int FUN_00526430(); };
extern "C" int __cdecl FUN_0067de30(...);
struct C_006a1710 { void FUN_006a1710(unsigned int); };
struct C_006a1c40 { int FUN_006a1c40(); };
extern "C" void __cdecl FUN_007573a0(...);
extern "C" int __cdecl FUN_0079ab90(...);
struct C_007a0ee0 { void FUN_007a0ee0(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00f473a0(...);
#pragma pack(push, 1)
struct Fr0_00460d40 {
    int dead0[42];
};
#pragma pack(pop)

// @ 0x00460d40
extern "C" void __cdecl FUN_00460d40(int a4, int a8, int a12, int a16, int a20, int a24, int a28)
{
    Fr0_00460d40 fb;
    (*((int*)((char*)&fb + 128))) = *(int*)g_015d3e8c;
    (*((int*)((char*)&fb + 132))) = *(int*)g_015d3e90;
    (*((int*)((char*)&fb + 136))) = *(int*)g_015d3e94;
    (*((float*)((char*)&fb + 140))) = (float)*(float*)g_01486114;
    FUN_0040cf10((unsigned int)a8, (unsigned int)108983984, (unsigned int)(int)(int)((float*)((char*)&fb + 140)));
    (*((int*)((char*)&fb + 60))) = (int)(int)FUN_0079ab90((unsigned int)1, (unsigned int)0, (unsigned int)(int)((int*)((char*)&fb + 128)), (unsigned int)4);
    (*((int*)((char*)&fb + 144))) = (*((int*)((char*)&fb + 60)));
    if ((*((int*)((char*)&fb + 144))) != 0) {
        (*((int*)((char*)&fb + 64))) = (*((int*)((char*)&fb + 144)));
        (*((int*)((char*)&fb + 8))) = (int)(int)((int)*(int*)((char*)(*((int*)((char*)&fb + 64))) + 4) + 1);
        *(int*)((char*)(*((int*)((char*)&fb + 64))) + 4) = (int)(int)((int)*(int*)((char*)(*((int*)((char*)&fb + 64))) + 4) + 1);
    }
    (*((int*)((char*)&fb + 148))) = 0;
    (*((int*)((char*)&fb + 152))) = 0;
    (*((int*)((char*)&fb + 156))) = 0;
    ((C_00429360*)(int)((int*)((char*)&fb + 160)))->FUN_00429360((unsigned int)(int)((int*)((char*)&fb + 87)));
    ((C_007a0ee0*)(*((int*)((char*)&fb + 144))))->FUN_007a0ee0((unsigned int)a12, (unsigned int)(int)((int*)((char*)&fb + 148)));
    (*((int*)((char*)&fb + 104))) = 0;
    (*((int*)((char*)&fb + 108))) = 0;
    (*((int*)((char*)&fb + 112))) = 0;
    ((C_00429360*)(int)((int*)((char*)&fb + 116)))->FUN_00429360((unsigned int)(int)((int*)((char*)&fb + 86)));
    (*((int*)((char*)&fb + 96))) = 0;
    (*((int*)((char*)&fb + 100))) = ((*((int*)((char*)&fb + 152))) - (*((int*)((char*)&fb + 148)))) / 20;
    for (; (unsigned int)(*((int*)((char*)&fb + 96))) < (unsigned int)(*((int*)((char*)&fb + 100))); (*((int*)((char*)&fb + 96))) = (*((int*)((char*)&fb + 96))) + 1) {
        (*((int*)((char*)&fb + 88))) = 0;
        (*((int*)((char*)&fb + 56))) = (*((int*)((char*)&fb + 96))) * 20 + (*((int*)((char*)&fb + 148)));
        (*((int*)((char*)&fb + 92))) = (int)(int)((int)((int)*(int*)((char*)(*((int*)((char*)&fb + 56))) + 4) - (int)*(int*)(char*)(*((int*)((char*)&fb + 56)))) >> 3);
        for (; (unsigned int)(*((int*)((char*)&fb + 88))) < (unsigned int)(*((int*)((char*)&fb + 92))); (*((int*)((char*)&fb + 88))) = (*((int*)((char*)&fb + 88))) + 1) {
            (*((int*)((char*)&fb + 52))) = (*((int*)((char*)&fb + 96))) * 20 + (*((int*)((char*)&fb + 148)));
            ((C_0041ef20*)(int)((int*)((char*)&fb + 104)))->FUN_0041ef20((unsigned int)(int)((int)*(int*)(char*)(*((int*)((char*)&fb + 52))) + ((*((int*)((char*)&fb + 88))) << 3)));
        }
    }
    (*((int*)((char*)&fb + 80))) = (int)(int)FUN_00f473a0((unsigned int)56, (unsigned int)(int)g_013eb8a4, (unsigned int)0, (unsigned int)0, (unsigned int)0, (unsigned int)0);
    if ((*((int*)((char*)&fb + 80))) != 0) {
        (*((int*)((char*)&fb + 4))) = ((C_006a1c40*)(*((int*)((char*)&fb + 80))))->FUN_006a1c40();
    } else {
        (*((int*)((char*)&fb + 4))) = 0;
    }
    (*((int*)((char*)&fb + 124))) = (*((int*)((char*)&fb + 4)));
    ((C_006a1710*)(*((int*)((char*)&fb + 124))))->FUN_006a1710((unsigned int)a8);
    (*((int*)((char*)&fb + 0))) = (int)FUN_0067de30();
    ((il2c_vc0*)(*((int*)((char*)&fb + 0))))->s13((*((int*)((char*)&fb + 124))), a16, a20);
    if ((int)(unsigned char)((C_00526430*)(int)((int*)((char*)&fb + 104)))->FUN_00526430() == 0) {
        FUN_007573a0((unsigned int)a4, (unsigned int)(int)((int*)((char*)&fb + 104)), (unsigned int)a16, (unsigned int)a20, (unsigned int)a24, (unsigned int)0, (unsigned int)(*((int*)((char*)&fb + 124))), (unsigned int)0, (unsigned int)0, (unsigned int)0, (unsigned int)0, (unsigned int)a28);
    }
    ((C_0041eb80*)(int)((int*)((char*)&fb + 104)))->FUN_0041eb80();
    ((C_00432de0*)(int)((int*)((char*)&fb + 148)))->FUN_00432de0();
    if ((*((int*)((char*)&fb + 144))) != 0) {
        ((C_00453540*)(*((int*)((char*)&fb + 144))))->FUN_00453540();
    }
    return;
}
