// 0x00e14c70: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPUIMissions.cpp, match/slices/s00e14a30/s00e14a30.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
};

extern "C" unsigned char g_013f6b3c[];
struct C_00810000 { int FUN_00810000(); };
struct C_008120d0 { void FUN_008120d0(unsigned int, unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x00e14c70
extern "C" int __fastcall FUN_00e14c70(char* self, int edx_unused)
{
    int t1002;
    int v_l12[3];
    int t1005;
    int t1008;
    int t1009;
    int t1012;
    int t1013;
    int t1016;
    int t1022;
    int t1026;
    int t1027;
    int t1033;
    t1002 = (int)((int)(self));
    if ((int)*(int*)((char*)(t1002) + 84) == (int)0) {
        (*(int*)&v_l12[0]) = (int)((int)717448359);
        (*(int*)&v_l12[2]) = (int)((int)1078345984);
        (*(int*)&v_l12[1]) = (int)((int)84978011);
        t1005 = (int)FUN_00f473a0((unsigned int)((int)24), (unsigned int)((int)g_013f6b3c), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
        if (t1005 != (int)0) {
            t1008 = (int)(t1005);
            t1009 = (int)((C_00810000*)(t1008))->FUN_00810000();
            t1012 = (int)(t1009);
        } else {
            t1012 = (int)((int)0);
        }
        t1013 = (int)(*(int*)((char*)(t1002) + 84));
        if (t1012 != t1013) {
            if (t1012 != (int)0) {
                t1016 = (int)(t1012);
                ((il2c_vc0*)(t1016))->s1();
            }
            *(int*)((char*)(t1002) + 84) = (int)(t1012);
            if (t1013 != (int)0) {
                t1022 = (int)(t1013);
                ((il2c_vc1*)(t1022))->s2();
            }
        }
        t1026 = (int)(*(int*)((char*)(t1002) + 84));
        t1027 = (int)((int)&v_l12);
        ((C_008120d0*)(t1026))->FUN_008120d0((unsigned int)(t1027), (unsigned int)((int)0), (unsigned int)((int)95787258));
    }
    t1033 = (int)(*(int*)((char*)(t1002) + 84));
    return (int)(t1033);
}
