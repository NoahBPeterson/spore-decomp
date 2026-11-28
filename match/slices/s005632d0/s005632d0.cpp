// 0x005632d0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s005628d0/s005628d0.cpp.

struct C_0041e4d0 { void FUN_0041e4d0(unsigned int); };
struct C_004e19a0 { void FUN_004e19a0(unsigned int); };
struct C_0050f740 { void FUN_0050f740(unsigned int, unsigned int); };
struct C_00526430 { int FUN_00526430(); };
struct C_00565740 { void FUN_00565740(unsigned int); };
struct C_00565760 { void FUN_00565760(unsigned int); };
struct C_00565780 { int FUN_00565780(); };
struct C_005658b0 { int FUN_005658b0(); };
struct C_005677f0 { void FUN_005677f0(); };
__forceinline bool il2c_cc_ne(int a, int b) { return a != b; }


struct D_005632d0 { int FUN_005632d0(int a4, int a8); };
// @ 0x005632d0
// @ 0x005632d0
int D_005632d0::FUN_005632d0(int a4, int a8)
{
    int dead_0_15[3];
    int dead_1_12[3];
    int v_l20;
    int v_l36;
    int dead_2[6];
    int v_l64;
    int dead_3[2];
    ((C_0050f740*)a8)->FUN_0050f740((unsigned int)(int)*(int*)(char*)a8, (unsigned int)(int)*(int*)((char*)a8 + 4));
    ((C_0041e4d0*)a8)->FUN_0041e4d0((unsigned int)((C_00565780*)a4)->FUN_00565780());
    ((C_00565740*)a4)->FUN_00565740((unsigned int)(int)&v_l36);
    ((C_00565760*)a4)->FUN_00565760((unsigned int)(int)&v_l20);
    for (; (int)(unsigned char)il2c_cc_ne(v_l36, v_l20) != 0; ((C_005677f0*)(int)&v_l36)->FUN_005677f0()) {
        v_l64 = (int)(int)*(int*)((char*)((C_005658b0*)(int)&v_l36)->FUN_005658b0() + 4);
        ((C_004e19a0*)a8)->FUN_004e19a0((unsigned int)(int)(v_l64 * 80 + (int)*(int*)((char*)(int)this + 20)));
    }
    return !((int)(int)(unsigned char)((C_00526430*)a8)->FUN_00526430());
}
