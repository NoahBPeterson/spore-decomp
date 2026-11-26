// 0x00f19e00: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00f18eb0/s00f18eb0.cpp, src/game/SPGonzago/_at_00f10000.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual int s3(int);
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
    virtual int s8();
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
    virtual int s8();
};
struct il2c_vc3 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3(int);
};

extern "C" unsigned char g_017f243b[];
extern "C" unsigned char g_018eb45e[];
struct C_00b1fdb0 { int FUN_00b1fdb0(); };
extern "C" int __cdecl FUN_00b3d300(...);

// @ 0x00f19e00
extern "C" bool __cdecl FUN_00f19e00(int a4)
{
    int t1000;
    int t1001;
    int t1007;
    int t1010;
    int t1015;
    int t1020;
    int t1026;
    int t1027;
    bool t1030;
    bool t1032;
    t1000 = (int)((int)(a4));
    t1001 = (int)(*(int*)((char*)(t1000) + 100));
    if (t1001 != (int)0) {
        t1000 = (int)((il2c_vc0*)(t1001))->s3((int)((int)g_017f243b));
        t1007 = (int)(t1000);
        if (t1007 != (int)0) {
            t1010 = (int)(t1007);
            t1000 = (int)((il2c_vc1*)(t1010))->s8();
            if (t1000 != (int)48704686) {
                t1015 = (int)(t1007);
                t1000 = (int)((il2c_vc2*)(t1015))->s8();
                if (t1000 == (int)g_018eb45e) {
                    t1020 = (int)(t1007);
                    ((il2c_vc3*)(t1020))->s3((int)((int)(-805081592)));
                    t1026 = (int)FUN_00b3d300();
                    t1027 = (int)(t1026);
                    t1000 = (int)((C_00b1fdb0*)(t1027))->FUN_00b1fdb0();
                    if (t1007 == t1000) goto Lf19e60;
                }
                t1030 = true;
                return (bool)(t1030);
            }
        }
    }
    Lf19e60:;
    t1032 = false;
    return (bool)(t1032);
}
