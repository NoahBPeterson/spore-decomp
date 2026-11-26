// 0x0112bbf0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
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

// @ 0x0112bbf0
extern "C" int __fastcall FUN_0112bbf0(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1003;
    unsigned char t2;
    int t1007;
    int t1008;
    int t1013;
    t1002 = (int)((int)(self));
    t1003 = (int)(t1002 + (int)8);
    ((C_0107de50*)(t1003))->FUN_0107de50();
    t2 = (unsigned char)((unsigned char)(a4) & (unsigned char)1);
    *(int*)((char*)(t1002)) = (int)((int)g_013ef094);
    if (t2 != (unsigned char)0) {
        t1007 = (int)(*(unsigned short*)((char*)(t1002) + 4));
        t1008 = (int)((int)(*(int*)g_016e4178));
        ((il2c_vc0*)(t1008))->s5((int)(t1002), (int)(t1007), (int)((int)18));
    }
    t1013 = (int)(t1002);
    return (int)(t1013);
}
