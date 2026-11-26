// 0x00ed33a0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00ed2600/s00ed2600.cpp, src/game/SPEditors/_at_00ed0000.cpp.

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
};

extern "C" unsigned char g_016c7aa4[];
struct C_00ed1f00 { int FUN_00ed1f00(unsigned int, unsigned int); };
struct C_00ed3120 { int FUN_00ed3120(unsigned int, unsigned int); };
struct C_00f3c7f0 { int FUN_00f3c7f0(unsigned int); };

// @ 0x00ed33a0
extern "C" void __fastcall FUN_00ed33a0(char* self, int edx_unused, int a4)
{
    int t1001;
    int t1005;
    int t1006;
    int t1009;
    int t1010;
    int t1011;
    int t1012;
    int t1015;
    int t1021;
    int t1022;
    t1001 = (int)((int)(a4));
    t1005 = (int)((int)(self));
    t1006 = (int)(t1005 + (int)112);
    t1009 = (int)((C_00ed1f00*)((int)(self)))->FUN_00ed1f00((unsigned int)(t1006), (unsigned int)(t1001));
    t1010 = (int)(t1009);
    if (t1001 != (int)(-2)) {
        if (t1010 != (int)0) {
            t1011 = (int)((int)(*(int*)g_016c7aa4));
            t1012 = (int)(*(int*)((char*)(t1011) + 116));
            t1009 = (int)((C_00f3c7f0*)(t1012))->FUN_00f3c7f0((unsigned int)(t1001));
            if (t1009 == (int)0) {
                t1015 = (int)(*(int*)((char*)(t1010)));
                ((il2c_vc0*)(t1015))->s8();
                t1021 = (int)(*(int*)((char*)(t1010) + 4));
                t1022 = (int)(t1005);
                t1009 = (int)((C_00ed3120*)(t1022))->FUN_00ed3120((unsigned int)(t1021), (unsigned int)((int)1));
            }
        }
    }
    return;
}
