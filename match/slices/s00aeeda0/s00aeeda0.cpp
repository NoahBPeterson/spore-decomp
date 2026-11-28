// 0x00aeeda0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00aee680/s00aee680.cpp, src/game/SPGonzago/SPAnimalBehaviorTrees.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3(int, int, int, int, int, int);
};
struct il2c_vc1 {
    virtual void s0();
    virtual int s1();
};
struct il2c_vc2 {
    virtual void s0();
    virtual int s1();
};

extern "C" int __cdecl FUN_0067dcd0(...);
struct C_00684610 { int FUN_00684610(unsigned int); };
struct C_00e39fb0 { int FUN_00e39fb0(unsigned int, unsigned int); };

// @ 0x00aeeda0
extern "C" bool __stdcall FUN_00aeeda0(int a4, int a8)
{
    int t1000;
    int v_l16;
    int v_l12[3];
    int t1004;
    int t1009;
    int t1010;
    int t1011;
    int t1015;
    int t1016;
    int t1017;
    int t1018;
    int t1019;
    int t1020;
    int t1023;
    int t1026;
    bool t1030;
    int t1033;
    int t1034;
    int t1035;
    int t1038;
    bool t1039;
    bool t1044;
    t1000 = (int)((int)(a4));
    v_l16 = (int)((int)0);
    (*(int*)&v_l12[1]) = (int)((int)89840164);
    (*(int*)&v_l12[2]) = (int)((int)89840163);
    (*(int*)&v_l12[0]) = (int)(t1000);
    t1004 = (int)FUN_0067dcd0();
    t1009 = (int)((int)&v_l16);
    t1010 = (int)((int)&v_l12);
    t1011 = (int)(t1004);
    ((il2c_vc0*)(t1011))->s3((int)(t1010), (int)(t1009), (int)((int)0), (int)((int)0), (int)((int)0), (int)((int)0));
    t1015 = (int)(v_l16);
    t1016 = (int)((int)&a8);
    t1017 = (int)((int)&a4);
    t1018 = (int)(t1015 + (int)24);
    t1019 = (int)(t1018);
    t1020 = (int)((C_00e39fb0*)(t1019))->FUN_00e39fb0((unsigned int)(t1017), (unsigned int)(t1016));
    t1023 = (int)(t1015 + (int)28);
    if ((int)*(int*)((char*)(t1020)) == t1023) {
        if (t1015 != (int)0) {
            t1026 = (int)(t1015);
            t1020 = (int)((il2c_vc1*)(t1026))->s1();
        }
        t1030 = false;
        return (bool)(t1030);
    }
    t1033 = (int)((int)&a8);
    t1034 = (int)(t1018);
    t1035 = (int)((C_00684610*)(t1034))->FUN_00684610((unsigned int)(t1033));
    t1038 = (int)(v_l16);
    t1039 = *(bool*)((char*)(t1035) + 20);
    if (t1038 != (int)0) {
        t1035 = (int)((il2c_vc2*)(t1038))->s1();
    }
    t1044 = t1039;
    return t1044;
}
