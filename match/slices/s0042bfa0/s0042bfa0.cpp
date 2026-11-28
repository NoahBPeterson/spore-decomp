// 0x0042bfa0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0042b9e0/s0042b9e0.cpp.

extern "C" void __cdecl FUN_0042e240(...);
struct C_0042f2e0 { void FUN_0042f2e0(unsigned int, unsigned int); };
struct C_004769b0 { int FUN_004769b0(unsigned int, unsigned int); };
extern "C" void __cdecl FUN_004ab450(...);
struct C_004c0b80 { int FUN_004c0b80(); };
struct C_004c2100 { void FUN_004c2100(unsigned int); };


struct D_0042bfa0 { void FUN_0042bfa0(int a4, int a8); };
// @ 0x0042bfa0
// @ 0x0042bfa0
void D_0042bfa0::FUN_0042bfa0(int a4, int a8)
{
    int v_l24;
    int dead_0_15[4];
    int v_l28;
    int dead_4_35[3];
    int v_l140_62;
    int dead_3[6];
    int dead_2_17[15];
    int v_l52;
    int v_l48_y;
    int v_l44_e;
    int v_l40;
    int dead_1[2];
    int dead_6_56[4];
    int v_l192_14;
    int v_l188_19;
    int v_l184;
    int v_l180_a;
    int v_l176_26;
    int dead_5_26;
    int v_l168_20;
    int v_l164_60;
    int v_l160_c;
    int v_l156;
    if ((unsigned int)a4 > (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) >> 2)) {
        ((C_0042f2e0*)(int)&v_l28)->FUN_0042f2e0((unsigned int)a4, (unsigned int)((int)this + 12));
        v_l52 = v_l28;
        v_l40 = v_l52;
        v_l48_y = v_l40;
        FUN_004ab450((unsigned int)(int)&v_l44_e, (unsigned int)v_l48_y, (unsigned int)a4, (unsigned int)a8);
        v_l24 = v_l28 + (a4 << 2);
        ((C_004c2100*)(int)this)->FUN_004c2100((unsigned int)(int)&v_l28);
        v_l140_62 = v_l28;
        for (; (unsigned int)v_l140_62 < (unsigned int)v_l24; v_l140_62 = v_l140_62 + 4) {
        }
        ((C_004c0b80*)(int)&v_l28)->FUN_004c0b80();
    } else {
        if ((unsigned int)a4 > (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) >> 2)) {
            v_l168_20 = (int)(int)*(int*)((char*)(int)this + 4);
            v_l164_60 = (int)(int)*(int*)(char*)(int)this;
            v_l160_c = v_l164_60;
            v_l156 = (int)(int)*(int*)(char*)a8;
            for (; v_l160_c != v_l168_20; v_l160_c = v_l160_c + 4) {
                *(int*)(char*)v_l160_c = v_l156;
            }
            v_l192_14 = (int)(int)(a4 - (int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) >> 2));
            v_l188_19 = (int)(int)*(int*)((char*)(int)this + 4);
            v_l176_26 = v_l188_19;
            v_l184 = v_l176_26;
            FUN_004ab450((unsigned int)(int)&v_l180_a, (unsigned int)v_l184, (unsigned int)v_l192_14, (unsigned int)a8);
            *(int*)((char*)(int)this + 4) = (int)(int)((int)*(int*)((char*)(int)this + 4) + (int)((int)(a4 - (int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) >> 2)) << 2));
        } else {
            FUN_0042e240((unsigned int)(int)*(int*)(char*)(int)this, (unsigned int)a4, (unsigned int)a8);
            ((C_004769b0*)(int)this)->FUN_004769b0((unsigned int)(int)((int)*(int*)(char*)(int)this + (a4 << 2)), (unsigned int)(int)*(int*)((char*)(int)this + 4));
        }
    }
    return;
}
