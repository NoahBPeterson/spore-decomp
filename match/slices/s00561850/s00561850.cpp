// 0x00561850: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s005609a0/s005609a0.cpp, src/game/SPEditors/SPObjectTemplateDB.cpp.

struct C_0050d440 { void FUN_0050d440(unsigned int); };
struct C_00553fb0 { int FUN_00553fb0(); };
struct C_00564960 { void FUN_00564960(unsigned int, unsigned int); };
#pragma pack(push, 1)
struct Fr0_00561850 {
    int dead0[12];
    int v_l132;
    int v_l128;
    int dead1[6];
    int v_l100;
    int v_l96;
    int v_l92;
    int v_l88;
    int v_l84;
    int v_l80;
    int v_l76;
    int v_l72;
    int v_l68;
    int v_l64;
    int v_l60;
    int v_l56;
    unsigned char v_l52;
    char dead2;
    char dead3;
    char dead4;
    int v_l48;
    int v_l44;
    int dead5[4];
    int v_l24;
    unsigned char v_l20;
    char dead6;
    char dead7;
    char dead8;
    int v_l16;
    int v_l12;
    int v_l8;
};
struct Fr1_00561850 {
    int dead0[1];
};
#pragma pack(pop)


struct D_00561850 { void FUN_00561850(int a4); };
// @ 0x00561850
void D_00561850::FUN_00561850(int a4)
{
    Fr0_00561850 fb;
    Fr1_00561850 fa;
    fb.v_l16 = (int)(int)(a4 * 80 + (int)*(int*)((char*)(int)this + 20));
    ((C_0050d440*)(int)&fb.v_l48)->FUN_0050d440((unsigned int)(fb.v_l16 + 44));
    fb.v_l8 = fb.v_l48;
    fb.v_l12 = fb.v_l44;
    for (; fb.v_l8 != fb.v_l12; fb.v_l8 = fb.v_l8 + 4) {
        fb.v_l60 = (int)(int)*(int*)(char*)fb.v_l8;
        fb.v_l100 = 1;
        fb.v_l96 = fb.v_l60;
        fb.v_l76 = fb.v_l96;
        fb.v_l72 = fb.v_l100;
        fb.v_l68 = fb.v_l76;
        fb.v_l64 = fb.v_l72;
        ((C_00564960*)((int)this + 172))->FUN_00564960((unsigned int)(int)&fb.v_l56, (unsigned int)(int)&fb.v_l68);
        if ((int)fb.v_l52 == 0) {
            *(int*)((char*)fb.v_l56 + 4) = (int)(int)((int)*(int*)((char*)fb.v_l56 + 4) + 1);
        }
    }
    fb.v_l132 = 1;
    fb.v_l128 = (int)(int)*(int*)((char*)fb.v_l16 + 4);
    fb.v_l92 = fb.v_l128;
    fb.v_l88 = fb.v_l132;
    fb.v_l84 = fb.v_l92;
    fb.v_l80 = fb.v_l88;
    ((C_00564960*)((int)this + 220))->FUN_00564960((unsigned int)(int)&fb.v_l24, (unsigned int)(int)&fb.v_l84);
    if ((int)fb.v_l20 == 0) {
        *(int*)((char*)fb.v_l24 + 4) = (int)(int)((int)*(int*)((char*)fb.v_l24 + 4) + 1);
    }
    ((C_00553fb0*)(int)&fb.v_l48)->FUN_00553fb0();
    return;
}
