// 0x00dbf920: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

struct il2c_vc0 {
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
    virtual int s23(int);
};

struct C_00bddd10 { int FUN_00bddd10(); };
extern "C" int __cdecl FUN_00ffbe50(...);
struct C_00ffc320 { int FUN_00ffc320(); };
extern "C" int __cdecl FUN_0102aa50(...);

// @ 0x00dbf920
extern "C" float __cdecl FUN_00dbf920(int a4, int a8, int a12, int a16)
{
    int t1001;
    int t1002;
    unsigned char t1004;
    int t1009;
    int t1010;
    int t1013;
    int t1015;
    int t1019;
    int t1020;
    int t1023;
    int t1024;
    int t1027;
    int t1028;
    int t1029;
    t1001 = (int)((int)(a16));
    t1002 = (int)((unsigned int)(t1001) >> (int)12);
    t1004 = (unsigned char)((unsigned char)(t1002) & (unsigned char)1);
    *(unsigned char*)&(a16) = (unsigned char)(t1004);
    t1009 = (int)FUN_00ffbe50();
    t1010 = (int)(t1009);
    t1013 = (int)((C_00bddd10*)(t1010))->FUN_00bddd10();
    if (t1013 != (int)0) {
        t1015 = (int)(t1013);
        t1019 = (int)((il2c_vc0*)(t1015))->s23((int)((int)(-1338788861)));
        t1020 = (int)(t1019);
    } else {
        t1020 = (int)((int)0);
    }
    t1023 = (int)FUN_00ffbe50();
    t1024 = (int)(t1023);
    t1027 = (int)((C_00ffc320*)(t1024))->FUN_00ffc320();
    if (t1020 != (int)0) {
        t1028 = (int)((int)(a16));
        t1029 = (int)((int)(a4));
        t1027 = (int)FUN_0102aa50((unsigned int)(t1020), (unsigned int)(t1029), (unsigned int)(t1028));
        if ((unsigned char)(t1027) == (unsigned char)0) goto Ldbf998;
        if (t1020 == (int)*(int*)((char*)(t1029) + 1676)) goto Ldbf998;
        return (float)((float)1);
    }
    if (t1027 != (int)0) {
        if (t1004 != (unsigned char)0) {
            return (float)((float)1);
        }
    }
    Ldbf998:;
    return (float)((float)0);
}
