// 0x00ec0c90: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00ec0a40/s00ec0a40.cpp.

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
    virtual void s36();
    virtual void s37();
    virtual void s38();
    virtual void s39();
    virtual void s40();
    virtual void s41();
    virtual void s42();
    virtual void s43();
    virtual void s44();
    virtual void s45();
    virtual int s46(int);
};

extern "C" unsigned char g_017f243b[];
struct C_00c0f780 { int FUN_00c0f780(); };
struct C_00c0f8a0 { int FUN_00c0f8a0(unsigned int); };
extern "C" int __cdecl FUN_00c7d090(...);

// @ 0x00ec0c90
extern "C" bool __cdecl FUN_00ec0c90(int a4, int a8)
{
    int t1000;
    int t1006;
    int t1007;
    int t1008;
    int t1011;
    int t1015;
    int t1019;
    bool t1022;
    bool t1024;
    t1000 = (int)((int)(a4));
    if (t1000 != (int)0) {
        t1006 = (int)((il2c_vc0*)(t1000))->s3((int)((int)(-805081592)));
        t1007 = (int)(t1006);
        if (t1007 != (int)0) {
            t1008 = (int)(t1007);
            t1006 = (int)((C_00c0f780*)(t1008))->FUN_00c0f780();
            if (t1006 != (int)(-1)) {
                t1011 = (int)(t1007);
                t1006 = (int)((C_00c0f8a0*)(t1011))->FUN_00c0f8a0((unsigned int)(t1006));
                if (t1006 != (int)0) {
                    t1015 = (int)(t1006);
                    t1006 = (int)((il2c_vc1*)(t1015))->s46((int)((int)g_017f243b));
                    if (t1006 != (int)0) {
                        t1019 = (int)((int)(a8));
                        t1006 = (int)FUN_00c7d090((unsigned int)(t1006), (unsigned int)(t1019));
                        if ((unsigned char)(t1006) != (unsigned char)0) {
                            t1022 = true;
                            return (bool)(t1022);
                        }
                    }
                }
            }
        }
    }
    t1024 = false;
    return (bool)(t1024);
}
