// 0x004b5440: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004b4930/s004b4930.cpp, src/game/SPBake/SPEditorPaintTheme.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
};

struct C_00425990 { int FUN_00425990(); };
extern "C" void __cdecl FUN_00f47380(...);
#pragma pack(push, 1)
struct Fr0_004b5440 {
    int dead0[3];
    int v_l12;
    int v_l8;
};
#pragma pack(pop)
__forceinline void il2c_d_FUN_00f47380(int p, int fl) { if (fl & 1) FUN_00f47380((unsigned int)(p)); }


struct D_004b5440 { void FUN_004b5440(); };
// @ 0x004b5440
void D_004b5440::FUN_004b5440()
{
    Fr0_004b5440 fb;
    fb.v_l12 = (int)(int)*(int*)((char*)(int)this + 4);
    fb.v_l8 = (int)(int)*(int*)(char*)(int)this;
    for (; (unsigned int)fb.v_l8 < (unsigned int)fb.v_l12; fb.v_l8 = fb.v_l8 + 4) {
        if ((int)*(int*)(char*)fb.v_l8 != 0) {
            ((il2c_vc0*)(int)*(int*)(char*)fb.v_l8)->s1();
        }
        il2c_d_FUN_00f47380(fb.v_l8, 0);
    }
    ((C_00425990*)(int)this)->FUN_00425990();
    return;
}
