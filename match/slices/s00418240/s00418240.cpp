// 0x00418240: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00417d60/s00417d60.cpp, src/game/SPBake/SPEditorBaker.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual int s1();
};

struct C_00420920 { void FUN_00420920(); };
struct C_00420ab0 { void FUN_00420ab0(); };
struct C_00426220 { void FUN_00426220(); };
struct C_00427f70 { void FUN_00427f70(); };
struct C_004c0b80 { void FUN_004c0b80(); };
#pragma pack(push, 1)
struct Fr0_00418240 {
    int v_l156;
    int v_l152;
    int dead0[3];
    int v_l136;
    int v_l132;
    int dead1[3];
    int v_l116;
    int v_l112;
    int dead2[3];
    int v_l96;
    int v_l92;
    int dead3[3];
    int v_l76;
    int v_l72;
    int dead4[3];
    int v_l56;
    int v_l52;
    int dead5[3];
    int v_l36;
    int dead6[2];
    int v_l24;
    int v_l20;
    int dead7[3];
};
#pragma pack(pop)


struct D_00418240 { void FUN_00418240(); };
// @ 0x00418240
void D_00418240::FUN_00418240()
{
    Fr0_00418240 fb;
    ((C_00420ab0*)((int)this + 3240))->FUN_00420ab0();
    fb.v_l24 = (int)this + 2960;
    fb.v_l20 = (int)(int)*(int*)(char*)fb.v_l24;
    for (; (unsigned int)fb.v_l20 < (unsigned int)*(int*)((char*)fb.v_l24 + 4); fb.v_l20 = fb.v_l20 + 4) {
    }
    ((C_004c0b80*)fb.v_l24)->FUN_004c0b80();
    ((C_00420920*)((int)this + 2680))->FUN_00420920();
    fb.v_l52 = (int)this + 2400;
    fb.v_l36 = (int)(int)*(int*)(char*)fb.v_l52;
    for (; (unsigned int)fb.v_l36 < (unsigned int)*(int*)((char*)fb.v_l52 + 4); fb.v_l36 = fb.v_l36 + 4) {
    }
    ((C_004c0b80*)fb.v_l52)->FUN_004c0b80();
    fb.v_l72 = (int)this + 2284;
    fb.v_l56 = (int)(int)*(int*)(char*)fb.v_l72;
    for (; (unsigned int)fb.v_l56 < (unsigned int)*(int*)((char*)fb.v_l72 + 4); fb.v_l56 = fb.v_l56 + 4) {
    }
    ((C_004c0b80*)fb.v_l72)->FUN_004c0b80();
    fb.v_l92 = (int)this + 1364;
    fb.v_l76 = (int)(int)*(int*)(char*)fb.v_l92;
    for (; (unsigned int)fb.v_l76 < (unsigned int)*(int*)((char*)fb.v_l92 + 4); fb.v_l76 = fb.v_l76 + 56) {
    }
    ((C_00426220*)fb.v_l92)->FUN_00426220();
    fb.v_l112 = (int)this + 1148;
    fb.v_l96 = (int)(int)*(int*)(char*)fb.v_l112;
    for (; (unsigned int)fb.v_l96 < (unsigned int)*(int*)((char*)fb.v_l112 + 4); fb.v_l96 = fb.v_l96 + 12) {
    }
    ((C_00427f70*)fb.v_l112)->FUN_00427f70();
    fb.v_l132 = (int)this + 228;
    fb.v_l116 = (int)(int)*(int*)(char*)fb.v_l132;
    for (; (unsigned int)fb.v_l116 < (unsigned int)*(int*)((char*)fb.v_l132 + 4); fb.v_l116 = fb.v_l116 + 56) {
    }
    ((C_00426220*)fb.v_l132)->FUN_00426220();
    fb.v_l152 = (int)this + 12;
    fb.v_l136 = (int)(int)*(int*)(char*)fb.v_l152;
    for (; (unsigned int)fb.v_l136 < (unsigned int)*(int*)((char*)fb.v_l152 + 4); fb.v_l136 = fb.v_l136 + 12) {
    }
    ((C_00427f70*)fb.v_l152)->FUN_00427f70();
    fb.v_l156 = (int)this + 8;
    if ((int)*(int*)(char*)fb.v_l156 != 0) {
        ((il2c_vc0*)(int)*(int*)(char*)fb.v_l156)->s1();
    }
    return;
}
