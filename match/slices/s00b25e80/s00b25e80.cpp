// 0x00b25e80: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00b25c30/s00b25c30.cpp, src/game/SPGonzago/SPGameNounManager.cpp.

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
    virtual int s9(int, int);
};

extern "C" unsigned char g_0145f82c[];
extern "C" int __cdecl FUN_00883860(...);
struct C_00b215a0 { void FUN_00b215a0(); };
struct C_00b25cd0 { void FUN_00b25cd0(); };

// @ 0x00b25e80
extern "C" void __fastcall FUN_00b25e80(char* self, int edx_unused)
{
    int t1003;
    int t1004;
    int t1006;
    int t1010;
    int t1016;
    int t1017;
    int t1018;
    int t1019;
    int t1022;
    t1003 = (int)((int)(self));
    t1004 = (int)(t1003 + (int)(-4));
    t1006 = (int)(t1004);
    ((C_00b25cd0*)(t1006))->FUN_00b25cd0();
    t1010 = (int)(t1004);
    ((C_00b215a0*)(t1010))->FUN_00b215a0();
    t1016 = (int)FUN_00883860();
    t1017 = (int)(t1016);
    *(int*)((char*)(t1003) + 60) = (int)(t1017);
    *(int*)((char*)(t1003) + 64) = (int)(t1004);
    *(int*)((char*)(t1003) + 68) = (int)((int)g_0145f82c);
    *(int*)((char*)(t1003) + 72) = (int)((int)3);
    *(int*)((char*)(t1003) + 76) = (int)((int)0);
    if (t1017 != (int)0) {
        if (t1004 != (int)0) {
            t1018 = (int)((int)0);
            do {
                t1019 = (int)(*(int*)((char*)(t1018) + (int)g_0145f82c));
                t1022 = (int)(t1017);
                t1016 = (int)((il2c_vc0*)(t1022))->s9((int)(t1004), (int)(t1019));
                t1018 = (int)(t1018 + (int)4);
            } while ((unsigned int)(t1018) < (unsigned int)12);
        }
    }
    return;
}
