// 0x0104e7b0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPToolManager.cpp, match/slices/s0104e060/s0104e060.cpp.

struct il2c_vc0 {
    virtual void s0();
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
    virtual void s45();
    virtual void s46();
    virtual void s47();
};

extern "C" unsigned char g_013ebb38[];
extern "C" unsigned char g_013f09b4[];
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x0104e7b0
// @ 0x0104e7b0
extern "C" int __stdcall FUN_0104e7b0(int a4)
{
    int t1003;
    int t1006;
    int t1007;
    int t1009;
    int t1010;
    int t1016;
    t1003 = (int)FUN_00f473a0((unsigned int)((int)24), (unsigned int)((int)g_013f09b4), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)g_013ebb38), (unsigned int)((int)209));
    t1006 = (int)(t1003);
    t1007 = (int)(t1006 + (int)16);
    if (t1007 != (int)0) {
        t1009 = (int)((int)(a4));
        t1010 = (int)(*(int*)((char*)(t1009)));
        *(int*)((char*)(t1007)) = (int)(t1010);
        if (t1010 != (int)0) {
            ((il2c_vc0*)(t1010))->s0();
        }
        t1016 = (int)(*(int*)((char*)(t1009) + 4));
        *(int*)((char*)(t1007) + 4) = (int)(t1016);
        if (t1016 != (int)0) {
            ((il2c_vc1*)(t1016))->s47();
        }
        t1003 = (int)(t1006);
    }
    return (int)(t1003);
}
