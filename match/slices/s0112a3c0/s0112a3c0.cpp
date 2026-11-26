// 0x0112a3c0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s01129d50/s01129d50.cpp.

struct il2c_vc0 {
    virtual void s0(int);
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5(int, int, int);
};

extern "C" unsigned char g_014a706c[];
extern "C" unsigned char g_014a7074[];
extern "C" unsigned char g_014a707c[];
extern "C" unsigned char g_014a7084[];
extern "C" unsigned char g_014a708c[];
extern "C" unsigned char g_016e4178[];
struct C_005efd40 { void FUN_005efd40(); };

// @ 0x0112a3c0
extern "C" int __fastcall FUN_0112a3c0(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1003;
    int t1008;
    unsigned char t7;
    int t1012;
    int t1013;
    int t1018;
    t1002 = (int)((int)(self));
    t1003 = (int)(*(int*)((char*)(t1002) + 24));
    *(int*)((char*)(t1002)) = (int)((int)g_014a708c);
    *(int*)((char*)(t1002) + 8) = (int)((int)g_014a7084);
    *(int*)((char*)(t1002) + 12) = (int)((int)g_014a707c);
    *(int*)((char*)(t1002) + 16) = (int)((int)g_014a7074);
    *(int*)((char*)(t1002) + 20) = (int)((int)g_014a706c);
    if (t1003 != (int)0) {
        if ((unsigned short)*(unsigned short*)((char*)(t1003) + 4) != (unsigned short)0) {
            *(unsigned short*)((char*)(t1003) + 6) -= (unsigned short)1;
            if ((unsigned short)*(unsigned short*)((char*)(t1003) + 6) == (unsigned short)0) {
                ((il2c_vc0*)(t1003))->s0((int)((int)1));
            }
        }
    }
    t1008 = (int)(t1002);
    ((C_005efd40*)(t1008))->FUN_005efd40();
    t7 = (unsigned char)((unsigned char)(a4) & (unsigned char)1);
    if (t7 != (unsigned char)0) {
        t1012 = (int)(*(unsigned short*)((char*)(t1002) + 4));
        t1013 = (int)((int)(*(int*)g_016e4178));
        ((il2c_vc1*)(t1013))->s5((int)(t1002), (int)(t1012), (int)((int)36));
    }
    t1018 = (int)(t1002);
    return (int)(t1018);
}
