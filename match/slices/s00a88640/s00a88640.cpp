// 0x00a88640: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00a87fb0/s00a87fb0.cpp, src/game/Swarm/DistributeEffect.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7(int, int, int);
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
    virtual void s8(int, int, int);
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual int s9(int, int);
};


// @ 0x00a88640
extern "C" int __cdecl FUN_00a88640(int a4, int a8)
{
    int t1001;
    int t1003;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1012;
    int t1013;
    int t2;
    int t1014;
    int t1015;
    int t1019;
    int t1020;
    int t1021;
    int t1022;
    int t1025;
    int t1026;
    int t9;
    int t1027;
    int t1028;
    int t1032;
    int t1033;
    int t1034;
    int t1037;
    t1001 = (int)((int)(a8));
    t1003 = (int)((int)(a4));
    t1006 = (int)((int)0);
    t1007 = (int)(t1003 + (int)2);
    do {
        t1008 = (int)(*(unsigned short*)((char*)(t1007)));
        if ((unsigned short)(t1008) > (unsigned short)0) {
            t1009 = (int)(*(unsigned short*)((char*)(t1007) - 2));
            t1012 = (int)((unsigned short)(t1008));
            t1013 = (int)(*(int*)((char*)(t1003) + 100));
            t2 = (int)(t1009 << (int)2);
            t1014 = (int)(t1013 + t2);
            t1015 = (int)(t1001);
            ((il2c_vc0*)(t1015))->s7((int)(t1006), (int)(t1014), (int)(t1012));
        }
        t1006 = (int)(t1006 + (int)1);
        t1007 = (int)(t1007 + (int)4);
    } while (t1006 < (int)25);
    t1019 = (int)((int)0);
    t1020 = (int)(t1003 + (int)122);
    do {
        t1021 = (int)(*(unsigned short*)((char*)(t1020)));
        if ((unsigned short)(t1021) > (unsigned short)0) {
            t1022 = (int)(*(unsigned short*)((char*)(t1020) - 2));
            t1025 = (int)((unsigned short)(t1021));
            t1026 = (int)(*(int*)((char*)(t1003) + 160));
            t9 = (int)(t1022 << (int)2);
            t1027 = (int)(t1026 + t9);
            t1028 = (int)(t1001);
            ((il2c_vc1*)(t1028))->s8((int)(t1019), (int)(t1027), (int)(t1025));
        }
        t1019 = (int)(t1019 + (int)1);
        t1020 = (int)(t1020 + (int)4);
    } while (t1019 < (int)10);
    t1032 = (int)((int)0);
    t1033 = (int)(t1003 + (int)180);
    do {
        t1034 = (int)(*(int*)((char*)(t1033)));
        if (t1034 != (int)0) {
            t1037 = (int)(t1001);
            t1034 = (int)((il2c_vc2*)(t1037))->s9((int)(t1032), (int)(t1034));
        }
        t1032 = (int)(t1032 + (int)1);
        t1033 = (int)(t1033 + (int)4);
    } while (t1032 < (int)9);
    return (int)(t1034);
}
