// 0x00419690: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00419000/s00419000.cpp, src/game/SPBake/SPEditorBaker.cpp.

struct C_0041e3b0 { void FUN_0041e3b0(unsigned int); };
struct C_0041ee90 { void FUN_0041ee90(unsigned int); };
struct C_0041efb0 { void FUN_0041efb0(unsigned int); };
struct C_0041f1e0 { void FUN_0041f1e0(unsigned int); };
struct C_00421bf0 { void FUN_00421bf0(unsigned int); };
struct C_00422a50 { int FUN_00422a50(unsigned int); };
#pragma pack(push, 1)
struct Fr0_00419690 {
    int dead0[45];
    int v_l24;
    int v_l20;
    int v_l16;
    int v_l12;
    int v_l8;
};
struct Fr1_00419690 {
    int dead0[1];
};
#pragma pack(pop)


struct D_00419690 { void FUN_00419690(int a4); };
// @ 0x00419690
void D_00419690::FUN_00419690(int a4)
{
    Fr0_00419690 fb;
    Fr1_00419690 fa;
    *(int*)((char*)(int)this + 44) = 0;
    fb.v_l12 = (int)(int)*(int*)((char*)(int)this + 36);
    fb.v_l16 = (int)this + 48;
    fb.v_l20 = (int)(int)*(int*)((char*)fb.v_l12 + 8);
    fb.v_l24 = fb.v_l20 + 152;
    fb.v_l8 = (int)(int)((int)((int)*(int*)((char*)fb.v_l24 + 4) - (int)*(int*)(char*)fb.v_l24) / 140);
    ((C_0041ee90*)fb.v_l16)->FUN_0041ee90((unsigned int)fb.v_l8);
    ((C_0041efb0*)(fb.v_l16 + 20))->FUN_0041efb0((unsigned int)(fb.v_l12 + 144));
    ((C_0041e3b0*)(fb.v_l16 + 40))->FUN_0041e3b0((unsigned int)fb.v_l8);
    ((C_0041e3b0*)(fb.v_l16 + 60))->FUN_0041e3b0((unsigned int)fb.v_l8);
    ((C_0041ee90*)(fb.v_l16 + 80))->FUN_0041ee90((unsigned int)fb.v_l8);
    ((C_00421bf0*)(fb.v_l16 + 100))->FUN_00421bf0((unsigned int)fb.v_l8);
    ((C_0041f1e0*)(fb.v_l16 + 120))->FUN_0041f1e0((unsigned int)fb.v_l8);
    *(int*)((char*)a4 + 28) = 0;
    ((C_00422a50*)a4)->FUN_00422a50((unsigned int)(int)this);
    return;
}
