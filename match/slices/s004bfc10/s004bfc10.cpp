// 0x004bfc10: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/SPEditorResourceFactory.cpp, match/slices/s004bf430/s004bf430.cpp.

extern __declspec(thread) int tls_4;
struct C_004bfc40 { int FUN_004bfc40(unsigned int, unsigned int); };

// @ 0x004bfc10
extern "C" void __cdecl FUN_004bfc10(int a4)
{
    int v_l8;
    int dead_0[12];
    v_l8 = *(int*)&tls_4;
    ((C_004bfc40*)v_l8)->FUN_004bfc40((unsigned int)a4, (unsigned int)4);
    return;
}
