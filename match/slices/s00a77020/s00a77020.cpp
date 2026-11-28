// 0x00a77020: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/Swarm/_at_00a70000.cpp, match/slices/s00a76cf0/s00a76cf0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual int s6(int);
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual int s6(int);
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual int s6(int);
};


// @ 0x00a77020
extern "C" int __fastcall FUN_00a77020(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1003;
    int t1005;
    int t1008;
    int t1011;
    int t1014;
    int t1017;
    int t1020;
    float t1023;
    float t1024;
    float t1025;
    float t1026;
    int t1028;
    int t1031;
    t1002 = (int)((int)(self));
    t1003 = (int)(*(int*)((char*)(t1002) + 112));
    t1005 = (int)((int)(a4));
    if (t1003 != (int)0) {
        t1008 = (int)((il2c_vc0*)(t1003))->s6((int)(t1005));
        if ((unsigned char)(t1008) == (unsigned char)0) goto La77094;
    }
    t1011 = (int)(*(int*)((char*)(t1002) + 116));
    if (t1011 != (int)0) {
        t1014 = (int)((il2c_vc1*)(t1011))->s6((int)(t1005));
        if ((unsigned char)(t1014) == (unsigned char)0) goto La77094;
    }
    t1017 = (int)(*(int*)((char*)(t1002) + 120));
    if (t1017 != (int)0) {
        t1020 = (int)((il2c_vc2*)(t1017))->s6((int)(t1005));
        if ((unsigned char)(t1020) == (unsigned char)0) goto La77094;
    }
    t1023 = (float)(*(float*)((char*)(t1005)));
    if (t1023 >= (float)*(float*)((char*)(t1002) + 24)) {
        t1024 = (float)(*(float*)((char*)(t1002) + 32));
        if (t1024 > t1023) {
            t1025 = (float)(*(float*)((char*)(t1005) + 4));
            if (t1025 >= (float)*(float*)((char*)(t1002) + 28)) {
                t1026 = (float)(*(float*)((char*)(t1002) + 36));
                if (t1026 > t1025) {
                    t1028 = (int)((int)1);
                    return (int)(t1028);
                }
            }
        }
    }
    La77094:;
    t1031 = (int)((int)0);
    return (int)(t1031);
}
