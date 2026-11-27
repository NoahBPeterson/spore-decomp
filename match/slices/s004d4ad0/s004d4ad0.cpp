// 0x004d4ad0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004d44e0/s004d44e0.cpp, src/game/SPBake/SPEditorSpeciesManager.cpp.

extern "C" unsigned char g_01601760[];
struct C_00454860 { void FUN_00454860(unsigned int); };
struct C_004746a0 { int FUN_004746a0(); };
struct C_004769b0 { void FUN_004769b0(unsigned int, unsigned int); };
struct C_004e07d0 { void FUN_004e07d0(); };
struct C_004e1bf0 { int FUN_004e1bf0(); };
struct C_00540470 { void FUN_00540470(unsigned int); };
struct C_00a68fb0 { int FUN_00a68fb0(unsigned int); };
#pragma pack(push, 1)
struct Fr0_004d4ad0 {
    int dead0[70];
};
struct Fr1_004d4ad0 {
    int dead0[1];
};
#pragma pack(pop)


struct D_004d4ad0 { void FUN_004d4ad0(); };
// @ 0x004d4ad0
void D_004d4ad0::FUN_004d4ad0()
{
    Fr0_004d4ad0 fb;
    Fr1_004d4ad0 fa;
    ((C_00540470*)(int)((int*)((char*)&fb + 168)))->FUN_00540470((unsigned int)(int)((int*)((char*)&fb + 135)));
    ((C_004e07d0*)(int)((int*)((char*)&fb + 168)))->FUN_004e07d0();
    (*((int*)((char*)&fb + 120))) = (int)this + 1520;
    (*((int*)((char*)&fb + 124))) = (int)this + 1516;
    (*((int*)((char*)&fb + 128))) = (int)(int)((unsigned int)(int)*(int*)(char*)(*((int*)((char*)&fb + 124))) < (unsigned int)*(int*)(char*)(*((int*)((char*)&fb + 120))) ? (*((int*)((char*)&fb + 120))) : (*((int*)((char*)&fb + 124))));
    (*((int*)((char*)&fb + 108))) = (int)this + 1508;
    (*((int*)((char*)&fb + 112))) = (int)this + 1512;
    (*((int*)((char*)&fb + 116))) = (int)(int)((unsigned int)(int)*(int*)(char*)(*((int*)((char*)&fb + 112))) < (unsigned int)*(int*)(char*)(*((int*)((char*)&fb + 108))) ? (*((int*)((char*)&fb + 108))) : (*((int*)((char*)&fb + 112))));
    (*((int*)((char*)&fb + 104))) = (int)(int)((unsigned int)(int)*(int*)(char*)(*((int*)((char*)&fb + 116))) < (unsigned int)*(int*)(char*)(*((int*)((char*)&fb + 128))) ? (*((int*)((char*)&fb + 128))) : (*((int*)((char*)&fb + 116))));
    (*((int*)((char*)&fb + 276))) = (int)(int)*(int*)(char*)(*((int*)((char*)&fb + 104)));
    (*((int*)((char*)&fb + 92))) = (int)this + 1500;
    (*((int*)((char*)&fb + 96))) = (int)this + 1504;
    (*((int*)((char*)&fb + 100))) = (int)(int)((unsigned int)(int)*(int*)(char*)(*((int*)((char*)&fb + 96))) < (unsigned int)*(int*)(char*)(*((int*)((char*)&fb + 92))) ? (*((int*)((char*)&fb + 92))) : (*((int*)((char*)&fb + 96))));
    (*((int*)((char*)&fb + 80))) = (int)this + 1496;
    (*((int*)((char*)&fb + 84))) = (int)this + 1492;
    (*((int*)((char*)&fb + 88))) = (int)(int)((unsigned int)(int)*(int*)(char*)(*((int*)((char*)&fb + 84))) < (unsigned int)*(int*)(char*)(*((int*)((char*)&fb + 80))) ? (*((int*)((char*)&fb + 80))) : (*((int*)((char*)&fb + 84))));
    (*((int*)((char*)&fb + 76))) = (int)(int)((unsigned int)(int)*(int*)(char*)(*((int*)((char*)&fb + 88))) < (unsigned int)*(int*)(char*)(*((int*)((char*)&fb + 100))) ? (*((int*)((char*)&fb + 100))) : (*((int*)((char*)&fb + 88))));
    (*((int*)((char*)&fb + 272))) = (int)(int)*(int*)(char*)(*((int*)((char*)&fb + 76)));
    if ((unsigned int)(*((int*)((char*)&fb + 272))) > (unsigned int)(*((int*)((char*)&fb + 276)))) {
        *(int*)((char*)(int)this + 1716) = 2;
    } else {
        if ((unsigned int)(*((int*)((char*)&fb + 276))) > (unsigned int)(*((int*)((char*)&fb + 272)))) {
            *(int*)((char*)(int)this + 1716) = 1;
        }
    }
    if ((int)*(int*)((char*)(int)this + 1512) == (*((int*)((char*)&fb + 276)))) {
        (*((int*)((char*)&fb + 164))) = 34;
        ((C_00454860*)(int)((int*)((char*)&fb + 168)))->FUN_00454860((unsigned int)(int)((int*)((char*)&fb + 164)));
    }
    if ((int)*(int*)((char*)(int)this + 1508) == (*((int*)((char*)&fb + 276)))) {
        (*((int*)((char*)&fb + 160))) = 37;
        ((C_00454860*)(int)((int*)((char*)&fb + 168)))->FUN_00454860((unsigned int)(int)((int*)((char*)&fb + 160)));
    }
    if ((int)*(int*)((char*)(int)this + 1516) == (*((int*)((char*)&fb + 276)))) {
        (*((int*)((char*)&fb + 156))) = 36;
        ((C_00454860*)(int)((int*)((char*)&fb + 168)))->FUN_00454860((unsigned int)(int)((int*)((char*)&fb + 156)));
    }
    if ((int)*(int*)((char*)(int)this + 1520) == (*((int*)((char*)&fb + 276)))) {
        (*((int*)((char*)&fb + 152))) = 35;
        ((C_00454860*)(int)((int*)((char*)&fb + 168)))->FUN_00454860((unsigned int)(int)((int*)((char*)&fb + 152)));
    }
    (*((int*)((char*)&fb + 40))) = (*((int*)((char*)&fb + 172))) - (*((int*)((char*)&fb + 168))) >> 2;
    (*((int*)((char*)&fb + 36))) = (int)((C_00a68fb0*)(int)g_01601760)->FUN_00a68fb0((unsigned int)((*((int*)((char*)&fb + 40))) - 1));
    *(int*)((char*)(int)this + 1568) = (int)(int)*(int*)((char*)(*((int*)((char*)&fb + 168))) + (*((int*)((char*)&fb + 36))) * 4);
    ((C_004769b0*)(int)((int*)((char*)&fb + 168)))->FUN_004769b0((unsigned int)(*((int*)((char*)&fb + 168))), (unsigned int)(*((int*)((char*)&fb + 172))));
    if ((int)*(int*)((char*)(int)this + 1492) == (*((int*)((char*)&fb + 276)))) {
        (*((int*)((char*)&fb + 148))) = 30;
        ((C_00454860*)(int)((int*)((char*)&fb + 168)))->FUN_00454860((unsigned int)(int)((int*)((char*)&fb + 148)));
    }
    if ((int)*(int*)((char*)(int)this + 1500) == (*((int*)((char*)&fb + 276)))) {
        (*((int*)((char*)&fb + 144))) = 32;
        ((C_00454860*)(int)((int*)((char*)&fb + 168)))->FUN_00454860((unsigned int)(int)((int*)((char*)&fb + 144)));
    }
    if ((int)*(int*)((char*)(int)this + 1496) == (*((int*)((char*)&fb + 276)))) {
        (*((int*)((char*)&fb + 140))) = 31;
        ((C_00454860*)(int)((int*)((char*)&fb + 168)))->FUN_00454860((unsigned int)(int)((int*)((char*)&fb + 140)));
    }
    if ((int)*(int*)((char*)(int)this + 1504) == (*((int*)((char*)&fb + 276)))) {
        (*((int*)((char*)&fb + 136))) = 33;
        ((C_00454860*)(int)((int*)((char*)&fb + 168)))->FUN_00454860((unsigned int)(int)((int*)((char*)&fb + 136)));
    }
    if ((unsigned int)((*((int*)((char*)&fb + 172))) - (*((int*)((char*)&fb + 168))) >> 2) > (unsigned int)0) {
        (*((int*)((char*)&fb + 0))) = ((C_004746a0*)(int)((int*)((char*)&fb + 168)))->FUN_004746a0() - 1;
        (*((int*)((char*)&fa + 0))) = (int)((C_00a68fb0*)(int)g_01601760)->FUN_00a68fb0((unsigned int)(*((int*)((char*)&fb + 0))));
        *(int*)((char*)(int)this + 1572) = (int)(int)*(int*)((char*)(*((int*)((char*)&fb + 168))) + (*((int*)((char*)&fa + 0))) * 4);
    } else {
        *(int*)((char*)(int)this + 1572) = 30;
    }
    ((C_004e1bf0*)(int)((int*)((char*)&fb + 168)))->FUN_004e1bf0();
    return;
}
