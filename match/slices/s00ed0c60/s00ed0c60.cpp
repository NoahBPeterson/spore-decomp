// 0x00ed0c60: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00ed0b70/s00ed0b70.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual int s5();
};
struct il2c_vc1 {
    virtual void s0();
    virtual int s1();
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
    virtual int s2();
};


// @ 0x00ed0c60
extern "C" bool __fastcall FUN_00ed0c60(char* self, int edx_unused, int a4, int a8)
{
    int t1000;
    int t1003;
    int t1004;
    bool t1010;
    int t1013;
    int t1015;
    int t1018;
    int t1023;
    bool t1028;
    t1000 = (int)((int)(a4));
    t1003 = (int)((int)(self));
    if (t1000 != (int)51122631) {
        if (t1000 != (int)120314641) goto Led0cb7;
        t1004 = (int)(*(int*)((char*)(t1003) + 16));
        ((il2c_vc0*)(t1004))->s5();
        t1010 = false;
        return (bool)(t1010);
    }
    if ((unsigned char)*(unsigned char*)((char*)(t1003) + 4) != (unsigned char)0) {
        t1013 = (int)(*(int*)((char*)(t1003) + 44));
        t1015 = (int)((int)(a8));
        if (t1015 != t1013) {
            if (t1015 != (int)0) {
                t1018 = (int)(t1015);
                t1000 = (int)((il2c_vc1*)(t1018))->s1();
            }
            *(int*)((char*)(t1003) + 44) = (int)(t1015);
            if (t1013 != (int)0) {
                t1023 = (int)(t1013);
                t1000 = (int)((il2c_vc2*)(t1023))->s2();
            }
        }
    }
    Led0cb7:;
    t1028 = false;
    return (bool)(t1028);
}
