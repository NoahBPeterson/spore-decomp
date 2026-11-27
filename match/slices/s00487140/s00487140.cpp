// 0x00487140: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00486910/s00486910.cpp, src/game/SPBake/_at_00480000.cpp.

extern "C" int __cdecl FUN_0041db10(...);
struct C_0048c720 { int FUN_0048c720(unsigned int); };
#pragma pack(push, 1)
struct Fr0_00487140 {
    int dead0[2];
    int v_l84;
    int v_l80;
    int v_l76;
    int v_l72;
    int v_l68;
    int v_l64;
    int v_l60;
    int v_l56;
    int v_l52;
    int v_l48;
    int v_l44[3];
    int v_l32[3];
    int v_l20[3];
    int v_l8;
};
struct Fr1_00487140 {
    int dead0[1];
};
#pragma pack(pop)


struct D_00487140 { void FUN_00487140(int a4); };
// @ 0x00487140
void D_00487140::FUN_00487140(int a4)
{
    Fr0_00487140 fb;
    Fr1_00487140 fa;
    fb.v_l48 = (int)(int)*(int*)((char*)(int)this + 12);
    fb.v_l52 = (int)(int)*(int*)((char*)(int)this + 8);
    fb.v_l56 = fb.v_l52;
    L487161:;
    if (fb.v_l56 != fb.v_l48) {
        if ((int)*(int*)(char*)fb.v_l56 != a4) {
            fb.v_l56 = fb.v_l56 + 4;
            goto L487161;
        }
    }
    fb.v_l8 = fb.v_l56;
    fb.v_l60 = (int)(int)*(int*)((char*)(int)this + 12);
    if (fb.v_l8 != fb.v_l60) {
        fb.v_l68 = (int)(int)FUN_0041db10((unsigned int)(int)&fb.v_l20, (unsigned int)(a4 + 28), (unsigned int)((int)this + 28));
        fb.v_l64 = a4 + 64;
        *(float*)(char*)fb.v_l64 = *(float*)(char*)fb.v_l68;
        *(float*)((char*)fb.v_l64 + 4) = *(float*)((char*)fb.v_l68 + 4);
        *(float*)((char*)fb.v_l64 + 8) = *(float*)((char*)fb.v_l68 + 8);
        fb.v_l76 = (int)(int)FUN_0041db10((unsigned int)(int)&fb.v_l32, (unsigned int)(a4 + 40), (unsigned int)((int)this + 40));
        fb.v_l72 = a4 + 76;
        *(float*)(char*)fb.v_l72 = *(float*)(char*)fb.v_l76;
        *(float*)((char*)fb.v_l72 + 4) = *(float*)((char*)fb.v_l76 + 4);
        *(float*)((char*)fb.v_l72 + 8) = *(float*)((char*)fb.v_l76 + 8);
        fb.v_l84 = (int)(int)FUN_0041db10((unsigned int)(int)&fb.v_l44, (unsigned int)(a4 + 52), (unsigned int)((int)this + 52));
        fb.v_l80 = a4 + 88;
        *(float*)(char*)fb.v_l80 = *(float*)(char*)fb.v_l84;
        *(float*)((char*)fb.v_l80 + 4) = *(float*)((char*)fb.v_l84 + 4);
        *(float*)((char*)fb.v_l80 + 8) = *(float*)((char*)fb.v_l84 + 8);
        ((C_0048c720*)((int)this + 8))->FUN_0048c720((unsigned int)fb.v_l8);
    }
    return;
}
