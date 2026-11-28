// 0x00992480: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/UTFSpore_Win32/WatchGraph.cpp, match/slices/s00992480/s00992480.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual double s1();
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
    virtual void s32();
    virtual void s33();
    virtual void s34();
    virtual void s35();
    virtual int s36();
};


// @ 0x00992480
extern "C" bool __fastcall FUN_00992480(char* self, int edx_unused)
{
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1011;
    double t6;
    int t1015;
    int t1016;
    int t1017;
    int t1018;
    bool t1027;
    t1004 = (int)((int)(self));
    t1005 = (int)(*(int*)((char*)(t1004) + 524));
    t1006 = (int)(t1004 + (int)524);
    if (t1005 != (int)0) {
        t1007 = (int)(t1005 + (int)(-4));
        goto L9924a0;
    }
    L99249a:;
    t1007 = (int)((int)0);
    L9924a0:;
    if (t1006 != (int)0) {
        t1008 = (int)(t1006 + (int)(-4));
    } else {
        t1008 = (int)((int)0);
    }
    if (t1007 != t1008) {
        if ((int)*(int*)((char*)(t1007) + 20) != (int)0) {
            t1011 = (int)(t1007);
            t6 = (double)((il2c_vc0*)(t1011))->s1();
            t1015 = (int)(*(int*)((char*)(t1004) + 548));
            t1016 = (int)(*(int*)((char*)(t1007) + 20));
            *(float*)((char*)(t1016) + (t1015)*4) = (float)(t6);
        }
        t1017 = (int)(*(int*)((char*)(t1007) + 4));
        if (t1017 == (int)0) goto L99249a;
        t1007 = (int)(t1017 + (int)(-4));
        goto L9924a0;
    }
    *(int*)((char*)(t1004) + 548) += (int)1;
    t1018 = (int)(*(int*)((char*)(t1004) + 548));
    if ((unsigned int)(t1018) >= (unsigned int)*(int*)((char*)(t1004) + 544)) {
        *(int*)((char*)(t1004) + 548) = (int)((int)0);
    }
    ((il2c_vc1*)((t1004 + (int)(4))))->s36();
    t1027 = true;
    return (bool)(t1027);
}
