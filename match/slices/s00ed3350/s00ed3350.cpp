// 0x00ed3350: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEditors/_at_00ed0000.cpp, match/slices/s00ed2600/s00ed2600.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7(int);
};

struct C_00ed1f00 { int FUN_00ed1f00(unsigned int, unsigned int); };
struct C_00ed1f40 { int FUN_00ed1f40(unsigned int); };
struct C_00ed3120 { int FUN_00ed3120(unsigned int, unsigned int); };

// @ 0x00ed3350
extern "C" void __fastcall FUN_00ed3350(char* self, int edx_unused, int a4)
{
    int t1001;
    int t1004;
    int t1006;
    int t1009;
    int t1010;
    int t1013;
    int t1014;
    int t1020;
    int t1021;
    t1001 = (int)((int)(a4));
    t1004 = (int)((int)(self));
    if (t1001 != (int)(-2)) {
        t1006 = (int)(t1004 + (int)112);
        t1009 = (int)((C_00ed1f00*)((int)(self)))->FUN_00ed1f00((unsigned int)(t1006), (unsigned int)(t1001));
        if (t1009 == (int)0) {
            t1010 = (int)(t1004);
            t1009 = (int)((C_00ed1f40*)(t1010))->FUN_00ed1f40((unsigned int)(t1006));
            t1013 = (int)(t1009);
            if (t1013 != (int)0) {
                t1014 = (int)(*(int*)((char*)(t1013)));
                ((il2c_vc0*)(t1014))->s7((int)(t1001));
                t1020 = (int)(*(int*)((char*)(t1013) + 4));
                t1021 = (int)(t1004);
                t1009 = (int)((C_00ed3120*)(t1021))->FUN_00ed3120((unsigned int)(t1020), (unsigned int)((int)1));
            }
        }
    }
    return;
}
