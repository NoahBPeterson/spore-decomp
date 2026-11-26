// 0x005b4ad0: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s005b4170/s005b4170.cpp.

// lifted by il2c_lift + l2c_search (ref@t1004); CI scorer MATCH; corpus status nonmatching/residual
struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
};


// @ 0x005b4ad0
extern "C" int __fastcall FUN_005b4ad0(char* self, int edx_unused, int a4, int a8, int a12, int a16, int a20, int a24)
{
    int t1000;
    int t1004;
    int t1005;
    int t1007;
    int t1010;
    int t1016;
    int t1020;
    int t1021;
    int t1022;
    unsigned char t1023;
    unsigned char t1024;
    int t1025;
    t1000 = (int)((int)(a4));
    t1004 = (int)((int)(self));
    int& t1004_r = t1004;
    t1005 = (int)(*(int*)((char*)(t1004_r) + 28));
    t1007 = (int)(*(int*)((char*)(t1000)));
    if (t1007 != t1005) {
        if (t1007 != (int)0) {
            t1010 = (int)(t1007);
            ((il2c_vc0*)(t1010))->s1();
        }
        *(int*)((char*)(t1004_r) + 28) = (int)(t1007);
        if (t1005 != (int)0) {
            t1016 = (int)(t1005);
            ((il2c_vc1*)(t1016))->s2();
        }
    }
    t1020 = (int)((int)(a8));
    t1021 = (int)((int)(a12));
    t1022 = (int)((int)(a16));
    *(int*)((char*)(t1004_r) + 56) = (int)(t1020);
    t1023 = (unsigned char)((unsigned char)(a24));
    *(int*)((char*)(t1004_r) + 60) = (int)(t1021);
    t1024 = (unsigned char)((unsigned char)(a20));
    *(int*)((char*)(t1004_r) + 64) = (int)(t1022);
    t1025 = (int)(*(int*)((char*)(t1004_r) + 28));
    *(unsigned char*)((char*)(t1004_r) + 68) = (unsigned char)(t1023);
    *(unsigned char*)((char*)(t1004_r) + 69) = (unsigned char)(t1024);
    if (t1025 != (int)0) {
        t1025 = (int)(*(int*)((char*)(t1025) + 828));
        *(int*)((char*)(t1004_r) + 32) = (int)(t1025);
    }
    return (int)(t1025);
}
