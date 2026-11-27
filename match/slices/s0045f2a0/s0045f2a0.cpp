// 0x0045f2a0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0045edf0/s0045edf0.cpp.

struct C_00429300 { int FUN_00429300(); };
struct C_0045f240 { void FUN_0045f240(unsigned int); };
struct C_0045f390 { void FUN_0045f390(unsigned int, unsigned int); };
#pragma pack(push, 1)
struct Fr0_0045f2a0 {
    int dead0[4];
    int v_l52;
    int v_l48;
    int v_l44;
    int v_l40;
    int v_l36;
    int v_l32;
    int v_l28;
    int v_l24;
    int v_l20;
    int dead1[3];
};
#pragma pack(pop)
__forceinline bool il2c_cc_e(int a, int b) { return a == b; }


struct D_0045f2a0 { void FUN_0045f2a0(int a4); };
// @ 0x0045f2a0
void D_0045f2a0::FUN_0045f2a0(int a4)
{
    Fr0_0045f2a0 fb;
    if ((int)(unsigned char)il2c_cc_e((int)this + 12, a4 + 12) != 0) {
        fb.v_l28 = (int)(int)*(int*)(char*)(int)this;
        *(int*)(char*)(int)this = (int)(int)*(int*)(char*)a4;
        *(int*)(char*)a4 = fb.v_l28;
        fb.v_l40 = a4 + 4;
        fb.v_l36 = (int)this + 4;
        fb.v_l32 = (int)(int)*(int*)(char*)fb.v_l36;
        *(int*)(char*)fb.v_l36 = (int)(int)*(int*)(char*)fb.v_l40;
        *(int*)(char*)fb.v_l40 = fb.v_l32;
        fb.v_l52 = a4 + 8;
        fb.v_l48 = (int)this + 8;
        fb.v_l44 = (int)(int)*(int*)(char*)fb.v_l48;
        *(int*)(char*)fb.v_l48 = (int)(int)*(int*)(char*)fb.v_l52;
        *(int*)(char*)fb.v_l52 = fb.v_l44;
    } else {
        ((C_0045f240*)(int)&fb.v_l24)->FUN_0045f240((unsigned int)(int)this);
        if (a4 != (int)this) {
            ((C_0045f390*)(int)this)->FUN_0045f390((unsigned int)(int)*(int*)(char*)a4, (unsigned int)(int)*(int*)((char*)a4 + 4));
        }
        if ((int)&fb.v_l24 != a4) {
            ((C_0045f390*)a4)->FUN_0045f390((unsigned int)fb.v_l24, (unsigned int)fb.v_l20);
        }
        ((C_00429300*)(int)&fb.v_l24)->FUN_00429300();
    }
    return;
}
