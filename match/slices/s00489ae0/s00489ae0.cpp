// 0x00489ae0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00489530/s00489530.cpp, src/game/SPBake/SPEditorManipulationUtilities.cpp.

struct C_00489c60 { int FUN_00489c60(unsigned int, unsigned int); };
struct C_0048afc0 { void FUN_0048afc0(unsigned int); };
struct C_0048bdd0 { void FUN_0048bdd0(); };
#pragma pack(push, 1)
struct Fr0_00489ae0 {
    int v_l28;
    int v_l24;
    int v_l20;
    int v_l16;
    int v_l12;
    int v_l8;
};
#pragma pack(pop)


struct D_00489ae0 { void FUN_00489ae0(); };
// @ 0x00489ae0
void D_00489ae0::FUN_00489ae0()
{
    Fr0_00489ae0 fb;
    if ((int)*(int*)((char*)(int)this + 32) != 0) {
        fb.v_l8 = 0;
        fb.v_l24 = (int)(int)((int)*(int*)((char*)(int)this + 24) + 8);
        fb.v_l12 = (int)(int)((int)((int)*(int*)((char*)fb.v_l24 + 4) - (int)*(int*)(char*)fb.v_l24) >> 2);
        for (; fb.v_l8 < fb.v_l12; fb.v_l8 = fb.v_l8 + 1) {
            ((C_0048afc0*)(int)this)->FUN_0048afc0((unsigned int)(int)*(int*)((char*)(int)*(int*)((char*)(int)*(int*)((char*)(int)this + 24) + 8) + fb.v_l8 * 4));
        }
        ((C_0048bdd0*)(int)this)->FUN_0048bdd0();
        fb.v_l16 = 0;
        fb.v_l28 = (int)(int)((int)*(int*)((char*)(int)this + 24) + 8);
        fb.v_l20 = (int)(int)((int)((int)*(int*)((char*)fb.v_l28 + 4) - (int)*(int*)(char*)fb.v_l28) >> 2);
        for (; fb.v_l16 < fb.v_l20; fb.v_l16 = fb.v_l16 + 1) {
            ((C_0048afc0*)(int)this)->FUN_0048afc0((unsigned int)(int)*(int*)((char*)(int)*(int*)((char*)(int)*(int*)((char*)(int)this + 24) + 8) + fb.v_l16 * 4));
        }
        ((C_00489c60*)(int)this)->FUN_00489c60((unsigned int)(int)*(int*)((char*)(int)this + 24), (unsigned int)1);
    }
    return;
}
