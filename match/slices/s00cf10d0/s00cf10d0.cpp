// 0x00cf10d0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00cf0cf0/s00cf0cf0.cpp, src/game/SPGonzago/SPCityInputStrategy.cpp.

struct il2c_vc0 {
    virtual int s0();
};
struct il2c_vc1 {
    virtual int s0();
};
struct il2c_vc2 {
    virtual void s0();
    virtual int s1();
};
struct il2c_vc3 {
    virtual int s0();
};
struct il2c_vc4 {
    virtual void s0();
    virtual int s1();
};
struct il2c_vc5 {
    virtual void s0();
    virtual int s1();
};

struct C_00ac0730 { int FUN_00ac0730(unsigned int, unsigned int); };

// @ 0x00cf10d0
extern "C" int __cdecl FUN_00cf10d0(int a4, int a8, int a12)
{
    int t1001;
    int t1003;
    int t1005;
    int v_l4;
    int t1008;
    int t1011;
    int t1014;
    int t1015;
    int t1016;
    int t1017;
    int t1018;
    int t1021;
    int t1022;
    int t1025;
    int t1030;
    int t1033;
    int t1036;
    int t1041;
    int t1046;
    t1001 = (int)((int)(a8));
    t1003 = (int)((int)(a4));
    if (t1003 != t1001) {
        t1005 = (int)(t1003 + (int)4);
        v_l4 = (int)(t1005);
        if (t1005 != t1001) {
            goto Lcf10fa;
            Lcf10f6:;
            t1003 = (int)((int)(a4));
            Lcf10fa:;
            t1008 = (int)(*(int*)((char*)(t1005)));
            if (t1008 != (int)0) {
                t1011 = (int)(t1008);
                t1001 = (int)((il2c_vc0*)(t1011))->s0();
            }
            t1014 = (int)(t1005);
            if (t1005 != t1003) {
                Lcf1110:;
                t1015 = (int)(*(int*)((char*)(t1014) - 4));
                if (t1015 != (int)0) {
                    t1016 = (int)(t1015 + (int)52);
                } else {
                    t1016 = (int)((int)0);
                }
                if (t1008 != (int)0) {
                    t1017 = (int)(t1008 + (int)52);
                } else {
                    t1017 = (int)((int)0);
                }
                t1018 = (int)((int)&a12);
                t1001 = (int)((C_00ac0730*)(t1018))->FUN_00ac0730((unsigned int)(t1017), (unsigned int)(t1016));
                if ((unsigned char)(t1001) != (unsigned char)0) {
                    t1021 = (int)(*(int*)((char*)(t1014) - 4));
                    t1022 = (int)(*(int*)((char*)(t1014)));
                    if (t1021 != t1022) {
                        if (t1021 != (int)0) {
                            t1025 = (int)(t1021);
                            t1001 = (int)((il2c_vc1*)(t1025))->s0();
                        }
                        *(int*)((char*)(t1014)) = (int)(t1021);
                        if (t1022 != (int)0) {
                            t1030 = (int)(t1022);
                            t1001 = (int)((il2c_vc2*)(t1030))->s1();
                        }
                    }
                    t1005 = (int)(v_l4);
                    t1014 = (int)(t1014 + (int)(-4));
                    if (t1014 != (int)(a4)) goto Lcf1110;
                }
            }
            t1033 = (int)(*(int*)((char*)(t1014)));
            if (t1008 != t1033) {
                if (t1008 != (int)0) {
                    t1036 = (int)(t1008);
                    t1001 = (int)((il2c_vc3*)(t1036))->s0();
                }
                *(int*)((char*)(t1014)) = (int)(t1008);
                if (t1033 != (int)0) {
                    t1041 = (int)(t1033);
                    t1001 = (int)((il2c_vc4*)(t1041))->s1();
                }
            }
            if (t1008 != (int)0) {
                t1046 = (int)(t1008);
                t1001 = (int)((il2c_vc5*)(t1046))->s1();
            }
            t1005 = (int)(t1005 + (int)4);
            v_l4 = (int)(t1005);
            if (t1005 != (int)(a8)) goto Lcf10f6;
        }
    }
    return (int)(t1001);
}
