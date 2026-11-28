// 0x00c1d5e0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPCreatureBase.cpp, match/slices/s00c1c9f0/s00c1c9f0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual int s4();
};

struct C_00c14e70 { int FUN_00c14e70(unsigned int); };
struct C_00c17350 { void FUN_00c17350(unsigned int, unsigned int); };
struct C_00c1d460 { int FUN_00c1d460(unsigned int, unsigned int); };

// @ 0x00c1d5e0
extern "C" int __fastcall FUN_00c1d5e0(char* self, int edx_unused, int a4, int a8, int a12)
{
    int t1003;
    int t1004;
    int t1005;
    int t1009;
    int t1011;
    int t1014;
    int t1018;
    int t1019;
    int t1020;
    int t1025;
    int t1030;
    t1003 = (int)((int)(self));
    if ((unsigned char)(a4) != (unsigned char)0) {
        t1004 = (int)((int)(a12));
        t1005 = (int)((C_00c14e70*)((int)(self)))->FUN_00c14e70((unsigned int)(t1004));
        if (t1005 != (int)0) {
            t1009 = (int)(t1005);
            t1011 = (int)((il2c_vc0*)(t1009))->s4();
            if ((unsigned char)(t1011) != (unsigned char)0) goto Lc1d62e;
        }
        t1014 = (int)(t1003);
        ((C_00c17350*)(t1014))->FUN_00c17350((unsigned int)(t1004), (unsigned int)((int)0));
        t1018 = (int)((int)(a8));
        t1019 = (int)(t1003);
        t1020 = (int)((C_00c1d460*)(t1019))->FUN_00c1d460((unsigned int)(t1018), (unsigned int)(t1004));
        return (int)(t1020);
    }
    t1025 = (int)((int)(a12));
    ((C_00c17350*)((int)(self)))->FUN_00c17350((unsigned int)(t1025), (unsigned int)((int)0));
    Lc1d62e:;
    t1030 = (int)((int)0);
    return (int)(t1030);
}
