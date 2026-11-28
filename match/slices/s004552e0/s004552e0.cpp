// 0x004552e0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00454330/s00454330.cpp.

struct C_00456360 { int FUN_00456360(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00456410(...);
__forceinline bool il2c_cc_l(int a, int b) { return a < b; }


struct D_004552e0 { int FUN_004552e0(int a4, int a8); };
// @ 0x004552e0
int D_004552e0::FUN_004552e0(int a4, int a8)
{
    int v_l24;
    int v_l20_q;
    int v_l16_i;
    int v_l12_40;
    int v_l8;
    int dead_0[7];
    v_l12_40 = (int)(int)*(int*)((char*)(int)this + 4);
    if (a4 != v_l12_40 && (int)(unsigned char)il2c_cc_l((int)(int)*(int*)(char*)a8, (int)*(int*)(char*)a4) != 0) {
        v_l16_i = (int)(int)*(int*)(char*)(int)this;
        v_l8 = (int)(int)FUN_00456410((unsigned int)v_l16_i, (unsigned int)a4, (unsigned int)a8, (unsigned int)(int)*(unsigned char*)((char*)(int)this + 280));
    } else {
        v_l20_q = (int)(int)*(int*)((char*)(int)this + 4);
        v_l8 = (int)(int)FUN_00456410((unsigned int)a4, (unsigned int)v_l20_q, (unsigned int)a8, (unsigned int)(int)*(unsigned char*)((char*)(int)this + 280));
    }
    v_l24 = (int)(int)*(int*)((char*)(int)this + 4);
    if (v_l8 == v_l24 || (int)(unsigned char)il2c_cc_l((int)(int)*(int*)(char*)a8, (int)*(int*)(char*)v_l8) != 0) {
        v_l8 = (int)((C_00456360*)(int)this)->FUN_00456360((unsigned int)v_l8, (unsigned int)a8);
    }
    return v_l8;
}
