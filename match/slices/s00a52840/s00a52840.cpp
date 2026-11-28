// 0x00a52840: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00a52080/s00a52080.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual int s6(int, int, int, int, int);
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual int s7(int, int, int, float);
};

extern "C" int __cdecl FUN_00a67d00(...);

// @ 0x00a52840
extern "C" void __cdecl FUN_00a52840(int a4, int a8, int a12, int a16, int a20)
{
    int t1001;
    int t1003;
    int t1006;
    int t1007;
    int t1008;
    int t1014;
    int t1015;
    int t1016;
    int t1017;
    int t1018;
    int t1024;
    int t1027;
    int t1028;
    if ((int)(a16) == (int)1) {
        t1001 = (int)((int)(a4));
        if ((unsigned char)*(unsigned char*)((char*)(t1001) + 52) != (unsigned char)0) {
            t1003 = (int)FUN_00a67d00();
            t1006 = (int)((int)(a20));
            t1007 = (int)(t1003);
            t1008 = (int)(*(int*)((char*)(t1006)));
            switch ((unsigned int)(t1008)) { case 1: goto La5288a; case 2: goto La52869; default: goto La528a6; }
            goto La52869;
            goto La5288a;
            goto La528a6;
            La52869:;
            t1014 = (int)(*(int*)((char*)(t1006) + 8));
            t1015 = (int)(*(int*)((char*)(t1006) + 4));
            t1016 = (int)((int)(a12));
            t1017 = (int)((int)(a8));
            t1018 = (int)(*(int*)((char*)(t1001) + 48));
            ((il2c_vc0*)(t1007))->s6((int)(t1018), (int)(t1017), (int)(t1016), (int)(t1015), (int)(t1014));
            return;
            La5288a:;
            t1024 = (int)((int)(a12));
            t1027 = (int)((int)(a8));
            t1028 = (int)(*(int*)((char*)(t1001) + 48));
            ((il2c_vc1*)(t1007))->s7((int)(t1028), (int)(t1027), (int)(t1024), (float)(*(float*)((char*)(t1006) + 4)));
        }
        La528a6:;
    }
    return;
}
