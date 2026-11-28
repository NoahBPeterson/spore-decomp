// 0x007aa3a0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEngine/SPGraphicsTextureManager.cpp, match/slices/s007a9ae0/s007a9ae0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual int s5(int);
};
struct il2c_vc2 {
    virtual void s0();
    virtual int s1();
};


// @ 0x007aa3a0
// @ 0x007aa3a0
extern "C" bool __fastcall FUN_007aa3a0(char* self, int edx_unused, int a4)
{
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1015;
    int t1019;
    int t1024;
    int t1025;
    int t1026;
    int t1027;
    int t1028;
    bool t1033;
    bool t1037;
    t1004 = (int)((int)(self));
    t1005 = (int)(*(int*)((char*)(t1004) + 12));
    if (t1005 != (int)0) {
        t1006 = (int)(t1004 + (int)8);
        if ((int)*(int*)((char*)(t1004) + 8) == (int)0) {
            t1007 = (int)(*(int*)((char*)(t1006)));
            if (t1007 != (int)0) {
                *(int*)((char*)(t1006)) = (int)((int)0);
                ((il2c_vc0*)(t1007))->s1();
            }
            t1015 = (int)(t1005);
            ((il2c_vc1*)(t1015))->s5((int)(t1006));
        }
    }
    t1019 = (int)(*(int*)((char*)(t1004) + 12));
    if (t1019 != (int)0) {
        *(int*)((char*)(t1004) + 12) = (int)((int)0);
        ((il2c_vc2*)(t1019))->s1();
    }
    t1024 = (int)(*(int*)((char*)(t1004) + 8));
    if (t1024 != (int)0) {
        t1025 = (int)(*(int*)((char*)(t1024) + 24));
        if (t1025 != (int)0) {
            t1026 = (int)((int)(a4));
            t1027 = (int)(*(int*)((char*)(t1026) + 36));
            t1028 = (int)(*(int*)((char*)(t1026) + 32));
            *(int*)((char*)(t1026) + 32) = (int)(t1025);
            *(int*)((char*)(t1026) + 36) = (int)((int)0);
            if (t1027 != (int)0) {
                t1026 = (int)((int (__cdecl*)(int))(t1027))((int)(t1028));
            }
            t1033 = true;
            return (bool)(t1033);
        }
    }
    t1037 = false;
    return (bool)(t1037);
}
