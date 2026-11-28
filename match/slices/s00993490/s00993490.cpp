// 0x00993490: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/UTFSpore_Win32/winxhtml.cpp, match/slices/s00992480/s00992480.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9(int, int);
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
    virtual void s9(int, int);
};
struct il2c_vc2 {
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


// @ 0x00993490
extern "C" void __fastcall FUN_00993490(char* self, int edx_unused, int a4)
{
    int t1002;
    float t1003;
    int t1005;
    float t1006;
    float t1008;
    int t1010;
    int t1012;
    int t1017;
    int t1019;
    t1002 = (int)((int)(a4));
    t1003 = (float)(*(float*)((char*)(t1002)));
    t1005 = (int)((int)(self));
    t1006 = (float)(*(float*)((char*)(t1005) + 43188));
    if (!(t1006 != t1003)) {
        t1008 = (float)(*(float*)((char*)(t1005) + 43192));
        if (t1008 == (float)*(float*)((char*)(t1002) + 4)) goto L99350f;
    }
    t1010 = (int)(*(int*)((char*)(t1005) + 43168));
    *(float*)((char*)(t1005) + 43188) = (float)(t1003);
    *(float*)((char*)(t1005) + 43192) = (float)(*(float*)((char*)(t1002) + 4));
    if (t1010 != (int)0) {
        t1012 = (int)(*(float*)((char*)(t1002) + 4));
        ((il2c_vc0*)(t1010))->s9((int)(t1012), (int)((int)0));
    }
    t1017 = (int)(*(int*)((char*)(t1005) + 43148));
    if (t1017 != (int)0) {
        t1019 = (int)(*(float*)((char*)(t1002)));
        ((il2c_vc1*)(t1017))->s9((int)(t1019), (int)((int)0));
    }
    ((il2c_vc2*)((t1005 + (int)(4))))->s36();
    L99350f:;
    return;
}
