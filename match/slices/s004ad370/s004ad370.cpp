// 0x004ad370: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/SPEditorManipulationUtilities.cpp, match/slices/s004ac610/s004ac610.cpp.

struct C_00451e20 { void FUN_00451e20(unsigned int); };
struct C_00453540 { void FUN_00453540(); };
struct C_004b91c0 { int FUN_004b91c0(); };
struct C_004b94a0 { int FUN_004b94a0(unsigned int); };
#pragma pack(push, 1)
struct il2c_pi_4_int_8919c3cc { char pad[4]; int x; __forceinline int f() { return (int)((int)x++ + 1); } };
#pragma pack(pop)


struct D_004ad370 { void FUN_004ad370(int a4); };
// @ 0x004ad370
// @ 0x004ad370
void D_004ad370::FUN_004ad370(int a4)
{
    int v_l16_i;
    int v_l12_40;
    int v_l8;
    int v_l20;
    int dead_0[3];
    int v_l48_i;
    int v_l44;
    int v_l40_w;
    int v_l36;
    int v_l52;
    v_l36 = (int)this + 48;
    if (a4 != (int)*(int*)(char*)v_l36) {
        v_l20 = (int)(int)*(int*)(char*)v_l36;
        if (a4 != 0) {
            ((il2c_pi_4_int_8919c3cc*)((char*)a4))->f();
        }
        *(int*)(char*)v_l36 = a4;
        if (v_l20 != 0) {
            ((C_00453540*)v_l20)->FUN_00453540();
        }
    }
    v_l8 = ((C_004b91c0*)a4)->FUN_004b91c0();
    v_l16_i = 0;
    v_l40_w = (int)this + 24;
    v_l12_40 = (int)(int)((int)((int)*(int*)((char*)v_l40_w + 4) - (int)*(int*)(char*)v_l40_w) >> 2);
    for (; v_l16_i < v_l12_40; v_l16_i = v_l16_i + 1) {
        v_l44 = (int)(int)((int)*(int*)((char*)(int)this + 24) + (v_l16_i << 2));
        v_l48_i = (int)(int)*(int*)(char*)v_l44;
        ((C_00451e20*)v_l48_i)->FUN_00451e20((unsigned int)v_l8);
    }
    v_l52 = (int)(int)*(int*)((char*)(int)this + 48);
    ((C_004b94a0*)v_l52)->FUN_004b94a0((unsigned int)(int)this);
    return;
}
