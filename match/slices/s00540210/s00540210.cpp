// 0x00540210: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0053f960/s0053f960.cpp.

struct C_00453540 { int FUN_00453540(); };
#pragma pack(push, 1)
struct il2c_pi_4_int_8919c3cc { char pad[4]; int x; __forceinline int f() { return (int)((int)x++ + 1); } };
#pragma pack(pop)
template<class T> __forceinline T il2c_k(T v) { return v; }


struct D_00540210 { void FUN_00540210(); };
// @ 0x00540210
void D_00540210::FUN_00540210()
{
    int v_l24;
    int dead_0_15[3];
    int v_l8;
    int v_l28;
    int v_l44_e;
    int dead_1[3];
    v_l24 = (int)this + 148;
    if ((int)*(int*)(char*)v_l24 != 0) {
        v_l8 = (int)(int)*(int*)(char*)v_l24;
        if (il2c_k(0) != 0) {
            ((il2c_pi_4_int_8919c3cc*)(il2c_k((char*)0)))->f();
        }
        *(int*)(char*)v_l24 = 0;
        if (v_l8 != 0) {
            ((C_00453540*)v_l8)->FUN_00453540();
        }
    }
    v_l44_e = (int)this + 144;
    if ((int)*(int*)(char*)v_l44_e != 0) {
        v_l28 = (int)(int)*(int*)(char*)v_l44_e;
        if (il2c_k(0) != 0) {
            ((il2c_pi_4_int_8919c3cc*)(il2c_k((char*)0)))->f();
        }
        *(int*)(char*)v_l44_e = 0;
        if (v_l28 != 0) {
            ((C_00453540*)v_l28)->FUN_00453540();
        }
    }
    return;
}
