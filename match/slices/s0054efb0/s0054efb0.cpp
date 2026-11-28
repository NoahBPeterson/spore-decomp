// 0x0054efb0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/SPPollinatorAssetDirectory.cpp, match/slices/s0054eb10/s0054eb10.cpp.

extern "C" unsigned char g_013f3cb0[];
struct C_0054f1a0 { void FUN_0054f1a0(); };
struct C_005543a0 { void FUN_005543a0(unsigned int, unsigned int); };
struct C_00564140 { int FUN_00564140(unsigned int); };
struct C_005687d0 { void FUN_005687d0(unsigned int, unsigned int); };
struct C_009221b0 { void FUN_009221b0(unsigned int); };
struct C_00922270 { void FUN_00922270(); };


struct D_0054efb0 { bool FUN_0054efb0(); };
// @ 0x0054efb0
bool D_0054efb0::FUN_0054efb0()
{
    int v_l80_c;
    int v_l76_q;
    int v_l72_k;
    int v_l68_t;
    int dead_0_15[6];
    int v_l40_h;
    int v_l36_c;
    int v_l32_p[2];
    int v_l24;
    int v_l20_q;
    int v_l16_i;
    int v_l12_40;
    int v_l8;
    int v_l92_k;
    int v_l88_12;
    int v_l84;
    int v_l96;
    int v_l104_d;
    int v_l100;
    int v_l108;
    if ((int)*(unsigned char*)((char*)(int)this + 56) != 0) {
        v_l8 = (int)this + 8;
        ((C_009221b0*)v_l8)->FUN_009221b0((unsigned int)(int)g_013f3cb0);
        v_l76_q = (int)((C_00564140*)((int)this + 92))->FUN_00564140((unsigned int)(int)&v_l32_p);
        v_l72_k = (int)(int)*(int*)((char*)v_l76_q + 4);
        v_l68_t = (int)(int)*(int*)(char*)v_l76_q;
        v_l24 = v_l68_t;
        v_l20_q = v_l72_k;
        v_l88_12 = (int)this + 92;
        v_l84 = (int)(int)((int)*(int*)((char*)v_l88_12 + 4) + (int)((int)*(int*)((char*)v_l88_12 + 8) << 2));
        v_l80_c = (int)(int)*(int*)(char*)v_l84;
        v_l40_h = v_l80_c;
        v_l36_c = v_l84;
        v_l96 = v_l36_c;
        v_l92_k = v_l40_h;
        v_l16_i = v_l92_k;
        v_l12_40 = v_l96;
        v_l100 = (int)this + 60;
        ((C_005543a0*)v_l100)->FUN_005543a0((unsigned int)(int)*(int*)((char*)v_l100 + 4), (unsigned int)(int)*(int*)((char*)v_l100 + 8));
        *(int*)((char*)v_l100 + 12) = 0;
        v_l104_d = (int)this + 92;
        ((C_005543a0*)v_l104_d)->FUN_005543a0((unsigned int)(int)*(int*)((char*)v_l104_d + 4), (unsigned int)(int)*(int*)((char*)v_l104_d + 8));
        *(int*)((char*)v_l104_d + 12) = 0;
        v_l108 = (int)this + 156;
        ((C_005687d0*)v_l108)->FUN_005687d0((unsigned int)(int)*(int*)((char*)v_l108 + 4), (unsigned int)(int)*(int*)((char*)v_l108 + 8));
        *(int*)((char*)v_l108 + 12) = 0;
        ((C_0054f1a0*)(int)this)->FUN_0054f1a0();
        ((C_00922270*)v_l8)->FUN_00922270();
    }
    return *(bool*)((char*)(int)this + 56);
}
