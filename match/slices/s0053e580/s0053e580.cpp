// 0x0053e580: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0053e120/s0053e120.cpp, match/slices/s0053f960/s0053f960.cpp.

struct C_005404a0 { int FUN_005404a0(unsigned int); };
struct C_005407a0 { void FUN_005407a0(unsigned int); };
struct C_00540950 { void FUN_00540950(unsigned int); };
extern "C" void __cdecl FUN_011e073e(...);
template<class T> __forceinline T il2c_k(T v) { return v; }


struct D_0053e580 { void FUN_0053e580(); };
// @ 0x0053e580
void D_0053e580::FUN_0053e580()
{
    int dead_0[14];
    int dead_1_21[5];
    int v_l64;
    int dead_2_d[5];
    int v_l88;
    int dead_3[12];
    int v_l112;
    ((C_005407a0*)((int)this + 32))->FUN_005407a0((unsigned int)16384);
    *(int*)((char*)(int)this + 52) = 0;
    *(int*)((char*)(int)this + 56) = 0;
    v_l64 = (int)this + 60;
    ((C_005407a0*)v_l64)->FUN_005407a0((unsigned int)16384);
    FUN_011e073e((unsigned int)(int)((il2c_k(0) << 3) + (int)*(int*)(char*)v_l64), (unsigned int)255, (unsigned int)131072);
    v_l88 = (int)this + 104;
    ((C_00540950*)v_l88)->FUN_00540950((unsigned int)32768);
    FUN_011e073e((unsigned int)(int)(il2c_k(0) * 12 + (int)*(int*)(char*)v_l88), (unsigned int)255, (unsigned int)393216);
    v_l112 = (int)this + 124;
    ((C_00540950*)v_l112)->FUN_00540950((unsigned int)32768);
    FUN_011e073e((unsigned int)(int)(il2c_k(0) * 12 + (int)*(int*)(char*)v_l112), (unsigned int)255, (unsigned int)393216);
    ((C_005404a0*)((int)this + 80))->FUN_005404a0((unsigned int)32768);
    *(int*)((char*)(int)this + 100) = 0;
    return;
}
