// 0x00b26a10: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00b25c30/s00b25c30.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual int s6(int, int);
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual int s6(int, int, int, int);
};

extern "C" unsigned __int64 __rdtsc(void);
#pragma intrinsic(__rdtsc)
extern "C" unsigned char g_013cc2b8[];
extern "C" unsigned char g_0167df88[];
extern "C" unsigned char g_0167df8c[];
extern "C" unsigned char g_0167df90[];
extern "C" unsigned char g_0167df94[];
extern "C" unsigned char g_0167df98[];
extern "C" int __cdecl FUN_0067dcc0(...);
struct C_00b3d340 { int FUN_00b3d340(); };

// @ 0x00b26a10
extern "C" void __fastcall FUN_00b26a10(char* self, int edx_unused, int a4, int a8)
{
    int t1002;
    int t1003;
    int t1006;
    int t1009;
    int t1010;
    unsigned __int64 t8;
    unsigned int t1014;
    unsigned __int64 t9;
    unsigned int t1015;
    int t1016;
    int v_l8[2];
    int t1020;
    int t1021;
    int t1025;
    t1002 = (int)((int)(self));
    t1003 = (int)((C_00b3d340*)((int)(self)))->FUN_00b3d340();
    if (t1003 != (int)0) {
        t1006 = (int)((int)(a8));
        t1009 = (int)((int)(a4));
        t1010 = (int)(t1003);
        t1003 = (int)((il2c_vc0*)(t1010))->s6((int)(t1009), (int)(t1006));
    }
    if ((unsigned char)*(unsigned char*)((char*)(t1002) + 4) != (unsigned char)0) {
        if ((int)(*(int*)g_0167df98) == (int)1) {
            t8 = (unsigned __int64)__rdtsc();
            t1014 = (unsigned int)((unsigned int)(t8));
            t9 = (unsigned __int64)(t8 >> (int)32);
            t1015 = (unsigned int)((unsigned int)(t9));
            *(int*)g_0167df88 = (int)((int)(t1014));
        } else {
            t1016 = (int)((int)&v_l8);
            ((void (__stdcall*)(unsigned int))(*(int*)g_013cc2b8))((unsigned int)(t1016));
            t1020 = (int)((*(int*)&v_l8[0]));
            *(int*)&(t1015) = (int)((*(int*)&v_l8[1]));
            *(int*)g_0167df88 = (int)(t1020);
        }
        *(int*)g_0167df8c = (int)((int)(t1015));
        *(int*)g_0167df90 = (int)((int)0);
        *(int*)g_0167df94 = (int)((int)0);
        t1021 = (int)FUN_0067dcc0();
        t1025 = (int)(t1021);
        t1003 = (int)((il2c_vc1*)(t1025))->s6((int)((int)109435898), (int)((int)0), (int)((int)0), (int)((int)0));
    }
    return;
}
