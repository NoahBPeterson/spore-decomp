// 0x0045b3e0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0045aa70/s0045aa70.cpp.

struct C_0045b6f0 { void FUN_0045b6f0(unsigned int); };
#pragma pack(push, 1)
struct Fr0_0045b3e0 {
    int v_l48;
    int v_l44;
    int dead0[2];
    int v_l32;
    int v_l28;
    int v_l24;
    int v_l20;
    int v_l16;
    int v_l12;
    int v_l8;
};
#pragma pack(pop)


struct D_0045b3e0 { int FUN_0045b3e0(int a4, int a8, int a12); };
// @ 0x0045b3e0
int D_0045b3e0::FUN_0045b3e0(int a4, int a8, int a12)
{
    Fr0_0045b3e0 fb;
    fb.v_l32 = a12;
    fb.v_l28 = a8;
    fb.v_l16 = fb.v_l28;
    fb.v_l12 = fb.v_l32;
    fb.v_l16 = (int)(int)*(int*)((char*)fb.v_l16 + 8);
    while (fb.v_l16 == 0) {
        fb.v_l12 = fb.v_l12 + 4;
        fb.v_l16 = (int)(int)*(int*)(char*)fb.v_l12;
    }
    fb.v_l20 = a8;
    fb.v_l8 = (int)(int)*(int*)(char*)a12;
    if (fb.v_l8 == fb.v_l20) {
        *(int*)(char*)a12 = (int)(int)*(int*)((char*)fb.v_l8 + 8);
    } else {
        fb.v_l24 = (int)(int)*(int*)((char*)fb.v_l8 + 8);
        while (fb.v_l24 != fb.v_l20) {
            fb.v_l8 = fb.v_l24;
            fb.v_l24 = (int)(int)*(int*)((char*)fb.v_l8 + 8);
        }
        *(int*)((char*)fb.v_l8 + 8) = (int)(int)*(int*)((char*)fb.v_l24 + 8);
    }
    ((C_0045b6f0*)(int)this)->FUN_0045b6f0((unsigned int)fb.v_l20);
    *(int*)((char*)(int)this + 12) = (int)(int)((int)*(int*)((char*)(int)this + 12) - 1);
    fb.v_l48 = fb.v_l12;
    fb.v_l44 = fb.v_l16;
    *(int*)(char*)a4 = fb.v_l44;
    *(int*)((char*)a4 + 4) = fb.v_l48;
    return a4;
}
