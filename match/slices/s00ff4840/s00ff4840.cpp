// 0x00ff4840: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00ff4120/s00ff4120.cpp, src/game/SPGonzago/SPPlayerInventory.cpp.

// lifted by il2c_lift + l2c_search (swap@41); CI scorer MATCH; corpus status nonmatching/residual
struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual int s6();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual void s29();
    virtual void s30();
    virtual void s31();
    virtual void s32(int, int, int);
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
    virtual int s2();
};

extern "C" int __cdecl FUN_0062ffd0(...);

// @ 0x00ff4840
extern "C" bool __fastcall FUN_00ff4840(char* self, int edx_unused, int a4)
{
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1014;
    int t1015;
    int t1016;
    bool t1020;
    int t1023;
    int t1025;
    int t1029;
    int t1030;
    int t1033;
    int t1034;
    bool t1042;
    t1005 = (int)((int)(self));
    t1006 = (int)(*(int*)((char*)(t1005) + 76));
    t1007 = (int)(*(int*)((char*)(t1005) + 80));
    if (t1006 != t1007) {
        t1008 = (int)((int)(a4));
        do {
            t1009 = (int)(*(int*)((char*)(t1006)));
            t1014 = (int)((il2c_vc0*)(t1009))->s6();
            t1015 = (int)(*(int*)((char*)(t1014)));
            if (t1015 == (int)*(int*)((char*)(t1008))) {
                t1016 = (int)(*(int*)((char*)(t1014) + 4));
                if (t1016 == (int)*(int*)((char*)(t1008) + 4)) {
                    t1014 = (int)(*(int*)((char*)(t1014) + 8));
                    if (t1014 == (int)*(int*)((char*)(t1008) + 8)) goto Lff4883;
                }
            }
            t1006 = (int)(t1006 + (int)4);
        } while (t1006 != t1007);
    }
    t1020 = false;
    return (bool)(t1020);
    Lff4883:;
    t1023 = (int)(*(int*)((char*)(t1006)));
    t1025 = (int)(t1005);
    ((il2c_vc1*)(t1025))->s32((int)(t1023), (int)((int)0), (int)((int)1));
    t1030 = (int)(t1006 + (int)4);
    t1029 = (int)(*(int*)((char*)(t1005) + 80));
    if ((unsigned int)(t1030) < (unsigned int)(t1029)) {
        t1030 = (int)FUN_0062ffd0((unsigned int)(t1030), (unsigned int)(t1029), (unsigned int)(t1006));
    }
    *(int*)((char*)(t1005) + 80) += (int)(-4);
    t1033 = (int)(*(int*)((char*)(t1005) + 80));
    t1034 = (int)(*(int*)((char*)(t1033)));
    if (t1034 != (int)0) {
        t1030 = (int)((il2c_vc2*)(t1034))->s2();
    }
    t1042 = true;
    return (bool)(t1042);
}
