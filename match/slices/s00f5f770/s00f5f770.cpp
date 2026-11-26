// 0x00f5f770: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00f5e910/s00f5e910.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual int s3(int);
};

extern "C" unsigned char g_016c9478[];
struct C_00f5f6a0 { void FUN_00f5f6a0(unsigned int); };

// @ 0x00f5f770
extern "C" int __fastcall FUN_00f5f770(char* self, int edx_unused, int a4)
{
    int t1000;
    int t1003;
    float t1004;
    int t1005;
    int t1006;
    int t1007;
    unsigned char t3;
    int t1008;
    int t1012;
    int t12;
    int t1016;
    t1000 = (int)((int)(a4));
    t1003 = (int)((int)(self));
    if ((int)*(int*)((char*)(t1003) + 560) != (int)0) {
        t1004 = (float)(*(float*)((char*)(t1000) + 8));
        if (!(t1004 >= (float)*(float*)((char*)(t1000) + 12))) {
            t1005 = (int)(*(int*)((char*)(t1003) + 36));
            t1006 = (int)(*(int*)((char*)(t1005) + 8));
            t1007 = (int)((unsigned int)(t1006) >> (int)27);
            t3 = (unsigned char)((unsigned char)(t1007) & (unsigned char)1);
            if (t3 == (unsigned char)0) goto Lf5f7ca;
        }
        t1008 = (int)(t1003);
        ((C_00f5f6a0*)(t1008))->FUN_00f5f6a0((unsigned int)(t1000));
        t1000 = (int)(*(int*)((char*)(t1003) + 560));
        if (t1000 == (int)0) goto Lf5f7d7;
        if ((int)*(int*)((char*)(t1003) + 32) != (int)0) goto Lf5f7d7;
        if ((unsigned char)*(unsigned char*)((char*)(t1003) + 21) == (unsigned char)0) goto Lf5f7d7;
        t1012 = (int)(t1000 + (int)8);
        *(int*)&(a4) = (int)((int)0);
        t12 = (int)((il2c_vc0*)(t1012))->s3((int)((int)(a4)));
        return (int)(t12);
    }
    Lf5f7ca:;
    t1016 = (int)((int)(*(int*)g_016c9478));
    *(int*)((char*)(t1000)) = (int)(t1016);
    *(int*)g_016c9478 = (int)(t1000);
    Lf5f7d7:;
    return (int)(t1000);
}
