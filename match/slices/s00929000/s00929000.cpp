// 0x00929000: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00928b00/s00928b00.cpp.

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
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
};

struct C_00928f00 { void FUN_00928f00(unsigned int, unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00931fd0(...);

// @ 0x00929000
extern "C" bool __fastcall FUN_00929000(char* self, int edx_unused)
{
    int t1002;
    int t1003;
    int t1005;
    int t1006;
    int t1007;
    unsigned char t1;
    bool t1009;
    bool t1012;
    int t1014;
    int t1020;
    int t1021;
    int t1027;
    int t1028;
    int t1034;
    int t1035;
    int v_l520[130];
    int t1036;
    int t1040;
    bool t1045;
    t1002 = (int)((int)(self));
    t1003 = (int)(*(int*)((char*)(t1002) + 4));
    t1005 = (int)(t1003);
    t1006 = (int)(t1005 - (int)*(int*)((char*)(t1002)));
    t1007 = (int)(t1006 >> (int)2);
    t1 = (unsigned char)((unsigned char)*(unsigned char*)((char*)(t1002) + 1076) & (unsigned char)2);
    if (t1 == (unsigned char)0) {
        *(int*)((char*)(t1002) + 1092) = (int)((int)(-807534586));
        t1009 = false;
        return (bool)(t1009);
    }
    if ((unsigned int)(t1007) <= (unsigned int)1) {
        *(int*)((char*)(t1002) + 1092) = (int)((int)(-807534579));
        t1012 = false;
        return (bool)(t1012);
    }
    t1014 = (int)(*(int*)((char*)(t1003) - 4));
    ((il2c_vc0*)(t1014))->s13();
    t1020 = (int)(*(int*)((char*)(t1002) + 4));
    t1021 = (int)(*(int*)((char*)(t1020) - 4));
    ((il2c_vc1*)(t1021))->s6();
    t1027 = (int)(*(int*)((char*)(t1002) + 4));
    t1028 = (int)(*(int*)((char*)(t1027) - 4));
    ((il2c_vc2*)(t1028))->s2();
    *(int*)((char*)(t1002) + 4) += (int)(-4);
    t1034 = (int)(t1007 - (int)1);
    t1035 = (int)((int)&v_l520);
    t1036 = (int)(t1002);
    ((C_00928f00*)(t1036))->FUN_00928f00((unsigned int)(t1035), (unsigned int)((int)260), (unsigned int)(t1034));
    t1040 = (int)((int)&v_l520);
    FUN_00931fd0((unsigned int)(t1040));
    t1045 = true;
    return (bool)(t1045);
}
