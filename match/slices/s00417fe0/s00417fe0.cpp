// 0x00417fe0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00417d60/s00417d60.cpp, src/game/SPBake/SPEditorBaker.cpp.

struct C_0040f360 { void FUN_0040f360(); };
struct C_00418240 { void FUN_00418240(); };
struct C_0041e090 { void FUN_0041e090(); };
struct C_0041e5d0 { void FUN_0041e5d0(); };
struct C_0041eb80 { void FUN_0041eb80(); };
struct C_0041f270 { void FUN_0041f270(); };
struct C_00421230 { void FUN_00421230(); };
struct C_004237d0 { void FUN_004237d0(); };
struct C_00426c70 { void FUN_00426c70(); };
struct C_00453540 { void FUN_00453540(); };
struct C_004748c0 { void FUN_004748c0(); };
struct C_00690120 { int FUN_00690120(); };
#pragma pack(push, 1)
struct Fr0_00417fe0 {
    int dead0[10];
    int v_l60;
    int v_l56;
    int dead1[4];
    int v_l36;
    int v_l32;
    int dead2[6];
};
struct Fr1_00417fe0 {
    int v_l104;
};
#pragma pack(pop)


struct D_00417fe0 { void FUN_00417fe0(); };
// @ 0x00417fe0
void D_00417fe0::FUN_00417fe0()
{
    Fr0_00417fe0 fb;
    Fr1_00417fe0 fa;
    ((C_00418240*)((int)this + 252))->FUN_00418240();
    ((C_004748c0*)((int)this + 224))->FUN_004748c0();
    ((C_004237d0*)((int)this + 208))->FUN_004237d0();
    fb.v_l32 = (int)this + 196;
    if ((int)*(int*)(char*)fb.v_l32 != 0) {
        ((C_0040f360*)(int)*(int*)(char*)fb.v_l32)->FUN_0040f360();
    }
    fb.v_l36 = (int)this + 192;
    if ((int)*(int*)(char*)fb.v_l36 != 0) {
        ((C_0040f360*)(int)*(int*)(char*)fb.v_l36)->FUN_0040f360();
    }
    ((C_0041eb80*)((int)this + 172))->FUN_0041eb80();
    ((C_00421230*)((int)this + 152))->FUN_00421230();
    fb.v_l60 = (int)this + 128;
    fb.v_l56 = (int)(int)*(int*)(char*)fb.v_l60;
    for (; (unsigned int)fb.v_l56 < (unsigned int)*(int*)((char*)fb.v_l60 + 4); fb.v_l56 = fb.v_l56 + 8) {
    }
    ((C_00426c70*)fb.v_l60)->FUN_00426c70();
    ((C_0041eb80*)((int)this + 108))->FUN_0041eb80();
    ((C_0041f270*)((int)this + 88))->FUN_0041f270();
    ((C_0041e090*)((int)this + 68))->FUN_0041e090();
    ((C_0041e5d0*)((int)this + 48))->FUN_0041e5d0();
    ((C_0041eb80*)((int)this + 28))->FUN_0041eb80();
    ((C_0041eb80*)((int)this + 8))->FUN_0041eb80();
    fa.v_l104 = (int)this + 4;
    if ((int)*(int*)(char*)fa.v_l104 != 0) {
        ((C_00453540*)(int)((int)*(int*)(char*)fa.v_l104 + 4))->FUN_00453540();
    }
    if ((int)*(int*)(char*)(int)this != 0) {
        ((C_00690120*)(int)*(int*)(char*)(int)this)->FUN_00690120();
    }
    return;
}
