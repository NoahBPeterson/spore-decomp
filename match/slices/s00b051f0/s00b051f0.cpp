// 0x00b051f0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00b047b0/s00b047b0.cpp, src/game/SPGonzago/SPPlanet.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2(int);
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2(int);
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
    virtual void s2(int);
};
struct il2c_vc3 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc4 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc5 {
    virtual void s0();
    virtual void s1();
};

extern "C" int __cdecl FUN_00f47380(...);

// @ 0x00b051f0
extern "C" int __stdcall FUN_00b051f0(int a4, int a8)
{
    int t1000;
    int t1001;
    int t1004;
    int t1007;
    int t1008;
    unsigned int t1013;
    int t1014;
    int t1016;
    int t1017;
    int t1020;
    int t1023;
    int t1026;
    int t1027;
    int t1030;
    int t1033;
    int t1036;
    int t1037;
    int t1040;
    int t1043;
    int t1046;
    int t1047;
    int t1053;
    int t1056;
    int t1057;
    int t1063;
    int t1066;
    int t1067;
    t1000 = (int)((int)(a4));
    t1001 = (int)((int)(a8));
    if ((unsigned int)(t1000) < (unsigned int)(t1001)) {
        t1004 = (int)(t1001 - t1000);
        t1007 = (int)(t1000 + (int)4496);
        t1008 = (int)(t1004 - (int)1);
        t1013 = (unsigned int)((unsigned int)(t1008) / (unsigned int)6568);
        t1014 = (int)((int)(t1013) + (int)1);
        do {
            t1016 = (int)(*(int*)((char*)(t1007) + 4));
            t1017 = (int)(*(int*)((char*)(t1007)));
            if ((unsigned int)(t1017) < (unsigned int)(t1016)) {
                do {
                    t1020 = (int)(t1017);
                    ((il2c_vc0*)(t1020))->s2((int)((int)0));
                    t1017 = (int)(t1017 - (int)(-128));
                } while ((unsigned int)(t1017) < (unsigned int)(t1016));
            }
            t1023 = (int)(*(int*)((char*)(t1007)));
            if (t1023 != (int)0) {
                if ((int)*(int*)((char*)(t1023) - 4) != (int)0) {
                    FUN_00f47380((unsigned int)(t1023));
                }
            }
            t1026 = (int)(*(int*)((char*)(t1007) - 2068));
            t1027 = (int)(*(int*)((char*)(t1007) - 2072));
            if ((unsigned int)(t1027) < (unsigned int)(t1026)) {
                do {
                    t1030 = (int)(t1027);
                    ((il2c_vc1*)(t1030))->s2((int)((int)0));
                    t1027 = (int)(t1027 - (int)(-128));
                } while ((unsigned int)(t1027) < (unsigned int)(t1026));
            }
            t1033 = (int)(*(int*)((char*)(t1007) - 2072));
            if (t1033 != (int)0) {
                if ((int)*(int*)((char*)(t1033) - 4) != (int)0) {
                    FUN_00f47380((unsigned int)(t1033));
                }
            }
            t1036 = (int)(*(int*)((char*)(t1007) - 4140));
            t1037 = (int)(*(int*)((char*)(t1007) - 4144));
            if ((unsigned int)(t1037) < (unsigned int)(t1036)) {
                do {
                    t1040 = (int)(t1037);
                    ((il2c_vc2*)(t1040))->s2((int)((int)0));
                    t1037 = (int)(t1037 - (int)(-128));
                } while ((unsigned int)(t1037) < (unsigned int)(t1036));
            }
            t1043 = (int)(*(int*)((char*)(t1007) - 4144));
            if (t1043 != (int)0) {
                if ((int)*(int*)((char*)(t1043) - 4) != (int)0) {
                    FUN_00f47380((unsigned int)(t1043));
                }
            }
            t1046 = (int)(*(int*)((char*)(t1007) - 4240));
            t1047 = (int)(*(int*)((char*)(t1007) - 4244));
            if ((unsigned int)(t1047) < (unsigned int)(t1046)) {
                do {
                    t1008 = (int)(*(int*)((char*)(t1047)));
                    if (t1008 != (int)0) {
                        ((il2c_vc3*)(t1008))->s1();
                    }
                    t1047 = (int)(t1047 + (int)4);
                } while ((unsigned int)(t1047) < (unsigned int)(t1046));
            }
            t1053 = (int)(*(int*)((char*)(t1007) - 4244));
            if (t1053 != (int)0) {
                if ((int)*(int*)((char*)(t1053) - 4) != (int)0) {
                    FUN_00f47380((unsigned int)(t1053));
                }
            }
            t1056 = (int)(*(int*)((char*)(t1007) - 4328));
            t1057 = (int)(*(int*)((char*)(t1007) - 4332));
            if ((unsigned int)(t1057) < (unsigned int)(t1056)) {
                do {
                    t1008 = (int)(*(int*)((char*)(t1057)));
                    if (t1008 != (int)0) {
                        ((il2c_vc4*)(t1008))->s1();
                    }
                    t1057 = (int)(t1057 + (int)4);
                } while ((unsigned int)(t1057) < (unsigned int)(t1056));
            }
            t1063 = (int)(*(int*)((char*)(t1007) - 4332));
            if (t1063 != (int)0) {
                if ((int)*(int*)((char*)(t1063) - 4) != (int)0) {
                    FUN_00f47380((unsigned int)(t1063));
                }
            }
            t1066 = (int)(*(int*)((char*)(t1007) - 4416));
            t1067 = (int)(*(int*)((char*)(t1007) - 4420));
            if ((unsigned int)(t1067) < (unsigned int)(t1066)) {
                do {
                    t1008 = (int)(*(int*)((char*)(t1067)));
                    if (t1008 != (int)0) {
                        ((il2c_vc5*)(t1008))->s1();
                    }
                    t1067 = (int)(t1067 + (int)4);
                } while ((unsigned int)(t1067) < (unsigned int)(t1066));
            }
            t1000 = (int)(*(int*)((char*)(t1007) - 4420));
            if (t1000 != (int)0) {
                if ((int)*(int*)((char*)(t1000) - 4) != (int)0) {
                    t1000 = (int)FUN_00f47380((unsigned int)(t1000));
                }
            }
            t1007 = (int)(t1007 + (int)6568);
            t1014 = (int)(t1014 - (int)1);
        } while (t1014 != (int)0);
    }
    return (int)(t1000);
}
