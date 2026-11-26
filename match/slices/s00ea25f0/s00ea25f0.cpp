// 0x00ea25f0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPAudioCityMusicLoadSave.cpp, match/slices/s00ea1900/s00ea1900.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual int s5(int, int);
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
    virtual int s31(int);
};

extern "C" int __cdecl FUN_0067dd50(...);
struct C_0067dda0 { int FUN_0067dda0(); };
extern "C" int __cdecl FUN_0067dda0(...);
struct C_008105b0 { int FUN_008105b0(unsigned int, unsigned int); };
struct C_00ea2120 { int FUN_00ea2120(unsigned int); };

// @ 0x00ea25f0
extern "C" void __fastcall FUN_00ea25f0(char* self, int edx_unused)
{
    int t1002;
    int t1005;
    int t1008;
    int t1009;
    int t1012;
    int t1013;
    int t1020;
    int t1021;
    int t1024;
    int t1027;
    int t1030;
    int t1031;
    t1002 = (int)((int)(self));
    if ((unsigned char)*(unsigned char*)((char*)(t1002) + 38) == (unsigned char)0) {
        if ((unsigned char)*(unsigned char*)((char*)(t1002) + 37) == (unsigned char)0) goto Lea2664;
    }
    t1005 = (int)((C_0067dda0*)((int)(self)))->FUN_0067dda0();
    if (t1005 != (int)0) {
        t1008 = (int)FUN_0067dda0();
        t1009 = (int)(*(int*)((char*)(t1002) + 48));
        t1012 = (int)(*(int*)((char*)(t1002) + 44));
        t1013 = (int)(t1008);
        t1005 = (int)((il2c_vc0*)(t1013))->s5((int)(t1012), (int)(t1009));
    }
    if ((unsigned char)*(unsigned char*)((char*)(t1002) + 38) != (unsigned char)0) {
        t1005 = (int)FUN_0067dd50();
        if (t1005 != (int)0) {
            t1020 = (int)FUN_0067dd50();
            t1021 = (int)(*(int*)((char*)(t1002) + 40));
            t1024 = (int)(t1020);
            t1005 = (int)((il2c_vc1*)(t1024))->s31((int)(t1021));
        }
    }
    *(unsigned char*)((char*)(t1002) + 38) = (unsigned char)((int)0);
    if ((unsigned char)*(unsigned char*)((char*)(t1002) + 37) != (unsigned char)0) {
        t1027 = (int)(*(int*)((char*)(t1002) + 32));
        t1030 = (int)((C_008105b0*)(t1027))->FUN_008105b0((unsigned int)((int)84030144), (unsigned int)((int)1));
        t1031 = (int)(t1002);
        t1005 = (int)((C_00ea2120*)(t1031))->FUN_00ea2120((unsigned int)(t1030));
    }
    *(unsigned char*)((char*)(t1002) + 37) = (unsigned char)((int)0);
    Lea2664:;
    return;
}
