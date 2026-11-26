// 0x00961db0: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/UTFSpore_Win32/Window.cpp, match/slices/s00961db0/s00961db0.cpp.

// lifted by il2c_lift + l2c_search (swap@19); CI scorer MATCH; corpus status nonmatching/residual
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
    virtual void s2();
    virtual int s3(int, int);
};


// @ 0x00961db0
extern "C" void __fastcall FUN_00961db0(char* self, int edx_unused, int a4, int a8)
{
    int t1001;
    int t1004;
    int t1008;
    int t1009;
    int t1012;
    int t1013;
    int t1019;
    int t1025;
    int t1030;
    t1001 = (int)((int)0);
    t1004 = (int)((int)(self));
    if ((unsigned int)((int)(a8)) > (unsigned int)(t1001)) {
        do {
            t1008 = (int)((int)(a4));
            t1009 = (int)(*(int*)((char*)(t1008) + (t1001)*4));
            if (t1009 != (int)0) {
                goto L961dd0;
                L961dd0:;
                t1012 = (int)(t1009);
                t1009 = (int)(*(int*)((char*)(t1009) + 16));
                t1013 = (int)(*(int*)((char*)(t1012) + 12));
                if (t1013 != (int)0) {
                    ((il2c_vc0*)(t1013))->s1();
                }
                t1019 = (int)(*(int*)((char*)(t1012) + 8));
                if (t1019 != (int)0) {
                    ((il2c_vc1*)(t1019))->s1();
                }
                t1025 = (int)(*(int*)((char*)(t1004) + 28));
                t1008 = (int)((il2c_vc2*)(t1025))->s3((int)(t1012), (int)((int)24));
                if (t1009 != (int)0) goto L961dd0;
            }
            t1030 = (int)((int)(a4));
            *(int*)((char*)(t1030) + (t1001)*4) = (int)((int)0);
            t1001 = (int)(t1001 + (int)1);
        } while ((unsigned int)(t1001) < (unsigned int)((int)(a8)));
    }
    return;
}
