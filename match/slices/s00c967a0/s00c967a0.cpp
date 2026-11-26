// 0x00c967a0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00c95980/s00c95980.cpp, src/game/SPGonzago/SPTribe.cpp.

struct il2c_vc0 {
    virtual void s0();
};
struct il2c_vc1 {
    virtual void s0();
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
};

struct C_00aea5d0 { void FUN_00aea5d0(unsigned int, unsigned int); };
struct C_00c0b760 { int FUN_00c0b760(); };
struct C_00e25bd0 { void FUN_00e25bd0(unsigned int, unsigned int); };

// @ 0x00c967a0
extern "C" int __fastcall FUN_00c967a0(char* self, int edx_unused)
{
    int t1003;
    int t1004;
    int t1005;
    int t1007;
    int t1008;
    int t1012;
    int t1014;
    int t1015;
    int t1018;
    int v_l4;
    int t1021;
    int t1025;
    int t1026;
    int t1029;
    int t1033;
    int t1034;
    int t1040;
    int t1045;
    t1003 = (int)((int)(self));
    t1004 = (int)(*(int*)((char*)(t1003) + 232));
    t1005 = (int)(*(int*)((char*)(t1003) + 228));
    t1007 = (int)(t1003 + (int)228);
    t1008 = (int)(t1007);
    ((C_00e25bd0*)(t1008))->FUN_00e25bd0((unsigned int)(t1005), (unsigned int)(t1004));
    t1012 = (int)(*(int*)((char*)(t1003) + 832));
    if (t1012 != (int)*(int*)((char*)(t1003) + 836)) {
        do {
            t1014 = (int)(*(int*)((char*)(t1012)));
            t1015 = (int)(t1014);
            t1018 = (int)((C_00c0b760*)(t1015))->FUN_00c0b760();
            if (t1018 != (int)0) {
                v_l4 = (int)(t1014);
                if (t1014 != (int)0) {
                    t1021 = (int)(t1014);
                    ((il2c_vc0*)(t1021))->s0();
                }
                t1025 = (int)(*(int*)((char*)(t1007) + 4));
                if ((unsigned int)(t1025) < (unsigned int)*(int*)((char*)(t1007) + 8)) {
                    t1026 = (int)(t1025 + (int)4);
                    *(int*)((char*)(t1007) + 4) = (int)(t1026);
                    if (t1025 == (int)0) goto Lc96820;
                    *(int*)((char*)(t1025)) = (int)(t1014);
                    if (t1014 == (int)0) goto Lc9682d;
                    t1029 = (int)(t1014);
                    ((il2c_vc1*)(t1029))->s0();
                    goto Lc96820;
                }
                t1033 = (int)((int)&v_l4);
                t1034 = (int)(t1007);
                ((C_00aea5d0*)(t1034))->FUN_00aea5d0((unsigned int)(t1025), (unsigned int)(t1033));
                t1014 = (int)(v_l4);
                Lc96820:;
                if (t1014 != (int)0) {
                    t1040 = (int)(t1014);
                    ((il2c_vc2*)(t1040))->s1();
                }
            }
            Lc9682d:;
            t1012 = (int)(t1012 + (int)4);
        } while (t1012 != (int)*(int*)((char*)(t1003) + 836));
    }
    t1045 = (int)(t1007);
    return (int)(t1045);
}
