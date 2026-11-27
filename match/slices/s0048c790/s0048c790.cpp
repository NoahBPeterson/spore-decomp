// 0x0048c790: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0048c0f0/s0048c0f0.cpp, src/game/SPBake/SPEditorManipulationUtilities.cpp.

struct C_004541f0 { void FUN_004541f0(unsigned int); };
extern "C" void __cdecl FUN_004956b0(...);
struct C_00526430 { int FUN_00526430(); };
#pragma pack(push, 1)
struct Fr0_0048c790 {
    int v_l68;
    int v_l64;
    int v_l60;
    int v_l56;
    int dead0[2];
    int v_l44;
    int v_l40;
    int v_l36;
    int v_l32;
    int v_l28;
    int v_l24;
    int v_l20;
    int v_l16;
    int v_l12;
    int v_l8;
};
struct Fr1_0048c790 {
    int v_l72;
};
#pragma pack(pop)

// @ 0x0048c790
extern "C" void __cdecl FUN_0048c790(int a4, int a8, int a12)
{
    Fr0_0048c790 fb;
    Fr1_0048c790 fa;
    fb.v_l12 = a4 + 832;
    if ((int)(unsigned char)((C_00526430*)fb.v_l12)->FUN_00526430() != 0) {
        fa.v_l72 = 0;
    } else {
        fa.v_l72 = (int)(int)((int)((int)*(int*)((char*)fb.v_l12 + 4) - (int)*(int*)(char*)fb.v_l12) >> 2);
    }
    fb.v_l8 = fa.v_l72;
    fb.v_l16 = 0;
    for (; fb.v_l16 < fb.v_l8; fb.v_l16 = fb.v_l16 + 1) {
        fb.v_l20 = (int)(int)((int)*(int*)(char*)fb.v_l12 + (fb.v_l16 << 2));
        fb.v_l24 = (int)(int)*(int*)((char*)a8 + 4);
        fb.v_l28 = (int)(int)*(int*)(char*)a8;
        fb.v_l40 = fb.v_l28;
        L48c813:;
        if (fb.v_l40 != fb.v_l24) {
            fb.v_l32 = (int)(int)*(int*)(char*)fb.v_l40;
            fb.v_l36 = (int)(int)*(int*)(char*)fb.v_l20;
            if (fb.v_l32 != fb.v_l36) {
                fb.v_l40 = fb.v_l40 + 4;
                goto L48c813;
            }
        }
        fb.v_l44 = (int)(int)*(int*)((char*)a8 + 4);
        if (fb.v_l40 == fb.v_l44) {
            ((C_004541f0*)a8)->FUN_004541f0((unsigned int)(int)((int)*(int*)(char*)fb.v_l12 + (fb.v_l16 << 2)));
            fb.v_l56 = (int)(int)((int)*(int*)(char*)fb.v_l12 + (fb.v_l16 << 2));
            fb.v_l60 = (int)(int)*(int*)(char*)fb.v_l56;
            FUN_0048c790((unsigned int)fb.v_l60, (unsigned int)a8, (unsigned int)(int)(unsigned char)a12);
            if ((int)(unsigned char)a12 != 0) {
                fb.v_l64 = (int)(int)((int)*(int*)(char*)fb.v_l12 + (fb.v_l16 << 2));
                fb.v_l68 = (int)(int)*(int*)(char*)fb.v_l64;
                FUN_004956b0((unsigned int)fb.v_l68, (unsigned int)a8);
            }
        }
    }
    return;
}
