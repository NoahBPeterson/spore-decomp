// 0x004f8880: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004f85b0/s004f85b0.cpp.

extern "C" unsigned char g_016c8b44[];
struct C_004fc610 { void FUN_004fc610(unsigned int); };
struct C_00928a30 { int FUN_00928a30(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int); };
#pragma pack(push, 1)
struct Fr0_004f8880 {
    int v_l40;
    int v_l36;
    int v_l32;
    int dead0[3];
    int v_l16;
    int v_l12;
    int v_l8;
};
#pragma pack(pop)


struct D_004f8880 { int FUN_004f8880(int a4, int a8); };
// @ 0x004f8880
int D_004f8880::FUN_004f8880(int a4, int a8)
{
    Fr0_004f8880 fb;
    *(int*)&a4 = a4 + 16;
    *(int*)&a4 = a4 + 15 & -16;
    fb.v_l8 = (int)(int)*(int*)((char*)(int)this + 240);
    if ((unsigned int)a4 > (unsigned int)*(int*)((char*)(int)this + 244)) {
        fb.v_l16 = 32768;
        fb.v_l12 = (int)(int)((unsigned int)a4 > (unsigned int)32768 ? a4 : 32768);
        fb.v_l8 = (int)((C_00928a30*)*(int*)g_016c8b44)->FUN_00928a30((unsigned int)fb.v_l12, (unsigned int)16, (unsigned int)0, (unsigned int)0, (unsigned int)0, (unsigned int)0, (unsigned int)0, (unsigned int)0);
        ((C_004fc610*)((int)this + 88))->FUN_004fc610((unsigned int)(int)&fb.v_l8);
        *(int*)((char*)(int)this + 240) = fb.v_l8;
        *(int*)((char*)(int)this + 244) = fb.v_l12;
    }
    *(int*)((char*)(int)this + 240) = (int)(int)((int)*(int*)((char*)(int)this + 240) + a4);
    *(int*)((char*)(int)this + 244) = (int)(int)((int)*(int*)((char*)(int)this + 244) - a4);
    fb.v_l40 = fb.v_l8;
    fb.v_l36 = fb.v_l40 + 15 & -16;
    fb.v_l32 = fb.v_l36;
    *(int*)(char*)fb.v_l32 = -690563370;
    *(int*)((char*)fb.v_l32 + 4) = fb.v_l40;
    *(int*)((char*)fb.v_l32 + 8) = a8;
    *(int*)((char*)fb.v_l32 + 12) = 690563369;
    fb.v_l32 = fb.v_l32 + 16;
    return fb.v_l32;
}
