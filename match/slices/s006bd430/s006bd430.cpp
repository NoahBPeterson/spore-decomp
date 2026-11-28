// 0x006bd430: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s006bd150/s006bd150.cpp, src/game/UTFSpore_Win32/DatabasePackedFile_v2.cpp.

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
    virtual void s32(int);
};

struct C_006bcd30 { bool FUN_006bcd30(); };
struct C_006bef70 { int FUN_006bef70(unsigned int, unsigned int); };
struct C_00929290 { void FUN_00929290(); };

// @ 0x006bd430
// @ 0x006bd430
extern "C" bool __fastcall FUN_006bd430(char* self, int edx_unused, int a4)
{
    int t1003;
    int t1004;
    unsigned char t2;
    int t1005;
    bool t1008;
    int t1011;
    int t1015;
    int t1019;
    int t1023;
    int t1026;
    int t1030;
    int t1034;
    bool t1039;
    t1003 = (int)((int)(self));
    t1004 = (int)(*(int*)((char*)(t1003) + 20));
    if (t1004 != (int)0) {
        t2 = (unsigned char)((unsigned char)(t1004) & (unsigned char)2);
        if (t2 != (unsigned char)0) {
            t1008 = ((C_006bcd30*)((int)(self)))->FUN_006bcd30();
            if ((unsigned char)(a4) == (unsigned char)0) goto L6bd46d;
            if (t1008 == (unsigned char)0) goto L6bd46d;
            t1011 = (int)(t1003);
            ((il2c_vc0*)(t1011))->s9();
            t1015 = (int)(t1003 + (int)48);
            ((C_00929290*)(t1015))->FUN_00929290();
            *(int*)((char*)(t1003) + 20) = (int)((int)0);
            goto L6bd480;
        }
        t1008 = true;
        L6bd46d:;
        t1019 = (int)(t1003 + (int)48);
        ((C_00929290*)(t1019))->FUN_00929290();
        *(int*)((char*)(t1003) + 20) = (int)((int)0);
        goto L6bd480;
    }
    t1008 = true;
    L6bd480:;
    t1023 = (int)(*(int*)((char*)(t1003) + 1240));
    t1026 = (int)(t1003);
    ((il2c_vc1*)(t1026))->s32((int)(t1023));
    t1030 = (int)(t1003 + (int)1360);
    *(int*)((char*)(t1003) + 1240) = (int)((int)0);
    ((C_006bef70*)(t1030))->FUN_006bef70((unsigned int)((int)0), (unsigned int)((int)0));
    t1034 = (int)(t1003 + (int)1400);
    ((C_006bef70*)(t1034))->FUN_006bef70((unsigned int)((int)0), (unsigned int)((int)0));
    t1039 = t1008;
    return t1039;
}
