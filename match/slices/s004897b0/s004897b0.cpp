// 0x004897b0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/SPEditorManipulationUtilities.cpp, src/game/SPBake/_at_00480000.cpp, match/slices/s00489530/s00489530.cpp.

struct C_004893f0 { void FUN_004893f0(unsigned int, float); };
struct C_00489490 { void FUN_00489490(unsigned int, float); };
struct C_00489640 { void FUN_00489640(unsigned int, float); };
extern "C" int __cdecl FUN_004961d0(...);
extern "C" void __cdecl FUN_0049d1f0(unsigned int, float, unsigned int, unsigned int);
template<class T> __forceinline T il2c_k(T v) { return v; }


struct D_004897b0 { void FUN_004897b0(int a4, int a8); };
// @ 0x004897b0
void D_004897b0::FUN_004897b0(int a4, int a8)
{
    int v_l16_i[3];
    int v_l20;
    if (a4 != 0) {
        if ((int)(unsigned char)a8 == 0) {
            v_l20 = a4 + 72;
            *(float*)&v_l16_i[0] = *(float*)(char*)v_l20;
            *(float*)&v_l16_i[1] = *(float*)((char*)v_l20 + 4);
            *(float*)&v_l16_i[2] = *(float*)((char*)v_l20 + 8);
            FUN_0049d1f0((unsigned int)(int)*(int*)((char*)(int)this + 20), *(float*)((char*)(int)&v_l16_i + (il2c_k(0) << 2)), (unsigned int)0, (unsigned int)0);
        }
        ((C_00489640*)(int)this)->FUN_00489640((unsigned int)(int)*(int*)((char*)(int)this + 24), *(float*)((char*)(int)*(int*)((char*)(int)this + 24) + (il2c_k(0) << 2) + 28));
        ((C_004893f0*)(int)this)->FUN_004893f0((unsigned int)(int)*(int*)((char*)(int)this + 24), *(float*)((char*)(int)*(int*)((char*)(int)this + 24) + (il2c_k(0) << 2) + 40));
        ((C_00489490*)(int)this)->FUN_00489490((unsigned int)(int)*(int*)((char*)(int)this + 24), *(float*)((char*)(int)*(int*)((char*)(int)this + 24) + (il2c_k(0) << 2) + 52));
        FUN_004961d0((unsigned int)(int)*(int*)((char*)(int)this + 20), (unsigned int)(int)this);
    }
    return;
}
