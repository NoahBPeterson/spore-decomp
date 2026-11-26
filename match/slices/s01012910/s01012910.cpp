// 0x01012910: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

struct il2c_vc0 {
    virtual void s0();
};
struct il2c_vc1 {
    virtual void s0();
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
};

struct C_00aea5d0 { void FUN_00aea5d0(unsigned int, unsigned int); };
struct C_00b1fdb0 { int FUN_00b1fdb0(); };
extern "C" int __stdcall FUN_00b3d2a0(unsigned int);
struct C_00b8de30 { int FUN_00b8de30(); };
struct C_00ba9370 { int FUN_00ba9370(); };
struct C_00c485b0 { void FUN_00c485b0(); };
extern "C" int __cdecl FUN_00feb9f0(...);
struct C_00fec590 { int FUN_00fec590(unsigned int, unsigned int, unsigned int, unsigned int); };

// @ 0x01012910
extern "C" int __stdcall FUN_01012910(int a4, int a8)
{
    int t1001;
    int t1006;
    int t1007;
    int t1008;
    int t1011;
    int t1012;
    int t1015;
    int t1018;
    int t1019;
    int t1022;
    int t1023;
    int t1026;
    int t1027;
    int t1028;
    int t1035;
    int t1039;
    int t1040;
    int t1041;
    int t1044;
    int t1048;
    int t1054;
    int t1058;
    int t1060;
    t1001 = (int)((int)(a4));
    if (t1001 != (int)0) {
        t1006 = (int)FUN_00feb9f0();
        t1007 = (int)(t1001);
        t1008 = (int)(t1006);
        t1011 = (int)((C_00b8de30*)(t1007))->FUN_00b8de30();
        t1012 = (int)(t1011);
        t1015 = (int)((C_00b1fdb0*)(t1012))->FUN_00b1fdb0();
        t1018 = (int)FUN_00b3d2a0((unsigned int)(t1015));
        t1019 = (int)(t1018);
        t1022 = (int)((C_00ba9370*)(t1019))->FUN_00ba9370();
        t1023 = (int)(t1008);
        t1026 = (int)((C_00fec590*)(t1023))->FUN_00fec590((unsigned int)((int)(-1479990119)), (unsigned int)(t1001), (unsigned int)(t1022), (unsigned int)((int)0));
        t1027 = (int)(t1026);
        t1028 = (int)(t1027);
        ((C_00c485b0*)(t1028))->FUN_00c485b0();
        *(int*)&(a4) = (int)(t1027);
        if (t1027 != (int)0) {
            t1035 = (int)(t1027);
            ((il2c_vc0*)(t1035))->s0();
        }
        t1039 = (int)((int)(a8));
        t1040 = (int)(*(int*)((char*)(t1039) + 4));
        if ((unsigned int)(t1040) < (unsigned int)*(int*)((char*)(t1039) + 8)) {
            t1041 = (int)(t1040 + (int)4);
            *(int*)((char*)(t1039) + 4) = (int)(t1041);
            if (t1040 == (int)0) goto L101299f;
            *(int*)((char*)(t1040)) = (int)(t1027);
            if (t1027 == (int)0) goto L10129ac;
            t1044 = (int)(t1027);
            ((il2c_vc1*)(t1044))->s0();
            goto L101299f;
        }
        t1048 = (int)((int)&a4);
        ((C_00aea5d0*)(t1039))->FUN_00aea5d0((unsigned int)(t1040), (unsigned int)(t1048));
        t1027 = (int)((int)(a4));
        L101299f:;
        if (t1027 != (int)0) {
            t1054 = (int)(t1027);
            ((il2c_vc2*)(t1054))->s1();
        }
        L10129ac:;
        t1058 = (int)((int)1);
        return (int)(t1058);
    }
    t1060 = (int)((int)0);
    return (int)(t1060);
}
