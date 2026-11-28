// 0x00478e00: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/SPEditorExportUtilities.cpp, src/game/SPGonzago/InteractionAgent.cpp, match/slices/s00478930/s00478930.cpp, match/slices/s00472b80/s00472b80.cpp.

struct C_0040f360 { int FUN_0040f360(); };
extern "C" int __cdecl FUN_0042dee0(...);
struct C_0047bbf0 { void FUN_0047bbf0(unsigned int); };
extern "C" int __cdecl FUN_0047c140(...);
extern "C" void __cdecl FUN_0047c8a0(...);
extern "C" void __cdecl FUN_0047c920(...);
struct C_0047cf00 { void FUN_0047cf00(unsigned int); };
extern "C" void __cdecl FUN_00f47380(...);


struct D_00478e00 { void FUN_00478e00(int a4, int a8, int a12); };
// @ 0x00478e00
void D_00478e00::FUN_00478e00(int a4, int a8, int a12)
{
    int v_l8;
    int v_l736_d;
    int v_l732_48;
    int v_l728_b;
    int v_l724_27;
    unsigned char v_l718_10;
    char dead_0_a;
    int v_l716_71[2];
    int v_l708_21;
    int v_l704_16;
    int v_l700_19;
    int v_l696_b;
    int v_l692;
    int v_l688_28;
    int v_l684_13[166];
    int v_l20[3];
    int v_l772;
    int v_l768_13;
    unsigned char v_l762_11;
    char dead_1_32;
    int v_l760;
    int v_l756_c;
    int v_l752_14;
    unsigned char v_l747_17;
    unsigned char v_l746_16;
    unsigned char v_l745_47;
    int v_l744_c;
    int v_l740;
    int v_l788;
    int v_l784;
    unsigned char v_l778_17;
    char dead_2_b;
    int v_l776;
    int dead_5_30[11];
    int v_l856_a;
    int v_l852;
    unsigned char v_l846_11;
    char dead_4_21;
    int dead_3_67[8];
    int v_l812_26;
    int v_l808_b;
    int v_l804;
    int v_l800_12;
    int v_l796_49;
    int v_l792;
    int v_l908_11;
    int v_l904;
    int v_l912;
    if ((unsigned int)a8 <= (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)((char*)(int)this + 4)) / 668)) {
        if ((unsigned int)a8 > (unsigned int)0) {
            ((C_0047bbf0*)(int)&v_l684_13)->FUN_0047bbf0((unsigned int)a12);
            v_l688_28 = (int)(int)((int)((int)*(int*)((char*)(int)this + 4) - a4) / 668);
            v_l8 = (int)(int)*(int*)((char*)(int)this + 4);
            if ((unsigned int)a8 < (unsigned int)v_l688_28) {
                v_l744_c = (int)(int)*(int*)((char*)(int)this + 4);
                v_l740 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l736_d = (int)(int)((int)*(int*)((char*)(int)this + 4) - a8 * 668);
                v_l724_27 = v_l744_c;
                v_l728_b = v_l740;
                v_l732_48 = v_l736_d;
                FUN_0047c8a0((unsigned int)(int)&v_l716_71, (unsigned int)v_l732_48, (unsigned int)v_l728_b, (unsigned int)v_l724_27, (unsigned int)(int)v_l718_10);
                *(int*)((char*)(int)this + 4) = (int)(int)(a8 * 668 + (int)*(int*)((char*)(int)this + 4));
                v_l746_16 = (unsigned char)0;
                v_l745_47 = (unsigned char)0;
                v_l747_17 = (unsigned char)0;
                v_l756_c = v_l8;
                v_l752_14 = v_l8 - a8 * 668;
                while (v_l752_14 != a4) {
                    v_l752_14 = v_l752_14 - 668;
                    v_l756_c = v_l756_c - 668;
                    ((C_0047cf00*)v_l756_c)->FUN_0047cf00((unsigned int)v_l752_14);
                }
                v_l760 = a4;
                for (; v_l760 != a8 * 668 + a4; v_l760 = v_l760 + 668) {
                    ((C_0047cf00*)v_l760)->FUN_0047cf00((unsigned int)(int)&v_l684_13);
                }
            } else {
                v_l772 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l768_13 = v_l772;
                FUN_0047c920((unsigned int)v_l768_13, (unsigned int)(a8 - v_l688_28), (unsigned int)(int)&v_l684_13, (unsigned int)(int)v_l762_11);
                *(int*)((char*)(int)this + 4) = (int)(int)((a8 - v_l688_28) * 668 + (int)*(int*)((char*)(int)this + 4));
                v_l804 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l800_12 = v_l8;
                v_l796_49 = a4;
                v_l784 = v_l804;
                v_l788 = v_l800_12;
                v_l792 = v_l796_49;
                FUN_0047c8a0((unsigned int)(int)&v_l776, (unsigned int)v_l792, (unsigned int)v_l788, (unsigned int)v_l784, (unsigned int)(int)v_l778_17);
                *(int*)((char*)(int)this + 4) = (int)(int)(v_l688_28 * 668 + (int)*(int*)((char*)(int)this + 4));
                v_l808_b = a4;
                for (; v_l808_b != v_l8; v_l808_b = v_l808_b + 668) {
                    ((C_0047cf00*)v_l808_b)->FUN_0047cf00((unsigned int)(int)&v_l684_13);
                }
            }
            v_l812_26 = (int)&v_l20;
            if ((int)*(int*)(char*)v_l812_26 != 0) {
                ((C_0040f360*)(int)*(int*)(char*)v_l812_26)->FUN_0040f360();
            }
        }
    } else {
        v_l700_19 = (int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 668);
        v_l708_21 = (int)(int)((unsigned int)v_l700_19 > (unsigned int)0 ? v_l700_19 << 1 : 1);
        v_l692 = (int)(int)((unsigned int)v_l708_21 > (unsigned int)(v_l700_19 + a8) ? v_l708_21 : v_l700_19 + a8);
        v_l704_16 = (int)(int)(v_l692 != 0 ? (int)(int)FUN_0042dee0((unsigned int)((int)this + 12), (unsigned int)(v_l692 * 668), (unsigned int)4, (unsigned int)0) : 0);
        v_l696_b = (int)(int)FUN_0047c140((unsigned int)(int)*(int*)(char*)(int)this, (unsigned int)a4, (unsigned int)v_l704_16);
        v_l856_a = v_l696_b;
        v_l852 = v_l856_a;
        FUN_0047c920((unsigned int)v_l852, (unsigned int)a8, (unsigned int)a12, (unsigned int)(int)v_l846_11);
        v_l696_b = (int)(int)FUN_0047c140((unsigned int)a4, (unsigned int)(int)*(int*)((char*)(int)this + 4), (unsigned int)(a8 * 668 + v_l696_b));
        v_l912 = (int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) / 668);
        v_l908_11 = (int)(int)*(int*)(char*)(int)this;
        if (v_l908_11 != 0) {
            if ((int)*(int*)((char*)v_l908_11 - 4) != 0) {
                v_l904 = v_l908_11;
                FUN_00f47380((unsigned int)v_l904);
            }
        }
        *(int*)(char*)(int)this = v_l704_16;
        *(int*)((char*)(int)this + 4) = v_l696_b;
        *(int*)((char*)(int)this + 8) = v_l692 * 668 + v_l704_16;
    }
    return;
}
