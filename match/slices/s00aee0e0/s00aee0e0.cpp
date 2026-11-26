// 0x00aee0e0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00aed700/s00aed700.cpp, src/game/SPGonzago/SPAnimalBehaviorTrees.cpp.

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
    virtual int s17(int, int, int);
};

extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
#pragma intrinsic(_InterlockedExchange)
extern "C" unsigned char g_013ebc58[];
extern "C" unsigned char g_013effa8[];
extern "C" unsigned char g_0145c0e4[];
extern "C" unsigned char g_0186ca75[];
extern "C" int __cdecl FUN_0067dcd0(...);
extern "C" int __cdecl FUN_00926020(...);

// @ 0x00aee0e0
extern "C" void __cdecl FUN_00aee0e0(void)
{
    int t1002;
    int t1006;
    int t1007;
    int t1008;
    int t1010;
    int t1013;
    int t1015;
    t1002 = (int)((int)0);
    t1006 = (int)FUN_00926020((unsigned int)((int)44), (unsigned int)((int)g_013ebc58), (unsigned int)(t1002), (unsigned int)(t1002), (unsigned int)(t1002), (unsigned int)(t1002));
    if (t1006 != t1002) {
        *(int*)((char*)(t1006)) = (int)((int)g_013effa8);
        t1007 = (int)((int)0);
        t1008 = (int)(t1006 + (int)4);
        _InterlockedExchange((long volatile*)(t1008), (long)(t1007));
        *(int*)((char*)(t1006)) = (int)((int)g_0145c0e4);
        *(int*)((char*)(t1006) + 8) = (int)(t1002);
        *(int*)((char*)(t1006) + 12) = (int)((int)g_0186ca75);
        *(int*)((char*)(t1006) + 16) = (int)(t1002);
        *(int*)((char*)(t1006) + 20) = (int)(t1002);
        *(int*)((char*)(t1006) + 24) = (int)(t1002);
        *(int*)((char*)(t1006) + 32) = (int)(t1002);
        *(int*)((char*)(t1006) + 36) = (int)(t1002);
        *(int*)((char*)(t1006) + 40) = (int)(t1002);
        t1010 = (int)(t1006);
    } else {
        t1010 = (int)((int)0);
    }
    t1013 = (int)FUN_0067dcd0();
    t1015 = (int)(t1013);
    ((il2c_vc0*)(t1015))->s17((int)((int)1), (int)(t1010), (int)(t1002));
    return;
}
