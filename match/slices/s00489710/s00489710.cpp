// 0x00489710: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/SPEditorManipulationUtilities.cpp, src/game/SPBake/_at_00480000.cpp, match/slices/s00489530/s00489530.cpp.

struct C_00488a50 { int FUN_00488a50(); };
struct C_004893f0 { void FUN_004893f0(unsigned int, float); };
struct C_00489490 { void FUN_00489490(unsigned int, float); };
struct C_00489530 { void FUN_00489530(unsigned int, unsigned int); };
extern "C" void __cdecl FUN_0049d1f0(unsigned int, float, unsigned int, unsigned int);
template<class T> __forceinline T il2c_k(T v) { return v; }


struct D_00489710 { void FUN_00489710(int a4, int a8); };
// @ 0x00489710
void D_00489710::FUN_00489710(int a4, int a8)
{
    if ((int)(unsigned char)a8 == 0) {
        FUN_0049d1f0((unsigned int)(int)*(int*)((char*)(int)this + 20), *(float*)((char*)(int)*(int*)((char*)(int)this + 24) + (il2c_k(0) << 2) + 40), (unsigned int)0, (unsigned int)0);
    }
    ((C_00489530*)(int)this)->FUN_00489530((unsigned int)(int)*(int*)((char*)(int)this + 24), (unsigned int)a4);
    ((C_004893f0*)(int)this)->FUN_004893f0((unsigned int)(int)*(int*)((char*)(int)this + 24), *(float*)((char*)(int)*(int*)((char*)(int)this + 24) + (il2c_k(0) << 2) + 40));
    ((C_00489490*)(int)this)->FUN_00489490((unsigned int)(int)*(int*)((char*)(int)this + 24), *(float*)((char*)(int)*(int*)((char*)(int)this + 24) + (il2c_k(0) << 2) + 52));
    ((C_00488a50*)(int)this)->FUN_00488a50();
    return;
}
