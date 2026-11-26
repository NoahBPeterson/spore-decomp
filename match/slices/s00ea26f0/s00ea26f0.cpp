// 0x00ea26f0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00ea1900/s00ea1900.cpp, src/game/SPGonzago/SPAudioCityMusicLoadSave.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
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
    virtual void s11(int, int, int);
};
struct il2c_vc2 {
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
    virtual void s11(int, int, int);
};

struct C_00401030 { int FUN_00401030(); };
extern "C" int __cdecl FUN_00401030(...);
struct C_0064ab20 { void FUN_0064ab20(); };
extern "C" int __cdecl FUN_0067dcc0(...);
struct C_00811ad0 { int FUN_00811ad0(unsigned int); };
struct C_00ea25f0 { void FUN_00ea25f0(); };
struct C_00ea4b40 { void FUN_00ea4b40(); };

// @ 0x00ea26f0
extern "C" void __fastcall FUN_00ea26f0(char* self, int edx_unused)
{
    int t1002;
    int t1006;
    int t1009;
    int t1010;
    int t1014;
    int t1018;
    int t1024;
    int t1027;
    int t1029;
    int t1036;
    int t1038;
    int t1043;
    int t1047;
    int t1051;
    t1002 = (int)((int)(self));
    if ((unsigned char)*(unsigned char*)((char*)(t1002) + 36) != (unsigned char)0) {
        t1006 = (int)((C_00401030*)((int)(self)))->FUN_00401030();
        if (t1006 != (int)0) {
            t1009 = (int)FUN_00401030();
            t1010 = (int)(t1009);
            ((C_0064ab20*)(t1010))->FUN_0064ab20();
        }
    }
    t1014 = (int)(t1002);
    *(unsigned char*)((char*)(t1002) + 36) = (unsigned char)((int)0);
    ((C_00ea25f0*)(t1014))->FUN_00ea25f0();
    t1018 = (int)(*(int*)((char*)(t1002) + 20));
    if (t1018 != (int)0) {
        *(int*)((char*)(t1002) + 20) = (int)((int)0);
        ((il2c_vc0*)(t1018))->s1();
    }
    t1024 = (int)(t1002 + (int)16);
    t1027 = (int)FUN_0067dcc0();
    t1029 = (int)(t1027);
    ((il2c_vc1*)(t1029))->s11((int)(t1024), (int)((int)84625161), (int)((int)(-9999)));
    t1036 = (int)FUN_0067dcc0();
    t1038 = (int)(t1036);
    ((il2c_vc2*)(t1038))->s11((int)(t1024), (int)((int)85140361), (int)((int)(-9999)));
    t1043 = (int)(*(int*)((char*)(t1002) + 24));
    ((C_00ea4b40*)(t1043))->FUN_00ea4b40();
    t1047 = (int)(*(int*)((char*)(t1002) + 28));
    ((C_00811ad0*)(t1047))->FUN_00811ad0((unsigned int)((int)1));
    t1051 = (int)(*(int*)((char*)(t1002) + 32));
    ((C_00811ad0*)(t1051))->FUN_00811ad0((unsigned int)((int)1));
    return;
}
