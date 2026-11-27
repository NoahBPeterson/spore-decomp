// 0x005650b0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s005646b0/s005646b0.cpp.

struct C_00422c50 { void FUN_00422c50(); };
struct C_004769b0 { void FUN_004769b0(unsigned int, unsigned int); };
struct C_00564f50 { int FUN_00564f50(); };
struct C_005659e0 { void FUN_005659e0(unsigned int, unsigned int, unsigned int); };
struct C_00565df0 { void FUN_00565df0(unsigned int); };
struct C_00565f50 { void FUN_00565f50(unsigned int); };
struct C_005673e0 { void FUN_005673e0(unsigned int); };
extern "C" void __cdecl FUN_00567400(...);
#pragma pack(push, 1)
struct Fr0_005650b0 {
    int dead0[19];
    int v_l112;
    int v_l108;
    int v_l104;
    int v_l100;
    int v_l96;
    int v_l92;
    int v_l88;
    int dead1[8];
    int v_l52[2];
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
struct Fr1_005650b0 {
    int dead0[1];
};
#pragma pack(pop)
__forceinline bool il2c_cc_ne(int a, int b) { return a != b; }


struct D_005650b0 { void FUN_005650b0(int a4, int a8, int a12, int a16); };
// @ 0x005650b0
void D_005650b0::FUN_005650b0(int a4, int a8, int a12, int a16)
{
    Fr0_005650b0 fb;
    Fr1_005650b0 fa;
    ((C_005659e0*)a16)->FUN_005659e0((unsigned int)(int)&fb.v_l16, (unsigned int)a8, (unsigned int)a12);
    ((C_005673e0*)(int)&fb.v_l8)->FUN_005673e0((unsigned int)(int)&fb.v_l16);
    for (; (int)(unsigned char)il2c_cc_ne(fb.v_l8, fb.v_l12) != 0; ((C_00422c50*)(int)&fb.v_l8)->FUN_00422c50()) {
        fb.v_l36 = ((C_00564f50*)(int)&fb.v_l8)->FUN_00564f50() + 4;
        fb.v_l20 = (int)(int)*(int*)(char*)fb.v_l36;
        fb.v_l28 = (int)(int)*(int*)((char*)fb.v_l36 + 4);
        fb.v_l32 = (int)(int)*(int*)(char*)a4;
        fb.v_l24 = (int)(int)*(int*)((char*)a4 + 4);
        fb.v_l88 = (int)this + 348;
        ((C_004769b0*)fb.v_l88)->FUN_004769b0((unsigned int)(int)*(int*)(char*)fb.v_l88, (unsigned int)(int)*(int*)((char*)fb.v_l88 + 4));
        fb.v_l92 = (int)(int)((int)((int)*(int*)((char*)fb.v_l36 + 4) - (int)*(int*)(char*)fb.v_l36) >> 2);
        ((C_00565f50*)((int)this + 348))->FUN_00565f50((unsigned int)(int)((int)((int)((int)*(int*)((char*)a4 + 4) - (int)*(int*)(char*)a4) >> 2) + fb.v_l92));
        fb.v_l96 = (int)(int)*(int*)((char*)(int)this + 348);
        fb.v_l44 = (int)this + 348;
        fb.v_l40 = fb.v_l96;
        fb.v_l100 = (int)(int)*(int*)((char*)fb.v_l36 + 4);
        fb.v_l104 = (int)(int)*(int*)(char*)fb.v_l36;
        fb.v_l108 = (int)(int)*(int*)((char*)a4 + 4);
        fb.v_l112 = (int)(int)*(int*)(char*)a4;
        FUN_00567400((unsigned int)(int)&fb.v_l52, (unsigned int)fb.v_l112, (unsigned int)fb.v_l108, (unsigned int)fb.v_l104, (unsigned int)fb.v_l100, (unsigned int)fb.v_l44, (unsigned int)fb.v_l40);
        ((C_00565df0*)a4)->FUN_00565df0((unsigned int)((int)this + 348));
    }
    return;
}
