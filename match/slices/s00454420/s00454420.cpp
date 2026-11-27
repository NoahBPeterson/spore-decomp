// 0x00454420: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00454330/s00454330.cpp.

struct C_00440f60 { int FUN_00440f60(); };
struct C_00440ff0 { void FUN_00440ff0(unsigned int); };
struct C_004552e0 { int FUN_004552e0(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00456410(...);
#pragma pack(push, 1)
struct Fr0_00454420 {
    int dead0[6];
    int v_l84;
    int v_l80;
    int v_l76;
    int v_l72[7];
    int v_l44;
    int v_l40[8];
    int v_l8;
};
struct Fr1_00454420 {
    int v_l112;
};
#pragma pack(pop)
__forceinline bool il2c_cc_l(int a, int b) { return a < b; }


struct D_00454420 { int FUN_00454420(int a4); };
// @ 0x00454420
int D_00454420::FUN_00454420(int a4)
{
    Fr0_00454420 fb;
    Fr1_00454420 fa;
    fb.v_l76 = (int)(int)*(int*)((char*)(int)this + 4);
    fb.v_l80 = (int)(int)*(int*)(char*)(int)this;
    fb.v_l8 = (int)(int)FUN_00456410((unsigned int)fb.v_l80, (unsigned int)fb.v_l76, (unsigned int)a4, (unsigned int)(int)*(unsigned char*)((char*)(int)this + 280));
    fb.v_l84 = (int)(int)*(int*)((char*)(int)this + 4);
    if (fb.v_l8 == fb.v_l84 || (int)(unsigned char)il2c_cc_l((int)(int)*(int*)(char*)a4, (int)*(int*)(char*)fb.v_l8) != 0) {
        fa.v_l112 = ((C_00440f60*)(int)&fb.v_l72)->FUN_00440f60();
        fb.v_l44 = (int)(int)*(int*)(char*)a4;
        ((C_00440ff0*)(int)&fb.v_l40)->FUN_00440ff0((unsigned int)fa.v_l112);
        fb.v_l8 = (int)((C_004552e0*)(int)this)->FUN_004552e0((unsigned int)fb.v_l8, (unsigned int)(int)&fb.v_l44);
    }
    return fb.v_l8 + 4;
}
