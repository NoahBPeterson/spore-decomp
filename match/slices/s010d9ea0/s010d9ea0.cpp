// 0x010d9ea0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/Havok/_at_010d0000.cpp, match/slices/s010d9470/s010d9470.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual int s4(int, int);
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual int s4(int, int);
};

extern "C" unsigned char g_014a48f8[];
extern "C" unsigned char g_016e4178[];
struct C_010ec660 { void FUN_010ec660(unsigned int, unsigned int, unsigned int); };
struct C_010ed2a0 { int FUN_010ed2a0(unsigned int, unsigned int, unsigned int); };

// @ 0x010d9ea0
extern "C" int __cdecl FUN_010d9ea0(int a4, int a8, int a12, int a16)
{
    int t1000;
    int t1003;
    int t1005;
    int t1008;
    int t1009;
    int t1010;
    int t1011;
    int t1015;
    int t1018;
    int t1021;
    int t1022;
    int t1023;
    int t1024;
    t1000 = (int)((int)(*(int*)g_016e4178));
    t1003 = (int)((int)(a16));
    if (t1003 != (int)0) {
        t1005 = (int)((il2c_vc0*)(t1000))->s4((int)((int)128), (int)((int)28));
        t1008 = (int)((int)(a8));
        t1009 = (int)((int)(a4));
        t1010 = (int)(t1005);
        t1011 = (int)(t1010);
        *(unsigned short*)((char*)(t1010) + 4) = (unsigned short)((int)128);
        ((C_010ec660*)(t1011))->FUN_010ec660((unsigned int)(t1009), (unsigned int)(t1008), (unsigned int)(t1003));
        *(int*)((char*)(t1010)) = (int)((int)g_014a48f8);
        t1015 = (int)(t1010);
        return (int)(t1015);
    }
    t1018 = (int)((il2c_vc1*)(t1000))->s4((int)((int)48), (int)((int)28));
    t1021 = (int)((int)(a8));
    t1022 = (int)((int)(a4));
    t1023 = (int)(t1018);
    *(unsigned short*)((char*)(t1018) + 4) = (unsigned short)((int)48);
    t1024 = (int)((C_010ed2a0*)(t1023))->FUN_010ed2a0((unsigned int)(t1022), (unsigned int)(t1021), (unsigned int)((int)0));
    return (int)(t1024);
}
