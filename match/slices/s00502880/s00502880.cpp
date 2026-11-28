// 0x00502880: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00501f40/s00501f40.cpp.

extern "C" int __cdecl FUN_0042dee0(...);
struct C_004c0b80 { int FUN_004c0b80(); };
extern "C" int __cdecl FUN_00501a10(...);
struct C_00502f60 { void FUN_00502f60(unsigned int); };
extern "C" void __cdecl FUN_00503830(...);
extern "C" void __cdecl FUN_005038c0(...);
struct C_00503a50 { void FUN_00503a50(unsigned int); };
extern "C" void __cdecl FUN_00f47380(...);


struct D_00502880 { void FUN_00502880(int a4, int a8, int a12); };
// @ 0x00502880
// @ 0x00502880
void D_00502880::FUN_00502880(int a4, int a8, int a12)
{
    char dead_3_19;
    int v_l256_54[2];
    int v_l248_24;
    int v_l244_17;
    int v_l240;
    int v_l236_a;
    int v_l232_17;
    int v_l228_15;
    int v_l224_b[4];
    int v_l208_18[15];
    int dead_2_a[5];
    int dead_1_a[15];
    int dead_0_15[15];
    int v_l8;
    int v_l276_12;
    int v_l272_19;
    int v_l268;
    int v_l264_11;
    unsigned char v_l258;
    unsigned char v_l287;
    unsigned char v_l286_12;
    unsigned char v_l285;
    int v_l284_17;
    int v_l280;
    int v_l356_62;
    int v_l352;
    int v_l348_d;
    int v_l344_20;
    int v_l340;
    int v_l336_16;
    int v_l332_29;
    int v_l328_29;
    int v_l324_31;
    unsigned char v_l318;
    char dead_5_22;
    int v_l316_30;
    int v_l312_28;
    int v_l308;
    unsigned char v_l302_38;
    char dead_4_10;
    int v_l300_39;
    int v_l296_d;
    int v_l292;
    unsigned char v_l390;
    char dead_7_11;
    int dead_6[8];
    int v_l456_11;
    int v_l452_d;
    int v_l448_12;
    int dead_8_a[11];
    int v_l400_14;
    int v_l396;
    if ((unsigned int)a8 <= (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)((char*)(int)this + 4)) / 216)) {
        if ((unsigned int)a8 > (unsigned int)0) {
            ((C_00502f60*)(int)&v_l224_b)->FUN_00502f60((unsigned int)a12);
            v_l228_15 = (int)(int)((int)((int)*(int*)((char*)(int)this + 4) - a4) / 216);
            v_l8 = (int)(int)*(int*)((char*)(int)this + 4);
            if ((unsigned int)a8 < (unsigned int)v_l228_15) {
                v_l284_17 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l280 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l276_12 = (int)(int)((int)*(int*)((char*)(int)this + 4) - a8 * 216);
                v_l264_11 = v_l284_17;
                v_l268 = v_l280;
                v_l272_19 = v_l276_12;
                FUN_00503830((unsigned int)(int)&v_l256_54, (unsigned int)v_l272_19, (unsigned int)v_l268, (unsigned int)v_l264_11, (unsigned int)(int)v_l258);
                *(int*)((char*)(int)this + 4) = (int)(int)(a8 * 216 + (int)*(int*)((char*)(int)this + 4));
                v_l286_12 = (unsigned char)0;
                v_l285 = (unsigned char)0;
                v_l287 = (unsigned char)0;
                v_l296_d = v_l8;
                v_l292 = v_l8 - a8 * 216;
                while (v_l292 != a4) {
                    v_l292 = v_l292 - 216;
                    v_l296_d = v_l296_d - 216;
                    ((C_00503a50*)v_l296_d)->FUN_00503a50((unsigned int)v_l292);
                }
                v_l300_39 = a4;
                for (; v_l300_39 != a8 * 216 + a4; v_l300_39 = v_l300_39 + 216) {
                    ((C_00503a50*)v_l300_39)->FUN_00503a50((unsigned int)(int)&v_l224_b);
                }
            } else {
                v_l312_28 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l308 = v_l312_28;
                FUN_005038c0((unsigned int)v_l308, (unsigned int)(a8 - v_l228_15), (unsigned int)(int)&v_l224_b, (unsigned int)(int)v_l302_38);
                *(int*)((char*)(int)this + 4) = (int)(int)((a8 - v_l228_15) * 216 + (int)*(int*)((char*)(int)this + 4));
                v_l344_20 = (int)(int)*(int*)((char*)(int)this + 4);
                v_l340 = v_l8;
                v_l336_16 = a4;
                v_l324_31 = v_l344_20;
                v_l328_29 = v_l340;
                v_l332_29 = v_l336_16;
                FUN_00503830((unsigned int)(int)&v_l316_30, (unsigned int)v_l332_29, (unsigned int)v_l328_29, (unsigned int)v_l324_31, (unsigned int)(int)v_l318);
                *(int*)((char*)(int)this + 4) = (int)(int)(v_l228_15 * 216 + (int)*(int*)((char*)(int)this + 4));
                v_l348_d = a4;
                for (; v_l348_d != v_l8; v_l348_d = v_l348_d + 216) {
                    ((C_00503a50*)v_l348_d)->FUN_00503a50((unsigned int)(int)&v_l224_b);
                }
            }
            v_l356_62 = (int)&v_l208_18;
            v_l352 = (int)(int)*(int*)(char*)v_l356_62;
            for (; (unsigned int)v_l352 < (unsigned int)*(int*)((char*)v_l356_62 + 4); v_l352 = v_l352 + 4) {
            }
            ((C_004c0b80*)v_l356_62)->FUN_004c0b80();
        }
    } else {
        v_l240 = (int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 216);
        v_l248_24 = (int)(int)((unsigned int)v_l240 > (unsigned int)0 ? v_l240 << 1 : 1);
        v_l232_17 = (int)(int)((unsigned int)v_l248_24 > (unsigned int)(v_l240 + a8) ? v_l248_24 : v_l240 + a8);
        v_l244_17 = (int)(int)(v_l232_17 != 0 ? (int)(int)FUN_0042dee0((unsigned int)((int)this + 12), (unsigned int)(v_l232_17 * 216), (unsigned int)4, (unsigned int)0) : 0);
        v_l236_a = (int)(int)FUN_00501a10((unsigned int)(int)*(int*)(char*)(int)this, (unsigned int)a4, (unsigned int)v_l244_17);
        v_l400_14 = v_l236_a;
        v_l396 = v_l400_14;
        FUN_005038c0((unsigned int)v_l396, (unsigned int)a8, (unsigned int)a12, (unsigned int)(int)v_l390);
        v_l236_a = (int)(int)FUN_00501a10((unsigned int)a4, (unsigned int)(int)*(int*)((char*)(int)this + 4), (unsigned int)(a8 * 216 + v_l236_a));
        v_l456_11 = (int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) / 216);
        v_l452_d = (int)(int)*(int*)(char*)(int)this;
        if (v_l452_d != 0) {
            if ((int)*(int*)((char*)v_l452_d - 4) != 0) {
                v_l448_12 = v_l452_d;
                FUN_00f47380((unsigned int)v_l448_12);
            }
        }
        *(int*)(char*)(int)this = v_l244_17;
        *(int*)((char*)(int)this + 4) = v_l236_a;
        *(int*)((char*)(int)this + 8) = v_l232_17 * 216 + v_l244_17;
    }
    return;
}
