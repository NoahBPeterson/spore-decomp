// 0x00ea2670: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPAudioCityMusicLoadSave.cpp, match/slices/s00ea1900/s00ea1900.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual int s7();
};

extern "C" int __stdcall FUN_00675250(unsigned int, unsigned int);
struct C_00676e90 { int FUN_00676e90(); };
struct C_008105b0 { int FUN_008105b0(unsigned int, unsigned int); };
struct C_00ea2120 { void FUN_00ea2120(unsigned int); };
struct C_00ea23e0 { void FUN_00ea23e0(); };
struct C_00ea25f0 { int FUN_00ea25f0(); };

// @ 0x00ea2670
// @ 0x00ea2670
extern "C" bool __fastcall FUN_00ea2670(char* self, int edx_unused, int a4, int a8)
{
    int t1000;
    bool t1002;
    int t1005;
    int t1006;
    int t1009;
    bool t1015;
    int t1017;
    int t1018;
    int t1019;
    int t1022;
    int t1026;
    int t1030;
    int t1033;
    bool t1038;
    int t1040;
    bool t1044;
    t1000 = (int)((int)(a8));
    t1002 = ((int)(*(int*)((char*)(t1000) + 8)) == (int)((int)23));
    t1005 = (int)((int)(self));
    if (t1002 != (unsigned char)0) {
        t1006 = (int)(*(int*)((char*)(t1000)));
        t1009 = (int)((il2c_vc0*)(t1006))->s7();
        switch ((unsigned int)(t1009)) { case 84027824: goto Lea26da; case 84027832: goto Lea269f; default: goto Lea2698; }
        goto Lea2698;
        goto Lea269f;
        goto Lea26da;
        Lea2698:;
        t1015 = false;
        return (bool)(t1015);
        Lea269f:;
        t1017 = (int)(*(int*)((char*)(t1005) + 20));
        t1018 = (int)(t1005 + (int)(-12));
        t1019 = (int)((C_008105b0*)(t1017))->FUN_008105b0((unsigned int)((int)84030144), (unsigned int)((int)1));
        t1022 = (int)(t1018);
        ((C_00ea2120*)(t1022))->FUN_00ea2120((unsigned int)(t1019));
        t1026 = (int)(t1018);
        ((C_00ea23e0*)(t1026))->FUN_00ea23e0();
        t1030 = (int)FUN_00675250((unsigned int)((int)530338478), (unsigned int)((int)1));
        t1033 = (int)(t1030);
        ((C_00676e90*)(t1033))->FUN_00676e90();
        t1038 = t1002;
        return t1038;
        Lea26da:;
        t1040 = (int)(t1005 + (int)(-12));
        t1000 = (int)((C_00ea25f0*)(t1040))->FUN_00ea25f0();
    }
    t1044 = t1002;
    return t1044;
}
