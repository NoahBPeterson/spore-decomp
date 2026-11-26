// 0x00daab90: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPTribeBehaviorTrees.cpp, match/slices/s00daa530/s00daa530.cpp.

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
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual void s29();
    virtual void s30();
    virtual void s31();
    virtual void s32();
    virtual void s33();
    virtual void s34();
    virtual void s35();
    virtual void s36();
    virtual void s37();
    virtual void s38();
    virtual void s39();
    virtual void s40();
    virtual void s41();
    virtual void s42();
    virtual void s43();
    virtual void s44();
    virtual int s45(int);
};

extern "C" unsigned char g_015d1164[];
struct C_00bca2c0 { int FUN_00bca2c0(); };

// @ 0x00daab90
extern "C" float __cdecl FUN_00daab90(int a4)
{
    int t1001;
    int t1002;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    unsigned char t6;
    int t1009;
    int t1012;
    int t1015;
    t1001 = (int)((int)(a4));
    t1002 = (int)(*(int*)((char*)(t1001) + 2892));
    t1005 = (int)((C_00bca2c0*)(t1002))->FUN_00bca2c0();
    if (t1005 != (int)0) {
        if ((int)*(int*)((char*)(t1005)) == (int)22) {
            t1006 = (int)(t1005 + (int)57);
            t1007 = (int)(*(unsigned short*)((char*)(t1006) + 18));
            if ((unsigned short)(t1007) != (unsigned short)10) {
                if ((unsigned short)(t1007) != (unsigned short)16) {
                    t1008 = (int)((int)g_015d1164);
                    goto Ldaabd6;
                }
            }
            t6 = (unsigned char)((unsigned char)*(unsigned char*)((char*)(t1006) + 16) & (unsigned char)48);
            if (t6 != (unsigned char)0) {
                t1008 = (int)(*(int*)((char*)(t1006)));
                goto Ldaabd6;
            }
            t1009 = (int)((unsigned short)(t1007));
            t1008 = (int)(((int)(t1009) != (int)((int)0)) ? (int)(t1006) : (int)((int)0));
            Ldaabd6:;
            t1012 = (int)(*(int*)((char*)(t1008)));
            t1015 = (int)(t1001);
            t1005 = (int)((il2c_vc0*)(t1015))->s45((int)(t1012));
            if (t1005 != (int)0) {
                if ((int)*(int*)((char*)(t1005) + 8) == (int)55) {
                    return (float)((float)1);
                }
            }
        }
    }
    return (float)((float)0);
}
