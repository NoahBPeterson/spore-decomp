// 0x0112b680: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0112adf0/s0112adf0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5(int, int, int);
};

extern "C" unsigned char g_013ef094[];
extern "C" unsigned char g_016e4178[];
struct C_0107de50 { void FUN_0107de50(); };
struct C_0112b050 { void FUN_0112b050(); };

// @ 0x0112b680
extern "C" int __fastcall FUN_0112b680(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1003;
    int t1007;
    unsigned char t3;
    int t1011;
    int t1012;
    int t1017;
    t1002 = (int)((int)(self));
    t1003 = (int)(t1002 + (int)36);
    ((C_0107de50*)(t1003))->FUN_0107de50();
    t1007 = (int)(t1002 + (int)12);
    ((C_0112b050*)(t1007))->FUN_0112b050();
    t3 = (unsigned char)((unsigned char)(a4) & (unsigned char)1);
    *(int*)((char*)(t1002)) = (int)((int)g_013ef094);
    if (t3 != (unsigned char)0) {
        t1011 = (int)(*(unsigned short*)((char*)(t1002) + 4));
        t1012 = (int)((int)(*(int*)g_016e4178));
        ((il2c_vc0*)(t1012))->s5((int)(t1002), (int)(t1011), (int)((int)18));
    }
    t1017 = (int)(t1002);
    return (int)(t1017);
}
