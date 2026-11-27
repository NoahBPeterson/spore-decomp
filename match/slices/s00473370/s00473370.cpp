// 0x00473370: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00472b80/s00472b80.cpp, src/game/SPBake/SPEditorExportUtilities.cpp.

struct C_0040f360 { int FUN_0040f360(); };
struct C_00475880 { int FUN_00475880(); };
struct C_00475da0 { int FUN_00475da0(unsigned int, unsigned int); };
struct C_00478e00 { void FUN_00478e00(unsigned int, unsigned int, unsigned int); };
#pragma pack(push, 1)
struct Fr0_00473370 {
    int dead0[10];
    int v_l716;
    int dead1[2];
    int v_l704;
    int v_l700;
    int v_l696;
    int dead2[5];
    int v_l672[166];
    int v_l8;
};
#pragma pack(pop)


struct D_00473370 { void FUN_00473370(int a4); };
// @ 0x00473370
void D_00473370::FUN_00473370(int a4)
{
    Fr0_00473370 fb;
    if ((unsigned int)a4 > (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 668)) {
        fb.v_l704 = ((C_00475880*)(int)&fb.v_l672)->FUN_00475880();
        fb.v_l700 = (int)(int)(a4 - (int)((int)(int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 668));
        fb.v_l696 = (int)(int)*(int*)((char*)(int)this + 4);
        ((C_00478e00*)(int)this)->FUN_00478e00((unsigned int)fb.v_l696, (unsigned int)fb.v_l700, (unsigned int)fb.v_l704);
        fb.v_l716 = (int)&fb.v_l8;
        if ((int)*(int*)(char*)fb.v_l716 != 0) {
            ((C_0040f360*)(int)*(int*)(char*)fb.v_l716)->FUN_0040f360();
        }
    } else {
        ((C_00475da0*)(int)this)->FUN_00475da0((unsigned int)(int)(a4 * 668 + (int)*(int*)(char*)(int)this), (unsigned int)(int)*(int*)((char*)(int)this + 4));
    }
    return;
}
