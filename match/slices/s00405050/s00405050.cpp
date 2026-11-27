// 0x00405050: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00405000/s00405000.cpp, src/game/SPGonzago/SPCinematicActions.cpp.

struct C_00421d70 { void FUN_00421d70(); };
struct C_00421dd0 { void FUN_00421dd0(); };
struct C_00421e30 { void FUN_00421e30(); };
struct C_00837fa0 { void FUN_00837fa0(); };
extern "C" int __cdecl FUN_00f47380(...);
#pragma pack(push, 1)
struct Fr0_00405050 {
    int v_l140;
    int v_l136;
    int v_l132;
    int v_l128;
    int v_l124;
    int v_l120;
    int v_l116;
    int v_l112;
    int v_l108;
    int v_l104;
    int v_l100;
    int dead0[19];
    int v_l20;
    int v_l16;
    int v_l12;
    int v_l8;
};
#pragma pack(pop)


struct D_00405050 { void FUN_00405050(); };
// @ 0x00405050
void D_00405050::FUN_00405050()
{
    Fr0_00405050 fb;
    fb.v_l20 = (int)this + 184;
    if ((int)((int)*(int*)((char*)fb.v_l20 + 8) - (int)*(int*)(char*)fb.v_l20) > 1) {
        fb.v_l16 = (int)(int)((int)*(int*)((char*)fb.v_l20 + 8) - (int)*(int*)(char*)fb.v_l20);
        fb.v_l12 = (int)(int)*(int*)(char*)fb.v_l20;
        if (fb.v_l12 != 0) {
            fb.v_l8 = fb.v_l12;
            FUN_00f47380((unsigned int)fb.v_l8);
        }
    }
    ((C_00837fa0*)((int)this + 116))->FUN_00837fa0();
    ((C_00421e30*)((int)this + 88))->FUN_00421e30();
    ((C_00421dd0*)((int)this + 68))->FUN_00421dd0();
    ((C_00421d70*)((int)this + 48))->FUN_00421d70();
    fb.v_l112 = (int)this + 32;
    if ((int)((int)*(int*)((char*)fb.v_l112 + 8) - (int)*(int*)(char*)fb.v_l112) > 1) {
        fb.v_l108 = (int)(int)((int)*(int*)((char*)fb.v_l112 + 8) - (int)*(int*)(char*)fb.v_l112);
        fb.v_l104 = (int)(int)*(int*)(char*)fb.v_l112;
        if (fb.v_l104 != 0) {
            fb.v_l100 = fb.v_l104;
            FUN_00f47380((unsigned int)fb.v_l100);
        }
    }
    fb.v_l128 = (int)this + 16;
    if ((int)((int)*(int*)((char*)fb.v_l128 + 8) - (int)*(int*)(char*)fb.v_l128) > 1) {
        fb.v_l124 = (int)(int)((int)*(int*)((char*)fb.v_l128 + 8) - (int)*(int*)(char*)fb.v_l128);
        fb.v_l120 = (int)(int)*(int*)(char*)fb.v_l128;
        if (fb.v_l120 != 0) {
            fb.v_l116 = fb.v_l120;
            FUN_00f47380((unsigned int)fb.v_l116);
        }
    }
    if ((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) > 1) {
        fb.v_l140 = (int)(int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this);
        fb.v_l136 = (int)(int)*(int*)(char*)(int)this;
        if (fb.v_l136 != 0) {
            fb.v_l132 = fb.v_l136;
            FUN_00f47380((unsigned int)fb.v_l132);
        }
    }
    return;
}
