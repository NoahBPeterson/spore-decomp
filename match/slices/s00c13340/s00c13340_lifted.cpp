// 0x00c13340: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00c13340/s00c13340.cpp, src/game/SPGonzago/SPCreatureBase.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual int s3(int);
};
struct il2c_vc1 {
    virtual void s0();
    virtual int s1();
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual int s3(int);
};
struct il2c_vc3 {
    virtual void s0();
    virtual int s1();
};
struct il2c_vc4 {
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
    virtual int s25();
};


// @ 0x00c13340
extern "C" void __fastcall FUN_00c13340(char* self, int edx_unused)
{
    int t1004;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1015;
    int t1020;
    int t1025;
    int t1030;
    t1004 = (int)((int)(self));
    t1006 = (int)(t1004 + (int)3804);
    t1007 = (int)((int)4);
    t1008 = (int)((int)0);
    do {
        t1009 = (int)(*(int*)((char*)(t1006)));
        *(int*)((char*)(t1006) - 40) = (int)(t1008);
        if (t1009 != t1008) {
            ((il2c_vc0*)(t1009))->s3((int)(t1008));
            t1015 = (int)(*(int*)((char*)(t1006)));
            if (t1015 != t1008) {
                *(int*)((char*)(t1006)) = (int)(t1008);
                ((il2c_vc1*)(t1015))->s1();
            }
        }
        t1020 = (int)(*(int*)((char*)(t1006) + 4));
        if (t1020 != t1008) {
            ((il2c_vc2*)(t1020))->s3((int)(t1008));
            t1025 = (int)(*(int*)((char*)(t1006) + 4));
            if (t1025 != t1008) {
                *(int*)((char*)(t1006) + 4) = (int)(t1008);
                ((il2c_vc3*)(t1025))->s1();
            }
        }
        t1030 = (int)(*(int*)((char*)(t1006) - 4));
        if (t1030 != t1008) {
            *(int*)((char*)(t1006) - 4) = (int)(t1008);
            ((il2c_vc4*)(t1030))->s25();
        }
        t1006 = (int)(t1006 + (int)52);
        t1007 = (int)(t1007 - (int)1);
    } while (t1007 != (int)0);
    *(int*)((char*)(t1004) + 3076) = (int)(t1008);
    *(int*)((char*)(t1004) + 3080) = (int)(t1008);
    *(int*)((char*)(t1004) + 3084) = (int)(t1008);
    return;
}
