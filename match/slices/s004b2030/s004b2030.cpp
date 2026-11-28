// 0x004b2030: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/_at_004b0000.cpp, match/slices/s004b11f0/s004b11f0.cpp.

extern "C" void __cdecl FUN_0042e240(...);
struct C_004769b0 { int FUN_004769b0(unsigned int, unsigned int); };
struct C_004aa350 { void FUN_004aa350(unsigned int, unsigned int); };
extern "C" void __cdecl FUN_004ab450(...);
struct C_004e1bf0 { int FUN_004e1bf0(); };
struct C_0052c730 { void FUN_0052c730(unsigned int); };


struct D_004b2030 { void FUN_004b2030(int a4, int a8); };
// @ 0x004b2030
// @ 0x004b2030
void D_004b2030::FUN_004b2030(int a4, int a8)
{
    int v_l32_p;
    int dead_1_a;
    int v_l24;
    int v_l20_q;
    int dead_0_15[3];
    int v_l44;
    int v_l40_w;
    int v_l36;
    int v_l136_22;
    int v_l132_19;
    int dead_3_35[6];
    int dead_2[15];
    int v_l152_23;
    int dead_4_11;
    int v_l144_12;
    int v_l140;
    int dead_5_26[4];
    int v_l168_20;
    int v_l164_60;
    int v_l160_c;
    int v_l156;
    if ((unsigned int)a4 > (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) >> 2)) {
        ((C_004aa350*)(int)&v_l24)->FUN_004aa350((unsigned int)a4, (unsigned int)((int)this + 12));
        v_l44 = v_l24;
        v_l32_p = v_l44;
        v_l40_w = v_l32_p;
        FUN_004ab450((unsigned int)(int)&v_l36, (unsigned int)v_l40_w, (unsigned int)a4, (unsigned int)a8);
        v_l20_q = v_l24 + (a4 << 2);
        ((C_0052c730*)(int)this)->FUN_0052c730((unsigned int)(int)&v_l24);
        ((C_004e1bf0*)(int)&v_l24)->FUN_004e1bf0();
    } else {
        if ((unsigned int)a4 > (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) >> 2)) {
            v_l144_12 = (int)(int)*(int*)((char*)(int)this + 4);
            v_l140 = (int)(int)*(int*)(char*)(int)this;
            v_l136_22 = v_l140;
            v_l132_19 = (int)(int)*(int*)(char*)a8;
            for (; v_l136_22 != v_l144_12; v_l136_22 = v_l136_22 + 4) {
                *(int*)(char*)v_l136_22 = v_l132_19;
            }
            v_l168_20 = (int)(int)(a4 - (int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) >> 2));
            v_l164_60 = (int)(int)*(int*)((char*)(int)this + 4);
            v_l152_23 = v_l164_60;
            v_l160_c = v_l152_23;
            FUN_004ab450((unsigned int)(int)&v_l156, (unsigned int)v_l160_c, (unsigned int)v_l168_20, (unsigned int)a8);
            *(int*)((char*)(int)this + 4) = (int)(int)((int)*(int*)((char*)(int)this + 4) + (int)((int)(a4 - (int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) >> 2)) << 2));
        } else {
            FUN_0042e240((unsigned int)(int)*(int*)(char*)(int)this, (unsigned int)a4, (unsigned int)a8);
            ((C_004769b0*)(int)this)->FUN_004769b0((unsigned int)(int)((int)*(int*)(char*)(int)this + (a4 << 2)), (unsigned int)(int)*(int*)((char*)(int)this + 4));
        }
    }
    return;
}
