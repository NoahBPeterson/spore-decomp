// 0x0045c0f0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0045bc20/s0045bc20.cpp.

#include <string.h>
struct C_0045d790 { void FUN_0045d790(unsigned int); };
extern "C" int __cdecl FUN_0045da80(...);
extern "C" int __cdecl FUN_0045daa0(...);
#pragma pack(push, 1)
struct Fr0_0045c0f0 {
    int v_l260;
    int v_l256;
    int v_l252;
    int v_l248;
    int v_l244;
    int v_l240;
    int v_l236;
    int v_l232;
    int v_l228;
    int v_l224;
    int v_l220;
    int v_l216;
    int v_l212[16];
    int v_l148[16];
    int v_l84[16];
    int v_l20;
    int v_l16;
    int v_l12;
    int v_l8;
};
struct Fr1_0045c0f0 {
    int v_l264;
};
#pragma pack(pop)
struct S16 { int m0; int m1; int m2; int m3; int m4; int m5; int m6; int m7; int m8; int m9; int m10; int m11; int m12; int m13; int m14; int m15; };


struct D_0045c0f0 { void FUN_0045c0f0(); };
// @ 0x0045c0f0
void D_0045c0f0::FUN_0045c0f0()
{
    Fr0_0045c0f0 fb;
    Fr1_0045c0f0 fa;
    ((C_0045d790*)((int)this + 276))->FUN_0045d790((unsigned int)((int)this + 256));
    ((C_0045d790*)((int)this + 316))->FUN_0045d790((unsigned int)((int)this + 296));
    fb.v_l12 = 0;
    fb.v_l216 = (int)this + 276;
    fb.v_l8 = (int)(int)((int)((int)*(int*)((char*)fb.v_l216 + 4) - (int)*(int*)(char*)fb.v_l216) >> 6);
    for (; (unsigned int)fb.v_l12 < (unsigned int)fb.v_l8; fb.v_l12 = fb.v_l12 + 1) {
        fb.v_l220 = (int)(int)((fb.v_l12 << 6) + (int)*(int*)((char*)(int)this + 276));
        fb.v_l224 = (int)(int)((fb.v_l12 << 6) + (int)*(int*)((char*)(int)this + 276));
        fb.v_l228 = (int)(int)FUN_0045da80((unsigned int)(int)&fb.v_l84, (unsigned int)fb.v_l220);
        *(S16*)fb.v_l224 = *(S16*)fb.v_l228;
        fb.v_l232 = (int)(int)((fb.v_l12 << 6) + (int)*(int*)((char*)(int)this + 316));
        fb.v_l236 = (int)(int)((fb.v_l12 << 6) + (int)*(int*)((char*)(int)this + 316));
        fb.v_l240 = (int)(int)FUN_0045da80((unsigned int)(int)&fb.v_l148, (unsigned int)fb.v_l232);
        *(S16*)fb.v_l236 = *(S16*)fb.v_l240;
    }
    fb.v_l20 = 0;
    fb.v_l244 = (int)this + 296;
    fb.v_l16 = (int)(int)((int)((int)*(int*)((char*)fb.v_l244 + 4) - (int)*(int*)(char*)fb.v_l244) >> 6);
    for (; (unsigned int)fb.v_l20 < (unsigned int)fb.v_l16; fb.v_l20 = fb.v_l20 + 1) {
        if ((int)*(int*)((char*)(int)*(int*)((char*)(int)this + 236) + fb.v_l20 * 4) >= 0) {
            fb.v_l248 = (int)(int)((int)*(int*)((char*)(int)this + 236) + (fb.v_l20 << 2));
            fb.v_l252 = (int)(int)((int)((int)*(int*)(char*)fb.v_l248 << 6) + (int)*(int*)((char*)(int)this + 316));
            fb.v_l256 = (int)(int)((fb.v_l20 << 6) + (int)*(int*)((char*)(int)this + 296));
            fb.v_l260 = (int)(int)((fb.v_l20 << 6) + (int)*(int*)((char*)(int)this + 296));
            fa.v_l264 = (int)(int)FUN_0045daa0((unsigned int)(int)&fb.v_l212, (unsigned int)fb.v_l256, (unsigned int)fb.v_l252);
            *(S16*)fb.v_l260 = *(S16*)fa.v_l264;
        }
    }
    return;
}
