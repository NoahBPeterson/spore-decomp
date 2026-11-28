// 0x00656b80: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00656310/s00656310.cpp, src/game/SPEditors/SPUIAssetVerbs.cpp.

struct il2c_vc0 {
    virtual void s0();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc3 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
};

extern "C" unsigned char g_013fa29c[];
extern "C" unsigned char g_015261e4[];
extern "C" int __cdecl FUN_00656890(...);
struct C_00810000 { int FUN_00810000(); };
struct C_00810090 { void FUN_00810090(unsigned int, unsigned int); };
struct C_008120d0 { void FUN_008120d0(unsigned int, unsigned int, unsigned int); };
struct C_008121b0 { void FUN_008121b0(unsigned int, unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x00656b80
extern "C" void __fastcall FUN_00656b80(char* self, int edx_unused, int a4)
{
    int t1001;
    int t1004;
    int t1006;
    int t1009;
    int t1015;
    int t1019;
    int t1022;
    int t1023;
    int t1026;
    int t1027;
    int t1030;
    int t1036;
    int t1040;
    int t1041;
    int v_l12[3];
    int t1042;
    int t1046;
    int t1047;
    int t1051;
    int t1055;
    t1001 = (int)((int)(a4));
    t1004 = (int)((int)(self));
    t1006 = (int)(*(int*)((char*)(t1004) + 24));
    if (t1001 != t1006) {
        if (t1001 != (int)0) {
            t1009 = (int)(t1001);
            ((il2c_vc0*)(t1009))->s0();
        }
        *(int*)((char*)(t1004) + 24) = (int)(t1001);
        if (t1006 != (int)0) {
            t1015 = (int)(t1006);
            ((il2c_vc1*)(t1015))->s1();
        }
    }
    t1019 = (int)FUN_00f473a0((unsigned int)((int)24), (unsigned int)((int)g_013fa29c), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
    if (t1019 != (int)0) {
        t1022 = (int)(t1019);
        t1023 = (int)((C_00810000*)(t1022))->FUN_00810000();
        t1026 = (int)(t1023);
    } else {
        t1026 = (int)((int)0);
    }
    t1027 = (int)(*(int*)((char*)(t1004) + 20));
    if (t1026 != t1027) {
        if (t1026 != (int)0) {
            t1030 = (int)(t1026);
            ((il2c_vc2*)(t1030))->s1();
        }
        *(int*)((char*)(t1004) + 20) = (int)(t1026);
        if (t1027 != (int)0) {
            t1036 = (int)(t1027);
            ((il2c_vc3*)(t1036))->s2();
        }
    }
    t1040 = (int)((int)(*(int*)g_015261e4));
    t1041 = (int)((int)&v_l12);
    t1042 = (int)(*(int*)((char*)(t1004) + 20));
    (*(int*)&v_l12[0]) = (int)((int)(-1168186799));
    (*(int*)&v_l12[1]) = (int)((int)84978011);
    (*(int*)&v_l12[2]) = (int)(t1040);
    ((C_008120d0*)(t1042))->FUN_008120d0((unsigned int)(t1041), (unsigned int)((int)1), (unsigned int)((int)95787258));
    t1046 = (int)(*(int*)((char*)(t1004) + 24));
    t1047 = (int)(*(int*)((char*)(t1004) + 20));
    ((C_008121b0*)(t1047))->FUN_008121b0((unsigned int)(t1046), (unsigned int)((int)1), (unsigned int)((int)95787258));
    t1051 = (int)(*(int*)((char*)(t1004) + 20));
    ((C_00810090*)(t1051))->FUN_00810090((unsigned int)((int)&FUN_00656890), (unsigned int)(t1004));
    t1055 = (int)(*(int*)((char*)(t1004) + 20));
    FUN_00656890((unsigned int)(t1004), (unsigned int)(t1055), (unsigned int)((int)1));
    return;
}
