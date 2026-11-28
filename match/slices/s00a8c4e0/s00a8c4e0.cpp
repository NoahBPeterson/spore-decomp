// 0x00a8c4e0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/synth/vec_erase_vcall_dtor.cpp, src/game/Swarm/DistributeEffect.cpp, match/slices/s00a8b940/s00a8b940.cpp.

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
};

extern "C" int __cdecl FUN_00a882a0(...);

// @ 0x00a8c4e0
// @ 0x00a8c4e0
extern "C" int __fastcall FUN_00a8c4e0(char* self, int edx_unused, int a4, int a8)
{
    int t1001;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1012;
    int t1013;
    int t1014;
    int t1020;
    int t1021;
    int t1022;
    int t1023;
    int t1024;
    int t1025;
    t1001 = (int)((int)(a8));
    t1006 = (int)((int)(self));
    t1007 = (int)((int)(a4));
    t1008 = (int)(*(int*)((char*)(t1006) + 4));
    t1009 = (int)FUN_00a882a0((unsigned int)(t1001), (unsigned int)(t1008), (unsigned int)(t1007));
    t1012 = (int)(*(int*)((char*)(t1006) + 4));
    t1013 = (int)(t1009);
    if ((unsigned int)(t1009) < (unsigned int)(t1012)) {
        do {
            t1014 = (int)(*(int*)((char*)(t1013)));
            if (t1014 != (int)0) {
                ((il2c_vc0*)(t1014))->s14();
            }
            t1013 = (int)(t1013 + (int)4);
        } while ((unsigned int)(t1013) < (unsigned int)(t1012));
    }
    t1020 = (int)((int)(a4));
    t1021 = (int)(t1001 - t1020);
    t1022 = (int)(t1021 >> (int)2);
    t1023 = (int)(-t1022);
    t1024 = (int)(t1023 + t1023);
    t1025 = (int)(t1024 + t1024);
    *(int*)((char*)(t1006) + 4) += t1025;
    return (int)(t1020);
}
