// 0x004a37f0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004a3760/s004a3760.cpp, src/game/SPBake/SPEditorManipulationUtilities.cpp.

struct C_00425990 { void FUN_00425990(); };
struct C_00454860 { void FUN_00454860(unsigned int); };
extern "C" int __cdecl FUN_004a3920(...);
extern "C" int __cdecl FUN_004a88f0(...);
struct C_004e1bf0 { void FUN_004e1bf0(); };
struct C_0050d440 { void FUN_0050d440(unsigned int); };
struct C_0050d4e0 { void FUN_0050d4e0(unsigned int); };
struct C_00526430 { int FUN_00526430(); };
#pragma pack(push, 1)
struct Fr0_004a37f0 {
    int dead0[2];
    int v_l116;
    int dead1[3];
    int v_l100;
    int dead2[2];
    int v_l88;
    int dead3[1];
    int v_l80;
    int dead4[4];
    char dead5;
    char dead6;
    char dead7;
    unsigned char v_l57;
    int v_l56;
    int v_l52;
    int v_l48;
    int v_l44;
    int v_l40;
    int v_l36;
    int dead8[2];
    int v_l24;
    int v_l20;
    int v_l16;
    int dead9[2];
};
struct Fr1_004a37f0 {
    int dead0[1];
};
#pragma pack(pop)

// @ 0x004a37f0
extern "C" int __cdecl FUN_004a37f0(int a4, int a8, int a12)
{
    Fr0_004a37f0 fb;
    Fr1_004a37f0 fa;
    fb.v_l24 = 0;
    fb.v_l20 = 0;
    fb.v_l16 = 0;
    if (a8 != 0) {
        fb.v_l44 = 0;
        fb.v_l40 = 0;
        fb.v_l36 = 0;
        ((C_0050d4e0*)(int)&fb.v_l44)->FUN_0050d4e0((unsigned int)(int)FUN_004a3920((unsigned int)(int)&fb.v_l80, (unsigned int)a8, (unsigned int)0));
        ((C_004e1bf0*)(int)&fb.v_l80)->FUN_004e1bf0();
        if ((int)(unsigned char)((C_00526430*)(int)&fb.v_l44)->FUN_00526430() == 0) {
            fb.v_l52 = 0;
            fb.v_l48 = fb.v_l40 - fb.v_l44 >> 2;
            for (; fb.v_l52 < fb.v_l48; fb.v_l52 = fb.v_l52 + 1) {
                fb.v_l88 = fb.v_l44 + (fb.v_l52 << 2);
                fb.v_l57 = (unsigned char)(unsigned char)(int)FUN_004a88f0((unsigned int)a12, (unsigned int)(int)*(int*)(char*)fb.v_l88, (unsigned int)(int)&fb.v_l56);
                if ((int)fb.v_l57 != 0) {
                    if (fb.v_l56 != 0) {
                        ((C_00454860*)(int)&fb.v_l24)->FUN_00454860((unsigned int)(int)&fb.v_l56);
                    }
                }
            }
        }
        fb.v_l100 = fb.v_l44;
        for (; (unsigned int)fb.v_l100 < (unsigned int)fb.v_l40; fb.v_l100 = fb.v_l100 + 4) {
        }
        ((C_00425990*)(int)&fb.v_l44)->FUN_00425990();
    }
    ((C_0050d440*)a4)->FUN_0050d440((unsigned int)(int)&fb.v_l24);
    fb.v_l116 = fb.v_l24;
    for (; (unsigned int)fb.v_l116 < (unsigned int)fb.v_l20; fb.v_l116 = fb.v_l116 + 4) {
    }
    ((C_00425990*)(int)&fb.v_l24)->FUN_00425990();
    return a4;
}
