// 0x004c29c0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004c2100/s004c2100.cpp, src/game/SPGonzago/SPCastingManager.cpp.

extern "C" unsigned char g_013eb430[];
extern "C" unsigned char g_013ebb38[];
struct C_004292a0 { int FUN_004292a0(); };
struct C_0042f7e0 { void FUN_0042f7e0(unsigned int); };
struct C_004c1c80 { void FUN_004c1c80(unsigned int); };
struct C_004c2ad0 { void FUN_004c2ad0(unsigned int); };
extern "C" int __cdecl FUN_00f473a0(...);
extern "C" void __cdecl FUN_011e0744(...);
#pragma pack(push, 1)
struct Fr0_004c29c0 {
    int dead0[2];
    int v_l60;
    int v_l56;
    int v_l52;
    int dead1[4];
    int v_l32;
    int v_l28;
    int v_l24[5];
};
struct Fr1_004c29c0 {
    int dead0[1];
};
#pragma pack(pop)


struct D_004c29c0 { void FUN_004c29c0(int a4); };
// @ 0x004c29c0
void D_004c29c0::FUN_004c29c0(int a4)
{
    Fr0_004c29c0 fb;
    Fr1_004c29c0 fa;
    if (a4 == -1 || (unsigned int)a4 <= (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) >> 1)) {
        if ((unsigned int)a4 < (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) >> 1)) {
            ((C_004c1c80*)(int)this)->FUN_004c1c80((unsigned int)a4);
        }
        ((C_0042f7e0*)(int)&fb.v_l24)->FUN_0042f7e0((unsigned int)(int)this);
        ((C_004c2ad0*)(int)this)->FUN_004c2ad0((unsigned int)(int)&fb.v_l24);
        ((C_004292a0*)(int)&fb.v_l24)->FUN_004292a0();
    } else {
        fb.v_l52 = (int)(int)FUN_00f473a0((unsigned int)(a4 << 1), (unsigned int)(int)g_013eb430, (unsigned int)0, (unsigned int)0, (unsigned int)(int)g_013ebb38, (unsigned int)209);
        fb.v_l32 = fb.v_l52;
        fb.v_l28 = fb.v_l32;
        fb.v_l60 = (int)(int)*(int*)((char*)(int)this + 4);
        fb.v_l56 = (int)(int)*(int*)(char*)(int)this;
        FUN_011e0744((unsigned int)fb.v_l32, (unsigned int)fb.v_l56, (unsigned int)(fb.v_l60 - fb.v_l56 >> 1 << 1));
        fb.v_l28 = fb.v_l32 + (fb.v_l60 - fb.v_l56 >> 1 << 1);
        *(unsigned short*)(char*)fb.v_l28 = (unsigned short)(unsigned short)0;
        ((C_004292a0*)(int)this)->FUN_004292a0();
        *(int*)(char*)(int)this = fb.v_l32;
        *(int*)((char*)(int)this + 4) = fb.v_l28;
        *(int*)((char*)(int)this + 8) = fb.v_l32 + (a4 << 1);
    }
    return;
}
