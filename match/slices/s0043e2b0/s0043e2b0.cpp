// 0x0043e2b0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/SPEditorBlock.cpp, match/slices/s0043d690/s0043d690.cpp.

extern "C" unsigned char g_013ec420[];
extern "C" unsigned char g_013ec484[];
extern "C" unsigned char g_01470f1c[];
struct C_0043d690 { void FUN_0043d690(unsigned int, float, unsigned int, unsigned int, unsigned int); };
extern "C" void __cdecl FUN_004537f0(float, unsigned int);
extern "C" int __cdecl FUN_011e0810(...);
template<class T> __forceinline bool il2c_nz(T v) { return v != 0; }
template<class T> __forceinline T il2c_k(T v) { return v; }


struct D_0043e2b0 { void FUN_0043e2b0(); };
// @ 0x0043e2b0
// @ 0x0043e2b0
void D_0043e2b0::FUN_0043e2b0()
{
    int v_l16_i;
    int v_l12_40;
    int v_l8;
    int v_l20;
    int dead_0[2];
    int v_l32;
    int v_l40;
    unsigned char v_l33;
    v_l20 = (int)this + 1740;
    v_l8 = (int)(int)((int)((int)*(int*)((char*)v_l20 + 4) - (int)*(int*)(char*)v_l20) >> 2);
    *(float*)((char*)(int)this + 1088) = (float)*(float*)g_013ec420;
    *(float*)((char*)(int)this + 1092) = (float)*(float*)g_013ec484;
    if (v_l8 > 0) {
        FUN_004537f0((float)*(float*)g_01470f1c, (unsigned int)v_l8);
        *(int*)((char*)(int)this + 1084) = ((int) FUN_011e0810 ())-1;
        v_l12_40 = 0;
        for (; v_l12_40 < v_l8; v_l12_40 = v_l12_40 + 1) {
            if (il2c_k((unsigned int)11) < (unsigned int)60) {
                v_l32 = (int)(int)*(int*)((char*)(int)this + (int)(il2c_k((unsigned int)11) >> 5) * 4 + 3528);
                v_l33 = (unsigned char)(unsigned char)(unsigned char)il2c_nz((int)(int)((int)(1 << (int)(unsigned int)(il2c_k((unsigned int)11) % (unsigned int)32)) & v_l32));
            } else {
                v_l33 = (unsigned char)0;
            }
            if ((int)v_l33 == 0 || v_l12_40 != 0) {
                v_l40 = (int)(int)((int)*(int*)((char*)(int)this + 1740) + (v_l12_40 << 2));
                v_l16_i = (int)(int)*(int*)(char*)v_l40;
                ((C_0043d690*)(int)this)->FUN_0043d690((unsigned int)v_l12_40, *(float*)((char*)v_l16_i + 168), (unsigned int)0, (unsigned int)0, (unsigned int)1);
            }
        }
    }
    return;
}
