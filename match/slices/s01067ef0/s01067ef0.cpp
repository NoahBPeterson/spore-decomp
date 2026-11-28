// 0x01067ef0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPUISpace.cpp, match/slices/s010678e0/s010678e0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual int s7();
};


// @ 0x01067ef0
// @ 0x01067ef0
extern "C" int __fastcall FUN_01067ef0(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1003;
    int t1004;
    int t1014;
    int t1015;
    int t1016;
    int t1019;
    int t1020;
    int t1023;
    int t1029;
    int t1031;
    int t6;
    int t1032;
    int t7;
    int t1036;
    t1002 = (int)((int)(self));
    t1003 = (int)(*(int*)((char*)(t1002) + 1332));
    t1004 = (int)(t1003 - (int)*(int*)((char*)(t1002) + 1328));
    t1014 = (int)(t1004 / (int)40);
    t1015 = (int)((int)0);
    if (t1014 > (int)0) {
        t1016 = (int)((int)0);
        goto L1067f20;
        L1067f20:;
        t1019 = (int)(*(int*)((char*)(t1002) + 1328));
        t1020 = (int)(*(int*)((char*)(t1019) + t1016));
        if (t1020 != (int)0) {
            t1023 = (int)((il2c_vc0*)(t1020))->s7();
            if (t1023 == (int)(a4)) goto L1067f4b;
        }
        t1015 = (int)(t1015 + (int)1);
        t1016 = (int)(t1016 + (int)40);
        if (t1015 < t1014) goto L1067f20;
    }
    t1029 = (int)((int)0);
    return (int)(t1029);
    L1067f4b:;
    t1031 = (int)(*(int*)((char*)(t1002) + 1328));
    t6 = (int)(t1015 << (int)2);
    t1032 = (int)(t1015 + t6);
    t7 = (int)(t1032 << (int)3);
    t1036 = (int)(t1031 + t7);
    return (int)(t1036);
}
