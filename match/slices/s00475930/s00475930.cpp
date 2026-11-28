// 0x00475930: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPGameCameraController.cpp, src/game/SPGonzago/InteractionAgent.cpp, match/slices/s00474bd0/s00474bd0.cpp, match/slices/s00472b80/s00472b80.cpp.

extern "C" unsigned char g_01667bac[];
struct C_00478930 { void FUN_00478930(unsigned int); };
extern "C" int __cdecl FUN_00938400(...);


struct D_00475930 { int FUN_00475930(int a4, int a8); };
// @ 0x00475930
int D_00475930::FUN_00475930(int a4, int a8)
{
    int v_l24;
    int v_l20_q;
    int v_l16_i;
    int v_l12_40;
    int v_l8;
    int v_l28;
    int v_l36_i;
    int v_l32;
    int v_l48_y;
    int v_l44_e;
    int v_l40;
    v_l8 = (int)(int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this);
    if ((int)*(int*)(char*)(int)this == (int)g_01667bac) {
        v_l28 = (int)(int)*(int*)((char*)(int)this + 4);
        v_l12_40 = (int)(int)FUN_00938400((unsigned int)v_l28, (unsigned int)0, (unsigned int)a4, (unsigned int)a8);
    } else {
        v_l36_i = (int)(int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)((char*)(int)this + 4));
        v_l32 = (int)(int)*(int*)((char*)(int)this + 4);
        v_l12_40 = (int)(int)FUN_00938400((unsigned int)v_l32, (unsigned int)v_l36_i, (unsigned int)a4, (unsigned int)a8);
    }
    if (v_l12_40 >= (int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)((char*)(int)this + 4))) {
        ((C_00478930*)(int)this)->FUN_00478930((unsigned int)(v_l8 + v_l12_40));
        v_l40 = (int)(int)((int)*(int*)(char*)(int)this + v_l8);
        v_l12_40 = (int)(int)FUN_00938400((unsigned int)v_l40, (unsigned int)(v_l12_40 + 1), (unsigned int)a4, (unsigned int)a8);
    } else {
        if (v_l12_40 < 0) {
            v_l20_q = (int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) << 1);
            v_l24 = 7;
            v_l44_e = (int)(int)((unsigned int)v_l24 < (unsigned int)v_l20_q ? (int)&v_l20_q : (int)&v_l24);
            v_l16_i = (int)(int)*(int*)(char*)v_l44_e;
            for (; v_l12_40 < 0 && (unsigned int)v_l16_i < (unsigned int)1000000; v_l16_i = v_l16_i << 1) {
                ((C_00478930*)(int)this)->FUN_00478930((unsigned int)v_l16_i);
                v_l48_y = (int)(int)((int)*(int*)(char*)(int)this + v_l8);
                v_l12_40 = (int)(int)FUN_00938400((unsigned int)v_l48_y, (unsigned int)(v_l16_i + 1 - v_l8), (unsigned int)a4, (unsigned int)a8);
            }
        }
    }
    if (v_l12_40 >= 0) {
        *(int*)((char*)(int)this + 4) = (int)(int)((int)((int)*(int*)(char*)(int)this + v_l8) + v_l12_40);
    }
    return (int)this;
}
