// 0x00c0f490: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00c0eae0/s00c0eae0.cpp, src/game/SPGonzago/SPCreatureBase.cpp.

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
    virtual void s25();
};


// @ 0x00c0f490
extern "C" void __fastcall FUN_00c0f490(char* self, int edx_unused)
{
    int t1002;
    int t1003;
    int t1005;
    int t1011;
    int t1016;
    int t1021;
    int t1026;
    t1002 = (int)((int)(self));
    t1003 = (int)(*(int*)((char*)(t1002) + 44));
    t1005 = (int)((int)0);
    *(int*)((char*)(t1002) + 4) = (int)(t1005);
    if (t1003 != t1005) {
        ((il2c_vc0*)(t1003))->s3((int)(t1005));
        t1011 = (int)(*(int*)((char*)(t1002) + 44));
        if (t1011 != t1005) {
            *(int*)((char*)(t1002) + 44) = (int)(t1005);
            ((il2c_vc1*)(t1011))->s1();
        }
    }
    t1016 = (int)(*(int*)((char*)(t1002) + 48));
    if (t1016 != t1005) {
        ((il2c_vc2*)(t1016))->s3((int)(t1005));
        t1021 = (int)(*(int*)((char*)(t1002) + 48));
        if (t1021 != t1005) {
            *(int*)((char*)(t1002) + 48) = (int)(t1005);
            ((il2c_vc3*)(t1021))->s1();
        }
    }
    t1026 = (int)(*(int*)((char*)(t1002) + 40));
    if (t1026 != t1005) {
        *(int*)((char*)(t1002) + 40) = (int)(t1005);
        ((il2c_vc4*)(t1026))->s25();
        return;
    }
    return;
}
