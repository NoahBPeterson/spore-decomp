// 0x0045f140: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0045edf0/s0045edf0.cpp.

extern "C" unsigned char g_013eb430[];
extern "C" unsigned char g_013ebb38[];
struct C_00429300 { int FUN_00429300(); };
struct C_0045ebd0 { void FUN_0045ebd0(unsigned int); };
struct C_0045f240 { void FUN_0045f240(unsigned int); };
struct C_0045f2a0 { void FUN_0045f2a0(unsigned int); };
extern "C" int __cdecl FUN_00f473a0(...);
extern "C" void __cdecl FUN_011e0744(...);
#pragma pack(push, 1)
struct Fr0_0045f140 {
    int dead0[2];
    int v_l60;
    int v_l56;
    int v_l52;
    int dead1[4];
    int v_l32;
    int v_l28;
    int v_l24[5];
};
struct Fr1_0045f140 {
    int dead0[1];
};
#pragma pack(pop)


struct D_0045f140 { void FUN_0045f140(int a4); };
// @ 0x0045f140
void D_0045f140::FUN_0045f140(int a4)
{
    Fr0_0045f140 fb;
    Fr1_0045f140 fa;
    if (a4 == -1 || (unsigned int)a4 <= (unsigned int)(int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this)) {
        if ((unsigned int)a4 < (unsigned int)(int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this)) {
            ((C_0045ebd0*)(int)this)->FUN_0045ebd0((unsigned int)a4);
        }
        ((C_0045f240*)(int)&fb.v_l24)->FUN_0045f240((unsigned int)(int)this);
        ((C_0045f2a0*)(int)this)->FUN_0045f2a0((unsigned int)(int)&fb.v_l24);
        ((C_00429300*)(int)&fb.v_l24)->FUN_00429300();
    } else {
        fb.v_l52 = (int)(int)FUN_00f473a0((unsigned int)a4, (unsigned int)(int)g_013eb430, (unsigned int)0, (unsigned int)0, (unsigned int)(int)g_013ebb38, (unsigned int)209);
        fb.v_l32 = fb.v_l52;
        fb.v_l28 = fb.v_l32;
        fb.v_l60 = (int)(int)*(int*)((char*)(int)this + 4);
        fb.v_l56 = (int)(int)*(int*)(char*)(int)this;
        FUN_011e0744((unsigned int)fb.v_l32, (unsigned int)fb.v_l56, (unsigned int)(fb.v_l60 - fb.v_l56));
        fb.v_l28 = fb.v_l60 - fb.v_l56 + fb.v_l32;
        *(unsigned char*)(char*)fb.v_l28 = (unsigned char)0;
        ((C_00429300*)(int)this)->FUN_00429300();
        *(int*)(char*)(int)this = fb.v_l32;
        *(int*)((char*)(int)this + 4) = fb.v_l28;
        *(int*)((char*)(int)this + 8) = fb.v_l32 + a4;
    }
    return;
}
