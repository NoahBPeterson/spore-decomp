// 0x00accd70: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00acc140/s00acc140.cpp, src/game/SPGonzago/_at_00ac0000.cpp.

// lifted by il2c_lift + l2c_search (bind@t1008); CI scorer MATCH; corpus status nonmatching/residual
struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
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
};

extern "C" unsigned char g_0145a184[];
extern "C" void __cdecl FUN_00f47380(...);

template<class HsT> __forceinline HsT& hs_bind(HsT& x) { HsT& r = x; return r; }
// @ 0x00accd70
extern "C" int __stdcall FUN_00accd70(int a4, int a8)
{
    int t1001;
    int v_l4;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1010;
    int t1011;
    int t1017;
    int t1021;
    int t1022;
    int t1023;
    int t1029;
    int t1033;
    int t1034;
    int t1035;
    int t1041;
    int t1046;
    int t1047;
    int t1048;
    int t1054;
    int t1060;
    t1001 = (int)((int)0);
    v_l4 = (int)(t1001);
    if ((unsigned int)((int)(a8)) > (unsigned int)(t1001)) {
        do {
            t1006 = (int)((int)(a4));
            t1007 = (int)(*(int*)((char*)(t1006) + (t1001)*4));
            if (t1007 != (int)0) {
                do {
                    t1008 = (int)(t1007);
                    t1007 = (int)(*(int*)((char*)(t1007) + 104));
                    *(int*)((char*)(hs_bind(t1008)) + 4) = (int)((int)g_0145a184);
                    t1009 = (int)(*(int*)((char*)(t1008) + 88));
                    t1010 = (int)(*(int*)((char*)(t1008) + 84));
                    if ((unsigned int)(t1010) < (unsigned int)(t1009)) {
                        do {
                            t1011 = (int)(*(int*)((char*)(t1010)));
                            if (t1011 != (int)0) {
                                ((il2c_vc0*)(t1011))->s1();
                            }
                            t1010 = (int)(t1010 + (int)4);
                        } while ((unsigned int)(t1010) < (unsigned int)(t1009));
                    }
                    t1017 = (int)(*(int*)((char*)(t1008) + 84));
                    if (t1017 != (int)0) {
                        if ((int)*(int*)((char*)(t1017) - 4) != (int)0) {
                            FUN_00f47380((unsigned int)(t1017));
                        }
                    }
                    t1021 = (int)(*(int*)((char*)(t1008) + 68));
                    t1022 = (int)(*(int*)((char*)(t1008) + 64));
                    if ((unsigned int)(t1022) < (unsigned int)(t1021)) {
                        do {
                            t1023 = (int)(*(int*)((char*)(t1022)));
                            if (t1023 != (int)0) {
                                ((il2c_vc1*)(t1023))->s1();
                            }
                            t1022 = (int)(t1022 + (int)4);
                        } while ((unsigned int)(t1022) < (unsigned int)(t1021));
                    }
                    t1029 = (int)(*(int*)((char*)(t1008) + 64));
                    if (t1029 != (int)0) {
                        if ((int)*(int*)((char*)(t1029) - 4) != (int)0) {
                            FUN_00f47380((unsigned int)(t1029));
                        }
                    }
                    t1033 = (int)(*(int*)((char*)(t1008) + 48));
                    t1034 = (int)(*(int*)((char*)(t1008) + 44));
                    if ((unsigned int)(t1034) < (unsigned int)(t1033)) {
                        do {
                            t1035 = (int)(*(int*)((char*)(t1034)));
                            if (t1035 != (int)0) {
                                ((il2c_vc2*)(t1035))->s1();
                            }
                            t1034 = (int)(t1034 + (int)4);
                        } while ((unsigned int)(t1034) < (unsigned int)(t1033));
                    }
                    t1041 = (int)(*(int*)((char*)(t1008) + 44));
                    if (t1041 != (int)0) {
                        if ((int)*(int*)((char*)(t1041) - 4) != (int)0) {
                            FUN_00f47380((unsigned int)(t1041));
                        }
                    }
                    t1046 = (int)(*(int*)((char*)(t1008) + 28));
                    t1047 = (int)(*(int*)((char*)(t1008) + 24));
                    if ((unsigned int)(t1047) < (unsigned int)(t1046)) {
                        do {
                            t1048 = (int)(*(int*)((char*)(t1047)));
                            if (t1048 != (int)0) {
                                ((il2c_vc3*)(t1048))->s1();
                            }
                            t1047 = (int)(t1047 + (int)4);
                        } while ((unsigned int)(t1047) < (unsigned int)(t1046));
                    }
                    t1054 = (int)(*(int*)((char*)(t1008) + 24));
                    if (t1054 != (int)0) {
                        if ((int)*(int*)((char*)(t1054) - 4) != (int)0) {
                            FUN_00f47380((unsigned int)(t1054));
                        }
                    }
                    FUN_00f47380((unsigned int)(t1008));
                } while (t1007 != (int)0);
                t1001 = (int)(v_l4);
            }
            t1060 = (int)((int)(a4));
            *(int*)((char*)(t1060) + (t1001)*4) = (int)((int)0);
            t1001 = (int)(t1001 + (int)1);
            v_l4 = (int)(t1001);
        } while ((unsigned int)(t1001) < (unsigned int)((int)(a8)));
    }
    return (int)(t1001);
}
