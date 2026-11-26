// 0x0107e670: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0107e670/s0107e670.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual int s4(int, int);
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
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual int s4(int, int);
};
struct il2c_vc3 {
    virtual void s0(int);
};

extern "C" unsigned char g_016e4178[];
struct C_0107e700 { int FUN_0107e700(unsigned int); };
struct C_01080830 { int FUN_01080830(unsigned int, unsigned int); };

// @ 0x0107e670
extern "C" int __stdcall FUN_0107e670(int a4)
{
    int t1000;
    int t1005;
    int t1006;
    int t1007;
    int t1010;
    int t1011;
    int t1013;
    int t1014;
    int t1017;
    int t1018;
    int t1023;
    int t1024;
    int t1027;
    int t1028;
    int t1030;
    int t1034;
    int t1037;
    t1000 = (int)((int)(*(int*)g_016e4178));
    t1005 = (int)((il2c_vc0*)(t1000))->s4((int)((int)20), (int)((int)23));
    t1006 = (int)((int)(a4));
    t1007 = (int)(t1005);
    *(unsigned short*)((char*)(t1005) + 4) = (unsigned short)((int)20);
    t1010 = (int)((C_0107e700*)(t1007))->FUN_0107e700((unsigned int)(t1006));
    t1011 = (int)(t1010);
    t1013 = (int)((int)&a4);
    t1014 = (int)(t1011);
    t1017 = (int)((il2c_vc1*)(t1014))->s5((int)(t1013));
    if ((unsigned char)*(unsigned char*)((char*)(t1017)) == (unsigned char)0) {
        t1018 = (int)((int)(*(int*)g_016e4178));
        t1023 = (int)((il2c_vc2*)(t1018))->s4((int)((int)36), (int)((int)23));
        t1024 = (int)(t1023);
        *(unsigned short*)((char*)(t1023) + 4) = (unsigned short)((int)36);
        t1027 = (int)((C_01080830*)(t1024))->FUN_01080830((unsigned int)(t1011), (unsigned int)((int)4096));
        t1028 = (int)(t1027);
        if ((unsigned short)*(unsigned short*)((char*)(t1011) + 4) != (unsigned short)0) {
            *(unsigned short*)((char*)(t1011) + 6) -= (unsigned short)1;
            if ((unsigned short)*(unsigned short*)((char*)(t1011) + 6) == (unsigned short)0) {
                t1030 = (int)(t1011);
                ((il2c_vc3*)(t1030))->s0((int)((int)1));
            }
        }
        t1034 = (int)(t1028);
        return (int)(t1034);
    }
    t1037 = (int)(t1011);
    return (int)(t1037);
}
