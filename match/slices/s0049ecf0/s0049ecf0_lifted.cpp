// 0x0049ecf0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0049ecf0/s0049ecf0.cpp, src/game/SPBake/SPEditorManipulationUtilities.cpp.

#include <string.h>
struct C_004098a0 { void FUN_004098a0(unsigned int); };
struct C_0041cb40 { void FUN_0041cb40(unsigned int); };
extern "C" int __cdecl FUN_0041daf0(...);
extern "C" int __cdecl FUN_0041db10(...);
extern "C" int __cdecl FUN_0041dc10(...);
extern "C" int __cdecl FUN_0041de20(...);
extern "C" int __cdecl FUN_0041ded0(...);
struct C_00448e90 { int FUN_00448e90(unsigned int, unsigned int); };
struct C_00449420 { void FUN_00449420(unsigned int, unsigned int); };
#pragma pack(push, 1)
struct Fr0_0049ecf0 {
    int v_l388;
    int v_l384;
    int v_l380;
    int v_l376;
    int v_l372;
    int v_l368;
    int v_l364;
    int v_l360;
    int v_l356;
    int v_l352;
    int v_l348;
    int v_l344;
    int v_l340;
    int v_l336[9];
    int v_l300[3];
    int v_l288[3];
    int v_l276[3];
    int v_l264[9];
    int v_l228[9];
    int v_l192[9];
    float v_l156;
    float v_l152;
    float v_l148;
    float v_l144;
    float v_l140;
    float v_l136;
    int v_l132;
    int v_l128[9];
    int v_l92[3];
    int v_l80;
    int v_l76[9];
    int v_l40[9];
};
#pragma pack(pop)
struct S9 { int m0; int m1; int m2; int m3; int m4; int m5; int m6; int m7; int m8; };

// @ 0x0049ecf0
extern "C" void __cdecl FUN_0049ecf0(int a4, int a8, int a12, int a16, int a20, int a24)
{
    Fr0_0049ecf0 fb;
    ((C_0041cb40*)(int)&fb.v_l40)->FUN_0041cb40((unsigned int)(a4 + 168));
    ((C_004098a0*)(int)&fb.v_l92)->FUN_004098a0((unsigned int)(a4 + 72));
    ((C_0041cb40*)(int)&fb.v_l128)->FUN_0041cb40((unsigned int)(a4 + 168));
    fb.v_l340 = (int)(int)FUN_0041ded0((unsigned int)(int)&fb.v_l228, (unsigned int)(int)&fb.v_l128);
    *(S9*)(int)&fb.v_l128 = *(S9*)fb.v_l340;
    fb.v_l344 = (int)(int)FUN_0041de20((unsigned int)(int)&fb.v_l264, (unsigned int)(int)&fb.v_l128, (unsigned int)(int)&a24);
    *(S9*)(int)&fb.v_l76 = *(S9*)fb.v_l344;
    ((C_00448e90*)a4)->FUN_00448e90((unsigned int)(int)&a12, (unsigned int)1);
    ((C_00449420*)a4)->FUN_00449420((unsigned int)(int)&a24, (unsigned int)1);
    fb.v_l80 = (int)(int)((int)((int)*(int*)((char*)a8 + 4) - (int)*(int*)(char*)a8) >> 2);
    fb.v_l132 = 0;
    for (; fb.v_l132 < fb.v_l80; fb.v_l132 = fb.v_l132 + 1) {
        fb.v_l348 = (int)(int)((int)*(int*)(char*)a8 + (fb.v_l132 << 2));
        fb.v_l352 = (int)(int)*(int*)(char*)fb.v_l348;
        fb.v_l356 = (int)(int)FUN_0041db10((unsigned int)(int)&fb.v_l276, (unsigned int)(fb.v_l352 + 72), (unsigned int)(int)&fb.v_l92);
        fb.v_l144 = *(float*)(char*)fb.v_l356;
        fb.v_l140 = *(float*)((char*)fb.v_l356 + 4);
        fb.v_l136 = *(float*)((char*)fb.v_l356 + 8);
        fb.v_l360 = (int)(int)FUN_0041dc10((unsigned int)(int)&fb.v_l300, (unsigned int)(a4 + 72), (unsigned int)(int)FUN_0041daf0((unsigned int)(int)&fb.v_l288, (unsigned int)(int)(int)&fb.v_l144, (unsigned int)(int)&fb.v_l76));
        fb.v_l156 = *(float*)(char*)fb.v_l360;
        fb.v_l152 = *(float*)((char*)fb.v_l360 + 4);
        fb.v_l148 = *(float*)((char*)fb.v_l360 + 8);
        fb.v_l364 = (int)(int)((int)*(int*)(char*)a8 + (fb.v_l132 << 2));
        fb.v_l368 = (int)(int)*(int*)(char*)fb.v_l364;
        fb.v_l372 = (int)(int)FUN_0041de20((unsigned int)(int)&fb.v_l336, (unsigned int)(fb.v_l368 + 168), (unsigned int)(int)&fb.v_l76);
        *(S9*)(int)&fb.v_l192 = *(S9*)fb.v_l372;
        fb.v_l376 = (int)(int)((int)*(int*)(char*)a8 + (fb.v_l132 << 2));
        fb.v_l380 = (int)(int)*(int*)(char*)fb.v_l376;
        ((C_00449420*)fb.v_l380)->FUN_00449420((unsigned int)(int)&fb.v_l192, (unsigned int)1);
        fb.v_l384 = (int)(int)((int)*(int*)(char*)a8 + (fb.v_l132 << 2));
        fb.v_l388 = (int)(int)*(int*)(char*)fb.v_l384;
        ((C_00448e90*)fb.v_l388)->FUN_00448e90((unsigned int)(int)(int)&fb.v_l156, (unsigned int)1);
    }
    return;
}
