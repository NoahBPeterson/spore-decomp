// 0x005f4f80: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEditors/SPSwatchStrategies.cpp, match/slices/s005f4310/s005f4310.cpp.

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
    virtual int s9(int);
};

struct C_005f3b20 { void FUN_005f3b20(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int); };

// @ 0x005f4f80
extern "C" int __fastcall FUN_005f4f80(char* self, int edx_unused, int a4, int a8, int a12, int a16, int a20, int a24, int a28)
{
    int t1000;
    int t1003;
    int t1004;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1010;
    int t1011;
    int t1012;
    int t1016;
    int t1017;
    int t1020;
    t1000 = (int)((int)(a8));
    t1003 = (int)((int)(self));
    if (t1000 != (int)0) {
        t1004 = (int)((int)(a28));
        t1006 = (int)((int)(a4));
        *(int*)((char*)(t1003) + 88) = (int)(t1004);
        *(unsigned char*)&(a8) = (unsigned char)((int)1);
        if ((int)*(int*)((char*)(t1006) + 4) == (int)1033349348) {
            *(unsigned char*)&(a8) = (unsigned char)((int)0);
        }
        t1007 = (int)((int)(a8));
        t1008 = (int)((int)(a24));
        t1009 = (int)((int)(a20));
        t1010 = (int)((int)(a16));
        t1011 = (int)((int)(a12));
        t1012 = (int)(t1003);
        ((C_005f3b20*)(t1012))->FUN_005f3b20((unsigned int)(t1000), (unsigned int)(t1000), (unsigned int)((int)1), (unsigned int)(t1011), (unsigned int)(t1010), (unsigned int)(t1009), (unsigned int)(t1008), (unsigned int)(t1007));
        t1000 = (int)(*(int*)((char*)(t1006)));
        *(int*)((char*)(t1003) + 64) = (int)(t1000);
        t1016 = (int)(*(int*)((char*)(t1006) + 4));
        *(int*)((char*)(t1003) + 68) = (int)(t1016);
        t1017 = (int)(*(int*)((char*)(t1006) + 8));
        *(int*)((char*)(t1003) + 72) = (int)(t1017);
        if ((int)*(int*)((char*)(t1006)) != (int)0) {
            t1020 = (int)(t1003);
            t1000 = (int)((il2c_vc0*)(t1020))->s9((int)(t1006));
        }
    }
    return (int)(t1000);
}
